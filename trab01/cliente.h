#include <stdio.h>
#include <stdlib.h>


typedef struct Cliente {

    int codCliente;
    char nome[100];
    int status;


} Cliente;

// cria e retorna um tipo pessoa
void criarCliente(FILE *arquivo) {
    Cliente c;
    printf("Digite o nome da pessoa: ");
    scanf("%*c");
    fgets(c.nome, 100, stdin);
    printf("Digite a matricula: ");
    scanf("%d", &c.codCliente);
    c.status = 1; // Defina o status como 1 (ocupado) por padrão
    Salva(&c, arquivo);
}

// Salva no arquivo out, na posição atual do cursor
void Salva(Cliente *func, FILE *out) {
    // Verifique o status antes de salvar
    if (func->status == 0) {
        // A posição pode ser sobrescrita, então não atualize o status
        fseek(out, -(long)sizeof(Cliente), SEEK_CUR);
    } else {
        // Posicione-se no final do arquivo para adicionar um novo registro
        fseek(out, 0, SEEK_END);
    }

    fwrite(&func->codCliente, sizeof(int), 1, out);
    fwrite(func->nome, sizeof(char), sizeof(func->nome), out);

    // Se o status for 0, mantenha o status anterior, caso contrário, defina como 1 (ocupado)
    if (func->status != 0) {
        func->status = 1;
    }

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

int calcularIndiceHash(int chave) {
    return chave % 7;
}

void buscarCliente(FILE *arquivo, int chave) {
    Cliente cliente;
    int indice = calcularIndiceHash(chave);

   // Posicionar-se no início do registro na tabela hash
    /*fseek(arquivo, sizeof(Cliente) * indice, SEEK_SET);

    // Ler o cliente correspondente
    fread(&cliente, sizeof(Cliente), 1, arquivo);

    // Verificar se a chave corresponde ao cliente desejado
    if (cliente.codCliente == chave) {
        printf("Cliente encontrado:\n");
        printf("Chave: %d\n", cliente.codCliente);
        printf("Nome: %s\n", cliente.nome);
        // Exibir outros campos do cliente, se necessário
    } else {
        printf("\n%d\n", indice);
        printf("Cliente com chave %d nao encontrado.\n", chave);
    }*/

        // Reinicie a busca a partir do início do arquivo
    rewind(arquivo);

    // Procura o cliente com a chave correspondente
    while (fread(&cliente, sizeof(Cliente), 1, arquivo) == 1) {
        if (cliente.codCliente == chave ) {
            printf("Cliente encontrado:\n");
            printf("Chave: %d\n", cliente.codCliente);
            printf("Nome: %s\n", cliente.nome);
            return; // Cliente encontrado, saia da função
        }
        printf("Cliente encontrado:\n");
        printf("Chave: %d\n", cliente.codCliente);
        printf("Nome: %s\n", cliente.nome);
    }
}

void marcarPosicaoLivre(FILE *arquivo, int chave) {
    Cliente cliente;

    // Posicione-se no início do registro correspondente na tabela hash
    int indice = calcularIndiceHash(chave);
    fseek(arquivo, sizeof(Cliente) * indice, SEEK_SET);

    // Ler o cliente correspondente
    fread(&cliente, sizeof(Cliente), 1, arquivo);

    // Verificar se a chave corresponde ao cliente desejado e se o status é ocupado
    if (cliente.codCliente == chave && cliente.status != 1) {
        cliente.status = 0; // Marque como posição livre
        // Posicione-se novamente no início do registro e atualize o cliente no arquivo
        fseek(arquivo, sizeof(Cliente) * indice, SEEK_SET);
        fwrite(&cliente, sizeof(Cliente), 1, arquivo);
        printf("Posicao marcada como livre para ser sobrescrita.\n");
    } else {
        printf("Cliente com chave %d não encontrado ou já marcado como livre.\n", chave);
       
    }
}

