#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 7

// Estrutura para armazenar um elemento na tabela
struct Cliente {
    char nome[100];
    int codigo;
};

// Função para criar um novo elemento
struct Cliente* createNode(char nome[], int codigo) {
    struct Cliente* newNode = (struct Cliente*)malloc(sizeof(struct Cliente));
    strcpy(newNode->nome, nome);
    newNode->codigo = codigo;
    return newNode;
}

// Função para calcular o índice na tabela hash
int hash(int key, int attempt, int size) {
    return (key + attempt) % size;  // Use uma fórmula para tentar posições alternativas
}

// Função para inserir um elemento na tabela com tratamento de colisões
void insert(char nome[], int codigo, struct Cliente* table[]) {
    int index = hash(codigo, 0, TABLE_SIZE); // Índice inicial

    int attempt = 0;
    while (table[index] != NULL) {
        // Se a posição estiver ocupada, tente a próxima posição
        attempt++;
        index = hash(codigo, attempt, TABLE_SIZE);

        // Se todas as posições estiverem ocupadas, saia
        if (attempt >= TABLE_SIZE) {
            printf("Tabela cheia. Não é possível inserir o cliente (%s, %d).\n", nome, codigo);
            return;
        }
    }

    table[index] = createNode(nome, codigo);
}

// Função para imprimir a tabela hash
void printTable(struct Cliente* table[]) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        printf("Tabela[%d]: ", i);
        if (table[i] != NULL) {
            printf("(%s, %d)\n", table[i]->nome, table[i]->codigo);
        } else {
            printf("NULL\n");
        }
    }
}

int main() {
    // Inicialize a tabela hash com NULL
    struct Cliente* table[TABLE_SIZE];
    for (int i = 0; i < TABLE_SIZE; i++) {
        table[i] = NULL;
    }

    // Inserir elementos na tabela com tratamento de colisões
    insert("Cliente1", 7, table);
    insert("Cliente2", 14, table);
    insert("Cliente3", 21, table);
    insert("Cliente4", 8, table);
    insert("Cliente5", 28, table);
    insert("Cliente6", 14, table);
    insert("Cliente7", 1, table);  // Inserindo um cliente que causará colisão

    // Imprimir a tabela hash
    printTable(table);

    return 0;
}
