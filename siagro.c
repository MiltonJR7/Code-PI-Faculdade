#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MAXTAM 100
#define MAXSTR 100

//--------------------------------------------------   DADOS   -----------------------------------------------------------------

typedef struct {
    char nome[MAXSTR], email[MAXSTR];
    char cpf[12], rg[10];
} clientesPF;

typedef struct {
    char nomeEmpresarial[MAXSTR], emailEmpresarial[MAXSTR];
    char cnpj[15];
} clientesPJ;

typedef struct {
    char nome[MAXSTR], categoria[MAXSTR];
    int quantidade;
    float preco;
} maquinarios;

typedef struct {
    char nome[MAXSTR], categoria[MAXSTR];
    int quantidade;
    float preco;
} pecas;

int quantPF = 0;
int quantPJ = 0;
int quantMaq = 0;
int quantPec = 0;
clientesPF listaPF[MAXTAM];
clientesPJ listaPJ[MAXTAM];
maquinarios listaMaq[MAXTAM];
pecas listaPec[MAXTAM];

//--------------------------------------------------   FIM DOS DADOS   -----------------------------------------------------------------
//--------------------------------------------------  SALVAR DADOS   -----------------------------------------------------------------

int salvarPF() {
    FILE *arqPF = fopen("dadosPF.bin", "ab");

    if(arqPF == NULL) {
        printf("ERRO: impossivel abrir o arquivo!");
        return 1;
    }
    
    fwrite(&listaPF[quantPF - 1], sizeof(clientesPF), 1, arqPF);
    fclose(arqPF);

    printf("Salvo com sucesso em dadosPF.bin\n");
    return 0;
}

int salvarPJ() {
    FILE *arqPJ = fopen("dadosPJ.bin", "ab");

    if(arqPJ == NULL) {
        printf("ERRO: impossivel abrir o arquivo!");
        return 1;
    }
    
    fwrite(&listaPJ[quantPJ - 1], sizeof(clientesPJ), 1, arqPJ);
    fclose(arqPJ);

    printf("Salvo com sucesso em dadosPJ.bin\n");
    return 0;
}

int salvarProd() {
    FILE *arqProd = fopen("dadosProdutos.bin", "ab");

    if(arqProd == NULL) {
        printf("ERRO: impossivel abrir o arquivo!");
        return 1;
    }
    
    fwrite(&listaMaq[quantMaq - 1], sizeof(maquinarios), 1, arqProd);
    fclose(arqProd);

    printf("Salvo com sucesso em dadosProdutos.bin\n");
    return 0;
}

int salvarProdPeca() {
    FILE *arqProdPecas = fopen("dadosPecas.bin", "ab");

    if(arqProdPecas == NULL) {
        printf("ERRO: impossivel abrir o arquivo!");
        return 1;
    }
    
    fwrite(&listaPec[quantPec - 1], sizeof(pecas), 1, arqProdPecas);
    fclose(arqProdPecas);
 
    printf("Salvo com sucesso em dadosPecas.bin\n");
    return 0;
}

//--------------------------------------------------   FIM DO SALVAR DADOS   -----------------------------------------------------------------
//--------------------------------------------------   CADASTRAR DADOS   -----------------------------------------------------------------

int cadastrarClientes() {
    int op;

    do
    {
        printf("\n--- CONSULTAS ---\n");
        printf("\n1 - Pessoa fisica");
        printf("\n2 - Pessoa juridica");
        printf("\n0 - Sair");
        printf("\nEscolha: ");
        scanf("%d", &op);
        getchar();

        switch (op)
        {
        case 1:
                if(quantPF < MAXTAM) {

                    printf("\n --- CADASTRO PESSOA FISICA --- \n");
                    printf("\nDigite seu nome: ");
                    fgets(listaPF[quantPF].nome, MAXSTR, stdin);
                    listaPF[quantPF].nome[strcspn(listaPF[quantPF].nome, "\n")] = '\0';
            
                    printf("\nDigite seu email: ");
                    fgets(listaPF[quantPF].email, MAXSTR, stdin);
                    listaPF[quantPF].email[strcspn(listaPF[quantPF].email, "\n")] = '\0';
            
                    printf("\nDigite seu CPF: ");
                    scanf("%11s", listaPF[quantPF].cpf);
            
                    printf("\nDigite seu RG: ");
                    scanf("%9s", listaPF[quantPF].rg);
                    getchar();
            
                    quantPF++;
                    salvarPF();
                    return 1;
                } else {
                    printf("ERRO: vetor cheio!\n\n");
                    return 0;
                }
            break;
        case 2: 
                if(quantPJ < MAXTAM) {

                    printf("\n --- CADASTRO PESSOA JURIDICA --- \n");
                    printf("\nDigite o nome empresarial: ");
                    fgets(listaPJ[quantPJ].nomeEmpresarial, MAXSTR, stdin);
                    listaPJ[quantPJ].nomeEmpresarial[strcspn(listaPJ[quantPJ].nomeEmpresarial, "\n")] = '\0';
            
                    printf("\nDigite o email empresarial: ");
                    fgets(listaPJ[quantPJ].emailEmpresarial, MAXSTR, stdin);
                    listaPJ[quantPJ].emailEmpresarial[strcspn(listaPJ[quantPJ].emailEmpresarial, "\n")] = '\0';
            
                    printf("\nDigite o CNPJ: ");
                    scanf("%s", listaPJ[quantPJ].cnpj);
                    getchar();
            
                    quantPJ++;
                    salvarPJ();
                    return 1;
                } else {
                    printf("ERRO: vetor cheio!\n\n");
                    return 0;
                }
            break;
        
        default:
                printf("\nDigite uma opcao valida!");   
            break;
        }
    } while (op != 0);
    
    return 0;
}

int cadastroProdutos() {
    int op;

    do {
        printf("\n--- CADASTRAR PRODUTOS ---\n");
        printf("\n1 - Maquinario");
        printf("\n2 - Pecas para Maquinario");
        printf("\n0 - Sair");
        printf("\nEscolha: ");
        scanf("%d", &op);
        getchar();

        switch (op)
        {
        case 1:
                if (quantMaq < MAXTAM) {
                    printf("\n--- CADASTRO MAQUINARIOS ---\n");
                    printf("\nNome: ");
                    fgets(listaMaq[quantMaq].nome, MAXSTR, stdin);
                    listaMaq[quantMaq].nome[strcspn(listaMaq[quantMaq].nome, "\n")] = '\0';

                    printf("\nCategoria: ");
                    fgets(listaMaq[quantMaq].categoria, MAXSTR, stdin);
                    listaMaq[quantMaq].categoria[strcspn(listaMaq[quantMaq].categoria, "\n")] = '\0';

                    printf("\nQuantidade: ");
                    scanf("%d", &listaMaq[quantMaq].quantidade);

                    printf("\nPreco: ");
                    scanf("%f", &listaMaq[quantMaq].preco);
                    getchar();

                    quantMaq++;
                    salvarProd();
                    return 1;
                } else {
                    printf("ERRO: vetor cheio!\n\n");
                    return 0;
                }                
            break;
        case 2:
                if (quantPec < MAXTAM) {
                    printf("\n--- CADASTRO PECAS PARA MAQUINARIOS ---\n");
                    printf("\nNome: ");
                    fgets(listaPec[quantPec].nome, MAXSTR, stdin);
                    listaPec[quantPec].nome[strcspn(listaPec[quantPec].nome, "\n")] = '\0';

                    printf("\nCategoria: ");
                    fgets(listaPec[quantPec].categoria, MAXSTR, stdin);
                    listaPec[quantPec].categoria[strcspn(listaPec[quantPec].categoria, "\n")] = '\0';

                    printf("\nQuantidade: ");
                    scanf("%d", &listaPec[quantPec].quantidade);

                    printf("\nPreco: ");
                    scanf("%f", &listaPec[quantPec].preco);
                    getchar();

                    quantPec++;
                    salvarProdPeca();
                    return 1;
                } else {
                    printf("ERRO: vetor cheio!\n\n");
                    return 0;
                }   
            break;
        
        default:
                printf("\nDigite uma opcao valida!");
            break;
        }
    } while (op != 0);
    
    return 0;
}

//--------------------------------------------------   FIM DO CADASTRAR DADOS   -----------------------------------------------------------------
//--------------------------------------------------   CONSULTAR DADOS   -----------------------------------------------------------------

void consultarInfos() {
    FILE *arqPF = fopen("dadosPF.bin", "rb");
    FILE *arqPJ = fopen("dadosPJ.bin", "rb");
    FILE *arqProd = fopen("dadosProdutos.bin", "rb");
    FILE *arqProdPecas = fopen("dadosPecas.bin", "rb");
    int op;

    if (arqPF) {
        quantPF = fread(listaPF, sizeof(clientesPF), MAXTAM, arqPF);
        fclose(arqPF);
    } else {
        quantPF = 0;
        printf("Arquivo dadosPF.bin nao encontrado.\n");
    }

    if (arqPJ) {
        quantPJ = fread(listaPJ, sizeof(clientesPJ), MAXTAM, arqPJ);
        fclose(arqPJ);
    } else {
        quantPJ = 0;
        printf("Arquivo dadosPJ.bin nao encontrado.\n");
    }

    if (arqProd) {
        quantMaq = fread(listaMaq, sizeof(maquinarios), MAXTAM, arqProd);
        fclose(arqProd);
    } else {
        quantMaq = 0;
        printf("Arquivo dadosProdutos.bin nao encontrado.\n");
    }

    if (arqProdPecas) {
        quantPec = fread(listaPec, sizeof(pecas), MAXTAM, arqProdPecas);
        fclose(arqProdPecas);
    } else {
        quantPec = 0;
        printf("Arquivo dadosPecas.bin nao encontrado.\n");
    }

    do {
        printf("\n--- CONSULTAS ---\n");
        printf("1 - Pessoa Fisica\n");
        printf("2 - Pessoa Juridica\n");
        printf("3 - Maquinarios\n");
        printf("4 - Pecas\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &op);
        getchar();

        switch (op) {
        case 1:
            if (quantPF == 0)
                printf("\nNenhum cliente PF cadastrado.\n");
            else
                for (int i = 0; i < quantPF; i++)
                    printf("\nNome: %s | Email: %s | CPF: %s | RG: %s\n",
                        listaPF[i].nome, listaPF[i].email, listaPF[i].cpf, listaPF[i].rg);
            break;

        case 2:
            if (quantPJ == 0)
                printf("\nNenhum cliente PJ cadastrado.\n");
            else
                for (int i = 0; i < quantPJ; i++)
                    printf("\nEmpresa: %s | Email: %s | CNPJ: %s\n",
                        listaPJ[i].nomeEmpresarial, listaPJ[i].emailEmpresarial, listaPJ[i].cnpj);
            break;

        case 3:
            if (quantMaq == 0)
                printf("\nNenhum maquinario cadastrado.\n");
            else
                for (int i = 0; i < quantMaq; i++)
                    printf("\nNome: %s | Categoria: %s | Quantidade: %d | Preco: %.2f\n",
                        listaMaq[i].nome, listaMaq[i].categoria, listaMaq[i].quantidade, listaMaq[i].preco);
            break;

        case 4:
            if (quantPec == 0)
                printf("\nNenhuma peca cadastrada.\n");
            else
                for (int i = 0; i < quantPec; i++)
                    printf("\nNome: %s | Categoria: %s | Quantidade: %d | Preco: %.2f\n",
                        listaPec[i].nome, listaPec[i].categoria, listaPec[i].quantidade, listaPec[i].preco);
            break;

        case 0:
            printf("\nSaindo...\n");
            break;

        default:
            printf("\nDigite uma opcao valida!\n");
        }
    } while (op != 0);
}

//--------------------------------------------------   FIM DO CONSULTAR DADOS   -----------------------------------------------------------------

void formatarPJ() {

    



}

//--------------------------------------------------   MAIN PROGRAMA   -----------------------------------------------------------------

int main() {
    int op;
    
    do {
        printf("\n--- Menu ---\n");
        printf("\n1 - Cadastro Clientes");
        printf("\n2 - Cadastro Produtos");
        printf("\n3 - Consultar");
        printf("\n0 - Sair");
        printf("\nEscolha uma opcao: ");
        scanf("%d", &op);
        getchar();

        switch (op) {
        case 1:
                cadastrarClientes();
            break;
        case 2:
                cadastroProdutos();
            break;
        case 3:
                consultarInfos();
            break;
        case 0:
                printf("\nFinalizando...");
            break;

        default:
                printf("\nDigite uma opcao valida!");
            break;
        }
    } while (op != 0);

    return 0;
}

//--------------------------------------------------   FIM DO MAIN PROGRAMA   -----------------------------------------------------------------