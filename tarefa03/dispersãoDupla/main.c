#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dispersaoDupla.h"


int main() {
    // Inicialize a tabela hash com NULL
    struct Cliente* table[TABLE_SIZE];
    for (int i = 0; i < TABLE_SIZE; i++) {
        table[i] = NULL;
    }

    int opcao, chave;
    int escolha;
    int codigoBusca;
    int codigoLivre;


    do {
        printf("\n1. Inserir cliente\n2. Buscar cliente\n3. Marcar posicao livre\n4. Imprimir todos o clientes\n5. Imprimir numero total de colisoes\n6. Preencher tabela automaticamente\n7. Sair\nEscolha uma alternativa: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: ;
                struct Cliente* novoCliente = criarCliente();
                insert("teste", novoCliente->codigo, table);
                printf("Cliente inserido na tabela.\n");
                break;
            
            case 2: ;
                int codigoBusca;
                printf("Código do cliente a ser buscado: ");
                scanf("%d", &codigoBusca);
                struct Cliente* clienteEncontrado = search(codigoBusca, table);
                if (clienteEncontrado != NULL) {
                    printf("Cliente encontrado: %s, %d\n", clienteEncontrado->nome, clienteEncontrado->codigo);
                } else {
                    printf("Cliente com código %d não encontrado.\n", codigoBusca);
                }
                break;
            
            case 3: ;
                int codigoLivre;
                printf("Código do cliente a ser marcado como livre: ");
                scanf("%d", &codigoLivre);
                marcarComoLivre(codigoLivre, table);
                printf("Posição marcada como livre.\n");
                break;

            case 4: ;
                printTable(table);
                break;

            case 5: ;
                printTodasColisao(colisaoTotal);
                break;
            
            case 6:
                preencherTabela(table);
                break;
        }
    } while (opcao != 7);

    return 0;
}