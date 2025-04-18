#include <stdio.h>
#include <string.h>
#define MAXTAM 100
#define MAXSTR 100

typedef struct {
    char nome[MAXSTR], email[MAXSTR];
    int cpf, rg;
} clientesPF;

typedef struct {
    char nomeEmpresarial[MAXSTR], emailEmpresarial[MAXSTR];
    int cnpj;
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
                    scanf("%d", &listaPF[quantPF].cpf);
            
                    printf("\nDigite seu RG: ");
                    scanf("%d", &listaPF[quantPF].rg);
                    getchar();
            
                    quantPF++;
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
                    scanf("%d", &listaPJ[quantPJ].cnpj);
                    getchar();
            
                    quantPJ++;
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

void consultarInfos() {
    int op, i, op2;

    do {
        printf("\n--- CONSULTAS ---\n");
        printf("\n1 - Clientes");
        printf("\n0 - Sair");
        printf("\nEscolha: ");
        scanf("%d", &op);
        getchar();

        switch (op) {
            case 1:
                    while (op2 != 0) {
                        printf("\n--- CONSULTAS ---\n");
                        printf("\n1 - Pessoa Fisica");
                        printf("\n2 - Pessoa Juridica");
                        printf("\n0 - Sair");
                        printf("\nEscolha: ");
                        scanf("%d", &op2);
                        getchar();

                        switch (op2) {
                        case 1:
                                for (i = 0; i < quantPF; i++) {
                                    printf("\nNome: %s", listaPF[i].nome);
                                    printf("\nCPF: %d", listaPF[i].cpf);
                                    printf("\nRG: %d", listaPF[i].rg);
                                    printf("\nEmail: %s", listaPF[i].email);
                                }
                            break;
                        case 2:
                                for (i = 0; i < quantPJ; i++) {
                                    printf("\nNome: %s", listaPJ[i].nomeEmpresarial);
                                    printf("\nCNPJ: %d", listaPJ[i].cnpj);
                                    printf("\nEmail: %s", listaPJ[i].emailEmpresarial);
                                }
                            break;
                        default:
                                printf("\nDigite uma opcao valida!");
                            break;
                        }
                    }
                    
                break;   
            case 0:
                    printf("\nSaindo...");
                break;
        default:
                printf("\nDigite uma opcao valida!");
            break;
        }
    } while (op != 0);   
}

void salvarArq() {
    FILE *arqPF = fopen("C:/Faculdade/PI/CodeC/Dados/clientesPF.txt", "w");
    FILE *arqPJ = fopen("C:/Faculdade/PI/CodeC/Dados/clientesPJ.txt", "w");
    FILE *arqProd = fopen("C:/Faculdade/PI/CodeC/Dados/produtos.txt", "w");
    FILE *arqProdPecas = fopen("C:/Faculdade/PI/CodeC/Dados/produtosPecas.txt", "w");
    int i;

    if (arqPF) {
        for (i = 0; i < quantPF; i++) {
            fprintf(arqPF, "\nNome: %s", listaPF[i].nome);
            fprintf(arqPF, "\nCpf: %d", listaPF[i].cpf);
            fprintf(arqPF, "\nRG: %d", listaPF[i].rg);
            fprintf(arqPF, "\nEmail: %s\n", listaPF[i].email);
        }
        fclose(arqPF);
    } else {
        printf("ERRO: nao foi possivel abrir o arquivo clientesPF.txt\n\n");
    }

    if (arqPJ) {
        for (i = 0; i < quantPJ; i++) {
            fprintf(arqPJ, "\nNome: %s", listaPJ[i].nomeEmpresarial);
            fprintf(arqPJ, "\nCnpj: %d", listaPJ[i].cnpj);
            fprintf(arqPJ, "\nEmail: %s\n", listaPJ[i].emailEmpresarial);
        }
        fclose(arqPJ);
    } else {
        printf("ERRO: nao foi possivel abrir o arquivo clientesPJ.txt\n\n");
    }

    if (arqProd) {
        for (i = 0; i < quantMaq; i++) {
            fprintf(arqProd, "\nNome: %s", listaMaq[i].nome);
            fprintf(arqProd, "\nCategoria: %s", listaMaq[i].categoria);
            fprintf(arqProd, "\nQuantidade: %d", listaMaq[i].quantidade);
            fprintf(arqProd, "\nPreco: %.2f\n", listaMaq[i].preco);
        }
        fclose(arqProd);
    } else {
        printf("ERRO: nao foi possivel abrir o arquivo produtos.txt\n\n");
    }

    if (arqProdPecas) {
        for (i = 0; i < quantPec; i++) {
            fprintf(arqProdPecas, "\nNome: %s", listaPec[i].nome);
            fprintf(arqProdPecas, "\nCategoria: %s", listaPec[i].categoria);
            fprintf(arqProdPecas, "\nQuantidade: %d", listaPec[i].quantidade);
            fprintf(arqProdPecas, "\nPreco: %.2f\n", listaPec[i].preco);
        }
        fclose(arqProdPecas);
    } else {
        printf("ERRO: nao foi possivel abrir o arquivo produtosPecas.txt\n\n");
    }
}

int main() {
    int op;
    
    do {
        printf("\n--- Menu ---\n");
        printf("\n1 - Cadastro Clientes");
        printf("\n2 - Cadastro Produtos");
        printf("\n3 - Consultar");
        printf("\n4 - Salvar Infos");
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
        case 4:
                salvarArq();
            break;
        default:
                printf("\nDigite uma opcao valida!");
            break;
        }
    } while (op != 0);

    return 0;
}