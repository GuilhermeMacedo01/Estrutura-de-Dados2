#include <stdio.h>
#include <stdlib.h>

typedef struct Cliente {

    int codCliente;
    char nome[100];

} Cliente;

// cria e retorna um tipo pessoa
void criarCliente(FILE *arquivo) {
    Cliente c;
    printf("Digite o nome da pessoa: ");
    scanf("%*c");
    fgets(c.nome, 100, stdin);
    printf("Digite a matricula: ");
    scanf("%d", &c.codCliente);
    Salva(&c,arquivo);
}

// Salva no arquivo out, na posição atual do cursor
void Salva(Cliente *func, FILE *out) {

    fwrite(&func->codCliente, sizeof(int), 1, out);

    //func->nome ao invés de &func->nome,
    //pois string já é ponteiro
    fwrite(func->nome, sizeof(char),
        sizeof(func->nome), out);

    long posicao = ftell(out);
    inserirNaTabela(func->codCliente, posicao);
}

Cliente *le(FILE *in) {
    Cliente *func = (Cliente *)
    malloc(sizeof(Cliente));
    
    if (0 >= fread(&func->codCliente, sizeof(int), 1, in)) {
        free(func);
        return NULL;
    }
    fread(func->nome, sizeof(char), sizeof(func->nome), in);

    return func;
}
