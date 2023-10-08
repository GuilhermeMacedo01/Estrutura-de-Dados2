#include <stdio.h>
#include <stdlib.h>

// Tamanho da tabela
#define TABLE_SIZE 7 // Tamanho da tabela hash (mod 7)

typedef struct HashNode {
    int chave;
    long posicao;
    int status; // 0 para posição livre, 1 para posição ocupada
    struct HashNode* proximo;

} HashNode;

HashNode* tabelaHash[TABLE_SIZE];

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
    novoNo->status = 1; // Marcar como posição ocupada
    novoNo->proximo = tabelaHash[indice];
    tabelaHash[indice] = novoNo;
}

long buscarNaTabela(int chave) {
    int indice = hash(chave);
    HashNode* noAtual = tabelaHash[indice];
    while (noAtual != NULL) {
        if (noAtual->chave == chave && noAtual->status == 1) {
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
            if (noAtual->status == 1) { // Salvar apenas posições ocupadas
                fwrite(&noAtual->chave, sizeof(int), 1, arquivoHash);
                fwrite(&noAtual->posicao, sizeof(long), 1, arquivoHash);
            }
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

void removerCliente(int chave) {
    int indice = hash(chave);
    HashNode* noAtual = tabelaHash[indice];
    while (noAtual != NULL) {
        if (noAtual->chave == chave && noAtual->status == 1) {
            noAtual->status = 0; // Marcar como posição livre

           
            return;
        }
        noAtual = noAtual->proximo;
    }
    // Cliente não encontrado na tabela ou posição já livre
}