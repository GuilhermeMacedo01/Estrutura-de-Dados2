#include <stdio.h>
#include <stdlib.h>

#define TABLE_SIZE 7

typedef struct Cliente {
    int codCliente;
    char nome[100];
    int status;
} Cliente;

typedef struct HashNode {
    int chave;
    int status;
    long posicao;
    struct HashNode* proximo;
} HashNode;

HashNode* tabelaHash[TABLE_SIZE];
FILE* arquivoClientes; // Arquivo que armazena os registros dos clientes

int hash(int chave) {
    return chave % TABLE_SIZE;
}

void inicializarTabela() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        tabelaHash[i] = NULL;
    }
}

void inserirNaTabela(int chave, long posicao) {
    int indice = hash(chave);
    HashNode* novoNo = (HashNode*)malloc(sizeof(HashNode));
    novoNo->chave = chave;
    novoNo->posicao = posicao;
    novoNo->status = 1;
    novoNo->proximo = tabelaHash[indice];
    tabelaHash[indice] = novoNo;
}

long buscarNaTabela(int chave) {
    int indice = hash(chave);
    HashNode* noAtual = tabelaHash[indice];
    while (noAtual != NULL) {
        if (noAtual->chave == chave) {
            return noAtual->posicao;
        }
        noAtual = noAtual->proximo;
    }
    return -1; // Cliente não encontrado na tabela ou posição livre
}

void salvarTabelaHash() {
    FILE* arquivoHash = fopen("tabela_hash.dat", "w+b");

    if (arquivoHash == NULL) {
        printf("Não foi possível abrir o arquivo da tabela hash.\n");
        return;
    }

    for (int i = 0; i < TABLE_SIZE; i++) {
        HashNode* noAtual = tabelaHash[i];
        while (noAtual != NULL) {
            fwrite(&noAtual->chave, sizeof(int), 1, arquivoHash);
            fwrite(&noAtual->posicao, sizeof(long), 1, arquivoHash);
            noAtual = noAtual->proximo;
        }
    }

    fclose(arquivoHash);
}

void carregarTabelaHash() {
    FILE* arquivoHash = fopen("tabela_hash.dat", "rb");

    if (arquivoHash == NULL) {
        printf("Não foi possível abrir o arquivo da tabela hash.\n");
        return;
    }

    for (int i = 0; i < TABLE_SIZE; i++) {
        tabelaHash[i] = NULL;
    }

    int chave;
    long posicao;
    while (fread(&chave, sizeof(int), 1, arquivoHash) == 1 &&
           fread(&posicao, sizeof(long), 1, arquivoHash) == 1) {
        inserirNaTabela(chave, posicao);
    }

    fclose(arquivoHash);
}


void criarCliente() {
    Cliente c;
    printf("Digite o nome da pessoa: ");
    scanf("%*c");
    fgets(c.nome, 100, stdin);
    printf("Digite o código do cliente: ");
    scanf("%d", &c.codCliente);

    if (c.codCliente >= TABLE_SIZE) {
        // Verificar se existe pelo menos uma posição livre na tabela hash
        int indiceVazio = -1;
        for (int i = 0; i < TABLE_SIZE; i++) {
            if (tabelaHash[i] == NULL) {
                indiceVazio = i;
                break;
            }
        }

        if (indiceVazio == -1) {
            printf("Não é possível inserir um novo cliente, pois a tabela hash está cheia.\n");
            return;
        }

        // Agora, podemos inserir o cliente na posição vazia
        inserirNaTabela(c.codCliente, -1); // Não sabemos a posição no arquivo ainda
        printf("Cliente agendado para inserção após a liberação de uma posição vazia na tabela hash.\n");
    } else {
        // A chave é menor que TABLE_SIZE, então podemos inserir diretamente
        if (buscarOcupado(c.codCliente) == 1) {
            printf("Esse código já está em uso.\n");
        } else {
            // Salvar o cliente no arquivo de clientes e obter a posição no arquivo
            fseek(arquivoClientes, 0, SEEK_END);
            long posicao = ftell(arquivoClientes);
            fwrite(&c, sizeof(Cliente), 1, arquivoClientes);

            // Atualizar a tabela hash com a chave do cliente e a posição no arquivo
            inserirNaTabela(c.codCliente, posicao);
            printf("Cliente inserido com sucesso.\n");
        }
    }
}


Cliente* lerCliente(long posicao) {
    fseek(arquivoClientes, posicao, SEEK_SET);
    Cliente* c = (Cliente*)malloc(sizeof(Cliente));
    fread(c, sizeof(Cliente), 1, arquivoClientes);
    return c;
}

void buscarCliente(int chave) {
    long posicao = buscarNaTabela(chave);
    if (posicao != -1) {
        Cliente* c = lerCliente(posicao);
        printf("Cliente encontrado:\n");
        printf("Chave: %d\n", c->codCliente);
        printf("Nome: %s", c->nome);
        
    } else {
        printf("Cliente com chave %d não encontrado.\n", chave);
        
    }
    
}

int buscarOcupado(int chave) {
    long posicao = buscarNaTabela(chave);
    if (posicao != -1) {
        Cliente* c = lerCliente(posicao);
        
        return c->status;
    } else {
        
        return 0;
    }
    return 0;
}

void marcarPosicaoLivre(int chave) {
    long posicao = buscarNaTabela(chave);
    if (posicao != -1) {
        Cliente* c = lerCliente(posicao);
        if (c->status == 1) {
            c->status = 0; // Marque como posição livre
            fseek(arquivoClientes, posicao, SEEK_SET);
            fwrite(c, sizeof(Cliente), 1, arquivoClientes);
            printf("Posição marcada como livre para ser sobrescrita.\n");
        } else {
            printf("Cliente com chave %d já marcado como livre.\n", chave);
        }
    } else {
        printf("Cliente com chave %d não encontrado.\n", chave);
    }
}

void imprimirTodosClientes() {
    fseek(arquivoClientes, 0, SEEK_SET);
    Cliente c;

    printf("\nLista de Clientes:\n");

    while (fread(&c, sizeof(Cliente), 1, arquivoClientes) == 1) {
        if (c.status == 1) {
            printf("Cod: %d", c.codCliente);
            int indice = buscarNaTabela(c.codCliente); // Encontre o índice da tabela hash
            printf(" | Indice Tabela Hash: %d", indice);
            printf(" | Status: %d", c.status);
            printf(" | Nome: %s", c.nome);

            printf("\n");
        }
    }
}
