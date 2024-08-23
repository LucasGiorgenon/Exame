#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <float.h>  // Adicione isto para DBL_MAX
#include <windows.h> // Adicione isto para Sleep()

#define MAX_PILOTOS 18 // Valor fictício 
#define MAX_VOLTAS 4   // Valor que define o vencedor da prova

// Struct para adicionar as variáveis referente a cada piloto
typedef struct {
    char codigo[10], nome[50];
    int voltas_completadas;
    double melhor_volta;
    double velocidade_media;
    double tempo_total; // Corrigido o tipo da variável
} Piloto;

// Define modelo de cabeçalho do log
typedef struct {
    char hora[20];
    char codigo[10];
    int numero_volta;
    double tempo_volta;
    double velocidade_media_volta;
} LogEntry;
// Foi realizada a criação de duas structs visando futuras ampliações de software, facilitando aumentar as variáveis por piloto, porém sem
// necessariamente alterar o cabeçalho.

Piloto pilotos[MAX_PILOTOS];
int piloto_count = 0;

LogEntry logs[MAX_VOLTAS * MAX_PILOTOS];
int log_count = 0;

void adicionar_piloto(const char* codigo, const char* nome) {
    // Função realiza inserção dos pilotos até o último piloto inserido
    for (int i = 0; i < piloto_count; i++) {
        if (strcmp(pilotos[i].codigo, codigo) == 0) {
            return;
        }
    }

    strcpy(pilotos[piloto_count].codigo, codigo);
    strcpy(pilotos[piloto_count].nome, nome);
    pilotos[piloto_count].voltas_completadas = 0;
    pilotos[piloto_count].tempo_total = 0.0;
    pilotos[piloto_count].melhor_volta = DBL_MAX; // Usar DBL_MAX corretamente
    pilotos[piloto_count].velocidade_media = 0;
    piloto_count++;
}

int encontrar_piloto_index(const char* codigo) {
    for (int i = 0; i < piloto_count; i++) {
        if (strcmp(pilotos[i].codigo, codigo) == 0) {
            return i;
        }
    }
    return -1; // Piloto não encontrado
}

void processar_log_entry(const char* linha) {
    LogEntry entry;
    sscanf(linha, "%*s %s %d %lf %lf", entry.codigo, &entry.numero_volta, &entry.tempo_volta, &entry.velocidade_media_volta);

    int piloto_index = encontrar_piloto_index(entry.codigo);
    if (piloto_index == -1) {
        return; // Piloto não encontrado
    }

    if (entry.numero_volta > pilotos[piloto_index].voltas_completadas) {
        pilotos[piloto_index].voltas_completadas = entry.numero_volta;
        pilotos[piloto_index].tempo_total += entry.tempo_volta;
    }

    if (entry.tempo_volta < pilotos[piloto_index].melhor_volta) {
        pilotos[piloto_index].melhor_volta = entry.tempo_volta;
    }

    pilotos[piloto_index].velocidade_media = (pilotos[piloto_index].velocidade_media * (entry.numero_volta - 1) + entry.velocidade_media_volta) / entry.numero_volta;
}

/*void ler_arquivo(const char* nome_arquivo) {
    FILE *file = fopen(nome_arquivo, "r");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo");
        exit(EXIT_FAILURE);
    }

    char linha[100];
    while (fgets(linha, sizeof(linha), file)) {
        if (strstr(linha, "Hora") == NULL) {
            processar_log_entry(linha);
        }
    }
    fclose(file);
}
*/

void calcular_resultados() {
    Piloto vencedor;
    for (int i = 0; i < piloto_count; i++) {
        if (pilotos[i].voltas_completadas >= 4) {
            vencedor = pilotos[i];
            break;
        }
    }
    printf("Tempo Total\t Posição Chegada\t Código Piloto\t Nome Piloto\t Voltas Completadas \n");
    for (int i = 0; i < piloto_count; i++) {
        printf("%d\t\t%s\t%s\t%d\t\t%.3lf\n", 
            (pilotos[i].voltas_completadas == 4 && pilotos[i].tempo_total < vencedor.tempo_total) ? 1 : 2,
            pilotos[i].codigo,
            pilotos[i].nome,
            pilotos[i].voltas_completadas,
            pilotos[i].tempo_total);
    }
}

void exibir_melhor() {
    double melhor_volta_corrida = DBL_MAX;
    for (int i = 0; i < piloto_count; i++) {
        if (pilotos[i].melhor_volta < melhor_volta_corrida) {
            melhor_volta_corrida = pilotos[i].melhor_volta;
        }
    }
    printf("Melhor volta da corrida: %.3lf\n", melhor_volta_corrida);
}

int main() {
    //ler_arquivo("log.txt");

    int max_add = 0;
    for (size_t i = 0; i < piloto_count; i++) {
        adicionar_piloto("033", "Exemplo Nome"); // Substitua com os dados corretos
        max_add++;

        if (max_add == MAX_PILOTOS) {
            break;
        }
    }

    calcular_resultados();
    Sleep(100);  // Use Sleep para esperar 100ms no Windows
    exibir_melhor(); 
    
    return 0;
}
