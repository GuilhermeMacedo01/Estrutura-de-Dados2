#include <stdio.h>
#include <stdlib.h>
#include "cliente.h"
#include "compartimento_hash.h"

void imprimeClientes(FILE *arquivo){
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
}

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

    // Criar e salvar alguns clientes

    /*while (i<6)
    {
        criarCliente(arquivo);
        i++;
    }*/
    
    Cliente cliente1 = {
        cliente1.codCliente = 49, 
       "Tiquinho",
        cliente1.status = 1};
    Cliente cliente2 = {
       cliente2.codCliente = 51, "Luis Henrique",1};
    Cliente cliente3 = {
        cliente3.codCliente = 59, "Janderson",1};
    Cliente cliente4 = {
        cliente4.codCliente = 3, "Adryelson",1};
    Cliente cliente5 = {
        cliente5.codCliente = 87, "Lucas Perri",1};
    Cliente cliente6 = {
        cliente6.codCliente = 103, "Segovinha",1};
    

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
    imprimeClientes(arquivo);

    // Fechar o arquivo novamente
    fclose(arquivo);

    // Salvar a tabela hash no arquivo "tabela_hash"
    salvarTabelaHash();

    arquivo = fopen("tabela_hash.dat", "r+b");

    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }

    FILE *arquivoClientes;
    int chaveProcurada;

    // Abra o arquivo de clientes em modo de leitura binária
    arquivoClientes = fopen("clientes.dat", "r+b");

    if (arquivoClientes == NULL) {
        perror("Erro ao abrir o arquivo de clientes");
        return 1;
    }

    printf("\n<---------- Procurar cliente ---------->\n\n");
    printf("Digite a chave do cliente a ser procurado: ");
    scanf("%d", &chaveProcurada);


    //Função para buscar um cliente
    buscarCliente(arquivoClientes, chaveProcurada);

    //Função para remover Cliente
    //remover(arquivoClientes,chaveProcurada);

    // Carregar a tabela hash a partir do arquivo "tabela_hash"
    carregarTabelaHash();

    fclose(arquivo);
    fclose(arquivoClientes);

    FILE *arquivo2;

    // Abrir o arquivo no modo "r+b" para escrita e leitura binária
    arquivo2 = fopen("clientes.dat", "a+b");
    fseek(arquivo2, 0, SEEK_SET);

    printf("\n<---------- Pos remocao---------->\n\n");

    Cliente cliente8 = {2, "Diego  Costa",1};
    Salva(&cliente8, arquivo2);

    fclose(arquivo2);

    // Abre o arquivo para leitura binária
    arquivo2 = fopen("clientes.dat", "r+b");

    if (arquivo2 == NULL) 
    {
        printf("Não foi possível abrir o arquivo novamente.\n\n");
        return 1;
    }


    imprimeClientes(arquivo2);
    fclose(arquivo2);

    return 0;

}

void remover(FILE *arquivo, int chave){
    removerCliente(49);
    marcarPosicaoLivre(arquivo, 49);
}

