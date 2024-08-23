#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_PILOTOS 18 // Valor ficticio 
#define MAX_VOLTAS 4 //Valor que define o vencedor da prova

//Struct para adicionar as variaveis referente a cada piloto
typedef struct {
    char codigo[10], nome[50], tempo_total;
    int voltas_completadas;
    double melhor_volta;
    double velocidade_media;
} Piloto;
//Deine modelo de cabecalho do log
typedef struct {
    char hora[20];
    char codigo[10];
    int numero_volta;
    double tempo_volta;
    double velocidade_media_volta;
} LogEntry;

// Foi realizado a criacao de duas structs visando futuras ampliacoes de software, facilitando aumentar as variaveis por piloto porem sem 
// necessariamente alterar o cabecalho.

Piloto pilotos[MAX_PILOTOS];
int piloto_count = 0;

LogEntry logs[MAX_VOLTAS * MAX_PILOTOS];
int log_count = 0;

void adicionar_piloto(const char* codigo, const char* nome) {
    //Funcao realiza insercao dos pilotos ate o ultimo piloto inserido
    for (int i = 0; i < piloto_count; i++) {
        if (strcmp(pilotos[i].codigo, codigo) == 0) {
            return;
        }
    }

    strcpy(pilotos[piloto_count].codigo, codigo);   //Copia as variaveis lidas para as variaveis locais existentes por meio do srcpy
    strcpy(pilotos[piloto_count].nome, nome);       //Copia as variaveis lidas para as variaveis locais existentes por meio do srcpy
    pilotos[piloto_count].voltas_completadas = 0;
    pilotos[piloto_count].tempo_total = 0;
    pilotos[piloto_count].melhor_volta = _DBL_MAX_;
    pilotos[piloto_count].velocidade_media = 0;
    piloto_count++;
}

/*

Caso seja necessario tambem e possivel procurar piloto por piloto para verificar se ele participou da corrida

*/
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

    // Acumular dados para cálculo da velocidade média
    pilotos[piloto_index].velocidade_media = (pilotos[piloto_index].velocidade_media * (entry.numero_volta - 1) + entry.velocidade_media_volta) / entry.numero_volta;
}

void ler_arquivo(const char* nome_arquivo) {
//Realizando leitura de um arquivo consierando que o log seja feito em .txt

    FILE *file = fopen(nome_arquivo, "log_corrida.txt");
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

void calcular_resultados() {
    // Encontrar o primeiro piloto a completar 4 voltas
    Piloto vencedor;
    for (int i = 0; i < piloto_count; i++) {
        if (pilotos[i].voltas_completadas >= 4) {
            vencedor = pilotos[i];
            break;
        }
    }
    // /t auxilia para que o print seja de forma tabulada, seja dos titulos para cabecalho ou de todas as variaveis utilizadas 
    printf("Posição Chegada\t Código Piloto\t Nome Piloto\t Voltas Completadas\t Tempo Total\n");
    for (int i = 0; i < piloto_count; i++) {
        printf("%d\t\t%s\t%s\t%d\t\t%.3lf\n", 
            (pilotos[i].voltas_completadas == 4 && pilotos[i].tempo_total < vencedor.tempo_total) ? 1 : 2,
            pilotos[i].codigo,
            pilotos[i].nome,
            pilotos[i].voltas_completadas,
            pilotos[i].tempo_total);
    }
}
//faz tratamento das informacoes para verificar a melhor volta da corrida e o piloto que realizou o feito
void exibir_melhor() {
    double melhor_volta_corrida = _DBL_MAX_;
    for (int i = 0; i < piloto_count; i++) {
        if (pilotos[i].melhor_volta < melhor_volta_corrida) {
            melhor_volta_corrida = pilotos[i].melhor_volta;
        }
    }
    
    printf("Melhor volta da corrida: %.3lf\n", melhor_volta_corrida);
}

int main() {

    
/*
    Caso seja de opção atualiar algum piloto de forma manual separada do .txt tambem e possivel

    adicionar_piloto("038", "F.MASSA");
    adicionar_piloto("033", "R.BARRICHELLO");
    adicionar_piloto("002", "K.RAIKKONEN");
    adicionar_piloto("023", "M.WEBBER");
    adicionar_piloto("015", "F.ALONSO");
    adicionar_piloto("011", "S.VETTEL");
    */

    // Lê o log
    ler_arquivo("log.txt");
    
        for (size_t i = 0; i = piloto_count; i++)
    {
        max_add = 0; // Numero pilotos sendo lido no arquivo e adicionado ao programa

        adicionar_piloto();
        max_add i++

        if (max_add == MAX_PILOTOS) // Numero lido deve ser igual ao numero maximo de pilotos da corrida
        {
           return;
        }
    }

    // Calcula e exibe os resultados de maneira tabulada
    calcular_resultados();
    delay(100);
    exibir_melhor(); 
    
    return 0;
}