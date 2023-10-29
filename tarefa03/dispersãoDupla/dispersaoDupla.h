#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define TABLE_SIZE 10

int colisaoTotal;
int colisao;
int S = TABLE_SIZE - 1;
float fatorDeCarga;

// Estrutura para armazenar um elemento na tabela
struct Cliente {
    char nome[100];
    int codigo;
    int status;
};

// Função para criar um novo elemento
struct Cliente* createNode(char nome[], int codigo) {
    struct Cliente* newNode = (struct Cliente*)malloc(sizeof(struct Cliente));
    strcpy(newNode->nome, nome);
    newNode->codigo = codigo;
    return newNode;
};

// Função para buscar um cliente pelo código
struct Cliente* search(int codigo, struct Cliente* table[]) {
    double total_search_time = 0;
    clock_t start_time = clock();
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (table[i] != NULL && table[i]->codigo == codigo) {
            clock_t end_time = clock();
            double search_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
            total_search_time += search_time;
            printf("Tempo de busca: %lf segundos\n", total_search_time);
            return table[i];
        }
    }
   
    return NULL; // Cliente não encontrado
}

// Função para calcular o índice na tabela hash
int hash(int key, int attempt, int size) {
    return (((key % size) + attempt*((key % S)+1))%size);  // Use uma fórmula para tentar posições alternativas
}

void preencherTabela(struct Cliente* table[]){
    srand(time(NULL));
    int table_size = TABLE_SIZE;
    for (int i = 0; i < fatorDeCarga; i++) {
        int codigo = rand() % 10000;  // Gere um número aleatório entre 0 e 999

        // Garanta que o código gerado esteja dentro do intervalo aceitável
        insert("teste",codigo, table);

    }
}
// Função para marcar a posição
void marcarPosicao(int index, int status, struct Cliente* table[]) {
    if (index >= 0 && index < TABLE_SIZE) {
        if (status == 0 || status == 1) {
            table[index]->status = status;
        }
    }
}


//Função para inserir o usuário na tabela
void insert(char nome[], int codigo, struct Cliente* table[]) {
    int index = hash(codigo, 0, TABLE_SIZE); // Índice inicial
    int attempt = 0;
    if(table[index] != NULL && table[index]->codigo == codigo){
        printf("O codigo inserido ja pertence a outro cliente\n");
        return;
    }
    else{
        while (table[index] != NULL && table[index]->status == 1) {
            // Se a posição estiver ocupada, tente a próxima posição
            printf("Bateu no indice: %d\n",index);
            colisaoTotal++;
            colisao++;
            attempt++;
            index = hash(codigo, attempt, TABLE_SIZE);

            // Se todas as posições estiverem ocupadas, saia
            if (attempt >= TABLE_SIZE) {
                printf("Tabela cheia. Nao e possivel inserir o cliente (%s, %d).\n", nome, codigo);
                return;
        }
    }
    printColisao();
    printf("Cliente inserido na tabela.\n");
    table[index] = createNode(nome, codigo);
    table[index]->status = 1; // Marcar a posição como ocupada
    }
}

//Função para marcar a posição como livre
void marcarComoLivre(int codigo, struct Cliente* table[]) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (table[i] != NULL && table[i]->codigo == codigo) {
            table[i]->status = 0; // Marcar a posição como livre
        }
    }
}

// Função para criar um cliente com entrada do usuário
struct Cliente* criarCliente() {
    char nome[100];
    int codigo;

    printf("Nome do cliente: ");
    scanf("%s", nome);

    printf("Código do cliente: ");
    scanf("%d", &codigo);

    return createNode(nome, codigo);
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

void printTodasColisao(){
    printf("O numero de colisoes é : %d\n",colisaoTotal);
}

void printColisao(){
    printf("O numero de colisoes é : %d\n",colisao);
    colisao = 0;
    return colisao;
}