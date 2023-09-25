#include <stdio.h>
#include <stdlib.h>
#include "cliente.h"

void main(int argc, char** argv) {

    FILE *arquivo;

    // Abrir o arquivo no modo "r+b" para escrita e leitura binária
    arquivo = fopen("clientes.dat", "wb");


    if (arquivo == NULL) {
        printf("Não foi possível abrir o arquivo.\n");
        return 1;
    }

    // Escrever dados no arquivo
    criarCliente(arquivo);

 
    // Fechar o arquivo
    fclose(arquivo);

    // Abre o arquivo para leitura binária
    arquivo = fopen("clientes.dat", "rb");

    if (arquivo == NULL) {
        printf("Não foi possível abrir o arquivo novamente.\n");
        return 1;
    }

    // Ler e imprimir os clientes do arquivo
    Cliente *clienteLido;

    while ((clienteLido = le(arquivo)) != NULL) {
        printf("Codigo do Cliente: %d\n", clienteLido->codCliente);
        printf("Nome do Cliente: %s\n", clienteLido->nome);
        free(clienteLido); // Liberar memória alocada para cada cliente
       
    }

    // Fechar o arquivo novamente
    fclose(arquivo);

    return 0;


}