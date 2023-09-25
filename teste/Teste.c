#include <stdio.h>
#include <stdlib.h>
void main(int argc, char** argv) {

    FILE *arquivo; // Declaração de um ponteiro de arquivo

    // Para criar um arquivo, usamos a função fopen com o modo "w" (write)
    arquivo = fopen("exemplo.txt", "w");

    if (arquivo == NULL) {
        printf("Não foi possível criar o arquivo.\n");
        return 1;
    }

    // Escrever no arquivo
    fprintf(arquivo, "Este é um exemplo de arquivo em C.\n");
    fprintf(arquivo, "Você pode escrever várias linhas aqui.\n");

    // Fechar o arquivo
    fclose(arquivo);

    // Abrir o arquivo para leitura
    arquivo = fopen("exemplo.txt", "r");

    if (arquivo == NULL) {
        printf("Não foi possível abrir o arquivo.\n");
        return 1;
    }

    // Ler e imprimir o conteúdo do arquivo
    char linha[100];
    while (fgets(linha, sizeof(linha), arquivo)) {
        printf("%s", linha);
    }

    // Fechar o arquivo novamente
    fclose(arquivo);

   return 0;
}