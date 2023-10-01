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

int calcularIndiceHash(int chave) {
    return chave % 7;
}

void buscarCliente(FILE *arquivo, int chave) {
    Cliente cliente;
    int indice = calcularIndiceHash(chave);

    // Posicionar-se no início do registro na tabela hash
    fseek(arquivo, sizeof(Cliente) * indice, SEEK_SET);

    // Ler o cliente correspondente
    fread(&cliente, sizeof(Cliente), 1, arquivo);

    // Verificar se a chave corresponde ao cliente desejado
    if (cliente.codCliente == chave) {
        printf("Cliente encontrado:\n");
        printf("Chave: %d\n", cliente.codCliente);
        printf("Nome: %s\n", cliente.nome);
        // Exibir outros campos do cliente, se necessário
    } else {
        printf("Cliente com chave %d não encontrado.\n", chave);
    }
}

void removerCliente(const char *nomeArquivo, int chave) {
    FILE *arquivoOriginal, *arquivoTemporario;
    Cliente cliente;

    // Abra o arquivo original em modo de leitura binária
    arquivoOriginal = fopen(nomeArquivo, "rb");

    if (arquivoOriginal == NULL) {
        perror("Erro ao abrir o arquivo de clientes");
        return;
    }

    // Abra um arquivo temporário em modo de escrita binária
    arquivoTemporario = fopen("temporario.dat", "wb");

    if (arquivoTemporario == NULL) {
        perror("Erro ao criar o arquivo temporário");
        fclose(arquivoOriginal);
        return;
    }

    // Percorra o arquivo original e copie os clientes para o arquivo temporário, exceto o que deseja remover
    while (fread(&cliente, sizeof(Cliente), 1, arquivoOriginal) == 1) {
        if (cliente.codCliente != chave) {
            fwrite(&cliente, sizeof(Cliente), 1, arquivoTemporario);
        }
    }

    // Feche ambos os arquivos
    fclose(arquivoOriginal);
    fclose(arquivoTemporario);

    // Substitua o arquivo original pelo arquivo temporário
    if (remove(nomeArquivo) != 0) {
        perror("Erro ao excluir o arquivo original");
        return;
    }
    
    if (rename("temporario.dat", nomeArquivo) != 0) {
        perror("Erro ao renomear o arquivo temporário");
    }
}