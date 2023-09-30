#include <stdio.h>
#include <stdlib.h>
#include "cliente.h"
#include "compartimento_hash.h"

int main(int argc, char** argv) {

    for (int i = 0; i < TABLE_SIZE; i++) 
    {
        tabelaHash[i] = NULL;
    }


    FILE *arquivo;

    // Abrir o arquivo no modo "r+b" para escrita e leitura binária
    arquivo = fopen("clientes.dat", "w+b");


    if (arquivo == NULL) 
    {
        arquivo = fopen("clientes.dat", "w+b");
    }

    int i = 0;

    /*while(i<5)
    {
        // Escrever dados no arquivo
        criarCliente(arquivo);
        i++;
    }*/

    // Criar e salvar alguns clientes
    Cliente cliente1 = {49, "Joao"};
    Cliente cliente2 = {51, "Carla"};
    Cliente cliente3 = {59, "Maria"};
    Cliente cliente4 = {3, "Jose"};
    Cliente cliente5 = {87, "Bia"};
    Cliente cliente6 = {103, "Ana"};
    

    Salva(&cliente1, arquivo);
    Salva(&cliente2, arquivo);
    Salva(&cliente3, arquivo);
    Salva(&cliente4, arquivo);
    Salva(&cliente5, arquivo);
    Salva(&cliente6, arquivo);
    
    printf("\n<---------- Dados Inseridos ---------->\n\n");
 
    // Fechar o arquivo
    fclose(arquivo);

    // Abre o arquivo para leitura binária
    arquivo = fopen("clientes.dat", "r+b");

    if (arquivo == NULL) 
    {
        printf("Não foi possível abrir o arquivo novamente.\n\n");
        return 1;
    }

    // Ler e imprimir os clientes do arquivo
    Cliente *clienteLido;

    fseek(arquivo, 0, SEEK_SET);

    while ((clienteLido = le(arquivo)) != NULL)
     {
        long posicao = buscarNaTabela(clienteLido->codCliente);
        printf("Codigo do Cliente: %d\n", clienteLido->codCliente);
        printf("Nome do Cliente: %s\n", clienteLido->nome);
        printf("Posicao no arquivo: %ld\n", posicao);
        free(clienteLido); // Liberar memória alocada para cada cliente
       
    }

    // Fechar o arquivo novamente
    fclose(arquivo);

    // Salvar a tabela hash no arquivo "tabela_hash"
    salvarTabelaHash();

    arquivo = fopen("tabela_hash.dat", "rb");

    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }

    FILE *arquivoClientes;
    int chaveProcurada;

    // Abra o arquivo de clientes em modo de leitura binária
    arquivoClientes = fopen("clientes.dat", "rb");

    if (arquivoClientes == NULL) {
        perror("Erro ao abrir o arquivo de clientes");
        return 1;
    }

    printf("Digite a chave do cliente a ser procurado: ");
    scanf("%d", &chaveProcurada);

    buscarCliente(arquivoClientes, chaveProcurada);
   

    // Carregar a tabela hash a partir do arquivo "tabela_hash"
    carregarTabelaHash();

    fclose(arquivo);
    fclose(arquivoClientes);
    
    return 0;

}