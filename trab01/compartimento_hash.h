#include <stdio.h>
#include <stdlib.h>


// tamanho da tabela
#define M 7


// tipo nó usado na lista encadeada
typedef struct No {
    Cliente cliente;
    struct No *proximo;
}No;

// tipo lista com um ponteiro para o primeiro nó
typedef struct Lista {
    No *inicio;
    int tam;
}Lista;

// nossa tabela (vetor de ponteiros para listas)
Lista *tabela[M];

//--------------------------------- fim definições variáveis --------------------

//--------------------------------- funções meus tipos --------------------------

// cria e retorna um tipo pessoa
Cliente criarCliente() {
    Cliente c;
    printf("Digite o nome da pessoa: ");
    scanf("%*c");
    fgets(c.nome, 50, stdin);
    printf("Digite a matricula: ");
    scanf("%d", &c.codCliente);
    return c;
}

// imprime uma pessoa
void imprimirPessoa(Cliente c) {
    printf("\tNome: %s\tcodigo: %d\n", c.nome, c.codCliente);
}

//-------------------------------- início funções lista -------------------------
// cria uma lista vazia e retorna seu endereço na memória
Lista* criarLista() {
    struct Lista *l = (struct Lista*)malloc(sizeof(struct Lista));
    l->inicio = NULL;
    l->tam = 0;
    return l;
}

/*
    inserir no início da lista
    PARÂMETROS
    p - nova pessoa a ser inserida
    *lista - endereço de uma lista encadeada.
*/
void inserirInicio(Cliente c, Lista *lista) {
    struct No *no = (struct No*)malloc(sizeof(struct No));
    no->cliente = c;
    no->proximo = lista->inicio;
    lista->inicio = no;
    lista->tam++;
}

// busca um elemento na lista
No* buscarNo(int cod, No *inicio) {

    while(inicio != NULL) {
        if(inicio->cliente.codCliente == cod)
            return inicio;
        else
            inicio = inicio->proximo;
    }
    return NULL;// matricula não encontrada
}

void imprimirLista(No *inicio) {
    while(inicio != NULL) {
        imprimirPessoa(inicio->cliente);
        inicio = inicio->proximo;
    }
}
//---------------------------------- fim funções lista -------------------------

//--------------------------- início funções tabela hash -----------------------
// inicializa a tabela com uma lista vazia em cada posição do vetor
void inicializar(){
    int i;
    for(i = 0; i < M; i++)
        tabela[i] = criarLista();
}

// função de espalhamento
int funcaoEspalhamento(int mat){
    return mat % M;
}

// cria uma pessoa e a insere na tabela
void inserTabela(){
    Cliente c = criarCliente();
    int indice = funcaoEspalhamento(c.codCliente);
    inserirInicio(c, tabela[indice]);
}

// busca uma pessoa. Seu retorno é um endereço ou NULL
Cliente* buscarClienteTabela(int mat){
    int indice = funcaoEspalhamento(mat);
    No *no = buscarNo(mat, tabela[indice]->inicio);
    if(no)
        return &no->cliente;
    else
        return NULL;
}

// imprimir tabela
void imprimirTabela(){
    int i;
    printf("\n---------------------TABELA-------------------------\n");
    for(i = 0; i < M; i++){
        printf("%d Lista tamanho: %d\n", i, tabela[i]->tam);
        imprimirLista(tabela[i]->inicio);
    }
    printf("---------------------FIM TABELA-----------------------\n");
}

/*int main() {
    int op, mat;
    Cliente *c;

    inicializar();

    do {
        printf("\n0 - Sair\n1 - Inserir\n2 - Buscar\n3 - Imprimir tabela\n");
        scanf("%d", &op);
        switch(op) {
        case 0:
            printf("saindo...\n");
            break;
        case 1:
            inserTabela();
            break;
        case 2:
            printf("Qual a matricula a ser buscada? ");
            scanf("%d", &mat);
            c = buscarClienteTabela(mat);
            if(c) {
                printf("Pessoa encontrada: Matricula: %d\tNome: %s", c->codCliente, c->nome);
            } else
                printf("Pessoa nao contrada!\n");
            break;
        case 3:
            imprimirTabela();
            break;
        default:
            printf("Opcao invalida!\n");
        }
    } while(op != 0);

    return 0;
}*/