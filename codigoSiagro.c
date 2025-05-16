#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>
#include <Windows.h>

#define MAXSTR 100

// STRUCTS PARA O PROJETO INTEIRO --------------------------------------------
typedef struct {
    int dia, mes, ano;
} date;

typedef struct {
    char nome[MAXSTR], email[MAXSTR], cpf[12];
} clientesPF;

typedef struct {
    char nomeEmpresarial[MAXSTR], emailEmpresarial[MAXSTR], cnpj[15];
} clientesPJ;

typedef struct {
    char nome[MAXSTR], categoria[MAXSTR], codigo[20];
    int quantidade;
    float preco;
} maquinarios;

typedef struct {
    char nome[MAXSTR], categoria[MAXSTR], codigo[20];
    int quantidade;
    float preco;
} pecas;

typedef struct {
    char tipoServico[MAXSTR], cpfParaContrato[12], cnpjParaContrato[15], descricao[MAXSTR];
    float preco;
    date D;
} servicos;

// TERMINA AQUI AS STRUCTS PARA O PROJETO INTEIRO --------------------------------------------
// FUNCOES DE SALVAR EM ARQUIVOS BINARIOS --------------------------------------------

void salvarClientePF(clientesPF PF) {
    FILE *arqPF = fopen("arqPF.bin", "ab+");

    if (arqPF == NULL) {
        printf("\nERRO: impossivel acessar o arquivo!\n");
    }

    fwrite(&PF, sizeof(clientesPF), 1, arqPF);
    fclose(arqPF);
}

void salvarClientePJ(clientesPJ PJ) {
    FILE *arqPJ = fopen("arqPJ.bin", "ab+");

    if (arqPJ == NULL) {
        printf("\nERRO: impossivel acessar o arquivo!\n");
    }

    fwrite(&PJ, sizeof(clientesPJ), 1, arqPJ);
    fclose(arqPJ);
}

void salvarMaquinario(maquinarios M) {
    FILE *arqMaq = fopen("arqMaquinario.bin", "ab+");

    if(arqMaq == NULL) {
        printf("\nERRO: impossivel acessar o arquivo!\n");
    }

    fwrite(&M, sizeof(maquinarios), 1, arqMaq);
    fclose(arqMaq);
}

void salvarPecas(pecas P) {
    FILE *arqPec = fopen("arqPecas.bin", "ab+");

    if(arqPec == NULL) {
        printf("\nERRO: impossivel acessar o arquivo!\n");
    }

    fwrite(&P, sizeof(pecas), 1, arqPec);
    fclose(arqPec);
}

void salvarServico(servicos S) {
    FILE *arqSer = fopen("arqServicos.bin", "ab+");

    if(arqSer == NULL) {
        printf("\nERRO: impossivel acessar o arquivo!\n");
    }

    fwrite(&S, sizeof(servicos), 1, arqSer);
    fclose(arqSer);
}

// TERMINA AQUI AS FUNCOES DE SALVAR EM ARQUIVOS BINARIOS --------------------------------------------
// FUNCOES DE VALIDAR CPF E CNPJ EM ARQUIVOS BINARIOS --------------------------------------------

int validarCPF(FILE *arqPF, char cpf[]) {
    clientesPF PF;

    rewind(arqPF);
    fread(&PF, sizeof(clientesPF), 1, arqPF);
    while (!feof(arqPF) && stricmp(cpf, PF.cpf) != 0) {
        fread(&PF, sizeof(clientesPF), 1, arqPF);
    }

    if (!feof(arqPF)) {
        return (ftell(arqPF) - sizeof(clientesPF));
    } else {
        return -1;
    }   
}

int validarCNPJ(FILE *arqPJ, char cnpj[]) {
    clientesPJ PJ;

    rewind(arqPJ);
    fread(&PJ, sizeof(clientesPJ), 1, arqPJ);
    while (!feof(arqPJ) && stricmp(cnpj, PJ.cnpj) != 0) {
        fread(&PJ, sizeof(clientesPJ), 1, arqPJ);
    }

    if (!feof(arqPJ)) {
        return(ftell(arqPJ) - sizeof(clientesPJ));
    } else {
        return -1;
    }
}

int validarMaquinario(FILE *arqMaq, char codigo[]) {
    maquinarios M;

    rewind(arqMaq);
    fread(&M, sizeof(maquinarios), 1, arqMaq);
    while (!feof(arqMaq) && stricmp(codigo, M.codigo) != 0) {
        fread(&M, sizeof(maquinarios), 1, arqMaq);
    }

    if(!feof(arqMaq)) {
        return(ftell(arqMaq) - sizeof(maquinarios));
    } else {
        return -1;
    }
}

int validarPecas(FILE *arqPec, char codigo[]) {
    pecas P;

    rewind(arqPec);
    fread(&P, sizeof(maquinarios), 1, arqPec);
    while (!feof(arqPec) && stricmp(codigo, P.codigo) != 0) {
        fread(&P, sizeof(maquinarios), 1, arqPec);
    }

    if(!feof(arqPec)) {
        return(ftell(arqPec) - sizeof(maquinarios));
    } else {
        return -1;
    }
}

// TERMINA AQUI AS FUNCOES DE VALIDAR CPF E CNPJ EM ARQUIVOS BINARIOS --------------------------------------------
// FUNCAO DE CADASTROS DE USUARIOS, MAQUINARIOS, SERVICOS E PECAS --------------------------------------------

void cadastroDeClientes() {
    clientesPF PF;
    clientesPJ PJ;
    maquinarios M;
    pecas P;
    servicos S;

    FILE *arqPF = fopen("arqPF.bin", "rb+");
    FILE *arqPJ = fopen("arqPJ.bin", "rb+");
    FILE *arqMaq = fopen("arqMaquinario.bin", "rb+");
    FILE *arqPec = fopen("arqPecas.bin", "rb+");
    FILE *arqSer = fopen("arqServicos.bin", "rb+");

    int op, op2, op3, posCPF, posCNPJ, posMaq, posPec, valido;

    if (arqPF == NULL || arqPJ == NULL || arqMaq == NULL || arqPec == NULL || arqSer == NULL) {
    arqPF = fopen("arqPF.bin", "wb+");
    arqPJ = fopen("arqPJ.bin", "wb+");
    arqMaq = fopen("arqMaquinario.bin", "wb+");
    arqPec = fopen("arqPecas.bin", "wb+");
    arqSer = fopen("arqServicos.bin", "wb+");

        if (arqPF == NULL || arqPJ == NULL || arqMaq == NULL || arqPec == NULL || arqSer == NULL) {
            printf("\nERRO ao criar o arquivo!"); 
            return;
        }
    }

    do {
        printf("\n--- CADASTROS ---\n");
        printf("\n1 - Clientes");
        printf("\n2 - Produtos");
        printf("\n3 - Servicos");
        printf("\n0 - Retornar ao menu");
        printf("\nEscolha: ");
        scanf("%d", &op);
        system("cls");
        getchar();

        switch (op) {
        case 1:
                do {
                    printf("\n--- CADASTRO DE CLIENTES ---\n");
                    printf("\n1 - Clientes PF");
                    printf("\n2 - Clientes PJ");
                    printf("\n0 - Retornar");
                    printf("\nEscolha: ");
                    scanf("%d", &op2);
                    system("cls");
                    getchar();

                    switch (op2) {
                    case 1:
                            do {
                                printf("\n--- CLIENTES PF ---\n");
                                printf("\nSeu cpf: ");
                                scanf("%11s", PF.cpf);
                                getchar();

                                posCPF = validarCPF(arqPF, PF.cpf);

                                if (posCPF == -1) {
                                    printf("\nSeu nome: ");
                                    fgets(PF.nome, MAXSTR, stdin);
                                    PF.nome[strcspn(PF.nome, "\n")] = '\0';

                                    printf("\nSeu email: ");
                                    fgets(PF.email, MAXSTR, stdin);
                                    PF.email[strcspn(PF.email, "\n")] = '\0';

                                    salvarClientePF(PF);
                                    printf("\nCliente cadastrado com sucesso!\n\n");
                                } else {
                                    clientesPF PF_ja_cadastrado;
                                    fseek(arqPF, posCPF, 0);
                                    fread(&PF_ja_cadastrado, sizeof(clientesPF), 1, arqPF);
                                    printf("\nO CPF digitado: %.3s.%.3s.%.3s-%.2s ja esta cadastrado!", PF_ja_cadastrado.cpf, PF_ja_cadastrado.cpf+3, PF_ja_cadastrado.cpf+6, PF_ja_cadastrado.cpf+9);
                                }
                                
                                printf("\nDeseja continuar? S/N: \n");
                            } while (toupper(getche()) == 'S');  
                        break;
                    case 2:
                            do {
                                printf("\n--- CLIENTES PJ ---\n");
                                printf("\nDigite seu cnpj: ");
                                scanf("%14s", PJ.cnpj);
                                getchar();

                                posCNPJ = validarCNPJ(arqPJ, PJ.cnpj);
                                
                                if (posCNPJ == -1) {
                                    printf("\nO nome empresarial: ");
                                    fgets(PJ.nomeEmpresarial, MAXSTR, stdin);
                                    PJ.nomeEmpresarial[strcspn(PJ.nomeEmpresarial, "\n")] = '\0';

                                    printf("\nO email empresarial: ");
                                    fgets(PJ.emailEmpresarial, MAXSTR, stdin);
                                    PJ.emailEmpresarial[strcspn(PJ.emailEmpresarial, "\n")] = '\0';
                                    
                                    salvarClientePJ(PJ);
                                    printf("\nCliente cadastrado com sucesso!\n\n");
                                } else {
                                    clientesPJ PJ_ja_cadastrado;
                                    fseek(arqPJ, posCNPJ, 0);
                                    fread(&PJ_ja_cadastrado, sizeof(clientesPJ), 1, arqPJ);
                                    printf("\nO CNPJ digitado: %.2s.%.3s.%.3s/%.4s-%2s ja esta cadastrado!", PJ_ja_cadastrado.cnpj, PJ_ja_cadastrado.cnpj+2, PJ_ja_cadastrado.cnpj+5, PJ_ja_cadastrado.cnpj+8, PJ_ja_cadastrado.cnpj+12);
                                }
                                
                                printf("\nDeseja continuar? S/N: \n");
                            } while (toupper(getche()) == 'S');
                        break;
                    case 0:
                            printf("\nRetornando...\n");
                        break;
                    default:
                            printf("\nERRO: escolha uma opcao valida!\n");
                        break;
                    }
                } while (op2 !=  0);      
            break;
        case 2:
                do {
                    printf("\n--- CADASTRO DE PRODUTOS ---\n");
                    printf("\n1 - Maquinario");
                    printf("\n2 - Pecas");
                    printf("\n0 - Retornar");
                    printf("\nEscolha: ");
                    scanf("%d", &op2);
                    system("cls");
                    getchar();

                    switch (op2) {
                    case 1:
                            do {
                                printf("\n--- MAQUINARIOS ---\n");
                                printf("\nDigite o codigo do maquinario: ");
                                scanf("%19s", M.codigo);
                                getchar();

                                posMaq = validarMaquinario(arqMaq, M.codigo);

                                if(posMaq == -1) {
                                    printf("\nNome do maquinario: ");
                                    fgets(M.nome, MAXSTR, stdin);
                                    M.nome[strcspn(M.nome, "\n")] = '\0';

                                    printf("\nCategoria do maquinario: ");
                                    fgets(M.categoria, MAXSTR, stdin);
                                    M.categoria[strcspn(M.categoria, "\n")] = '\0';
                                    
                                    printf("\nQuantidade disponivel: ");
                                    scanf("%d", &M.quantidade);

                                    printf("\nPreco do maquinario: ");
                                    scanf("%f", &M.preco);
                                    getchar();

                                    salvarMaquinario(M);
                                    printf("\nMaquinario cadastrado com sucesso!\n\n");
                                } else {
                                    maquinarios MAQ_ja_cadastrado;
                                    fseek(arqMaq, posMaq, 0);
                                    fread(&MAQ_ja_cadastrado, sizeof(maquinarios), 1, arqMaq);
                                    printf("\nO codigo digitado: %s ja esta cadastrado!", MAQ_ja_cadastrado.codigo);
                                }

                                printf("\nDeseja continuar? S/N: \n");
                            } while (toupper(getche()) == 'S');
                        break;
                    case 2:
                            do {
                                printf("\n--- PECAS ---\n");
                                printf("\nDigite o codigo da peca: ");
                                scanf("%19s", P.codigo);
                                getchar();

                                posPec = validarPecas(arqPec, P.codigo);

                                if(posMaq == -1) {
                                    printf("\nNome da peca: ");
                                    fgets(P.nome, MAXSTR, stdin);
                                    P.nome[strcspn(P.nome, "\n")] = '\0';

                                    printf("\nCategoria da peca: ");
                                    fgets(P.categoria, MAXSTR, stdin);
                                    P.categoria[strcspn(P.categoria, "\n")] = '\0';
                                    
                                    printf("\nQuantidade disponivel: ");
                                    scanf("%d", &P.quantidade);

                                    printf("\nPreco da peca: ");
                                    scanf("%f", &P.preco);
                                    getchar();

                                    salvarPecas(P);
                                    printf("\nMaquinario cadastrado com sucesso!\n\n");
                                } else {
                                    pecas PEC_ja_cadastrado;
                                    fseek(arqPec, posPec, 0);
                                    fread(&PEC_ja_cadastrado, sizeof(pecas), 1, arqMaq);
                                    printf("\nO codigo digitado: %s ja esta cadastrado!", PEC_ja_cadastrado.codigo);
                                }

                                printf("\nDeseja continuar? S/N: \n");
                            } while (toupper(getche()) == 'S');
                        break;
                    case 0:
                            printf("\nRetornando...\n");
                        break;
                    default:
                            printf("\nERRO: escolha uma opcao valida!\n");
                        break;
                    }

                } while (op2 != 0);             
            break;
        case 3:
                do {
                    printf("\n--- CADASTRO DE SERVICOS ---\n");
                    printf("\n1 - Cliente PF");
                    printf("\n2 - Cliente PJ");
                    printf("\n0 - Retornar");
                    printf("\nEscolha: ");
                    scanf("%d", &op3);
                    system("cls");
                    getchar();

                    switch (op3) {
                        case 1:
                                printf("\n--- CADASTRAR SERVICO PARA PF ---\n");
                                printf("\nDigite o cpf para cadastrar o servico: ");
                                scanf("%11s", S.cpfParaContrato);
                                getchar();

                                valido = 1;

                                while (fread(&PF, sizeof(clientesPF), 1, arqPF) == 1) {
                                    if (stricmp(S.cpfParaContrato, PF.cpf) == 0) {
                                        printf("\nQual o tipo de servico: ");
                                        fgets(S.tipoServico, MAXSTR, stdin);

                                        printf("\nQual a descricao: ");
                                        fgets(S.descricao, MAXSTR, stdin);

                                        printf("\nQual o preco do servico: ");
                                        scanf("%f", &S.preco);

                                        printf("\nQual a data para o servico <dd/mm/aaaa> : ");
                                        scanf("%d%d%d", &S.D.dia, &S.D.mes, &S.D.ano);
                                        getchar();

                                        valido = 0;
                                        salvarServico(S);
                                        printf("\nServico cadastrado com sucesso!\n\n");
                                    }                                           
                                }

                                if(valido == 1) {
                                    printf("\nO cpf nao foi cadastrado ainda!\n");
                                } 
                            break;
                        case 2:
                                printf("\n--- CADASTRAR SERVICO PARA PJ ---\n");
                                printf("\nDigite o cpf para cadastrar o servico: ");
                                scanf("%14s", S.cnpjParaContrato);
                                getchar();

                                valido = 1;

                                while (fread(&PJ, sizeof(clientesPJ), 1, arqPJ) == 1) {
                                    if (stricmp(S.cnpjParaContrato, PJ.cnpj) == 0) {
                                        printf("\nQual o tipo de servico: ");
                                        fgets(S.tipoServico, MAXSTR, stdin);

                                        printf("\nQual a descricao: ");
                                        fgets(S.descricao, MAXSTR, stdin);

                                        printf("\nQual o preco do servico: ");
                                        scanf("%f", &S.preco);

                                        printf("\nQual a data para o servico <dd/mm/aaaa> : ");
                                        scanf("%d%d%d", &S.D.dia, &S.D.mes, &S.D.ano);
                                        getchar();

                                        valido = 0;
                                        salvarServico(S);
                                        printf("\nServico cadastrado com sucesso!\n\n");
                                    }                                           
                                }

                                if(valido == 1) {
                                    printf("\nO cnpj nao foi cadastrado ainda!\n");
                                }
                            break;
                    case 0:
                            printf("\nRetornando...\n");
                        break;
                    default:
                            printf("\nERRO: escolha uma opcao valida!\n");
                        break;
                    }

                } while (op3 != 0);

            } while (op3 != 0);

        fclose(arqPF);
        fclose(arqPJ);
        fclose(arqMaq);
        fclose(arqPec);
        fclose(arqSer);

    } while (op != 0);
}

// TERMINA AQUI A FUNCAO DE CADASTROS DE USUARIOS, MAQUINARIOS, SERVICOS E PECAS --------------------------------------------
// FUNCAO DE BUSCA DE CADASTROS DE USUARIOS, MAQUINARIOS, SERVICOS E PECAS --------------------------------------------

void buscaDeCadastros() {
    clientesPF PF;
    clientesPJ PJ;
    maquinarios M;
    pecas P;
    servicos S;

    FILE *arqPF = fopen("arqPF.bin", "rb+");
    FILE *arqPJ = fopen("arqPJ.bin", "rb+");
    FILE *arqMaq = fopen("arqMaquinario.bin", "rb+");
    FILE *arqPec = fopen("arqPecas.bin", "rb+");
    FILE *arqSer = fopen("arqServicos.bin", "rb+");

    char buscCpf[12], buscCnpj[15], buscCodMaq[20], buscCodPec[20], buscCpfServ[12], buscCnpjServ[15];
    int op, op2, op3, achou, valido;

    if (arqPF == NULL || arqPJ == NULL || arqMaq == NULL || arqPec == NULL || arqSer == NULL) {
    arqPF = fopen("arqPF.bin", "wb+");
    arqPJ = fopen("arqPJ.bin", "wb+");
    arqMaq = fopen("arqMaquinario.bin", "wb+");
    arqPec = fopen("arqPecas.bin", "wb+");
    arqSer = fopen("arqServicos.bin", "wb+");

        if (arqPF == NULL || arqPJ == NULL || arqMaq == NULL || arqPec == NULL || arqSer == NULL) {
            printf("\nERRO ao criar o arquivo!");
            return;
        }
    }

    do {
        printf("\n--- BUSCA ---\n");
        printf("\n1 - Clientes");
        printf("\n2 - Produtos");
        printf("\n3 - Servicos");
        printf("\n0 - Retornar ao menu");
        printf("\nEscolha: ");
        scanf("%d", &op);
        system("cls");
        getchar();

        switch (op) {
        case 1:
                do {
                    printf("\n--- BUSCA DE CLIENTES ---\n");
                    printf("\n1 - Clientes PF");
                    printf("\n2 - Clientes PJ");
                    printf("\n0 - Retornar");
                    printf("\nEscolha: ");
                    scanf("%d", &op2);
                    system("cls");
                    getchar();

                    switch (op2) {
                    case 1:
                            printf("\n--- CLIENTES PF ---\n");
                            printf("\nUse o cpf para buscar: ");
                            scanf("%11s", buscCpf);
                            getchar();

                            achou = 1;
                            rewind(arqPF);
                            while (fread(&PF, sizeof(clientesPF), 1, arqPF) == 1) {
                                if (stricmp(buscCpf, PF.cpf) == 0) {
                                    printf("\nDados do cliente:");
                                    printf("\nNome: %s \nEmail: %s \nCpf: %.3s.%.3s.%.3s-%.2s\n", PF.nome, PF.email, PF.cpf, PF.cpf+3, PF.cpf+6, PF.cpf+9);
                                    achou = 0;
                                    break;
                                }
                            }

                            if (achou == 1) {
                                printf("\nERRO: nao ha cadastro com o cnpj digitado!");
                            }
                        break;
                    case 2:
                            printf("\n--- CLIENTES PJ ---\n");
                            printf("\nUse o cnpj para buscar: ");
                            scanf("%14s", buscCnpj);
                            getchar();

                            achou = 1;
                            rewind(arqPJ);
                            while (fread(&PJ, sizeof(clientesPJ), 1, arqPJ) == 1) {
                                if (stricmp(buscCnpj, PJ.cnpj) == 0) {
                                    printf("\nDados da empresa:");
                                    printf("\nNome: %s \nEmail: %s \nCnpj: %.2s.%.3s.%.3s/%.4s-%2s\n", PJ.nomeEmpresarial, PJ.emailEmpresarial, PJ.cnpj, PJ.cnpj+2, PJ.cnpj+5, PJ.cnpj+8, PJ.cnpj+12);
                                    achou = 0;
                                    break;
                                }
                            }

                            if (achou == 1) {
                                printf("\nERRO: nao ha cadastro com o cpf digitado!");
                            }
                        break;
                    case 0:
                            printf("\nRetornando...\n");
                        break;
                    default:
                            printf("\nERRO: escolha uma opcao valida!\n");
                        break;
                    }

                } while (op2 != 0);
            
            break;
        case 2:
                do {
                    printf("\n--- BUSCA DE PRODUTOS ---\n");
                    printf("\n1 - Maquinario");
                    printf("\n2 - Pecas");
                    printf("\n0 - Retornar");
                    printf("\nEscolha: ");
                    scanf("%d", &op2);
                    system("cls");
                    getchar();

                    switch (op2) {
                    case 1:
                            printf("\n--- MAQUINARIOS ---\n");
                            printf("\nUse o codigo para buscar: ");
                            scanf("%19s", buscCodMaq);
                            getchar();

                            achou = 1;
                            rewind(arqMaq);
                            while (fread(&M, sizeof(maquinarios), 1, arqMaq) == 1) {
                                if (stricmp(buscCodMaq, M.codigo) == 0) {
                                    printf("\nDados do maquinario:");
                                    printf("\nNome: %s \nCategoria: %s \nCodigo: %s \nQuantidade: %d \nPreco: %.2f\n", M.nome, M.categoria, M.codigo, M.quantidade, M.preco);
                                    achou = 0;
                                    break;
                                }
                            }

                            if (achou == 1) {
                                printf("\nERRO: nao ha cadastro com o codigo digitado!");
                            }
                        break;
                    case 2:
                            printf("\n--- PECAS ---\n");
                            printf("\nUse o codigo para buscar: ");
                            scanf("%19s", buscCodPec);
                            getchar();

                            achou = 1;
                            rewind(arqPec);
                            while (fread(&P, sizeof(pecas), 1, arqPec) == 1) {
                                if (stricmp(buscCodPec, P.codigo) == 0) {
                                    printf("\nDados da peca:");
                                    printf("\nNome: %s \nCategoria: %s \nCodigo: %s \nQuantidade: %d \nPreco: %.2f\n", P.nome, P.categoria, P.codigo, P.quantidade, P.preco);
                                    achou = 0;
                                    break;
                                }
                            }

                            if (achou == 1) {
                                printf("\nERRO: nao ha cadastro com o codigo digitado!");
                            }
                        break;
                    case 0:
                            printf("\nRetornando...\n");
                        break;
                    default:
                            printf("\nERRO: escolha uma opcao valida!\n");
                        break;
                    }

                } while (op2 != 0);
                
            break;
        case 3:
                do {
                    printf("\n--- BUSCA DE SERVICOS ---\n");
                    printf("\n1 - Cliente PF");
                    printf("\n2 - Cliente PJ");
                    printf("\n0 - Retornar");
                    printf("\nEscolha: ");
                    scanf("%d", &op3);
                    system("cls");
                    getchar();

                    switch (op3) {
                    case 1:
                            printf("\n--- BUSCA DE SERVICOS EM PF ---\n");
                            printf("\nDigite o cpf para cadastrar o servico: ");
                            scanf("%11s", buscCpfServ);
                            getchar();

                            valido = 1;

                            while (fread(&S, sizeof(servicos), 1, arqSer) == 1) {
                                if (stricmp(buscCpfServ, S.cpfParaContrato) == 0) {
                                    printf("\nDados do servico:");
                                    printf("\nTipo de servico: %s \nDescricao: %s \nPreco: %.2f \nData: %02d/%02d/%02d \nCPF: %.3s.%.3s.%.3s-%.2s\n", S.tipoServico, S.descricao, S.preco, S.D.dia, S.D.mes, S.D.ano, S.cpfParaContrato, S.cpfParaContrato+3, S.cpfParaContrato+6, S.cpfParaContrato+9);
                                    valido = 0;
                                }                                           
                            }

                            if(valido == 1) {
                                printf("\nNao a servicos cadastrados no cpf digitado!\n");
                            }
                        break;
                    case 2:
                            printf("\n--- BUSCA DE SERVICOS EM PJ ---\n");
                            printf("\nDigite o cnpj para cadastrar o servico: ");
                            scanf("%14s", buscCnpjServ);
                            getchar();

                            valido = 1;

                            while (fread(&S, sizeof(servicos), 1, arqSer) == 1) {
                                if (stricmp(buscCnpjServ, S.cnpjParaContrato) == 0) {
                                    printf("\nDados do servico:");
                                    printf("\nTipo de servico: %s \nDescricao: %s \nPreco: %.2f \nData: %02d/%02d/%02d \nCNPJ: %.2s.%.3s.%.3s/%.4s-%2s\n", S.tipoServico, S.descricao, S.preco, S.D.dia, S.D.mes, S.D.ano, S.cnpjParaContrato, S.cnpjParaContrato+2, S.cnpjParaContrato+5, S.cnpjParaContrato+8, S.cnpjParaContrato+12);
                                    valido = 0;
                                }                                           
                            }

                            if(valido == 1) {
                                printf("\nNao a servicos cadastrados no cnpj digitado!\n");
                            }
                        break;
                    case 0:
                            printf("\nRetornando...\n");
                        break;
                    
                    default:
                            printf("\nERRO: escolha uma opcao valida!\n");
                        break;
                    }

                } while (op3);
                
            break;
        case 0:
                printf("\nRetornando...\n");
            break;
        default:
                printf("\nERRO: escolha uma opcao valida!\n");
            break;
        }

        fclose(arqPF);
        fclose(arqPJ);
        fclose(arqMaq);
        fclose(arqPec);
        fclose(arqSer);

    } while (op != 0);
}

// TERMINA AQUI A FUNCAO DE BUSCA DE CADASTROS DE USUARIOS, MAQUINARIOS, SERVICOS E PECAS --------------------------------------------
// MAIN DO PROGRAMA INTEIRO DO PROJETO --------------------------------------------

int main() {
    int op;

    do {
        printf("\n--- MENU ---\n");
        printf("\n1 - Cadastro");
        printf("\n2 - Busca");
        printf("\n3 - Editar");
        printf("\n4 - Excluir");
        printf("\n0 - Sair");
        printf("\nEscolha: ");
        scanf("%d", &op);
        system("cls");
        getchar();

        switch (op) {
        case 1:
                cadastroDeClientes();
            break;
        case 2:
                buscaDeCadastros();
            break;
        case 0:
                printf("\nEcerrando...");
            break;
        default:
                printf("\nERRO: escolha uma opcao valida!\n");
            break;
        }
        
    } while (op != 0);

    return 0;
}

// TERMINA AQUI O MAIN DO PROGRAMA INTEIRO DO PROJETO --------------------------------------------