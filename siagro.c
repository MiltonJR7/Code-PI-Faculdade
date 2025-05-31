#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>
#include <Windows.h>

#define MAXSTR 100

// STRUCTS PARA O PROJETO INTEIRO --------------------------------------------
typedef struct {
    int dia, mes, ano;
    int dataVendaDia, dataVendaMes, dataVendaAno;
} date;

typedef struct {
    char nome[MAXSTR], email[MAXSTR], cpf[12], telefone[12];
    date D;
} clientesPF;

typedef struct {
    char nomeEmpresarial[MAXSTR], nomeDoResponsavel[MAXSTR],emailEmpresarial[MAXSTR], cnpj[15], telefoneEmpresarial[12];
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
    char tipoServico[MAXSTR], descricao[MAXSTR];
    float preco;
    char id[10];
    date D;
} servicos;

typedef struct {
    char cpfVenda[12], cnpjVenda[15], codigoVenda[20], IDServico[10];
    int quantDesejada, formaPagamento;
    float precoParaPagar, precoFinalPagar;
    date D;
} vendas;

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

void salvarVendas(vendas V) {
    FILE *arqVen = fopen("arqVendas.bin", "ab+");

    if(arqVen == NULL) {
        printf("\nERRO: impossivel acessar o arquivo!\n");
    }

    fwrite(&V, sizeof(vendas), 1, arqVen);
    fclose(arqVen);
}

// TERMINA AQUI AS FUNCOES DE SALVAR EM ARQUIVOS BINARIOS --------------------------------------------
// FUNCOES DE VALIDAR CPF E CNPJ EM ARQUIVOS BINARIOS --------------------------------------------

int validarCPF(FILE *arqPF, char cpf[]) {
    clientesPF PF;

    rewind(arqPF);
    while (fread(&PF, sizeof(clientesPF), 1, arqPF) == 1) {
        if (stricmp(cpf, PF.cpf) == 0) {
            return (ftell(arqPF) - sizeof(clientesPF));
        }
    }

    return -1;
}

int validarCNPJ(FILE *arqPJ, char cnpj[]) {
    clientesPJ PJ;

    rewind(arqPJ);
    while (fread(&PJ, sizeof(clientesPJ), 1, arqPJ) == 1) {
        if (stricmp(cnpj, PJ.cnpj) == 0) {
            return(ftell(arqPJ) - sizeof(clientesPJ));
        }
    }

    return -1;
}

int validarMaquinario(FILE *arqMaq, char codigo[]) {
    maquinarios M;

    rewind(arqMaq);
    while (fread(&M, sizeof(maquinarios), 1, arqMaq) == 1) {
        if(stricmp(codigo, M.codigo) == 0) {
            return(ftell(arqMaq) - sizeof(maquinarios));
        }
    }
    
    return -1;
}

int validarPecas(FILE *arqPec, char codigo[]) {
    pecas P;

    rewind(arqPec);
    while (fread(&P, sizeof(pecas), 1, arqPec) == 1) {
        if(stricmp(codigo, P.codigo) == 0) {
            return(ftell(arqPec) - sizeof(pecas));
        }
    }

    return -1;
}

int validarSerCadPF(FILE *arqPF, char cpfParaContrato[]) {
    clientesPF PF;

    rewind(arqPF);
    while (fread(&PF, sizeof(clientesPF), 1, arqPF) == 1) {
        if (stricmp(cpfParaContrato, PF.cpf) == 0) {
            return(ftell(arqPF) - sizeof(clientesPF));
        }
    }
    
    return -1;
}

int validarSerCadPJ(FILE *arqPJ, char cnpjParaContrato[]) {
    clientesPJ PJ;

    rewind(arqPJ);
    while (fread(&PJ, sizeof(clientesPJ), 1, arqPJ) == 1) {
        if (stricmp(cnpjParaContrato, PJ.cnpj) == 0) {
            return(ftell(arqPJ) - sizeof(clientesPJ));
        }
    }

    return -1;
}

int validarVendasPF(FILE *arqVen, char cpf[]) {
    vendas V;

    rewind(arqVen);
    while (fread(&V, sizeof(vendas), 1, arqVen) == 1) {
        if(stricmp(cpf, V.cpfVenda) == 0) {
            return(ftell(arqVen) - sizeof(vendas));
        }
    }

    return -1;
}

int validarVendasPJ(FILE *arqVen, char cnpj[]) {
    vendas V;

    rewind(arqVen);
    while (fread(&V, sizeof(vendas), 1, arqVen) == 1) {
        if(stricmp(cnpj, V.cnpjVenda) == 0) {
            return(ftell(arqVen) - sizeof(vendas));
        }
    }

    return -1;
}

int validarID(FILE *arqSer, char id[]) {
    servicos S;

    rewind(arqSer);
    while (fread(&S, sizeof(servicos), 1, arqSer) == 1) {
        if (stricmp(id, S.id) == 0) {
            return(ftell(arqSer) - sizeof(servicos));
        }
    }

    return -1;
}

void limparBuffer() {
    while (getchar() != '\n');
}

int validarData(vendas V) {
    if(V.D.dataVendaAno > 2025)
        return 1;

    if(V.D.dataVendaAno == 2025 && V.D.dataVendaMes > 5)
        return 1;

    if(V.D.dataVendaAno == 2025 && V.D.dataVendaMes == 5 && V.D.dataVendaDia > 30)
        return 1;
    
    return 0;
}

// TERMINA AQUI AS FUNCOES DE VALIDAR CPF E CNPJ EM ARQUIVOS BINARIOS --------------------------------------------
// INICIO DA FUNCAO DE CADASTROS ---------------------------------------------------------------------------------

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
    FILE *arqVen = fopen("arqVendas.bin", "rb+");

    int op, op2, op3, posCPF, posCNPJ, posMaq, posPec, posID;

    if (arqPF == NULL) {
        arqPF = fopen("arqPF.bin", "wb+");
        if (arqPF == NULL) {
            printf("\nERRO ao criar o arquivo de clientes PF!");
            return;
    	}
	}

	if (arqPJ == NULL) {
	    arqPJ = fopen("arqPJ.bin", "wb+");
	    if (arqPJ == NULL) {
	        printf("\nERRO ao criar o arquivo de clientes PJ!");
	        return;
	    }
	}

	if (arqMaq == NULL) {
	    arqMaq = fopen("arqMaquinario.bin", "wb+");
	    if (arqMaq == NULL) {
	        printf("\nERRO ao criar o arquivo de maquinarios!");
	        return;
	    }
	}

	if (arqPec == NULL) {
	    arqPec = fopen("arqPecas.bin", "wb+");
	    if (arqPec == NULL) {
	        printf("\nERRO ao criar o arquivo de pecas!");
	        return;
	    }
	}
	
	if (arqSer == NULL) {
	    arqSer = fopen("arqServicos.bin", "wb+");
	    if (arqSer == NULL) {
	        printf("\nERRO ao criar o arquivo de servicos!");
	        return;
	    }
	}

    if (arqVen == NULL) {
        arqVen = fopen("arqVendas.bin", "wb+");
	    if (arqVen == NULL) {
	        printf("\nERRO ao criar o arquivo de venda!");
	        return;
	    }
    }

    do {
        system("cls");
        printf("\n--- CADASTROS ---\n");
        printf("\n1 - Clientes");
        printf("\n2 - Produtos");
        printf("\n3 - Servicos");
        printf("\n0 - Retornar ao menu");
        printf("\nEscolha: ");
        scanf("%d", &op);
        getchar();

        switch (op) {
        case 1:
                do {
                    system("cls");
                    printf("\n--- CADASTRO DE CLIENTES ---\n");
                    printf("\n1 - Clientes PF");
                    printf("\n2 - Clientes PJ");
                    printf("\n0 - Retornar");
                    printf("\nEscolha: ");
                    scanf("%d", &op2);
                    getchar();

                    switch (op2) {
                    case 1:
                            do {
                                system("cls");
                                printf("\n--- CLIENTES PF ---\n");
                                printf("\nSeu cpf: ");
                                scanf("%11s", PF.cpf);
                                limparBuffer();

                                posCPF = validarCPF(arqPF, PF.cpf);

                                if (posCPF == -1) {
                                    printf("\nSeu nome: ");
                                    fgets(PF.nome, MAXSTR, stdin);
                                    PF.nome[strcspn(PF.nome, "\n")] = '\0';

                                    printf("\nSeu email: ");
                                    fgets(PF.email, MAXSTR, stdin);
                                    PF.email[strcspn(PF.email, "\n")] = '\0';

                                    printf("\nSeu telefone: ");
                                    scanf("%11s", PF.telefone);
                                    limparBuffer();

                                    do {
                                        printf("\nSua data de nascimento <dd mm aaaa>: ");
                                        scanf("%d%d%d", &PF.D.dia, &PF.D.mes, &PF.D.ano);
                                        getchar();
                                    } while (PF.D.dia < 1 || PF.D.dia > 31 || PF.D.mes < 1 || PF.D.mes > 12 || PF.D.ano > 2025);
                                    

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
                                system("cls");
                                printf("\n--- CLIENTES PJ ---\n");
                                printf("\nDigite seu cnpj: ");
                                scanf("%14s", PJ.cnpj);
                                limparBuffer();

                                posCNPJ = validarCNPJ(arqPJ, PJ.cnpj);
                                
                                if (posCNPJ == -1) {
                                    printf("\nO nome empresarial: ");
                                    fgets(PJ.nomeEmpresarial, MAXSTR, stdin);
                                    PJ.nomeEmpresarial[strcspn(PJ.nomeEmpresarial, "\n")] = '\0';

                                    printf("\nO email empresarial: ");
                                    fgets(PJ.emailEmpresarial, MAXSTR, stdin);
                                    PJ.emailEmpresarial[strcspn(PJ.emailEmpresarial, "\n")] = '\0';

                                    printf("\nO nome do responsavel: ");
                                    fgets(PJ.nomeDoResponsavel, MAXSTR, stdin);
                                    PJ.nomeDoResponsavel[strcspn(PJ.nomeDoResponsavel, "\n")] = '\0';

                                    printf("\nO telefone empresarial: ");
                                    scanf("%11s", PJ.telefoneEmpresarial);
                                    limparBuffer();
                                    
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
                    system("cls");
                    printf("\n--- CADASTRO DE PRODUTOS ---\n");
                    printf("\n1 - Maquinario");
                    printf("\n2 - Pecas");
                    printf("\n0 - Retornar");
                    printf("\nEscolha: ");
                    scanf("%d", &op2);
                    getchar();

                    switch (op2) {
                    case 1:
                            do {
                                system("cls");
                                printf("\n--- MAQUINARIOS ---\n");
                                printf("\nDigite o codigo do maquinario: ");
                                scanf("%19s", M.codigo);
                                limparBuffer();

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
                                system("cls");
                                printf("\n--- PECAS ---\n");
                                printf("\nDigite o codigo da peca: ");
                                scanf("%19s", P.codigo);
                                limparBuffer();

                                posPec = validarPecas(arqPec, P.codigo);

                                if(posPec == -1) {
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
                                    printf("\nPeca cadastrado com sucesso!\n\n");
                                } else {
                                    pecas PEC_ja_cadastrado;
                                    fseek(arqPec, posPec, 0);
                                    fread(&PEC_ja_cadastrado, sizeof(pecas), 1, arqPec);
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
                    system("cls");
                    printf("\n--- CADASTRO DE SERVICOS ---\n");
                    printf("\n1 - Cadastrar servicos");
                    printf("\n0 - Retornar");
                    printf("\nEscolha: ");
                    scanf("%d", &op3);
                    getchar();

                    switch (op3) {
                    case 1:
                            do {
                                system("cls");
                                printf("\n--- CADASTRO DE SERVICOS ---\n");
                                printf("\nDigite o id: ");
                                scanf("%9s", S.id);
                                limparBuffer();

                                posID = validarID(arqSer, S.id);

                                if(posID == -1) {
                                    printf("\nQual o tipo de servico: ");
                                    fgets(S.tipoServico, MAXSTR, stdin);
                                    S.tipoServico[strcspn(S.tipoServico, "\n")] = '\0';

                                    printf("\nQual a descricao: ");
                                    fgets(S.descricao, MAXSTR, stdin);
                                    S.descricao[strcspn(S.descricao, "\n")] = '\0';

                                    printf("\nQual o preco do servico: ");
                                    scanf("%f", &S.preco);
                                    getchar();

                                    salvarServico(S);
                                    printf("\nServico cadastrado com sucesso!\n\n");
                                } else {
                                    printf("\nERRO: o ID digitado ja esta vinculado a um servico!");
                                    printf("\n");
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
                } while (op3 != 0);
            break;

        case 0:
                printf("\nRetornando...\n");
            break;
        default:
                printf("\nERRO: escolha uma opcao valida!\n");
            break;
        }
    } while (op != 0);

    fclose(arqPF);
    fclose(arqPJ);
    fclose(arqMaq);
    fclose(arqPec);
    fclose(arqSer);
    fclose(arqVen);
}

// FIM DA FUNCAO DE CADASTROS -----------------------------------------------------------------------
// INICIO DA FUNCAO DE BUSCA ------------------------------------------------------------------------

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

    char buscCpf[12], buscCnpj[15], buscCodMaq[20], buscCodPec[20], buscID[10];
    int op, op2, op3, posID, posPF, posPJ, posMaq, posPec;
    
   if (arqPF == NULL) {
    arqPF = fopen("arqPF.bin", "wb+");
    if (arqPF == NULL) {
        printf("\nERRO ao criar o arquivo de clientes PF!");
        return;
    	}
	}

	if (arqPJ == NULL) {
	    arqPJ = fopen("arqPJ.bin", "wb+");
	    if (arqPJ == NULL) {
	        printf("\nERRO ao criar o arquivo de clientes PJ!");
	        return;
	    }
	}

	if (arqMaq == NULL) {
	    arqMaq = fopen("arqMaquinario.bin", "wb+");
	    if (arqMaq == NULL) {
	        printf("\nERRO ao criar o arquivo de maquinarios!");
	        return;
	    }
	}

	if (arqPec == NULL) {
	    arqPec = fopen("arqPecas.bin", "wb+");
	    if (arqPec == NULL) {
	        printf("\nERRO ao criar o arquivo de pecas!");
	        return;
	    }
	}
	
	if (arqSer == NULL) {
	    arqSer = fopen("arqServicos.bin", "wb+");
	    if (arqSer == NULL) {
	        printf("\nERRO ao criar o arquivo de servicos!");
	        return;
	    }
	}

    do {
        system("cls");
        printf("\n--- BUSCA ---\n");
        printf("\n1 - Clientes");
        printf("\n2 - Produtos");
        printf("\n3 - Servicos");
        printf("\n0 - Retornar ao menu");
        printf("\nEscolha: ");
        scanf("%d", &op);
        getchar();

        switch (op) {
        case 1:
                do {
                    system("cls");
                    printf("\n--- BUSCA DE CLIENTES ---\n");
                    printf("\n1 - Clientes PF");
                    printf("\n2 - Clientes PJ");
                    printf("\n0 - Retornar");
                    printf("\nEscolha: ");
                    scanf("%d", &op2);
                    getchar();

                    switch (op2) {
                    case 1:
                            system("cls");
                            printf("\n--- CLIENTES PF ---\n");
                            printf("\nUse o cpf para buscar: ");
                            scanf("%11s", buscCpf);
                            limparBuffer();

                            posPF = validarCPF(arqPF, buscCpf);

                            if(posPF == -1) {
                                printf("\nERRO: o cpf digitado nao esta cadastrado!\n");
                                system("pause");
                            } else {
                                fseek(arqPF, posPF, SEEK_SET);
                                fread(&PF, sizeof(clientesPF), 1, arqPF);

                                printf("\nDados do Cliente: ");
                                printf("\n----------------");
                                printf("\nNome: %s", PF.nome);
                                printf("\nTelefone: (%.2s) %.5s-%.4s", PF.telefone, PF.telefone+2, PF.telefone+7);
                                printf("\nEmail: %s", PF.email);
                                printf("\nData de nascimento: %02d/%02d/%04d", PF.D.dia, PF.D.mes, PF.D.ano);
                                printf("\n----------------\n");
                                system("pause");
                            }
                        break;
                    case 2:
                            system("cls");
                            printf("\n--- CLIENTES PJ ---\n");
                            printf("\nUse o cnpj para buscar: ");
                            scanf("%14s", buscCnpj);
                            limparBuffer();

                            posPJ = validarCNPJ(arqPJ, buscCnpj);

                            if(posPJ == -1) {
                                printf("\nERRO: o cnpj digitado nao esta cadastrado!\n");
                                system("pause");
                            } else {
                                fseek(arqPJ, posPJ, SEEK_SET);
                                fread(&PJ, sizeof(clientesPJ), 1, arqPJ);

                                printf("\nDados do Cliente: ");
                                printf("\n----------------");
                                printf("\nNome empresarial: %s", PJ.nomeEmpresarial);
                                printf("\nFone: (%.2s) %.5s-%.4s", PJ.telefoneEmpresarial, PJ.telefoneEmpresarial+2, PJ.telefoneEmpresarial+7);
                                printf("\nEmail: %s", PJ.emailEmpresarial);
                                printf("\nNome do responsavel: %s", PJ.nomeDoResponsavel);
                                printf("\n----------------\n");
                                system("pause");
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
                    system("cls");
                    printf("\n--- BUSCA DE PRODUTOS ---\n");
                    printf("\n1 - Maquinario");
                    printf("\n2 - Pecas");
                    printf("\n0 - Retornar");
                    printf("\nEscolha: ");
                    scanf("%d", &op2);
                    getchar();

                    switch (op2) {
                    case 1:
                            system("cls");
                            printf("\n--- MAQUINARIOS ---\n");
                            printf("\nUse o codigo para buscar: ");
                            scanf("%19s", buscCodMaq);
                            limparBuffer();

                            posMaq = validarMaquinario(arqMaq, buscCodMaq);

                            if(posMaq == -1) {
                                printf("\nERRO: o codigo do maquinario digitado nao esta cadastrado!\n");
                                system("pause");
                            } else {
                                fseek(arqMaq, posMaq, SEEK_SET);
                                fread(&M, sizeof(maquinarios), 1, arqMaq);

                                printf("\nDados do Maquinario: ");
                                printf("\n----------------");
                                printf("\nNome do maquinario: %s", M.nome);
                                printf("\nCategoria: %s", M.categoria);
                                printf("\nQuantidade: %d", M.quantidade);
                                printf("\nPreco: %.2f", M.preco);
                                printf("\n----------------\n");
                                system("pause");
                            }
                        break;
                    case 2:
                            system("cls");
                            printf("\n--- PECAS ---\n");
                            printf("\nUse o codigo para buscar: ");
                            scanf("%19s", buscCodPec);
                            limparBuffer();

                            posPec = validarPecas(arqPec, buscCodPec);

                            if (posPec == -1) {
                                printf("\nERRO: o codigo da pecas digitado nao esta cadastrado!\n");
                                system("pause");
                            } else {
                                fseek(arqPec, posPec, SEEK_SET);
                                fread(&P, sizeof(pecas), 1, arqPec);

                                printf("\nDados da Peca: ");
                                printf("\n----------------");
                                printf("\nNome da peca: %s", P.nome);
                                printf("\nCategoria: %s", P.categoria);
                                printf("\nQuantidade: %d", P.quantidade);
                                printf("\nPreco: %.2f", P.preco);
                                printf("\n----------------\n");
                                system("pause");
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
                    system("cls");
                    printf("\n--- BUSCA DE SERVICOS ---\n");
                    printf("\n1 - Buscar por ID");
                    printf("\n0 - Retornar");
                    printf("\nEscolha: ");
                    scanf("%d", &op3);
                    getchar();

                    switch (op3) {
                    case 1:
                            system("cls");
                            printf("\n--- BUSCA DE SERVICOS POR ID ---\n");
                            printf("\nDigite o ID para buscar: ");
                            scanf("%9s", buscID);
                            limparBuffer();

                            posID = validarID(arqSer, buscID);

                            if(posID == -1) {
                                printf("\nERRO: o id digitado nao esta vinculado a um servico!\n");
                                system("pause");
                            } else {
                                fseek(arqSer, posID, SEEK_SET);
                                fread(&S, sizeof(servicos), 1, arqSer);

                                printf("\nDados do Servico: ");
                                printf("\n----------------");
                                printf("\nID do servico: %s", S.id);
                                printf("\nTipo do servico: %s", S.tipoServico);
                                printf("\nDescricao: %s", S.descricao);
                                printf("\nPreco: %.2f", S.preco);
                                printf("\n----------------\n");

                                system("pause");
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
            break;
        case 0:
                printf("\nRetornando...\n");
            break;
        default:
                printf("\nERRO: escolha uma opcao valida!\n");
            break;
        }    
    } while (op != 0);

    fclose(arqPF);
    fclose(arqPJ);
    fclose(arqMaq);
    fclose(arqPec);
    fclose(arqSer);
}

// FIM DA FUNCAO DE BUSCAS ------------------------------------------------------------------------------------------
// INICIO DA FUNCAO DE EDITAR ---------------------------------------------------------------------------------------

void editarCadastros() {
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

    int op, op2, op3, posCPF, posCNPJ, posMaq, posPec, posID;

    do {
        system("cls");
        printf("\n--- EDICAO ---\n");
        printf("\n1 - Clientes");
        printf("\n2 - Produtos");
        printf("\n3 - Servicos");
        printf("\n0 - Retornar ao menu");
        printf("\nEscolha: ");
        scanf("%d", &op);
        getchar();

        switch (op) {
        case 1:
            do {
                system("cls");
                printf("\n--- EDICAO DE CLIENTES ---\n");
                printf("\n1 - Clientes PF");
                printf("\n2 - Clientes PJ");
                printf("\n0 - Retornar");
                printf("\nEscolha: ");
                scanf("%d", &op2);
                getchar();

                switch (op2) {
                case 1:
                        do {
                            system("cls");
                            printf("\n--- EDITAR CLIENTES PF ---\n");
                            printf("\nInforme o CPF do cliente para as alteracoes: ");
                            scanf("%11s", PF.cpf);
                            limparBuffer();

                            posCPF = validarCPF(arqPF, PF.cpf);

                            if (posCPF == -1) {
                                printf("\nERRO: CPF nao encontrado!\n");
                                system("pause");
                            } else {
                                fseek(arqPF, posCPF, SEEK_SET);
                                fread(&PF, sizeof(clientesPF), 1, arqPF);

                                printf("\nDados do Cliente: ");
                                printf("\n----------------");
                                printf("\nNome: %s", PF.nome);
                                printf("\nTelefone: (%.2s) %.5s-%.4s", PF.telefone, PF.telefone+2, PF.telefone+7);
                                printf("\nEmail: %s", PF.email);
                                printf("\nData de nascimento: %02d/%02d/%04d", PF.D.dia, PF.D.mes, PF.D.ano);
                                printf("\n----------------\n");

                                do {
                                    printf("\nDeseja alterar: \n 1- TELEFONE \n 2- EMAIL \n 0- SAIR DA EDICAO DESTE CLIENTE");
                                    printf("\nEscolha: ");
                                    scanf("%d", &op2);
                                    getchar();

                                    switch (op2) {
                                        case 1:
                                                system("cls");
                                                printf("\nNovo telefone: ");
                                                scanf("%11s", PF.telefone);
                                                limparBuffer();

                                                fseek(arqPF, posCPF, SEEK_SET);
                                                fwrite(&PF, sizeof(clientesPF), 1, arqPF);
                                                printf("\nTelefone salvo!\n");

                                                fseek(arqPF, posCPF, SEEK_SET);
                                                fread(&PF, sizeof(clientesPF), 1, arqPF);

                                                printf("\nDados do Cliente alterado: ");
                                                printf("\n----------------");
                                                printf("\nNome: %s", PF.nome);
                                                printf("\nTelefone: (%.2s) %.5s-%.4s", PF.telefone, PF.telefone+2, PF.telefone+7);
                                                printf("\nEmail: %s", PF.email);
                                                printf("\nData de nascimento: %02d/%02d/%04d", PF.D.dia, PF.D.mes, PF.D.ano);
                                                printf("\n----------------\n");

                                            break;

                                        case 2:
                                                system("cls");
                                                printf("\nNovo email: ");
                                                fgets(PF.email, MAXSTR, stdin);
                                                PF.email[strcspn(PF.email, "\n")] = '\0';

                                                fseek(arqPF, posCPF, SEEK_SET);
                                                fwrite(&PF, sizeof(clientesPF), 1, arqPF);
                                                printf("\nEmail salvo!\n");

                                                fseek(arqPF, posCPF, SEEK_SET);
                                                fread(&PF, sizeof(clientesPF), 1, arqPF);

                                                printf("\nDados do Cliente alterado: ");
                                                printf("\n----------------");
                                                printf("\nNome: %s", PF.nome);
                                                printf("\nTelefone: (%.2s) %.5s-%.4s", PF.telefone, PF.telefone+2, PF.telefone+7);
                                                printf("\nEmail: %s", PF.email);
                                                printf("\nData de nascimento: %02d/%02d/%04d", PF.D.dia, PF.D.mes, PF.D.ano);
                                                printf("\n----------------\n");

                                            break;
                                        case 0:
                                            printf("\nSaindo da edicao deste cliente...\n");
                                            break;

                                        default:
                                            printf("\nERRO: escolha uma opcao valida!\n");
                                            break;
                                    }
                                } while (op2 != 0);
                            }
                            printf("\nDeseja editar outro Cliente? (S/N): ");
                        } while (toupper(getche()) == 'S');
                    break;
                break;
                case 2:
                        do {
                            system("cls");
                            printf("\n--- EDITAR CLIENTES PJ ---\n");
                            printf("\nInforme o CNPJ do cliente para as alteracoes: ");
                            scanf("%14s", PJ.cnpj);
                            limparBuffer();

                            posCNPJ = validarCNPJ(arqPJ, PJ.cnpj);

                            if (posCNPJ == -1) {
                                printf("\nERRO: CNPJ nao encontrado!\n");
                                system("pause");
                            } else {
                                fseek(arqPJ, posCNPJ, SEEK_SET);
                                fread(&PJ, sizeof(clientesPJ), 1, arqPJ);

                                printf("\nDados do Cliente: ");
                                printf("\n----------------");
                                printf("\nNome empresarial: %s", PJ.nomeEmpresarial);
                                printf("\nFone: (%.2s) %.5s-%.4s", PJ.telefoneEmpresarial, PJ.telefoneEmpresarial+2, PJ.telefoneEmpresarial+7);
                                printf("\nEmail: %s", PJ.emailEmpresarial);
                                printf("\nNome do responsavel: %s", PJ.nomeDoResponsavel);
                                printf("\n----------------\n");

                                do {
                                    printf("\nDeseja alterar: \n 1- NOME EMPRESARIAL \n 2- TELEFONE \n 3- EMAIL \n 4- NOME DO RESPONSAVEL \n 0- SAIR DA EDICAO DESTE CLIENTE");
                                    printf("\nEscolha: ");
                                    scanf("%d", &op2);
                                    getchar();

                                    switch (op2) {
                                        case 1:
                                                system("cls");
                                                printf("\nNovo nome empresarial: ");
                                                fgets(PJ.nomeEmpresarial, MAXSTR, stdin);
                                                PJ.nomeEmpresarial[strcspn(PJ.nomeEmpresarial, "\n")] = '\0';

                                                fseek(arqPJ, posCNPJ, SEEK_SET);
                                                fwrite(&PJ, sizeof(clientesPJ), 1, arqPJ);
                                                printf("\nNome empresarial salvo!\n");

                                                fseek(arqPJ, posCNPJ, SEEK_SET);
                                                fread(&PJ, sizeof(clientesPJ), 1, arqPJ);

                                                printf("\nDados do Cliente alterado: ");
                                                printf("\n----------------");
                                                printf("\nNome empresarial: %s", PJ.nomeEmpresarial);
                                                printf("\nFone: (%.2s) %.5s-%.4s", PJ.telefoneEmpresarial, PJ.telefoneEmpresarial+2, PJ.telefoneEmpresarial+7);
                                                printf("\nEmail: %s", PJ.emailEmpresarial);
                                                printf("\nNome do responsavel: %s", PJ.nomeDoResponsavel);
                                                printf("\n----------------\n");

                                            break;

                                        case 2:
                                                system("cls");
                                                printf("\nNovo telefone: ");
                                                scanf("%11s", PJ.telefoneEmpresarial);
                                                limparBuffer();

                                                fseek(arqPJ, posCNPJ, SEEK_SET);
                                                fwrite(&PJ, sizeof(clientesPJ), 1, arqPJ);
                                                printf("\nTelefone salvo!\n");

                                                fseek(arqPJ, posCNPJ, SEEK_SET);
                                                fread(&PJ, sizeof(clientesPJ), 1, arqPJ);

                                                printf("\nDados do Cliente alterado: ");
                                                printf("\n----------------");
                                                printf("\nNome empresarial: %s", PJ.nomeEmpresarial);
                                                printf("\nFone: (%.2s) %.5s-%.4s", PJ.telefoneEmpresarial, PJ.telefoneEmpresarial+2, PJ.telefoneEmpresarial+7);
                                                printf("\nEmail: %s", PJ.emailEmpresarial);
                                                printf("\nNome do responsavel: %s", PJ.nomeDoResponsavel);
                                                printf("\n----------------\n");

                                            break;
                                        case 3:
                                                system("cls");
                                                printf("\nNovo email: ");
                                                fgets(PJ.emailEmpresarial, MAXSTR, stdin);
                                                PJ.emailEmpresarial[strcspn(PJ.emailEmpresarial, "\n")] = '\0';

                                                fseek(arqPJ, posCNPJ, SEEK_SET);
                                                fwrite(&PJ, sizeof(clientesPJ), 1, arqPJ);                              
                                                printf("\nEmail salvo!\n");

                                                fseek(arqPJ, posCNPJ, SEEK_SET);
                                                fread(&PJ, sizeof(clientesPJ), 1, arqPJ);

                                                printf("\nDados do Cliente alterado: ");
                                                printf("\n----------------");
                                                printf("\nNome empresarial: %s", PJ.nomeEmpresarial);
                                                printf("\nFone: (%.2s) %.5s-%.4s", PJ.telefoneEmpresarial, PJ.telefoneEmpresarial+2, PJ.telefoneEmpresarial+7);
                                                printf("\nEmail: %s", PJ.emailEmpresarial);
                                                printf("\nNome do responsavel: %s", PJ.nomeDoResponsavel);
                                                printf("\n----------------\n");

                                            break;
                                        case 4:
                                                system("cls");
                                                printf("\nNovo nome do responsavel: ");
                                                fgets(PJ.nomeDoResponsavel, MAXSTR, stdin);
                                                PJ.nomeDoResponsavel[strcspn(PJ.nomeDoResponsavel, "\n")] = '\0';

                                                fseek(arqPJ, posCNPJ, SEEK_SET);
                                                fwrite(&PJ, sizeof(clientesPJ), 1, arqPJ);
                                                printf("\nNome do responsavel salvo!\n");

                                                fseek(arqPJ, posCNPJ, SEEK_SET);
                                                fread(&PJ, sizeof(clientesPJ), 1, arqPJ);

                                                printf("\nDados do Cliente alterado: ");
                                                printf("\n----------------");
                                                printf("\nNome empresarial: %s", PJ.nomeEmpresarial);
                                                printf("\nFone: (%.2s) %.5s-%.4s", PJ.telefoneEmpresarial, PJ.telefoneEmpresarial+2, PJ.telefoneEmpresarial+7);
                                                printf("\nEmail: %s", PJ.emailEmpresarial);
                                                printf("\nNome do responsavel: %s", PJ.nomeDoResponsavel);
                                                printf("\n----------------\n");

                                            break;
                                        case 0:
                                            printf("\nSaindo da edicao deste cliente...\n");
                                            break;

                                        default:
                                            printf("\nERRO: escolha uma opcao valida!\n");
                                            break;
                                    }
                                } while (op2 != 0);
                            }
                            printf("\nDeseja editar outro Cliente? (S/N): ");
                        } while (toupper(getche()) == 'S');
                    break;
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
                system("cls");
                printf("\n--- EDICAO DE PRODUTOS ---\n");
                printf("\n1 - Maquinario");
                printf("\n2 - Pecas");
                printf("\n0 - Retornar");
                printf("\nEscolha: ");
                scanf("%d", &op2);
                getchar();

                switch (op2) {
                case 1:
                        do {
                            system("cls");
                            printf("\n--- EDITAR MAQUINARIO ---\n");
                            printf("\nInforme o CODIGO do maquinario para as alteracoes: ");
                            scanf("%19s", M.codigo);
                            limparBuffer();

                            posMaq = validarMaquinario(arqMaq, M.codigo);

                            if (posMaq == -1) {
                                printf("\nERRO: CODIGO nao encontrado!\n");
                                system("pause");
                            } else {
                                fseek(arqMaq, posMaq, SEEK_SET);
                                fread(&M, sizeof(maquinarios), 1, arqMaq);

                                printf("\nDados do Maquinario: ");
                                printf("\n----------------");
                                printf("\nNome do maquinario: %s", M.nome);
                                printf("\nCategoria: %s", M.categoria);
                                printf("\nQuantidade: %d", M.quantidade);
                                printf("\nPreco: %.2f", M.preco);
                                printf("\n----------------\n");

                                do {
                                    printf("\nDeseja alterar: \n 1- NOME \n 2- CATEGORIA \n 3- QUANTIDADE \n 4- PRECO \n0- SAIR DA EDICAO DESTE MAQUINARIO");
                                    printf("\nEscolha: ");
                                    scanf("%d", &op2);
                                    getchar();

                                    switch (op2) {
                                        case 1:
                                                system("cls");
                                                printf("\nNovo nome do maquinario: ");
                                                fgets(M.nome, MAXSTR, stdin);
                                                M.nome[strcspn(M.nome, "\n")] = '\0';

                                                fseek(arqMaq, posMaq, SEEK_SET);
                                                fwrite(&M, sizeof(maquinarios), 1, arqMaq);
                                                printf("\nNome do maquinario salvo!\n");

                                                fseek(arqMaq, posMaq, SEEK_SET);
                                                fread(&M, sizeof(maquinarios), 1, arqMaq);

                                                printf("\nDados do Maquinario alterado: ");
                                                printf("\n----------------");
                                                printf("\nNome do maquinario: %s", M.nome);
                                                printf("\nCategoria: %s", M.categoria);
                                                printf("\nQuantidade: %d", M.quantidade);
                                                printf("\nPreco: %.2f", M.preco);
                                                printf("\n----------------\n");

                                            break;

                                        case 2:
                                                system("cls");
                                                printf("\nNova categoria: ");
                                                fgets(M.categoria, MAXSTR, stdin);
                                                M.categoria[strcspn(M.categoria, "\n")] = '\0';

                                                fseek(arqMaq, posMaq, SEEK_SET);
                                                fwrite(&M, sizeof(maquinarios), 1, arqMaq); 
                                                printf("\nCategoria do maquinario salvo!\n");

                                                fseek(arqMaq, posMaq, SEEK_SET);
                                                fread(&M, sizeof(maquinarios), 1, arqMaq);
                                                
                                                printf("\nDados do Maquinario alterado: ");
                                                printf("\n----------------");
                                                printf("\nNome do maquinario: %s", M.nome);
                                                printf("\nCategoria: %s", M.categoria);
                                                printf("\nQuantidade: %d", M.quantidade);
                                                printf("\nPreco: %.2f", M.preco);
                                                printf("\n----------------\n");

                                            break;
                                        case 3:
                                                system("cls");
                                                printf("\nNova quantidade: ");
                                                scanf("%d", &M.quantidade);
                                                getchar();

                                                fseek(arqMaq, posMaq, SEEK_SET);
                                                fwrite(&M, sizeof(maquinarios), 1, arqMaq);
                                                printf("\nQuantidade do maquinario salvo!\n");

                                                fseek(arqMaq, posMaq, SEEK_SET);
                                                fread(&M, sizeof(maquinarios), 1, arqMaq);
                                                
                                                printf("\nDados do Maquinario alterado: ");
                                                printf("\n----------------");
                                                printf("\nNome do maquinario: %s", M.nome);
                                                printf("\nCategoria: %s", M.categoria);
                                                printf("\nQuantidade: %d", M.quantidade);
                                                printf("\nPreco: %.2f", M.preco);
                                                printf("\n----------------\n");

                                            break;
                                        case 4:
                                                system("cls");
                                                printf("\nNovo preco: ");
                                                scanf("%f", &M.preco);
                                                getchar();

                                                fseek(arqMaq, posMaq, SEEK_SET);
                                                fwrite(&M, sizeof(maquinarios), 1, arqMaq);
                                                printf("\nPreco do maquinario salvo!\n");

                                                fseek(arqMaq, posMaq, SEEK_SET);
                                                fread(&M, sizeof(maquinarios), 1, arqMaq);
                                                
                                                printf("\nDados do Maquinario alterado: ");
                                                printf("\n----------------");
                                                printf("\nNome do maquinario: %s", M.nome);
                                                printf("\nCategoria: %s", M.categoria);
                                                printf("\nQuantidade: %d", M.quantidade);
                                                printf("\nPreco: %.2f", M.preco);
                                                printf("\n----------------\n");
                                            break;
                                        case 0:
                                            printf("\nSaindo da edicao deste maquinario...\n");
                                            break;

                                        default:
                                            printf("\nERRO: escolha uma opcao valida!\n");
                                            break;
                                    }
                                } while (op2 != 0);
                            }
                            printf("\nDeseja editar outro Maquinario? (S/N): ");
                        } while (toupper(getche()) == 'S');
                    break;
                break;
                case 2:
                        do { 
                            system("cls");
                            printf("\n--- EDITAR PECAS ---\n");
                            printf("\nInforme o CODIGO da peca para as alteracoes: ");
                            scanf("%19s", P.codigo);
                            limparBuffer();

                            posPec = validarPecas(arqPec, P.codigo);

                            if (posPec == -1) {
                                printf("\nERRO: CODIGO nao encontrado!\n");
                                system("pause");
                            } else {
                                fseek(arqPec, posPec, SEEK_SET);
                                fread(&P, sizeof(pecas), 1, arqPec);

                                printf("\nDados da Peca: ");
                                printf("\n----------------");
                                printf("\nNome da peca: %s", P.nome);
                                printf("\nCategoria: %s", P.categoria);
                                printf("\nQuantidade: %d", P.quantidade);
                                printf("\nPreco: %.2f", P.preco);
                                printf("\n----------------\n");

                                do {
                                    printf("\nDeseja alterar: \n 1- NOME \n 2- CATEGORIA \n 3- QUANTIDADE \n 4- PRECO \n0- SAIR DA EDICAO DESTA PECA");
                                    printf("\nEscolha: ");
                                    scanf("%d", &op2);
                                    getchar();

                                    switch (op2) {
                                        case 1:
                                                system("cls");
                                                printf("\nNovo nome da peca: ");
                                                fgets(P.nome, MAXSTR, stdin);
                                                P.nome[strcspn(P.nome, "\n")] = '\0';

                                                fseek(arqPec, posPec, SEEK_SET);
                                                fwrite(&P, sizeof(pecas), 1, arqPec);
                                                printf("\nNome da peca salvo!\n");

                                                fseek(arqPec, posPec, SEEK_SET);
                                                fread(&P, sizeof(pecas), 1, arqPec);

                                                printf("\nDados da Peca alterado: ");
                                                printf("\n----------------");
                                                printf("\nNome da peca: %s", P.nome);
                                                printf("\nCategoria: %s", P.categoria);
                                                printf("\nQuantidade: %d", P.quantidade);
                                                printf("\nPreco: %.2f", P.preco);
                                                printf("\n----------------\n");

                                            break;

                                        case 2:
                                                system("cls");
                                                printf("\nNova categoria: ");
                                                fgets(P.categoria, MAXSTR, stdin);
                                                P.categoria[strcspn(P.categoria, "\n")] = '\0';

                                                fseek(arqPec, posPec, SEEK_SET);
                                                fwrite(&P, sizeof(pecas), 1, arqPec);
                                                printf("\nCategoria da peca salvo!\n");

                                                fseek(arqPec, posPec, SEEK_SET);
                                                fread(&P, sizeof(pecas), 1, arqPec);
                                                
                                                printf("\nDados da Peca alterado: ");
                                                printf("\n----------------");
                                                printf("\nNome da peca: %s", P.nome);
                                                printf("\nCategoria: %s", P.categoria);
                                                printf("\nQuantidade: %d", P.quantidade);
                                                printf("\nPreco: %.2f", P.preco);
                                                printf("\n----------------\n");

                                            break;
                                        case 3:
                                                system("cls");
                                                printf("\nNova quantidade: ");
                                                scanf("%d", &P.quantidade);
                                                getchar();

                                                fseek(arqPec, posPec, SEEK_SET);
                                                fwrite(&P, sizeof(pecas), 1, arqPec);
                                                printf("\nQuantidade da peca salvo!\n");

                                                fseek(arqPec, posPec, SEEK_SET);
                                                fread(&P, sizeof(pecas), 1, arqPec);
                                                
                                                printf("\nDados da Peca alterado: ");
                                                printf("\n----------------");
                                                printf("\nNome da peca: %s", P.nome);
                                                printf("\nCategoria: %s", P.categoria);
                                                printf("\nQuantidade: %d", P.quantidade);
                                                printf("\nPreco: %.2f", P.preco);
                                                printf("\n----------------\n");

                                            break;
                                        case 4:
                                                system("cls");
                                                printf("Novo preco: ");
                                                scanf("%f", &P.preco);
                                                getchar();

                                                fseek(arqPec, posPec, SEEK_SET);
                                                fwrite(&P, sizeof(pecas), 1, arqPec);
                                                printf("\nPreco da peca salvo!\n");

                                                fseek(arqPec, posPec, SEEK_SET);
                                                fread(&P, sizeof(pecas), 1, arqPec);
                                                
                                                printf("\nDados da Peca alterado: ");
                                                printf("\n----------------");
                                                printf("\nNome da peca: %s", P.nome);
                                                printf("\nCategoria: %s", P.categoria);
                                                printf("\nQuantidade: %d", P.quantidade);
                                                printf("\nPreco: %.2f", P.preco);
                                                printf("\n----------------\n");
                                            break;
                                        case 0:
                                            printf("\nSaindo da edicao desta peca...\n");
                                            break;

                                        default:
                                            printf("\nERRO: escolha uma opcao valida!\n");
                                            break;
                                    }
                                } while (op2 != 0);
                            }
                            printf("\nDeseja editar outra Peca? (S/N): ");
                        } while (toupper(getche()) == 'S');
                    break;
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
                system("cls");
                printf("\n--- EDICAO DE SERVICOS ---\n");
                printf("\n1 - Buscar por ID: ");
                printf("\n0 - Retornar");
                printf("\nEscolha: ");
                scanf("%d", &op3);
                getchar();

                switch (op3) {
                case 1:
                        do {
                            system("cls");
                            printf("\n--- EDITAR SERVICO POR ID ---\n");
                            printf("\nInforme o ID para as alteracoes em servico: ");
                            scanf("%9s", S.id);
                            limparBuffer();

                            posID = validarID(arqSer, S.id);

                            if (posID == -1) {
                                printf("\nERRO: o id digitado nao esta vinculado a um servico!\n");
                                system("pause");
                            } else {
                                fseek(arqSer, posID, SEEK_SET);
                                fread(&S, sizeof(servicos), 1, arqSer);

                                printf("\nDados do Servico: ");
                                printf("\n----------------");
                                printf("\nTipo do servico: %s", S.tipoServico);
                                printf("\nDescricao: %s", S.descricao);
                                printf("\nPreco: %.2f", S.preco);
                                printf("\n----------------\n");

                                do {
                                    printf("\nDeseja alterar: \n 1- TIPO \n 2- DESCRICAO \n 3- PRECO \n0- SAIR DA EDICAO DESTE SERVICO");
                                    printf("\nEscolha: ");
                                    scanf("%d", &op2);
                                    getchar();

                                    switch (op2) {
                                        case 1:
                                                system("cls");
                                                printf("\nNovo tipo do servico: ");
                                                fgets(S.tipoServico, MAXSTR, stdin);
                                                S.tipoServico[strcspn(S.tipoServico, "\n")] = '\0';

                                                fseek(arqSer, posID, SEEK_SET);
                                                fwrite(&S, sizeof(servicos), 1, arqSer);
                                                printf("\nTipo de servico salvo!\n");

                                                fseek(arqSer, posID, SEEK_SET);
                                                fread(&S, sizeof(servicos), 1, arqSer);

                                                printf("\nDados do Servico alterado: ");
                                                printf("\n----------------");
                                                printf("\nTipo do servico: %s", S.tipoServico);
                                                printf("\nDescricao: %s", S.descricao);
                                                printf("\nPreco: %.2f", S.preco);
                                                printf("\n----------------\n");

                                            break;

                                        case 2:
                                                system("cls");
                                                printf("\nNova descricao: ");
                                                fgets(S.descricao, MAXSTR, stdin);
                                                S.descricao[strcspn(S.descricao, "\n")] = '\0';

                                                fseek(arqSer, posID, SEEK_SET);
                                                fwrite(&S, sizeof(servicos), 1, arqSer);
                                                printf("\nDescricao do servico salvo!\n");

                                                fseek(arqSer, posID, SEEK_SET);
                                                fread(&S, sizeof(servicos), 1, arqSer);
                                                
                                                printf("\nDados do Servico alterado: ");
                                                printf("\n----------------");
                                                printf("\nID do servico: %s", S.id);
                                                printf("\nTipo do servico: %s", S.tipoServico);
                                                printf("\nDescricao: %s", S.descricao);
                                                printf("\nPreco: %.2f", S.preco);
                                                printf("\n----------------\n");

                                            break;
                                        case 3:
                                                system("cls");
                                                printf("\nNovo preco: ");
                                                scanf("%f", &S.preco);
                                                getchar();

                                                fseek(arqSer, posID, SEEK_SET);
                                                fwrite(&S, sizeof(servicos), 1, arqSer);
                                                printf("\nPreco do servico salvo!\n");

                                                fseek(arqSer, posID, SEEK_SET);
                                                fread(&S, sizeof(servicos), 1, arqSer);
                                                
                                                printf("\nDados do Servico alterado: ");
                                                printf("\n----------------");
                                                printf("\nID do servico: %s", S.id);
                                                printf("\nTipo do servico: %s", S.tipoServico);
                                                printf("\nDescricao: %s", S.descricao);
                                                printf("\nPreco: %.2f", S.preco);
                                                printf("\n----------------\n");

                                            break;
                                        case 0:
                                            printf("\nSaindo da edicao deste servico...\n");
                                            break;

                                        default:
                                            printf("\nERRO: escolha uma opcao valida!\n");
                                            break;
                                    }
                                } while (op2 != 0);
                            }
                            printf("\nDeseja editar outro Servico? (S/N): ");
                        } while (toupper(getche()) == 'S');
                    break;
                case 0:
                        printf("\nRetornando...\n");
                    break;
                
                default:
                        printf("\nERRO: escolha uma opcao valida!\n");
                    break;
                }
            break;

        case 0:
            printf("\nRetornando...\n");
            break;

        default:
            printf("\nERRO: escolha uma opcao valida!\n");
            break;
        }
    } while (op != 0);

    fclose(arqPF);
    fclose(arqPJ);
    fclose(arqMaq);
    fclose(arqPec);
    fclose(arqSer);
}

// FIM DA FUNCAO DE EDITAR ------------------------------------------------------------------------------------------------------
// INICIO DA FUNCAO DE VENDA ----------------------------------------------------------------------------------------------------

void realizarVenda() {
    clientesPF PF;
    clientesPJ PJ;
    maquinarios M;
    pecas P;
    servicos S;
    vendas V;

    FILE *arqPF = fopen("arqPF.bin", "rb+");
    FILE *arqPJ = fopen("arqPJ.bin", "rb+");
    FILE *arqMaq = fopen("arqMaquinario.bin", "rb+");
    FILE *arqPec = fopen("arqPecas.bin", "rb+");
    FILE *arqSer = fopen("arqServicos.bin", "rb+");
    FILE *arqVen = fopen("arqVendas.bin", "rb+");

    if (!arqPF || !arqPJ || !arqMaq || !arqPec || !arqSer || !arqVen) {
        printf("Erro ao abrir arquivos necessários.\n");
        return;
    }

    int op, op2, pos, posMaq, posPec, posSer, posData, valido;
    char opcao;
    
    do {
        system("cls");
        printf("\n--- VENDAS ---\n");
        printf("\n1 - Cliente PF");
        printf("\n2 - Cliente PJ");
        printf("\n0 - Retornar ao menu");
        printf("\nEscolha: ");
        scanf("%d", &op);

        switch (op) {
        case 1:
                system("cls");
                printf("\n--- VENDAS CLIENTE PF ---\n");
                printf("\n1 - Maquinario");
                printf("\n2 - Pecas");
                printf("\n3 - Servicos");
                printf("\n0 - Retornar");
                printf("\nEscolha: ");
                scanf("%d", &op2);

                switch (op2) {
                case 1:

                        do {
                            system("cls");
                            printf("\n--- LOJA DE MAQUINARIO ---\n");
                            printf("\nDigite seu cpf: ");
                            scanf("%11s", V.cpfVenda);
                            limparBuffer();

                            printf("\nDigite o codigo do maquinario: ");
                            scanf("%19s", V.codigoVenda);
                            limparBuffer();

                            pos = validarCPF(arqPF, V.cpfVenda);
                            posMaq = validarMaquinario(arqMaq, V.codigoVenda);

                            if(pos == -1 || posMaq == -1) {
                                printf("\nERRO: Um dos dados nao existe no cadastro!\n");
                                printf("\nTente novamente!\n");
                                system("pause");
                            }

                        } while (pos == -1 || posMaq == -1);

                        system("cls");
                        fseek(arqPF, pos, SEEK_SET);
                        fread(&PF, sizeof(clientesPF), 1, arqPF);

                        fseek(arqMaq, posMaq, SEEK_SET);
                        fread(&M, sizeof(maquinarios), 1, arqMaq);

                        printf("\nDados do cliente: ");
                        printf("\n----------------");
                        printf("\nNome: %s", PF.nome);
                        printf("\nTelefone: (%.2s) %.5s-%.4s", PF.telefone, PF.telefone+2, PF.telefone+7);
                        printf("\nEmail: %s", PF.email);
                        printf("\nData de nascimento: %02d/%02d/%04d", PF.D.dia, PF.D.mes, PF.D.ano);
                        printf("\n----------------\n");
                        
                        printf("\nDados do maquinario: ");
                        printf("\n----------------");
                        printf("\nNome do maquinario: %s", M.nome);
                        printf("\nCategoria: %s", M.categoria);
                        printf("\nQuantidade: %d", M.quantidade);
                        printf("\nPreco: %.2f", M.preco);
                        printf("\n----------------\n");

                        printf("\nDigite a quantidade da compra: ");
                        scanf("%d" , &V.quantDesejada);
                        getchar();

                        if (V.quantDesejada > M.quantidade) {
                            printf("\nEstoque insuficiente!\n");
                            system("pause");
                        } else {
                            V.precoParaPagar = V.quantDesejada * M.preco;   
                            
                            printf("\n--- FORMA DE PAGAMENTO ---\n");
                            printf("\n1 - Pix (10%% off)");
                            printf("\n2 - Boleto (+5%%)");
                            printf("\n3 - Financiamento (+10%%)");
                            printf("\nEscolha: ");
                            scanf("%d", &V.formaPagamento);
                            getchar();

                            if (V.formaPagamento == 1)
                                V.precoFinalPagar = V.precoParaPagar * 0.9;
                            else if (V.formaPagamento == 2)
                                V.precoFinalPagar = V.precoParaPagar * 1.05;
                            else if (V.formaPagamento == 3)
                                V.precoFinalPagar = V.precoParaPagar * 1.10;

                            printf("\nTotal da compra: %.2f\n", V.precoFinalPagar);

                            do {
                                valido = 1;

                                printf("\nData da venda (dd mm aaaa): ");
                                scanf("%d %d %d", &V.D.dataVendaDia, &V.D.dataVendaMes, &V.D.dataVendaAno);
                                getchar();

                                posData = validarData(V);

                                if (posData == 0) {
                                    printf("\nData menor ou igual a atual!\n");
                                    valido = 0; 
                                }

                                if (V.D.dataVendaMes < 1 || V.D.dataVendaMes > 12 || V.D.dataVendaDia < 1 || V.D.dataVendaDia > 31) {
                                    printf("\nData invalida!\n");
                                    valido = 0;
                                }
                            } while (valido == 0);

                            salvarVendas(V);

                            M.quantidade -= V.quantDesejada;
                            fseek(arqMaq, posMaq, SEEK_SET);
                            fwrite(&M, sizeof(maquinarios), 1, arqMaq); fflush(arqMaq);
                            printf("\nVenda registrada com sucesso!\n");
                            system("pause");
                        }
                    break;
                case 2:

                        do {
                            system("cls");
                            printf("\n--- LOJA DE PECAS ---\n");
                            printf("\nDigite seu cpf: ");
                            scanf("%11s", V.cpfVenda);
                            limparBuffer();
                            
                            printf("\nDigite o codigo da peca: ");
                            scanf("%19s", V.codigoVenda);
                            limparBuffer();

                            pos = validarCPF(arqPF, V.cpfVenda);
                            posPec = validarPecas(arqPec, V.codigoVenda);

                            if(pos == -1 || posPec == -1) {
                                printf("\nERRO: Um dos dados nao existe no cadastro!\n");
                                printf("\nTente novamente!\n");
                                system("pause");
                            }

                        } while (pos == -1 || posPec == -1);

                        system("cls");
                        fseek(arqPF, pos, SEEK_SET);
                        fread(&PF, sizeof(clientesPF), 1, arqPF);

                        fseek(arqPec, posPec, SEEK_SET);
                        fread(&P, sizeof(pecas), 1, arqPec);

                        printf("\nDados do cliente: ");
                        printf("\n----------------");
                        printf("\nNome: %s", PF.nome);
                        printf("\nTelefone: (%.2s) %.5s-%.4s", PF.telefone, PF.telefone+2, PF.telefone+7);
                        printf("\nEmail: %s", PF.email);
                        printf("\nData de nascimento: %02d/%02d/%04d", PF.D.dia, PF.D.mes, PF.D.ano);
                        printf("\n----------------\n");

                        printf("\n----------------\n");
                        printf("\nNome da peca: %s", P.nome);
                        printf("\nCategoria: %s", P.categoria);
                        printf("\nQuantidade: %d", P.quantidade);
                        printf("\nPreco: %.2f", P.preco);
                        printf("\n----------------\n");

                        printf("\nDigite a quantidade desejada: ");
                        scanf("%d", &V.quantDesejada);
                        getchar();

                        if (V.quantDesejada > P.quantidade) {
                            printf("\nEstoque insuficiente!\n");
                            system("pause");
                        } else {
                            V.precoParaPagar = V.quantDesejada * P.preco;

                            printf("\n--- FORMA DE PAGAMENTO ---\n");
                            printf("\n1 - Pix (10%% off)");
                            printf("\n2 - Boleto (+5%%)");
                            printf("\n3 - Financiamento (+10%%)");
                            printf("\nEscolha: ");
                            scanf("%d", &V.formaPagamento);
                            getchar();
                            
                            if (V.formaPagamento == 1)
                                V.precoFinalPagar = V.precoParaPagar * 0.9;
                            else if (V.formaPagamento == 2)
                                V.precoFinalPagar = V.precoParaPagar * 1.05;
                            else if (V.formaPagamento == 3)
                                V.precoFinalPagar = V.precoParaPagar * 1.10;

                            printf("\nTotal da compra: %.2f\n", V.precoFinalPagar);

                            do {
                                valido = 1;

                                printf("\nData da venda (dd mm aaaa): ");
                                scanf("%d %d %d", &V.D.dataVendaDia, &V.D.dataVendaMes, &V.D.dataVendaAno);
                                getchar();

                                posData = validarData(V);

                                if (posData == 0) {
                                    printf("\nData menor ou igual a atual!\n");
                                    valido = 0; 
                                }

                                if (V.D.dataVendaMes < 1 || V.D.dataVendaMes > 12 || V.D.dataVendaDia < 1 || V.D.dataVendaDia > 31) {
                                    printf("\nData invalida!\n");
                                    valido = 0;
                                }
                            } while (valido == 0);

                            salvarVendas(V);

                            P.quantidade -= V.quantDesejada;
                            fseek(arqPec, posPec, SEEK_SET);
                            fwrite(&P, sizeof(pecas), 1, arqPec); fflush(arqPec);
                            printf("\nVenda registrada com sucesso!\n");
                            system("pause");
                        }

                    break;
                case 3:

                        do {
                            system("cls");
                            printf("\n--- LOJA DE SERVICOS PF ---\n");
                            printf("\nDigite seu cpf: ");
                            scanf("%11s", V.cpfVenda);
                            limparBuffer();

                            rewind(arqSer);
                            while (fread(&S, sizeof(servicos), 1, arqSer) == 1) {
                                printf("\nDados do servico: ");
                                printf("\n----------------\n");
                                printf("\nPreco: %s", S.id);
                                printf("\nTipo do servico: %s", S.tipoServico);
                                printf("\nDescricao: %s", S.descricao);
                                printf("\nPreco: %.2f", S.preco);
                                printf("\n----------------\n");
                            }

                            printf("\nDigite o ID do servico: ");
                            scanf("%19s", V.IDServico);
                            limparBuffer();

                            rewind(arqSer);
                            pos = validarCPF(arqPF, V.cpfVenda);
                            posSer = validarID(arqSer, V.IDServico);

                            if(pos == -1 || posPec == -1) {
                                printf("\nERRO: Um dos dados nao existe no cadastro!\n");
                                printf("\nTente novamente!\n");
                                system("pause");
                            }
                            
                        } while (pos == -1 || posSer == -1);

                        system("cls");
                        fseek(arqPF, pos, SEEK_SET);
                        fread(&PF, sizeof(clientesPF), 1, arqPF);

                        fseek(arqSer, posSer, SEEK_SET);
                        fread(&S, sizeof(servicos), 1, arqSer);

                        printf("\nDados do cliente: ");
                        printf("\n----------------");
                        printf("\nNome: %s", PF.nome);
                        printf("\nTelefone: (%.2s) %.5s-%.4s", PF.telefone, PF.telefone+2, PF.telefone+7);
                        printf("\nEmail: %s", PF.email);
                        printf("\nData de nascimento: %02d/%02d/%04d", PF.D.dia, PF.D.mes, PF.D.ano);
                        printf("\n----------------\n");
                        
                        printf("\nDados do servico: ");
                        printf("\n----------------");
                        printf("\nTipo do servico: %s", S.tipoServico);
                        printf("\nDescricao: %s", S.descricao);
                        printf("\nPreco: %.2f", S.preco);
                        printf("\n----------------\n");

                        printf("\nDeseja contratar este servico? (S/N): ");
                        opcao = toupper(getche());

                        if (opcao != 'S') {
                            printf("\nRetornando...\n");
                        } else {
                            V.precoParaPagar = S.preco;   
                            
                            printf("\n--- FORMA DE PAGAMENTO ---\n");
                            printf("\n1 - Pix (10%% off)");
                            printf("\n2 - Boleto (+5%%)");
                            printf("\n3 - Financiamento (+10%%)");
                            printf("\nEscolha: ");
                            scanf("%d", &V.formaPagamento);
                            getchar();

                            if (V.formaPagamento == 1)
                                V.precoFinalPagar = V.precoParaPagar * 0.9;
                            else if (V.formaPagamento == 2)
                                V.precoFinalPagar = V.precoParaPagar * 1.05;
                            else if (V.formaPagamento == 3)
                                V.precoFinalPagar = V.precoParaPagar * 1.10;

                            printf("\nTotal da compra: %.2f\n", V.precoFinalPagar);

                            do {
                                valido = 1;

                                printf("\nData da venda (dd mm aaaa): ");
                                scanf("%d %d %d", &V.D.dataVendaDia, &V.D.dataVendaMes, &V.D.dataVendaAno);
                                getchar();

                                posData = validarData(V);

                                if (posData == 0) {
                                    printf("\nData menor ou igual a atual!\n");
                                    valido = 0; 
                                }

                                if (V.D.dataVendaMes < 1 || V.D.dataVendaMes > 12 || V.D.dataVendaDia < 1 || V.D.dataVendaDia > 31) {
                                    printf("\nData invalida!\n");
                                    valido = 0;
                                }
                            } while (valido == 0);

                            salvarVendas(V);
                            printf("\nVenda registrada com sucesso!\n");
                            system("pause");
                        }

                    break;
                case 0:
                        printf("\nRetornando...");
                    break;
                
                default:
                        printf("\nERRO: escolha uma opcao valida!\n");
                    break;
                }
            break;
        case 2:
                system("cls");
                printf("\n--- VENDAS CLIENTE PJ ---\n");
                printf("\n1 - Maquinario");
                printf("\n2 - Pecas");
                printf("\n3 - Servicos");
                printf("\n0 - Retornar");
                printf("\nEscolha: ");
                scanf("%d", &op2);

                switch (op2)
                {
                case 1:

                        do {
                            system("cls");
                            printf("\n--- LOJA DE MAQUINARIO ---\n");
                            printf("\nDigite seu cnpj: ");
                            scanf("%14s", V.cnpjVenda);
                            strcpy(V.cpfVenda, "");
                            limparBuffer();

                            printf("\nDigite o codigo do maquinario: ");
                            scanf("%19s", V.codigoVenda);
                            limparBuffer();

                            pos = validarCNPJ(arqPJ, V.cnpjVenda);
                            posMaq = validarMaquinario(arqMaq, V.codigoVenda);

                            if(pos == -1 || posPec == -1) {
                                printf("\nERRO: Um dos dados nao existe no cadastro!\n");
                                printf("\nTente novamente!\n");
                                system("pause");
                            }

                        } while (pos == -1 || posMaq == -1);

                        system("cls");
                        fseek(arqPJ, pos, SEEK_SET);
                        fread(&PJ, sizeof(clientesPJ), 1, arqPJ);

                        fseek(arqMaq, posMaq, SEEK_SET);
                        fread(&M, sizeof(maquinarios), 1, arqMaq);

                        printf("\nDados do cliente: ");
                        printf("\n----------------\n");
                        printf("\nNome empresarial: %s", PJ.nomeEmpresarial);
                        printf("\nFone: (%.2s) %.5s-%.4s", PJ.telefoneEmpresarial, PJ.telefoneEmpresarial+2, PJ.telefoneEmpresarial+7);
                        printf("\nEmail: %s", PJ.emailEmpresarial);
                        printf("\nNome do responsavel: %s", PJ.nomeDoResponsavel);
                        printf("\n----------------\n");
                        
                        printf("\nDados do maquinario: ");
                        printf("\n----------------");
                        printf("\nNome do maquinario: %s", M.nome);
                        printf("\nCategoria: %s", M.categoria);
                        printf("\nQuantidade: %d", M.quantidade);
                        printf("\nPreco: %.2f", M.preco);
                        printf("\n----------------\n");

                        printf("\nDigite a quantidade da compra: ");
                        scanf("%d" , &V.quantDesejada);
                        getchar();

                        if (V.quantDesejada > M.quantidade) {
                            printf("\nEstoque insuficiente!\n");
                            system("pause");
                        } else {
                            V.precoParaPagar = V.quantDesejada * M.preco;   
                            
                            printf("\n--- FORMA DE PAGAMENTO ---\n");
                            printf("\n1 - Pix (10%% off)");
                            printf("\n2 - Boleto (+5%%)");
                            printf("\n3 - Financiamento (+10%%)");
                            printf("\nEscolha: ");
                            scanf("%d", &V.formaPagamento);
                            getchar();

                            if (V.formaPagamento == 1)
                                V.precoFinalPagar = V.precoParaPagar * 0.9;
                            else if (V.formaPagamento == 2)
                                V.precoFinalPagar = V.precoParaPagar * 1.05;
                            else if (V.formaPagamento == 3)
                                V.precoFinalPagar = V.precoParaPagar * 1.10;

                            printf("\nTotal da compra: %.2f\n", V.precoFinalPagar);

                            do {
                                valido = 1;

                                printf("\nData da venda (dd mm aaaa): ");
                                scanf("%d %d %d", &V.D.dataVendaDia, &V.D.dataVendaMes, &V.D.dataVendaAno);
                                getchar();

                                posData = validarData(V);

                                if (posData == 0) {
                                    printf("\nData menor ou igual a atual!\n");
                                    valido = 0; 
                                }

                                if (V.D.dataVendaMes < 1 || V.D.dataVendaMes > 12 || V.D.dataVendaDia < 1 || V.D.dataVendaDia > 31) {
                                    printf("\nData invalida!\n");
                                    valido = 0;
                                }
                            } while (valido == 0);

                            salvarVendas(V);

                            M.quantidade -= V.quantDesejada;
                            fseek(arqMaq, posMaq, SEEK_SET); fflush(arqMaq);
                            fwrite(&M, sizeof(maquinarios), 1, arqMaq);
                            printf("\nVenda registrada com sucesso!\n");
                            system("pause");
                        }

                    break;
                case 2:

                        do {
                            system("cls");
                            printf("\n--- LOJA DE PECAS ---\n");
                            printf("\nDigite seu cnpj: ");
                            scanf("%14s", V.cnpjVenda);
                            strcpy(V.cpfVenda, "");
                            limparBuffer();
                            
                            printf("\nDigite o codigo da peca: ");
                            scanf("%19s", V.codigoVenda);
                            limparBuffer();

                            pos = validarCNPJ(arqPJ, V.cnpjVenda);
                            posPec = validarPecas(arqPec, V.codigoVenda);

                            if(pos == -1 || posPec == -1) {
                                printf("\nERRO: Um dos dados nao existe no cadastro!\n");
                                printf("\nTente novamente!\n");
                                system("pause");
                            }
                        } while (pos == -1 || posPec == -1);
                        
                        system("cls");
                        fseek(arqPJ, pos, SEEK_SET);
                        fread(&PJ, sizeof(clientesPJ), 1, arqPJ);

                        fseek(arqPec, posPec, SEEK_SET);
                        fread(&P, sizeof(pecas), 1, arqPec);

                        printf("\nDados do cliente: ");
                        printf("\n----------------\n");
                        printf("\nNome empresarial: %s", PJ.nomeEmpresarial);
                        printf("\nFone: (%.2s) %.5s-%.4s", PJ.telefoneEmpresarial, PJ.telefoneEmpresarial+2, PJ.telefoneEmpresarial+7);
                        printf("\nEmail: %s", PJ.emailEmpresarial);
                        printf("\nNome do responsavel: %s", PJ.nomeDoResponsavel);
                        printf("\n----------------\n");

                        printf("\nDados da peca: ");
                        printf("\n----------------\n");
                        printf("\nNome da peca: %s", P.nome);
                        printf("\nCategoria: %s", P.categoria);
                        printf("\nQuantidade: %d", P.quantidade);
                        printf("\nPreco: %.2f", P.preco);
                        printf("\n----------------\n");

                        printf("\nDigite a quantidade desejada: ");
                        scanf("%d", &V.quantDesejada);
                        getchar();

                        if (V.quantDesejada > P.quantidade) {
                            printf("\nEstoque insuficiente!\n");
                            system("pause");
                        } else {
                            V.precoParaPagar = V.quantDesejada * P.preco;

                            printf("\n--- FORMA DE PAGAMENTO ---\n");
                            printf("\n1 - Pix (10%% off)");
                            printf("\n2 - Boleto (+5%%)");
                            printf("\n3 - Financiamento (+10%%)");
                            printf("\nEscolha: ");
                            scanf("%d", &V.formaPagamento);
                            getchar();
                            
                            if (V.formaPagamento == 1)
                                V.precoFinalPagar = V.precoParaPagar * 0.9;
                            else if (V.formaPagamento == 2)
                                V.precoFinalPagar = V.precoParaPagar * 1.05;
                            else if (V.formaPagamento == 3)
                                V.precoFinalPagar = V.precoParaPagar * 1.10;

                            printf("\nTotal da compra: %.2f\n", V.precoFinalPagar);

                            do {
                                valido = 1;

                                printf("\nData da venda (dd mm aaaa): ");
                                scanf("%d %d %d", &V.D.dataVendaDia, &V.D.dataVendaMes, &V.D.dataVendaAno);
                                getchar();

                                posData = validarData(V);

                                if (posData == 0) {
                                    printf("\nData menor ou igual a atual!\n");
                                    valido = 0; 
                                }

                                if (V.D.dataVendaMes < 1 || V.D.dataVendaMes > 12 || V.D.dataVendaDia < 1 || V.D.dataVendaDia > 31) {
                                    printf("\nData invalida!\n");
                                    valido = 0;
                                }
                            } while (valido == 0);

                            salvarVendas(V);

                            P.quantidade -= V.quantDesejada;
                            fseek(arqPec, posPec, SEEK_SET);
                            fwrite(&P, sizeof(pecas), 1, arqPec); fflush(arqPec);
                            printf("\nVenda registrada com sucesso!\n");
                            system("pause");
                        }

                    break;
                case 3:

                        do {
                            system("cls");
                            printf("\n--- LOJA DE SERVICOS PJ ---\n");
                            printf("\nDigite seu cnpj: ");
                            scanf("%14s", V.cnpjVenda);
                            limparBuffer();

                            rewind(arqSer);
                            while (fread(&S, sizeof(servicos), 1, arqSer) == 1) {
                                printf("\nDados do servico: ");
                                printf("\n----------------\n");
                                printf("\nID do servico: %s", S.id);
                                printf("\nTipo do servico: %s", S.tipoServico);
                                printf("\nDescricao: %s", S.descricao);
                                printf("\nPreco: %.2f", S.preco);
                                printf("\n----------------\n");
                            }

                            printf("\nDigite o ID do servico: ");
                            scanf("%9s", V.IDServico);
                            limparBuffer();

                            rewind(arqSer);
                            pos = validarCNPJ(arqPJ, V.cnpjVenda);
                            posSer = validarID(arqSer, V.IDServico);

                            if(pos == -1 || posPec == -1) {
                                printf("\nERRO: Um dos dados nao existe no cadastro!\n");
                                printf("\nTente novamente!\n");
                                system("pause");
                            }

                        } while (pos == -1 || posSer == -1);

                        system("cls");
                        fseek(arqPJ, pos, SEEK_SET);
                        fread(&PJ, sizeof(clientesPJ), 1, arqPJ);

                        fseek(arqSer, posSer, SEEK_SET);
                        fread(&S, sizeof(servicos), 1, arqSer);

                        printf("\nDados do cliente: ");
                        printf("\n----------------\n");
                        printf("\nNome empresarial: %s", PJ.nomeEmpresarial);
                        printf("\nFone: (%.2s) %.5s-%.4s", PJ.telefoneEmpresarial, PJ.telefoneEmpresarial+2, PJ.telefoneEmpresarial+7);
                        printf("\nEmail: %s", PJ.emailEmpresarial);
                        printf("\nNome do responsavel: %s", PJ.nomeDoResponsavel);
                        printf("\n----------------\n");
                        
                        printf("\nDados do servico: ");
                        printf("\n----------------");
                        printf("\nTipo do servico: %s", S.tipoServico);
                        printf("\nDescricao: %s", S.descricao);
                        printf("\nPreco: %.2f", S.preco);
                        printf("\n----------------\n");

                        printf("\nDeseja contratar este servico? (S/N): ");
                        opcao = toupper(getche());

                        if (opcao != 'S') {
                            printf("\nRetornando...\n");
                        } else {
                            V.precoParaPagar = S.preco;   
                            
                            printf("\n--- FORMA DE PAGAMENTO ---\n");
                            printf("\n1 - Pix (10%% off)");
                            printf("\n2 - Boleto (+5%%)");
                            printf("\n3 - Financiamento (+10%%)");
                            printf("\nEscolha: ");
                            scanf("%d", &V.formaPagamento);
                            getchar();

                            if (V.formaPagamento == 1)
                                V.precoFinalPagar = V.precoParaPagar * 0.9;
                            else if (V.formaPagamento == 2)
                                V.precoFinalPagar = V.precoParaPagar * 1.05;
                            else if (V.formaPagamento == 3)
                                V.precoFinalPagar = V.precoParaPagar * 1.10;

                            printf("\nTotal da compra: %.2f\n", V.precoFinalPagar);
                            
                            do {
                                valido = 1;

                                printf("\nData da venda (dd mm aaaa): ");
                                scanf("%d %d %d", &V.D.dataVendaDia, &V.D.dataVendaMes, &V.D.dataVendaAno);
                                getchar();

                                posData = validarData(V);

                                if (posData == 0) {
                                    printf("\nData menor ou igual a atual!\n");
                                    valido = 0; 
                                }

                                if (V.D.dataVendaMes < 1 || V.D.dataVendaMes > 12 || V.D.dataVendaDia < 1 || V.D.dataVendaDia > 31) {
                                    printf("\nData invalida!\n");
                                    valido = 0;
                                }
                            } while (valido == 0);

                            salvarVendas(V);
                            printf("\nVenda registrada com sucesso!\n");
                            system("pause");
                        }

                    break;
                case 0:
                        printf("\nRetornando...");
                    break;
                
                default:
                        printf("\nERRO: escolha uma opcao valida!\n");
                    break;
                }
            break;
        case 0:
                printf("\nRetornando...");
            break;

        default:
                printf("\nERRO: escolha uma opcao valida!\n");
            break;
        }
    } while (op != 0);

    fclose(arqPF);
    fclose(arqPJ);
    fclose(arqMaq);
    fclose(arqPec);
    fclose(arqSer);
    fclose(arqVen);
}

// FIM DA FUNCAO DE VENDA --------------------------------------------------------------------------------------
// INICIO DA FUNCAO DE EXCLUSAO --------------------------------------------------------------------------------

void realizarExclusao() {
    clientesPF PF;
    clientesPJ PJ;
    maquinarios M;
    pecas P;
    servicos S;
    // vendas V;

    FILE *arqPF = fopen("arqPF.bin", "rb+");
    FILE *arqPJ = fopen("arqPJ.bin", "rb+");
    FILE *arqMaq = fopen("arqMaquinario.bin", "rb+");
    FILE *arqPec = fopen("arqPecas.bin", "rb+");
    FILE *arqSer = fopen("arqServicos.bin", "rb+");
    FILE *arqVen = fopen("arqVendas.bin", "rb+");

    //inicio abertura dos arquivos
    if (arqPF == NULL) {
        arqPF = fopen("arqPF.bin", "wb+");
        if (arqPF == NULL) {
            printf("\nERRO ao criar o arquivo de clientes PF!");
            return;
    	}
	}

	if (arqPJ == NULL) {
	    arqPJ = fopen("arqPJ.bin", "wb+");
	    if (arqPJ == NULL) {
	        printf("\nERRO ao criar o arquivo de clientes PJ!");
	        return;
	    }
	}

	if (arqMaq == NULL) {
	    arqMaq = fopen("arqMaquinario.bin", "wb+");
	    if (arqMaq == NULL) {
	        printf("\nERRO ao criar o arquivo de maquinarios!");
	        return;
	    }
	}

	if (arqPec == NULL) {
	    arqPec = fopen("arqPecas.bin", "wb+");
	    if (arqPec == NULL) {
	        printf("\nERRO ao criar o arquivo de pecas!");
	        return;
	    }
	}
	
	if (arqSer == NULL) {
	    arqSer = fopen("arqServicos.bin", "wb+");
	    if (arqSer == NULL) {
	        printf("\nERRO ao criar o arquivo de servicos!");
	        return;
	    }
	}

    if (arqVen == NULL) {
        arqVen = fopen("arqVendas.bin", "wb+");
	    if (arqVen == NULL) {
	        printf("\nERRO ao criar o arquivo de venda!");
	        return;
	    }
    }

    int op, op2, op3, pos, posVen;
    char cpfApagar[12], cnpjApagar[14], codigoApagar[20], idApagar[10];

    do {
        system("cls");
        printf("\n--- EXCLUSAO ---\n");
        printf("\n1 - Clientes");
        printf("\n2 - Produtos");
        printf("\n3 - Servicos");
        printf("\n0 - Retornar ao menu");
        printf("\nEscolha: ");
        scanf("%d", &op);
        getchar();

        switch (op) {
        case 1:
                system("cls");
                printf("\n--- EXCLUIR CLIENTES ---\n");
                printf("\n1 - Cliente PF");
                printf("\n2 - Cliente PJ");
                printf("\n0 - Retornar");
                printf("\nEscolha: ");
                scanf("%d", &op2);
                getchar();

                switch (op2) {
                case 1:
                        system("cls");
                        printf("\n--- EXCLUIR CLIENTE PF ---\n");
                        printf("\nDigite o cpf: ");
                        scanf("%11s", cpfApagar);
                        limparBuffer();

                        pos = validarCPF(arqPF, cpfApagar);

                        if (pos == -1) {
                            printf("\nERRO: o cpf digitado ainda nao foi cadastrado!\n");
                            system("pause");
                        } else {
                            fseek(arqPF, pos, SEEK_SET);
                            fread(&PF, sizeof(clientesPF), 1, arqPF);

                            printf("\nDados do cliente: ");
                            printf("\n----------------");
                            printf("\nNome: %s", PF.nome);
                            printf("\nTelefone: (%.2s) %.5s-%.4s", PF.telefone, PF.telefone+2, PF.telefone+7);
                            printf("\nEmail: %s", PF.email);
                            printf("\nData de nascimento: %02d/%02d/%04d", PF.D.dia, PF.D.mes, PF.D.ano);
                            printf("\n----------------\n");

                            posVen = validarVendasPF(arqVen, cpfApagar);

                            if (posVen == -1) {
                                printf("\nDeseja realmente excluir esse cliente? <S/N>: ");

                                if (toupper(getche()) == 'S') {
                                    FILE *temp = fopen("arqTemp.bin", "wb");

                                    if(temp == NULL) {
                                        printf("\nERRO: impossivel criar arquivo temp!\n");
                                    } else {
                                        rewind(arqPF);

                                        while (fread(&PF, sizeof(clientesPF), 1, arqPF) == 1) {
                                            if(stricmp(cpfApagar, PF.cpf) != 0) {
                                                fwrite(&PF, sizeof(clientesPF), 1, temp);
                                            }
                                        }
                                    }
                                    
                                    fclose(arqPF);
                                    fclose(temp);
                                    remove("arqPF.bin");
                                    rename("arqTemp.bin", "arqPF.bin");
                                    
                                    printf("\nCliente Excluido!\n");
                                    system("pause");
                                }

                            } else {
                                printf("\nNao e possivel excluir um cliente com uma compra registrada\n");
                                printf("\n");
                                system("pause");
                            }
                        }
                    break;
                case 2:
                        system("cls");
                        printf("\n--- EXCLUIR CLIENTE PJ ---\n");
                        printf("\nDigite o cnpj: ");
                        scanf("%14s", cnpjApagar);
                        limparBuffer();

                        pos = validarCNPJ(arqPJ, cnpjApagar);

                        if (pos == -1) {
                            printf("\nERRO: o cnpj digitado ainda nao foi cadastrado!\n");
                            printf("\n");
                            system("pause");
                        } else {
                            fseek(arqPJ, pos, SEEK_SET);
                            fread(&PJ, sizeof(clientesPJ), 1, arqPJ);

                            printf("\nDados do cliente: ");
                            printf("\n----------------");
                            printf("\nNome empresarial: %s", PJ.nomeEmpresarial);
                            printf("\nFone: (%.2s) %.5s-%.4s", PJ.telefoneEmpresarial, PJ.telefoneEmpresarial+2, PJ.telefoneEmpresarial+7);
                            printf("\nEmail: %s", PJ.emailEmpresarial);
                            printf("\nNome do responsavel: %s", PJ.nomeDoResponsavel);
                            printf("\n----------------\n");

                            posVen = validarVendasPJ(arqVen, cnpjApagar);

                            if (posVen == -1) {
                                printf("\nDeseja realmente excluir esse cliente? <S/N>: ");

                                if(toupper(getche()) == 'S') {
                                    FILE *temp = fopen("arqTemp.bin", "wb");

                                    if (temp == NULL) {
                                        printf("\nERRO: impossivel criar arquivo temp!\n");
                                    } else {
                                        rewind(arqPJ);

                                        while (fread(&PJ, sizeof(clientesPJ), 1, arqPJ) == 1) {
                                            if (strcmp(cnpjApagar, PJ.cnpj) != 0) {
                                                fwrite(&PJ, sizeof(clientesPJ), 1, temp);
                                            }
                                        }
                                    }

                                    fclose(arqPJ);
                                    fclose(temp);
                                    remove("arqPJ.bin");
                                    rename("arqTemp.bin", "arqPJ.bin");
                                    arqPJ = fopen("arqPJ.bin", "rb+");

                                    printf("\nCliente Excluido!\n");
                                    system("pause");
                                }
                            } else {
                                printf("\nNao e possivel excluir um cliente com uma compra registrada\n");
                                system("pause");
                            }
                        } 
                    break;
                case 0:
                        printf("\nRetornando...\n");
                    break;
                
                default:
                        printf("\nERRO: escolha uma opcao valida!\n");
                    break;
                }
            break;
        case 2:
                system("cls");
                printf("\n--- EXCLUIR PRODUTOS ---\n");
                printf("\n1 - Maquinario");
                printf("\n2 - Pecas");
                printf("\n0 - Retornar");
                printf("\nEscolha: ");
                scanf("%d", &op2);
                getchar();

                switch (op2) {
                case 1:
                        system("cls");
                        printf("\n--- EXCLUIR MAQUINARIO ---\n");
                        printf("\nDigite o codigo: ");
                        scanf("%19s", codigoApagar);
                        limparBuffer();

                        pos = validarMaquinario(arqMaq, codigoApagar);

                        if(pos == -1) {
                            printf("\nERRO: o codigo digitado ainda nao foi cadastrado!\n");
                            printf("\n");
                            system("pause");
                        } else {
                            fseek(arqMaq, pos, SEEK_SET);
                            fread(&M, sizeof(maquinarios), 1, arqMaq);

                            printf("\nDados do maquinario: ");
                            printf("\n----------------");
                            printf("\nNome do maquinario: %s", M.nome);
                            printf("\nCategoria: %s", M.categoria);
                            printf("\nQuantidade: %d", M.quantidade);
                            printf("\nPreco: %.2f", M.preco);
                            printf("\n----------------\n");

                            if(M.quantidade == 0) {
                                printf("\nDeseja realmente excluir esse produto? <S/N>: ");

                                if (toupper(getche()) == 'S') {
                                FILE *temp = fopen("arqTemp.bin", "wb");

                                if(temp == NULL) {
                                    printf("\nERRO: impossivel criar arquivo temp!\n");
                                    printf("\n");
                                    system("pause");
                                } else {
                                    rewind(arqMaq);

                                    while (fread(&M, sizeof(maquinarios), 1, arqMaq) == 1) {
                                        if (strcmp(codigoApagar, M.codigo) != 0) {
                                            fwrite(&M, sizeof(maquinarios), 1, temp);
                                        }
                                    }
                                }
                                
                                fclose(arqMaq);
                                fclose(temp);
                                remove("arqMaquinario.bin");
                                rename("arqTemp.bin", "arqMaquinario.bin");
                                arqMaq = fopen("arqMaquinario.bin", "rb+");

                                printf("\nProduto Excluido!\n");
                                printf("\n");
                                system("pause");
                                } 
                            } else {
                                printf("\nERRO: impossivel excluir com itens no estoque!\n");
                                system("pause");
                            }

                            
                        }
                    break;
                case 2:
                        system("cls");
                        printf("\n--- EXCLUIR PECAS ---\n");
                        printf("\nDigite o codigo: ");
                        scanf("%19s", codigoApagar);
                        limparBuffer();

                        pos = validarPecas(arqPec, codigoApagar);

                        if(pos == -1) {
                            printf("\nERRO: o codigo digitado ainda nao foi cadastrado!\n");
                            printf("\n");
                            system("pause");
                        } else {
                            fseek(arqPec, pos, SEEK_SET);
                            fread(&P, sizeof(pecas), 1, arqPec);

                            printf("\nDados da peca: ");
                            printf("\n----------------");
                            printf("\nNome da peca: %s", P.nome);
                            printf("\nCategoria: %s", P.categoria);
                            printf("\nQuantidade: %d", P.quantidade);
                            printf("\nPreco: %.2f", P.preco);
                            printf("\n----------------\n");

                            if(P.quantidade == 0) {
                            	printf("\nDeseja realmente excluir esse produto? <S/N>: ");
                            	
                            	if (toupper(getche()) == 'S') {
                                    FILE *temp = fopen("arqTemp.bin", "wb");

                                    if(temp == NULL) {
                                        printf("\nERRO: impossivel criar arquivo temp!\n");
                                    } else {
                                        rewind(arqPec);

                                        while (fread(&P, sizeof(pecas), 1, arqPec) == 1) {
                                            if (strcmp(codigoApagar, P.codigo) != 0) {
                                                fwrite(&P, sizeof(pecas), 1, temp);
                                            }
                                        }
                                    }
                                    
                                    fclose(arqPec);
                                    fclose(temp);
                                    remove("arqPecas.bin");
                                    rename("arqTemp.bin", "arqPecas.bin");
                                    arqPec = fopen("arqPecas.bin", "rb+");

                                    printf("\nProduto Excluido!\n");
                                    printf("\n");
                                    system("pause");
                            	}
                            } else {
                            	printf("\nERRO: impossivel excluir com itens no estoque!\n");
                                system("pause");
                            }
                        }
                    break;
                case 0:
                        printf("\nRetornando...");
                    break;
                default:
                        printf("\nERRO: escolha uma opcao valida!\n");
                    break;
                }
            break;
        case 3:
                system("cls");
                printf("\n--- EXCLUIR SERVICOS ---\n");
                printf("\n1 - Apagar");
                printf("\n0 - Retornar");
                printf("\nEscolha: ");
                scanf("%d", &op3);
                getchar();
                
                switch(op3) {
                	case 1:
                			system("cls");
                			printf("\n--- EXCLUIR POR ID ---\n");
                			printf("\nDigite o id: ");
                			scanf("%9s", idApagar);
                			limparBuffer();
                			
                			pos = validarID(arqSer, idApagar);
                			
                			if(pos == -1) {
                				printf("\nERRO: o ID digitado ainda nao foi cadastrado!\n");
                            	system("pause");
                			} else {
                				fseek(arqSer, pos, SEEK_SET);
                				fread(&S, sizeof(servicos), 1, arqSer);
                				
                				printf("\nDados do servico: ");
                				printf("\n----------------");
                                printf("\nID do servico: %s", S.id);
                                printf("\nTipo do servico: %s", S.tipoServico);
                                printf("\nDescricao: %s", S.descricao);
                                printf("\nPreco: %.2f", S.preco);
                                printf("\n----------------\n");
                                
                                printf("\nDeseja realmente excluir esse servico? <S/N>: ");
                                
                                if(toupper(getche()) == 'S') {
                                	FILE *temp = fopen("arqTemp.bin", "wb");
                                	
                                	if(temp == NULL) {
                                		printf("\nERRO: impossivel criar arquivo temp!\n");
                                	} else {
                                        rewind(arqSer);

                                        while(fread(&S, sizeof(servicos), 1, arqSer) == 1) {
                                            if(stricmp(idApagar, S.id) != 0) {
                                                fwrite(&S, sizeof(servicos), 1, temp);
                                            }
                                        }
                                		
                                        fclose(arqSer);
                                        fclose(temp);

                                        if (remove("arqServicos.bin") != 0) {
                                            perror("Erro ao remover arquivo");
                                        } else if (rename("arqTemp.bin", "arqServicos.bin") != 0) {
                                            perror("Erro ao renomear arquivo");
                                        } else {
                                            printf("\nProduto Excluido!\n");
                                        }

                                        arqSer = fopen("arqServicos.bin", "rb+");
                                        system("pause");
                                	}
                                }
                			}
                			
                		break;
                	case 0:
                			printf("\nRetornando...\n");
                		break;
                	default:
                			printf("\nERRO: escolha uma opcao valida!\n");
                		break;
                }
                
            break;
        
        default:
                printf("\nERRO: escolha uma opcao valida!\n");
            break;
        }
    } while (op != 0);

    fclose(arqPF);
    fclose(arqPJ);
    fclose(arqMaq);
    fclose(arqPec);
    fclose(arqSer);
    fclose(arqVen);
}

// FIM DA FUNCAO DE EXCLUSAO ----------------------------------------------------------------------------------------------------------------
// INICIO DA FUNCAO DE RELATORIOS -----------------------------------------------------------------------------------------------------------

void relatorios() {
    clientesPF PF;
    clientesPJ PJ;
    maquinarios M;
    pecas P;
    servicos S;
    vendas V;

    FILE *arqPF = fopen("arqPF.bin", "rb+");
    FILE *arqPJ = fopen("arqPJ.bin", "rb+");
    FILE *arqMaq = fopen("arqMaquinario.bin", "rb+");
    FILE *arqPec = fopen("arqPecas.bin", "rb+");
    FILE *arqSer = fopen("arqServicos.bin", "rb+");
    FILE *arqVen = fopen("arqVendas.bin", "rb+");

    int op, op2, op3;

    if (arqPF == NULL) {
        arqPF = fopen("arqPF.bin", "wb+");
        if (arqPF == NULL) {
            printf("\nERRO ao criar o arquivo de clientes PF!");
            return;
    	}
	}

	if (arqPJ == NULL) {
	    arqPJ = fopen("arqPJ.bin", "wb+");
	    if (arqPJ == NULL) {
	        printf("\nERRO ao criar o arquivo de clientes PJ!");
	        return;
	    }
	}

	if (arqMaq == NULL) {
	    arqMaq = fopen("arqMaquinario.bin", "wb+");
	    if (arqMaq == NULL) {
	        printf("\nERRO ao criar o arquivo de maquinarios!");
	        return;
	    }
	}

	if (arqPec == NULL) {
	    arqPec = fopen("arqPecas.bin", "wb+");
	    if (arqPec == NULL) {
	        printf("\nERRO ao criar o arquivo de pecas!");
	        return;
	    }
	}
	
	if (arqSer == NULL) {
	    arqSer = fopen("arqServicos.bin", "wb+");
	    if (arqSer == NULL) {
	        printf("\nERRO ao criar o arquivo de servicos!");
	        return;
	    }
	}

    if (arqVen == NULL) {
        arqVen = fopen("arqVendas.bin", "wb+");
	    if (arqVen == NULL) {
	        printf("\nERRO ao criar o arquivo de venda!");
	        return;
	    }
    }

    do {
        system("cls");
        printf("\n--- RELATORIOS ---\n");
        printf("\n1 - Clientes");
        printf("\n2 - Produtos");
        printf("\n3 - Servicos");
        printf("\n4 - Vendas");
        printf("\n0 - Retornar ao menu");
        printf("\nEscolha: ");
        scanf("%d", &op);
        getchar();

        switch (op) {
        case 1:
                system("cls");
                printf("\n--- RELATORIOS CLIENTES ---\n");
                printf("\n1 - Clientes PF");
                printf("\n2 - Clientes PJ");
                printf("\n0 - Retornar");
                printf("\nEscolha: ");
                scanf("%d", &op2);
                getchar();

                switch (op2) {
                case 1:
                        while (fread(&PF, sizeof(clientesPF), 1, arqPF) == 1) {
                            printf("\nDados do Cliente PF: ");
                            printf("\n----------------");
                            printf("\nNome: %s", PF.nome);
                            printf("\nTelefone: (%.2s) %.5s-%.4s", PF.telefone, PF.telefone+2, PF.telefone+7);
                            printf("\nEmail: %s", PF.email);
                            printf("\nData de nascimento: %02d/%02d/%04d", PF.D.dia, PF.D.mes, PF.D.ano);
                            printf("\n----------------\n");
                        }
                        system("pause");
                    break;
                case 2:
                        while (fread(&PJ, sizeof(clientesPJ), 1, arqPJ) == 1) {
                            printf("\nDados do Cliente PJ: ");
                            printf("\n----------------");
                            printf("\nNome empresarial: %s", PJ.nomeEmpresarial);
                            printf("\nFone: (%.2s) %.5s-%.4s", PJ.telefoneEmpresarial, PJ.telefoneEmpresarial+2, PJ.telefoneEmpresarial+7);
                            printf("\nEmail: %s", PJ.emailEmpresarial);
                            printf("\nNome do responsavel: %s", PJ.nomeDoResponsavel);
                            printf("\n----------------\n");
                        }
                        system("pause");
                    break;
                case 0:
                        printf("\nRetornando...");
                    break;
                default:
                        printf("\nERRO: escolha uma opcao valida!\n");
                        system("pause");
                    break;
                }
            break;
        case 2:
                system("cls");
                printf("\n--- RELATORIOS PRODUTOS ---\n");
                printf("\n1 - Maquinarios");
                printf("\n2 - Pecas");
                printf("\n0 - Retornar");
                printf("\nEscolha: ");
                scanf("%d", &op2);
                getchar();

                switch (op2) {
                case 1:
                        while (fread(&M, sizeof(maquinarios), 1, arqMaq) == 1) {
                            printf("\nDados do Maquinario: ");
                            printf("\n----------------");
                            printf("\nNome do maquinario: %s", M.nome);
                            printf("\nCategoria: %s", M.categoria);
                            printf("\nQuantidade: %d", M.quantidade);
                            printf("\nPreco: %.2f", M.preco);
                            printf("\n----------------\n");
                        }
                        system("pause");
                    break;
                case 2:
                        while (fread(&P, sizeof(pecas), 1, arqPec) == 1) {
                            printf("\nDados da Peca: ");
                            printf("\n----------------");
                            printf("\nNome da peca: %s", P.nome);
                            printf("\nCategoria: %s", P.categoria);
                            printf("\nQuantidade: %d", P.quantidade);
                            printf("\nPreco: %.2f", P.preco);
                            printf("\n----------------\n");
                        }
                        system("pause");
                    break;
                case 0:
                        printf("\nRetornando...");
                    break;
                default:
                        printf("\nERRO: escolha uma opcao valida!\n");
                        system("pause");
                    break;
                }
            break;
        case 3:
                system("cls");
                printf("\n--- RELATORIOS SERVICOS ---\n");
                printf("\n1 - Servicos");
                printf("\n0 - Retornar");
                printf("\nEscolha: ");
                scanf("%d", &op3);
                getchar();

                switch (op3) {
                case 1:
                        while(fread(&S, sizeof(servicos), 1, arqSer) == 1) {
                            printf("\nDados do Servico: ");
                            printf("\n----------------");
                            printf("\nID do servico: %s", S.id);
                            printf("\nTipo do servico: %s", S.tipoServico);
                            printf("\nDescricao: %s", S.descricao);
                            printf("\nPreco: %.2f", S.preco);
                            printf("\n----------------\n");
                        }
                        system("pause");
                    break;
                case 0:
                        printf("\nRetornar...");
                    break;
                default:
                        printf("\nERRO: escolha uma opcao valida!\n");
                        system("pause");
                    break;
                }
            break;
        case 4:
                system("cls");
                printf("\n--- RELATORIOS DE VENDAS ---\n");
                printf("\n1 - Vendas");
                printf("\n0 - Retornar");
                printf("\nEscolha: ");
                scanf("%d", &op3);
                getchar();

                switch (op3) {
                case 1:
                        system("cls");
                        rewind(arqVen);
                        while (fread(&V, sizeof(vendas), 1, arqVen) == 1) {          
                            if (strlen(V.cpfVenda) > 0) {

                                printf("\nDados da Venda: ");
                                printf("\n--------------------------------------------");
                                printf("\nCPF do cliente: %.3s.%.3s.%.3s-%.2s", V.cpfVenda, V.cpfVenda+3, V.cpfVenda+6, V.cpfVenda+9);
                                if (strlen(V.codigoVenda) > 0) {
                                    printf("\nCodigo do produto: %s", V.codigoVenda);
                                    printf("\nQuantidade do produto: %d", V.quantDesejada);
                                    if(V.formaPagamento == 1) {
                                        printf("\nForma de pagamento: PIX");
                                    } else if (V.formaPagamento == 2) {
                                        printf("\nForma de pagamento: BOLETO");
                                    } else {
                                        printf("\nForma de pagamento: FINANCIAMENTO");
                                    }
                                    printf("\nPreco da compra: %.2f", V.precoFinalPagar);
                                    printf("\nData da compra: %02d/%02d/%02d", V.D.dataVendaDia, V.D.dataVendaMes, V.D.dataVendaAno);
                                    printf("\n--------------------------------------------\n");
                                } else if (strlen(V.IDServico) > 0) {
                                    printf("\nID do servico: %s", V.IDServico);
                                    if(V.formaPagamento == 1) {
                                        printf("\nForma de pagamento: PIX");
                                    } else if (V.formaPagamento == 2) {
                                        printf("\nForma de pagamento: BOLETO");
                                    } else {
                                        printf("\nForma de pagamento: FINANCIAMENTO");
                                    }
                                    printf("\nPreco da compra: %.2f", V.precoFinalPagar);
                                    printf("\nData da compra: %02d/%02d/%02d", V.D.dataVendaDia, V.D.dataVendaMes, V.D.dataVendaAno);
                                    printf("\n--------------------------------------------\n");
                                }
                            } else if (strlen(V.cnpjVenda) > 0) {

                                printf("\nDados da Venda: ");
                                printf("\n--------------------------------------------");
                                printf("\nCNPJ do cliente: %.2s.%.3s.%.3s/%.4s-%2s", V.cnpjVenda, V.cnpjVenda+2, V.cnpjVenda+5, V.cnpjVenda+8, V.cnpjVenda+12);
                                if (strlen(V.codigoVenda) > 0) {
                                    printf("\nCodigo do produto: %s", V.codigoVenda);
                                    printf("\nQuantidade do produto: %d", V.quantDesejada);
                                    if(V.formaPagamento == 1) {
                                        printf("\nForma de pagamento: PIX");
                                    } else if (V.formaPagamento == 2) {
                                        printf("\nForma de pagamento: BOLETO");
                                    } else {
                                        printf("\nForma de pagamento: FINANCIAMENTO");
                                    }
                                    printf("\nPreco da compra: %.2f", V.precoFinalPagar);
                                    printf("\nData da compra: %02d/%02d/%02d", V.D.dataVendaDia, V.D.dataVendaMes, V.D.dataVendaAno);
                                    printf("\n--------------------------------------------\n");
                                } else if (strlen(V.IDServico) > 0) {
                                    printf("\nID do servico: %s", V.IDServico);
                                    if(V.formaPagamento == 1) {
                                        printf("\nForma de pagamento: PIX");
                                    } else if (V.formaPagamento == 2) {
                                        printf("\nForma de pagamento: BOLETO");
                                    } else {
                                        printf("\nForma de pagamento: FINANCIAMENTO");
                                    }
                                    printf("\nPreco da compra: %.2f", V.precoFinalPagar);
                                    printf("\nData da compra: %02d/%02d/%02d", V.D.dataVendaDia, V.D.dataVendaMes, V.D.dataVendaAno);
                                    printf("\n--------------------------------------------\n");
                                }
                            }
                        }
                        system("pause");
                    break;
                
                default:
                        printf("\nERRO: escolha uma opcao valida!\n");
                    break;
                }
            break;
        case 0:
                printf("\nRetornando...\n");
            break;
        default:
                printf("\nERRO: escolha uma opcao valida!\n");
            break;
        }
    } while (op != 0);

    fclose(arqPF);
    fclose(arqPJ);
    fclose(arqMaq);
    fclose(arqPec);
    fclose(arqSer);
    fclose(arqVen);
} 

// FIM DA FUNCAO DE RELATORIOS --------------------------------------------------------
// INICIO DA FUNCAO DE ORDENACAO ------------------------------------------------------

void ordenacao() {
    clientesPF PF, PF_ORD;
    clientesPJ PJ, PJ_ORD;
    maquinarios M, M_ORD;
    pecas P, P_ORD;
    servicos S, S_ORD;
    vendas V, V_ORD;

    FILE *arqPF = fopen("arqPF.bin", "rb+");
    FILE *arqPJ = fopen("arqPJ.bin", "rb+");
    FILE *arqMaq = fopen("arqMaquinario.bin", "rb+");
    FILE *arqPec = fopen("arqPecas.bin", "rb+");
    FILE *arqSer = fopen("arqServicos.bin", "rb+");
    FILE *arqVen = fopen("arqVendas.bin", "rb+");

    int op, op2, op3, i, qtd=0;

    if (arqPF == NULL) {
        arqPF = fopen("arqPF.bin", "wb+");
        if (arqPF == NULL) {
            printf("\nERRO ao criar o arquivo de clientes PF!");
            return;
    	}
	}

	if (arqPJ == NULL) {
	    arqPJ = fopen("arqPJ.bin", "wb+");
	    if (arqPJ == NULL) {
	        printf("\nERRO ao criar o arquivo de clientes PJ!");
	        return;
	    }
	}

	if (arqMaq == NULL) {
	    arqMaq = fopen("arqMaquinario.bin", "wb+");
	    if (arqMaq == NULL) {
	        printf("\nERRO ao criar o arquivo de maquinarios!");
	        return;
	    }
	}

	if (arqPec == NULL) {
	    arqPec = fopen("arqPecas.bin", "wb+");
	    if (arqPec == NULL) {
	        printf("\nERRO ao criar o arquivo de pecas!");
	        return;
	    }
	}
	
	if (arqSer == NULL) {
	    arqSer = fopen("arqServicos.bin", "wb+");
	    if (arqSer == NULL) {
	        printf("\nERRO ao criar o arquivo de servicos!");
	        return;
	    }
	}

    if (arqVen == NULL) {
        arqVen = fopen("arqVendas.bin", "wb+");
	    if (arqVen == NULL) {
	        printf("\nERRO ao criar o arquivo de venda!");
	        return;
	    }
    }

    do {
        system("cls");
        printf("\n--- ORDENACAO ---\n");
        printf("\n1 - Clientes");
        printf("\n2 - Produtos");
        printf("\n3 - Servicos");
        printf("\n4 - Vendas");
        printf("\n0 - Retornar ao menu");
        printf("\nEscolha: ");
        scanf("%d", &op);

        switch (op) {
        case 1:
                system("cls");
                printf("\n--- ORDENACAO DE CLIENTES ---\n");
                printf("\n1 - Clientes PF");
                printf("\n2 - Clientes PJ");
                printf("\n0 - Retornar");
                printf("\nEscolha: ");
                scanf("%d", &op2);

                switch (op2) {
                case 1:
                        fseek(arqPF, 0, SEEK_END);
                        qtd = ftell(arqPF) / sizeof(clientesPF);

                        while(qtd > 1) {
                            for(i=0; i<qtd-1; i++) {
                                fseek(arqPF, i * sizeof(clientesPF), SEEK_SET);
                                fread(&PF, sizeof(clientesPF), 1, arqPF);

                                fseek(arqPF, (i + 1) * sizeof(clientesPF), SEEK_SET);
                                fread(&PF_ORD, sizeof(clientesPF), 1, arqPF);
                                
                                if(strcmp(PF.nome, PF_ORD.nome) > 0) {
                                    fseek(arqPF, i * sizeof(clientesPF), SEEK_SET);
                                    fwrite(&PF_ORD, sizeof(clientesPF), 1, arqPF);

                                    fseek(arqPF, (i + 1) * sizeof(clientesPF), SEEK_SET);
                                    fwrite(&PF, sizeof(clientesPF), 1, arqPF);
                                }
                            }
                            qtd--;
                        }
                        fclose(arqPF);
                        printf("\nArquivo ordenado!\n");
	                    system("pause");
                    break;
                case 2:
                        fseek(arqPJ, 0, SEEK_END);
                        qtd = ftell(arqPJ) / sizeof(clientesPJ);

                        while(qtd > 1) {
                                for(i=0; i<qtd-1; i++) {
                                fseek(arqPJ, i * sizeof(clientesPJ), SEEK_SET);
                                fread(&PJ, sizeof(clientesPJ), 1, arqPJ);

                                fseek(arqPJ, (i + 1) * sizeof(clientesPJ), SEEK_SET);
                                fread(&PJ_ORD, sizeof(clientesPJ), 1, arqPJ);

                                if(strcmp(PJ.nomeEmpresarial, PJ_ORD.nomeEmpresarial) > 0) {
                                    fseek(arqPJ, i * sizeof(clientesPJ), SEEK_SET);
                                    fwrite(&PJ_ORD, sizeof(clientesPJ), 1, arqPJ);

                                    fseek(arqPJ, (i + 1) * sizeof(clientesPJ), SEEK_SET);
                                    fwrite(&PJ, sizeof(clientesPJ), 1, arqPJ);
                                }
                            }
                            qtd--;
                        }
                        fclose(arqPJ);
                        printf("\nArquivo ordenado!\n");
	                    system("pause");
                    break;
                case 0:
                        printf("\nRetornar...");
                    break;
                default:
                        printf("\nERRO: escolha uma opcao valida!\n");
                        system("pause");
                    break;
                }
            break;
        case 2:
                system("cls");
                printf("\n--- ORDENACAO DE PRODUTOS ---\n");
                printf("\n1 - Maquinarios");
                printf("\n2 - Pecas");
                printf("\n0 - Retornar");
                printf("\nEscolha: ");
                scanf("%d", &op2);

                switch (op2) {
                case 1:
                        fseek(arqMaq, 0, SEEK_END);
                        qtd = ftell(arqMaq) / sizeof(maquinarios);

                        while(qtd > 1) {
                                for(i=0; i<qtd-1; i++) {
                                fseek(arqMaq, i * sizeof(maquinarios), SEEK_SET);
                                fread(&M, sizeof(maquinarios), 1, arqMaq);

                                fseek(arqMaq, (i + 1) * sizeof(maquinarios), SEEK_SET);
                                fread(&M_ORD, sizeof(maquinarios), 1, arqMaq);

                                if(strcmp(M.nome, M_ORD.nome) > 0) {
                                    fseek(arqMaq, i * sizeof(maquinarios), SEEK_SET);
                                    fwrite(&M_ORD, sizeof(maquinarios), 1, arqMaq);

                                    fseek(arqMaq, (i + 1) * sizeof(maquinarios), SEEK_SET);
                                    fwrite(&M, sizeof(maquinarios), 1, arqMaq);
                                }
                            }
                            qtd--;
                        }
                        fclose(arqMaq);
                        printf("\nArquivo ordenado!\n");
	                    system("pause");
                    break;
                case 2:
                        fseek(arqPec, 0, SEEK_END);
                        qtd = ftell(arqPec) / sizeof(pecas);

                        while(qtd > 1) {
                                for(i=0; i<qtd-1; i++) {
                                fseek(arqPec, i * sizeof(pecas), SEEK_SET);
                                fread(&P, sizeof(pecas), 1, arqPec);

                                fseek(arqPec, (i + 1) * sizeof(pecas), SEEK_SET);
                                fread(&P_ORD, sizeof(pecas), 1, arqPec);

                                if(strcmp(P.nome, P_ORD.nome) > 0) {
                                fseek(arqPec, i * sizeof(pecas), SEEK_SET);
                                fwrite(&P_ORD, sizeof(pecas), 1, arqPec);

                                fseek(arqPec, (i + 1) * sizeof(pecas), SEEK_SET);
                                fwrite(&P, sizeof(pecas), 1, arqPec);
                                }
                            }
                            qtd--;
                        }
                        fclose(arqPec);
                        printf("\nArquivo ordenado!\n");
	                    system("pause");
                    break;
                case 0:
                        printf("\nRetornar...");
                    break;
                default:
                        printf("\nERRO: escolha uma opcao valida!\n");
                        system("pause");
                    break;
                }
            break;
        case 3:
                system("cls");
                printf("\n--- ORDENACAO DE SERVICO ---\n");
                printf("\n1 - Servicos");
                printf("\n0 - Retornar");
                printf("\nEscolha: ");
                scanf("%d", &op3);

                switch (op3) {
                case 1:
                        fseek(arqSer, 0, SEEK_END);
                        qtd = ftell(arqSer) / sizeof(servicos);

                        while(qtd > 1) {
                                for(i=0; i<qtd-1; i++) {
                                fseek(arqSer, i * sizeof(servicos), SEEK_SET);
                                fread(&S, sizeof(servicos), 1, arqSer);
                                
                                fseek(arqSer, (i + 1) * sizeof(servicos), SEEK_SET);
                                fread(&S_ORD, sizeof(servicos), 1, arqSer);

                                if(strcmp(S.tipoServico, S_ORD.tipoServico) > 0) {
                                    fseek(arqSer, i * sizeof(servicos), SEEK_SET);
                                    fwrite(&S_ORD, sizeof(servicos), 1, arqSer);

                                    fseek(arqSer, (i + 1) * sizeof(servicos), SEEK_SET);
                                    fwrite(&S, sizeof(servicos), 1, arqSer);
                                }
                            }
                            qtd--;
                        }
                        fclose(arqSer);
                        printf("\nArquivo ordenado!\n");
	                    system("pause");
                    break;
                case 0:
                        printf("\nRetornar...");
                    break;
                default:
                        printf("\nERRO: escolha uma opcao valida!\n");
                        system("pause");
                    break;
                }
            break;
        case 4:
                system("cls");
                printf("\n--- ORDENACAO DE VENDAS ---\n");
                printf("\n1 - Vendas");
                printf("\n0 - Retornar");
                printf("\nEscolha: ");
                scanf("%d", &op3);

                switch (op3) {
                case 1:
                        fseek(arqVen, 0, SEEK_END);
                        qtd = ftell(arqVen) / sizeof(vendas);

                        while(qtd > 1) {
                                for(i=0; i<qtd-1; i++) {
                                fseek(arqVen, i * sizeof(vendas), SEEK_SET);
                                fread(&V, sizeof(vendas), 1, arqVen);
                                
                                fseek(arqVen, (i + 1) * sizeof(vendas), SEEK_SET);
                                fread(&V_ORD, sizeof(vendas), 1, arqVen);

                                if(V.D.dataVendaAno > V_ORD.D.dataVendaAno || (V.D.dataVendaAno == V_ORD.D.dataVendaAno && V.D.dataVendaMes > V_ORD.D.dataVendaMes) || (V.D.dataVendaAno == V_ORD.D.dataVendaAno && V.D.dataVendaMes == V_ORD.D.dataVendaMes && V.D.dataVendaDia > V_ORD.D.dataVendaDia)) {
                                    fseek(arqVen, i * sizeof(vendas), SEEK_SET);
                                    fwrite(&V_ORD, sizeof(vendas), 1, arqVen);

                                    fseek(arqVen, (i + 1) * sizeof(vendas), SEEK_SET);
                                    fwrite(&V, sizeof(vendas), 1, arqVen);
                                }
                            }
                            qtd--;
                        }
                        fclose(arqVen);
                        printf("\nArquivo ordenado!\n");
	                    system("pause");
                    break;
                case 0:
                        printf("\nRetornar...");
                    break;
                default:
                        printf("\nERRO: escolha uma opcao valida!\n");
                        system("pause");
                    break;
                }
            break;
        case 0:
                printf("\nERRO: escolha uma opcao valida!\n");
            break;
        default:
                printf("\nERRO: escolha uma opcao valida!\n");
            break;
        }
    } while (op != 0);

    fclose(arqPF);
    fclose(arqPJ);
    fclose(arqMaq);
    fclose(arqPec);
    fclose(arqSer);
    fclose(arqVen);
}

// FIM DA FUNCAO DE ORDENACAO --------------------------------------------
// INICIO DA FUNCAO DO MAIN ----------------------------------------------

int main() {
    int op;

    do {
        system("cls");
        printf("\n--- MENU ---\n");
        printf("\n1 - Cadastro");
        printf("\n2 - Busca");
        printf("\n3 - Editar");
        printf("\n4 - Realizar venda");
        printf("\n5 - Excluir");
        printf("\n6 - Relatorios");
        printf("\n7 - Ordenacao");
        printf("\n0 - Sair");
        printf("\nEscolha: ");
        scanf("%d", &op);
        getchar();

        switch (op) {
        case 1:
                cadastroDeClientes();
            break;
        case 2:
                buscaDeCadastros();
            break;
        case 3:
                editarCadastros();
            break;
        case 4:
                realizarVenda();
            break;
        case 5:
                realizarExclusao();
            break;
        case 6:
    			relatorios();
    		break;
        case 7:
                ordenacao();
            break;
        case 0:
                printf("\nEncerrando...");
            break;
        default:
                printf("\nERRO: escolha uma opcao valida!\n");
            break;
        }

    } while (op != 0);

    return 0;
}

// FIM DA FUNCAO DO MAIN ----------------------------------------------