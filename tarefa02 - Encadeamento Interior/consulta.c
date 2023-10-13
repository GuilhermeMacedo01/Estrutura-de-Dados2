#include <stdio.h>
#include <stdlib.h>
#include "cliente.h"


int main() {
    arquivoClientes = fopen("clientes.dat", "w+b");
    if (arquivoClientes == NULL) {
        printf("Não foi possível abrir o arquivo de clientes.\n");
        return 1;
    }

    // Inicialize a tabela hash
    inicializarTabela();
    // Carregue a tabela hash do arquivo, se existir
    carregarTabelaHash();

    int opcao, chave;

    do {
        printf("\n1. Inserir cliente\n2. Buscar cliente\n3. Marcar posicao livre\n4. Imprimir todos o Clientes\n5. Sair\nEscolha uma alternativa: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                criarCliente();
                break;
            case 2:
                printf("Digite a chave do cliente a ser buscado: ");
                scanf("%d", &chave);
                buscarCliente(chave);
                break;
            case 3:
                printf("Digite a chave do cliente a ser marcado como livre: ");
                scanf("%d", &chave);
                marcarPosicaoLivre(chave);
                break;
            case 4:
                imprimirTodosClientes();
                break;
        }
    } while (opcao != 5);

    // Salve a tabela hash no arquivo
    salvarTabelaHash();

    fclose(arquivoClientes);

    return 0;
}