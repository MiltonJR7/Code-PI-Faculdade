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
    char tipoServico[MAXSTR], cpfParaContrato[12], cnpjParaContrato[15], descricao[MAXSTR];
    float preco;
    date D;
} servicos;

typedef struct {
    char cpfVenda[12], cnpjVenda[15], codigoVenda[20];
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

int validarSerPF(FILE *arqSer, char cpfParaContrato[]) {
    servicos S;

    rewind(arqSer);
    while (fread(&S, sizeof(servicos), 1, arqSer) == 1) {
        if (stricmp(cpfParaContrato, S.cpfParaContrato) == 0) {
            return(ftell(arqSer) - sizeof(servicos));
        }    
    }

    return -1;
}

int validarSerPJ(FILE *arqSer, char cnpjParaContrato[]) {
    servicos S;

    rewind(arqSer);
    while (fread(&S, sizeof(servicos), 1, arqSer) == 1) {
        if(stricmp(cnpjParaContrato, S.cnpjParaContrato) == 0) {
            return(ftell(arqSer) - sizeof(servicos));
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

void limparBuffer() {
    while (getchar() != '\n');
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

    int op, op2, op3, posCPF, posCNPJ, posMaq, posPec, posSerPF, posSerPJ, existeCpf, existeCnpj;

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

//fim de abertura de arquivo

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

                                    printf("\nSeu telefone:");
                                    scanf("%11s", PF.telefone);
                                    limparBuffer();

                                    printf("\nSua data de nascimento <dd mm aaaa>: ");
                                    scanf("%d%d%d", &PF.D.dia, &PF.D.mes, &PF.D.ano);
                                    getchar();

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

                                    printf("\nO telefone empresarial:");
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
                    printf("\n1 - Cliente PF");
                    printf("\n2 - Cliente PJ");
                    printf("\n0 - Retornar");
                    printf("\nEscolha: ");
                    scanf("%d", &op3);
                    getchar();

                    switch (op3) {
                        case 1:
                                system("cls");
                                printf("\n--- CADASTRAR SERVICO PARA PF ---\n");
                                printf("\nDigite o cpf para cadastrar o servico: ");
                                scanf("%11s", S.cpfParaContrato);
                                limparBuffer();

                                posSerPF = validarSerPF(arqSer, S.cpfParaContrato);
                                
                                if (posSerPF == -1) {
                                    
                                    existeCpf = validarSerCadPF(arqPF, S.cpfParaContrato);

                                    if (existeCpf == -1) {
                                        printf("\nERRO: o cpf digitado nao foi encontrado!\n");
                                    } else {
                                        printf("\nQual o tipo de servico: ");
                                        fgets(S.tipoServico, MAXSTR, stdin);
                                        S.tipoServico[strcspn(S.tipoServico, "\n")] = '\0';

                                        printf("\nQual a descricao: ");
                                        fgets(S.descricao, MAXSTR, stdin);
                                        S.descricao[strcspn(S.descricao, "\n")] = '\0';

                                        printf("\nQual o preco do servico: ");
                                        scanf("%f", &S.preco);

                                        printf("\nQual a data para o servico <dd/mm/aaaa> : ");
                                        scanf("%d%d%d", &S.D.dia, &S.D.mes, &S.D.ano);
                                        getchar();

                                        salvarServico(S);
                                        printf("\nServico cadastrado com sucesso!\n\n");
                                    }

                                } else {
                                    servicos S_cpf_jaCadastrado;
                                    fseek(arqSer, posSerPF, 0);
                                    fread(&S_cpf_jaCadastrado, sizeof(servicos), 1, arqSer);
                                    printf("\nO CPF digitado: %.3s.%.3s.%.3s-%.2s ja esta com um servico pendente!\n", S_cpf_jaCadastrado.cpfParaContrato, S_cpf_jaCadastrado.cpfParaContrato+3, S_cpf_jaCadastrado.cpfParaContrato+6, S_cpf_jaCadastrado.cpfParaContrato+9);
                                }                                           
                            break;
                        case 2:
                                system("cls");
                                printf("\n--- CADASTRAR SERVICO PARA PJ ---\n");
                                printf("\nDigite o cnpj para cadastrar o servico: ");
                                scanf("%14s", S.cnpjParaContrato);
                                limparBuffer();

                                posSerPJ = validarSerPJ(arqSer, S.cnpjParaContrato);
                                
                                if (posSerPJ == -1) {
                                    
                                    existeCnpj = validarSerCadPJ(arqPJ, S.cnpjParaContrato);

                                    if (existeCnpj == -1) {
                                        printf("\nERRO: o cnpj digitado nao foi encontrado!\n");
                                    } else {
                                        printf("\nQual o tipo de servico: ");
                                        fgets(S.tipoServico, MAXSTR, stdin);
                                        S.tipoServico[strcspn(S.tipoServico, "\n")] = '\0';

                                        printf("\nQual a descricao: ");
                                        fgets(S.descricao, MAXSTR, stdin);
                                        S.descricao[strcspn(S.descricao, "\n")] = '\0';

                                        printf("\nQual o preco do servico: ");
                                        scanf("%f", &S.preco);

                                        printf("\nQual a data para o servico <dd/mm/aaaa> : ");
                                        scanf("%d%d%d", &S.D.dia, &S.D.mes, &S.D.ano);
                                        getchar();

                                        salvarServico(S);
                                        printf("\nServico cadastrado com sucesso!\n\n");
                                    }

                                } else {
                                    servicos S_cnpj_jaCadastrado;
                                    fseek(arqSer, posSerPJ, 0);
                                    fread(&S_cnpj_jaCadastrado, sizeof(servicos), 1, arqSer);
                                    printf("\nO CNPJ digitado: %.2s.%.3s.%.3s/%.4s-%2s ja esta com um servico pendente!\n", S_cnpj_jaCadastrado.cnpjParaContrato, S_cnpj_jaCadastrado.cnpjParaContrato+2, S_cnpj_jaCadastrado.cnpjParaContrato+5, S_cnpj_jaCadastrado.cnpjParaContrato+8, S_cnpj_jaCadastrado.cnpjParaContrato+12);
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

    char buscCpf[12], buscCnpj[15], buscCodMaq[20], buscCodPec[20], buscCpfServ[12], buscCnpjServ[15];
    int op, op2, op3, achou;
    
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
//fim de abertura de arquivo

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

                            achou = 0;
                            rewind(arqPF);
                            while (fread(&PF, sizeof(clientesPF), 1, arqPF) == 1 && !achou) {
                                if (stricmp(buscCpf, PF.cpf) == 0) {
                                    printf("\nDados do cliente:");
                                    printf("\nNome: %s \nEmail: %s \nCpf: %.3s.%.3s.%.3s-%.2s \nFone: (%.2s) %.5s-%.4s \nData de nascimento: %02d/%02d/%04d \n", PF.nome, PF.email, PF.cpf, PF.cpf+3, PF.cpf+6, PF.cpf+9, PF.telefone, PF.telefone+2, PF.telefone+7, PF.D.dia, PF.D.mes, PF.D.ano);
                                    achou = 1;
                                    printf("\n");
                                    system("pause");
                                }
                            }

                            if (!achou) {
                                printf("\nERRO: nao ha cadastro com o CPF digitado!");
                                printf("\n");
                                system("pause");
                            }
                        break;
                    case 2:
                            system("cls");
                            printf("\n--- CLIENTES PJ ---\n");
                            printf("\nUse o cnpj para buscar: ");
                            scanf("%14s", buscCnpj);
                            limparBuffer();

                            achou = 0;
                            rewind(arqPJ);
                            while (fread(&PJ, sizeof(clientesPJ), 1, arqPJ) == 1 && !achou) {
                                if (stricmp(buscCnpj, PJ.cnpj) == 0) {
                                    printf("\nDados da empresa:");
                                    printf("\nNome: %s \nEmail: %s \nCnpj: %.2s.%.3s.%.3s/%.4s-%2s \nResponsavel: %s \nFone: (%.2s) %.5s-%.4s \n", PJ.nomeEmpresarial, PJ.emailEmpresarial, PJ.cnpj, PJ.cnpj+2, PJ.cnpj+5, PJ.cnpj+8, PJ.cnpj+12, PJ.nomeDoResponsavel, PJ.telefoneEmpresarial, PJ.telefoneEmpresarial+2, PJ.telefoneEmpresarial+7);
                                    achou = 1;
                                    printf("\n");
                                    system("pause");
                                }
                            }

                            if (!achou) {
                                printf("\nERRO: nao ha cadastro com o CNPJ digitado!");
                                printf("\n");
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

                            achou = 0;
                            rewind(arqMaq);
                            while (fread(&M, sizeof(maquinarios), 1, arqMaq) == 1 && !achou) {
                                if (stricmp(buscCodMaq, M.codigo) == 0) {
                                    printf("\nDados do maquinario:");
                                    printf("\nNome: %s \nCategoria: %s \nCodigo: %s \nQuantidade: %d \nPreco: %.2f\n", M.nome, M.categoria, M.codigo, M.quantidade, M.preco);
                                    achou = 1;
                                    printf("\n");
                                    system("pause");
                                }
                            }

                            if (!achou) {
                                printf("\nERRO: nao ha cadastro com o codigo digitado!");
                                printf("\n");
                                system("pause");
                            }
                        break;
                    case 2:
                            system("cls");
                            printf("\n--- PECAS ---\n");
                            printf("\nUse o codigo para buscar: ");
                            scanf("%19s", buscCodPec);
                            limparBuffer();

                            achou = 0;
                            rewind(arqPec);
                            while (fread(&P, sizeof(pecas), 1, arqPec) == 1 && !achou) {
                                if (stricmp(buscCodPec, P.codigo) == 0) {
                                    printf("\nDados da peca:");
                                    printf("\nNome: %s \nCategoria: %s \nCodigo: %s \nQuantidade: %d \nPreco: %.2f\n", P.nome, P.categoria, P.codigo, P.quantidade, P.preco);
                                    achou = 1;
                                    printf("\n");
                                    system("pause");
                                }
                            }

                            if (!achou) {
                                printf("\nERRO: nao ha cadastro com o codigo digitado!");
                                printf("\n");
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
                    printf("\n1 - Cliente PF");
                    printf("\n2 - Cliente PJ");
                    printf("\n0 - Retornar");
                    printf("\nEscolha: ");
                    scanf("%d", &op3);
                    getchar();

                    switch (op3) {
                    case 1:
                            system("cls");
                            printf("\n--- BUSCA DE SERVICOS EM PF ---\n");
                            printf("\nDigite o cpf para cadastrar o servico: ");
                            scanf("%11s", buscCpfServ);
                            limparBuffer();

                            achou = 0;

                            while (fread(&S, sizeof(servicos), 1, arqSer) == 1 && !achou) {
                                if (stricmp(buscCpfServ, S.cpfParaContrato) == 0) {
                                    printf("\nDados do servico:");
                                    printf("\nTipo de servico: %s \nDescricao: %s \nPreco: %.2f \nData: %02d/%02d/%02d \nCPF: %.3s.%.3s.%.3s-%.2s\n", S.tipoServico, S.descricao, S.preco, S.D.dia, S.D.mes, S.D.ano, S.cpfParaContrato, S.cpfParaContrato+3, S.cpfParaContrato+6, S.cpfParaContrato+9);
                                    achou = 1;
                                    printf("\n");
                                    system("pause");
                                }                                         
                            }

                            if (!achou) {
                                printf("\nNao a servicos cadastrados no cpf digitado!\n");
                                printf("\n");
                                system("pause");
                            }
                        break;
                    case 2:
                            system("cls");
                            printf("\n--- BUSCA DE SERVICOS EM PJ ---\n");
                            printf("\nDigite o cnpj para cadastrar o servico: ");
                            scanf("%14s", buscCnpjServ);
                            limparBuffer();

                            achou = 0;

                            while (fread(&S, sizeof(servicos), 1, arqSer) == 1 && !achou) {
                                if (stricmp(buscCnpjServ, S.cnpjParaContrato) == 0) {
                                    printf("\nDados do servico:");
                                    printf("\nTipo de servico: %s \nDescricao: %s \nPreco: %.2f \nData: %02d/%02d/%02d \nCNPJ: %.2s.%.3s.%.3s/%.4s-%2s\n", S.tipoServico, S.descricao, S.preco, S.D.dia, S.D.mes, S.D.ano, S.cnpjParaContrato, S.cnpjParaContrato+2, S.cnpjParaContrato+5, S.cnpjParaContrato+8, S.cnpjParaContrato+12);
                                    achou = 1;
                                    printf("\n");
                                    system("pause");
                                }                                          
                            }

                            if (!achou) {
                                printf("\nNao a servicos cadastrados no cnpj digitado!\n");
                                printf("\n");
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

    int op, op2, op3, posCPF, posCNPJ, posMaq, posPec, posSerPF, posSerPJ;

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
                                printf("ERRO: CPF nao encontrado!\n");
                            } else {
                                fseek(arqPF, posCPF, SEEK_SET);
                                fread(&PF, sizeof(clientesPF), 1, arqPF);

                                printf("\n----------------\n");
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
                                                printf("\nTelefone atualizado com sucesso!\n");

                                                printf("\nDados salvos: \n");
                                                fseek(arqPF, posCPF, SEEK_SET);
                                                fread(&PF, sizeof(clientesPF), 1, arqPF);

                                                printf("\n----------------\n");
                                                printf("\nNome: %s", PF.nome);
                                                printf("\nTelefone: (%.2s) %.5s-%.4s", PF.telefone, PF.telefone+2, PF.telefone+7);
                                                printf("\nEmail: %s", PF.email);
                                                printf("\nData de nascimento: %02d/%02d/%04d", PF.D.dia, PF.D.mes, PF.D.ano);
                                                printf("\n----------------\n");

                                            break;

                                        case 2:
                                                system("cls");
                                                printf("Novo email: ");
                                                fgets(PF.email, MAXSTR, stdin);
                                                PF.email[strcspn(PF.email, "\n")] = '\0';

                                                fseek(arqPF, posCPF, SEEK_SET);
                                                fwrite(&PF, sizeof(clientesPF), 1, arqPF);
                                                printf("\nEmail alterado!\n");

                                                printf("\nDados salvos: \n");
                                                fseek(arqPF, posCPF, SEEK_SET);
                                                fread(&PF, sizeof(clientesPF), 1, arqPF);

                                                printf("\n----------------\n");
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
                                printf("ERRO: CNPJ nao encontrado!\n");
                            } else {
                                fseek(arqPJ, posCNPJ, SEEK_SET);
                                fread(&PJ, sizeof(clientesPJ), 1, arqPJ);

                                printf("\n----------------\n");
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

                                                printf("\nNome empresarial atualizado com sucesso!\n");
                                                printf("\nDados salvos: \n");

                                                fseek(arqPJ, posCNPJ, SEEK_SET);
                                                fread(&PJ, sizeof(clientesPJ), 1, arqPJ);

                                                printf("\n----------------\n");
                                                printf("\nNome empresarial: %s", PJ.nomeEmpresarial);
                                                printf("\nFone: (%.2s) %.5s-%.4s", PJ.telefoneEmpresarial, PJ.telefoneEmpresarial+2, PJ.telefoneEmpresarial+7);
                                                printf("\nEmail: %s", PJ.emailEmpresarial);
                                                printf("\nNome do responsavel: %s", PJ.nomeDoResponsavel);
                                                printf("\n----------------\n");

                                            break;

                                        case 2:
                                                system("cls");
                                                printf("Novo telefone: ");
                                                scanf("%11s", PJ.telefoneEmpresarial);
                                                limparBuffer();

                                                fseek(arqPJ, posCNPJ, SEEK_SET);
                                                fwrite(&PJ, sizeof(clientesPJ), 1, arqPJ);

                                                printf("\nTelefone alterado!\n");
                                                printf("\nDados salvos: \n");

                                                fseek(arqPJ, posCNPJ, SEEK_SET);
                                                fread(&PJ, sizeof(clientesPJ), 1, arqPJ);

                                                printf("\n----------------\n");
                                                printf("\nNome empresarial: %s", PJ.nomeEmpresarial);
                                                printf("\nFone: (%.2s) %.5s-%.4s", PJ.telefoneEmpresarial, PJ.telefoneEmpresarial+2, PJ.telefoneEmpresarial+7);
                                                printf("\nEmail: %s", PJ.emailEmpresarial);
                                                printf("\nNome do responsavel: %s", PJ.nomeDoResponsavel);
                                                printf("\n----------------\n");

                                            break;
                                        case 3:
                                                system("cls");
                                                printf("Novo email: ");
                                                fgets(PJ.emailEmpresarial, MAXSTR, stdin);
                                                PJ.emailEmpresarial[strcspn(PJ.emailEmpresarial, "\n")] = '\0';

                                                fseek(arqPJ, posCNPJ, SEEK_SET);
                                                fwrite(&PJ, sizeof(clientesPJ), 1, arqPJ);
                                                
                                                printf("\nEmail alterado!\n");
                                                printf("\nDados salvos: \n");

                                                fseek(arqPJ, posCNPJ, SEEK_SET);
                                                fread(&PJ, sizeof(clientesPJ), 1, arqPJ);

                                                printf("\n----------------\n");
                                                printf("\nNome empresarial: %s", PJ.nomeEmpresarial);
                                                printf("\nFone: (%.2s) %.5s-%.4s", PJ.telefoneEmpresarial, PJ.telefoneEmpresarial+2, PJ.telefoneEmpresarial+7);
                                                printf("\nEmail: %s", PJ.emailEmpresarial);
                                                printf("\nNome do responsavel: %s", PJ.nomeDoResponsavel);
                                                printf("\n----------------\n");

                                            break;
                                        case 4:
                                                system("cls");
                                                printf("Novo nome do responsavel: ");
                                                fgets(PJ.nomeDoResponsavel, MAXSTR, stdin);
                                                PJ.nomeDoResponsavel[strcspn(PJ.nomeDoResponsavel, "\n")] = '\0';

                                                fseek(arqPJ, posCNPJ, SEEK_SET);
                                                fwrite(&PJ, sizeof(clientesPJ), 1, arqPJ);

                                                printf("\nNome do responsavel alterado!\n");
                                                printf("\nDados salvos: \n");

                                                fseek(arqPJ, posCNPJ, SEEK_SET);
                                                fread(&PJ, sizeof(clientesPJ), 1, arqPJ);

                                                printf("\n----------------\n");
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
                                printf("ERRO: CODIGO nao encontrado!\n");
                            } else {
                                fseek(arqMaq, posMaq, SEEK_SET);
                                fread(&M, sizeof(maquinarios), 1, arqMaq);

                                printf("\n----------------\n");
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
                                                
                                                printf("\nNome do maquinario atualizado com sucesso!\n");
                                                printf("\nDados salvos: \n");

                                                fseek(arqMaq, posMaq, SEEK_SET);
                                                fread(&M, sizeof(maquinarios), 1, arqMaq);

                                                printf("\n----------------\n");
                                                printf("\nNome do maquinario: %s", M.nome);
                                                printf("\nCategoria: %s", M.categoria);
                                                printf("\nQuantidade: %d", M.quantidade);
                                                printf("\nPreco: %.2f", M.preco);
                                                printf("\n----------------\n");

                                            break;

                                        case 2:
                                                system("cls");
                                                printf("Nova categoria: ");
                                                fgets(M.categoria, MAXSTR, stdin);
                                                M.categoria[strcspn(M.categoria, "\n")] = '\0';

                                                fseek(arqMaq, posMaq, SEEK_SET);
                                                fwrite(&M, sizeof(maquinarios), 1, arqMaq);
                                                
                                                printf("\nCategoria alterada!\n");
                                                printf("\nDados salvos: \n");

                                                fseek(arqMaq, posMaq, SEEK_SET);
                                                fread(&M, sizeof(maquinarios), 1, arqMaq);
                                                
                                                printf("\n----------------\n");
                                                printf("\nNome do maquinario: %s", M.nome);
                                                printf("\nCategoria: %s", M.categoria);
                                                printf("\nQuantidade: %d", M.quantidade);
                                                printf("\nPreco: %.2f", M.preco);
                                                printf("\n----------------\n");

                                            break;
                                        case 3:
                                                system("cls");
                                                printf("Nova quantidade: ");
                                                scanf("%d", &M.quantidade);
                                                getchar();

                                                fseek(arqMaq, posMaq, SEEK_SET);
                                                fwrite(&M, sizeof(maquinarios), 1, arqMaq);
                                                
                                                printf("\nQuantidade alterada!\n");
                                                printf("\nDados salvos: \n");

                                                fseek(arqMaq, posMaq, SEEK_SET);
                                                fread(&M, sizeof(maquinarios), 1, arqMaq);
                                                
                                                printf("\n----------------\n");
                                                printf("\nNome do maquinario: %s", M.nome);
                                                printf("\nCategoria: %s", M.categoria);
                                                printf("\nQuantidade: %d", M.quantidade);
                                                printf("\nPreco: %.2f", M.preco);
                                                printf("\n----------------\n");

                                            break;
                                        case 4:
                                                system("cls");
                                                printf("Novo preco: ");
                                                scanf("%f", &M.preco);
                                                getchar();

                                                fseek(arqMaq, posMaq, SEEK_SET);
                                                fwrite(&M, sizeof(maquinarios), 1, arqMaq);
                                                
                                                printf("\nPreco alterado!\n");
                                                printf("\nDados salvos: \n");

                                                fseek(arqMaq, posMaq, SEEK_SET);
                                                fread(&M, sizeof(maquinarios), 1, arqMaq);
                                                
                                                printf("\n----------------\n");
                                                printf("\nNome do maquinario: %s", M.nome);
                                                printf("\nCategoria: %s", M.categoria);
                                                printf("\nQuantidade: %d", M.quantidade);
                                                printf("\nPreco: %.2f", M.preco);
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
                            printf("\n--- EDITAR PECAS ---\n");
                            printf("\nInforme o CODIGO da peca para as alteracoes: ");
                            scanf("%19s", P.codigo);
                            limparBuffer();

                            posPec = validarPecas(arqPec, P.codigo);

                            if (posPec == -1) {
                                printf("ERRO: CODIGO nao encontrado!\n");
                            } else {
                                fseek(arqPec, posPec, SEEK_SET);
                                fread(&P, sizeof(pecas), 1, arqPec);

                                printf("\n----------------\n");
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
                                                
                                                printf("\nNome da peca atualizado com sucesso!\n");
                                                printf("\nDados salvos: \n");

                                                fseek(arqPec, posPec, SEEK_SET);
                                                fread(&P, sizeof(pecas), 1, arqPec);

                                                printf("\n----------------\n");
                                                printf("\nNome da peca: %s", P.nome);
                                                printf("\nCategoria: %s", P.categoria);
                                                printf("\nQuantidade: %d", P.quantidade);
                                                printf("\nPreco: %.2f", P.preco);
                                                printf("\n----------------\n");

                                            break;

                                        case 2:
                                                system("cls");
                                                printf("Nova categoria: ");
                                                fgets(P.categoria, MAXSTR, stdin);
                                                P.categoria[strcspn(P.categoria, "\n")] = '\0';

                                                fseek(arqPec, posPec, SEEK_SET);
                                                fwrite(&P, sizeof(pecas), 1, arqPec);
                                                
                                                printf("\nCategoria alterada!\n");
                                                printf("\nDados salvos: \n");

                                                fseek(arqPec, posPec, SEEK_SET);
                                                fread(&P, sizeof(pecas), 1, arqPec);
                                                
                                                printf("\n----------------\n");
                                                printf("\nNome da peca: %s", P.nome);
                                                printf("\nCategoria: %s", P.categoria);
                                                printf("\nQuantidade: %d", P.quantidade);
                                                printf("\nPreco: %.2f", P.preco);
                                                printf("\n----------------\n");

                                            break;
                                        case 3:
                                                system("cls");
                                                printf("Nova quantidade: ");
                                                scanf("%d", &P.quantidade);
                                                getchar();

                                                fseek(arqPec, posPec, SEEK_SET);
                                                fwrite(&P, sizeof(pecas), 1, arqPec);
                                                
                                                printf("\nQuantidade alterada!\n");
                                                printf("\nDados salvos: \n");

                                                fseek(arqPec, posPec, SEEK_SET);
                                                fread(&P, sizeof(pecas), 1, arqPec);
                                                
                                                printf("\n----------------\n");
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
                                                
                                                printf("\nPreco alterado!\n");
                                                printf("\nDados salvos: \n");

                                                fseek(arqPec, posPec, SEEK_SET);
                                                fread(&P, sizeof(pecas), 1, arqPec);
                                                
                                                printf("\n----------------\n");
                                                printf("\nNome da peca: %s", P.nome);
                                                printf("\nCategoria: %s", P.categoria);
                                                printf("\nQuantidade: %d", P.quantidade);
                                                printf("\nPreco: %.2f", P.preco);
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
        case 3:
            do {
                system("cls");
                printf("\n--- EDICAO DE SERVICOS ---\n");
                printf("\n1 - Cliente PF");
                printf("\n2 - Cliente PJ");
                printf("\n0 - Retornar");
                printf("\nEscolha: ");
                scanf("%d", &op3);
                getchar();

                switch (op3) {
                case 1:
                        do {
                            system("cls");
                            printf("\n--- EDITAR SERVICO PF ---\n");
                            printf("\nInforme o CPF do cliente para as alteracoes em servico: ");
                            scanf("%11s", S.cpfParaContrato);
                            limparBuffer();

                            posSerPF = validarSerPF(arqSer, S.cpfParaContrato);

                            if (posSerPF == -1) {
                                printf("ERRO: CPF nao existe servicos pendentes!\n");
                            } else {
                                fseek(arqSer, posSerPF, SEEK_SET);
                                fread(&S, sizeof(servicos), 1, arqSer);

                                printf("\n----------------\n");
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

                                                fseek(arqSer, posSerPF, SEEK_SET);
                                                fwrite(&S, sizeof(servicos), 1, arqSer);
                                                
                                                printf("\nTipo de servico atualizado com sucesso!\n");
                                                printf("\nDados salvos: \n");

                                                fseek(arqSer, posSerPF, SEEK_SET);
                                                fread(&S, sizeof(servicos), 1, arqSer);

                                                printf("\n----------------\n");
                                                printf("\nTipo do servico: %s", S.tipoServico);
                                                printf("\nDescricao: %s", S.descricao);
                                                printf("\nPreco: %.2f", S.preco);
                                                printf("\n----------------\n");

                                            break;

                                        case 2:
                                                system("cls");
                                                printf("Nova descricao: ");
                                                fgets(S.descricao, MAXSTR, stdin);
                                                S.descricao[strcspn(S.descricao, "\n")] = '\0';

                                                fseek(arqSer, posSerPF, SEEK_SET);
                                                fwrite(&S, sizeof(servicos), 1, arqSer);
                                                
                                                printf("\nDescriacao alterada!\n");
                                                printf("\nDados salvos: \n");

                                                fseek(arqSer, posSerPF, SEEK_SET);
                                                fread(&S, sizeof(servicos), 1, arqSer);
                                                
                                                printf("\n----------------\n");
                                                printf("\nTipo do servico: %s", S.tipoServico);
                                                printf("\nDescricao: %s", S.descricao);
                                                printf("\nPreco: %.2f", S.preco);
                                                printf("\n----------------\n");

                                            break;
                                        case 3:
                                                system("cls");
                                                printf("Novo preco: ");
                                                scanf("%f", &S.preco);
                                                getchar();

                                                fseek(arqSer, posSerPF, SEEK_SET);
                                                fwrite(&S, sizeof(servicos), 1, arqSer);
                                                
                                                printf("\nPreco alterado!\n");
                                                printf("\nDados salvos: \n");

                                                fseek(arqSer, posSerPF, SEEK_SET);
                                                fread(&S, sizeof(servicos), 1, arqSer);
                                                
                                                printf("\n----------------\n");
                                                printf("\nTipo do servico: %s", S.tipoServico);
                                                printf("\nDescricao: %s", S.descricao);
                                                printf("\nPreco: %.2f", S.preco);
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
                            printf("\n--- EDITAR SERVICO PJ ---\n");
                            printf("\nInforme o CNPJ do cliente para as alteracoes em servico: ");
                            scanf("%14s", S.cnpjParaContrato);
                            limparBuffer();

                            posSerPJ = validarSerPJ(arqSer, S.cnpjParaContrato);

                            if (posSerPJ == -1) {
                                printf("ERRO: CNPJ nao existe servicos pendentes!\n");
                            } else {
                                fseek(arqSer, posSerPJ, SEEK_SET);
                                fread(&S, sizeof(servicos), 1, arqSer);

                                printf("\n----------------\n");
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

                                                fseek(arqSer, posSerPJ, SEEK_SET);
                                                fwrite(&S, sizeof(servicos), 1, arqSer);
                                                
                                                printf("\nTipo de servico atualizado com sucesso!\n");
                                                printf("\nDados salvos: \n");

                                                fseek(arqSer, posSerPJ, SEEK_SET);
                                                fread(&S, sizeof(servicos), 1, arqSer);

                                                printf("\n----------------\n");
                                                printf("\nTipo do servico: %s", S.tipoServico);
                                                printf("\nDescricao: %s", S.descricao);
                                                printf("\nPreco: %.2f", S.preco);
                                                printf("\n----------------\n");

                                            break;

                                        case 2:
                                                system("cls");
                                                printf("Nova descricao: ");
                                                fgets(S.descricao, MAXSTR, stdin);
                                                S.descricao[strcspn(S.descricao, "\n")] = '\0';

                                                fseek(arqSer, posSerPJ, SEEK_SET);
                                                fwrite(&S, sizeof(servicos), 1, arqSer);
                                                
                                                printf("\nDescriacao alterada!\n");
                                                printf("\nDados salvos: \n");

                                                fseek(arqSer, posSerPJ, SEEK_SET);
                                                fread(&S, sizeof(servicos), 1, arqSer);
                                                
                                                printf("\n----------------\n");
                                                printf("\nTipo do servico: %s", S.tipoServico);
                                                printf("\nDescricao: %s", S.descricao);
                                                printf("\nPreco: %.2f", S.preco);
                                                printf("\n----------------\n");

                                            break;
                                        case 3:
                                                system("cls");
                                                printf("Novo preco: ");
                                                scanf("%f", &S.preco);
                                                getchar();

                                                fseek(arqSer, posSerPJ, SEEK_SET);
                                                fwrite(&S, sizeof(servicos), 1, arqSer);
                                                
                                                printf("\nPreco alterado!\n");
                                                printf("\nDados salvos: \n");

                                                fseek(arqSer, posSerPJ, SEEK_SET);
                                                fread(&S, sizeof(servicos), 1, arqSer);
                                                
                                                printf("\n----------------\n");
                                                printf("\nTipo do servico: %s", S.tipoServico);
                                                printf("\nDescricao: %s", S.descricao);
                                                printf("\nPreco: %.2f", S.preco);
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

void realizarVenda() {
    clientesPF PF;
    clientesPJ PJ;
    maquinarios M;
    pecas P;
    //servicos S;
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

    int op, op2, pos, posMaq, posPec;
    
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
                printf("\n0 - Retornar");
                printf("\nEscolha: ");
                scanf("%d", &op2);

                switch (op2)
                {
                case 1:
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

                        if (pos == -1 || posMaq == -1) {
                            printf("\nERRO: Um dos dados nao exite no cadastro!\n");
                        } else {
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
                                printf("Estoque insuficiente!\n");
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
                                printf("\nData da venda (dd mm aaaa): ");
                                scanf("%d %d %d", &V.D.dataVendaDia, &V.D.dataVendaMes, &V.D.dataVendaAno);
                                getchar();

                                salvarVendas(V);

                                M.quantidade -= V.quantDesejada;
                                fseek(arqMaq, posMaq, SEEK_SET);
                                fwrite(&M, sizeof(maquinarios), 1, arqMaq); fflush(arqMaq);
                                printf("\nVenda registrada com sucesso!\n");
                            }
                        }

                    break;
                case 2:
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
                            printf("\nERRO: Um dos dados nao exite no cadastro!\n");
                        } else {
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
                                printf("Estoque insuficiente!\n");
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
                                printf("\nData da venda (dd mm aaaa): ");
                                scanf("%d %d %d", &V.D.dataVendaDia, &V.D.dataVendaMes, &V.D.dataVendaAno);
                                getchar();

                                salvarVendas(V);

                                P.quantidade -= V.quantDesejada;
                                fseek(arqPec, posPec, SEEK_SET);
                                fwrite(&P, sizeof(pecas), 1, arqPec); fflush(arqPec);
                                printf("\nVenda registrada com sucesso!\n");
                            }
                        }
                    break;
                case 3:
                        system("cls");
                        printf("\n--- LOJA DE SERVICOS ---\n");
                        printf("\nDigite seu cpf: ");
                        scanf("%11s", PF.cpf);

                        printf("\n");


                    break;

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
                printf("\n0 - Retornar");
                printf("\nEscolha: ");
                scanf("%d", &op2);

                switch (op2)
                {
                case 1:
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

                        if (pos == -1 || posMaq == -1) {
                            printf("\nERRO: Um dos dados nao exite no cadastro!\n");
                        } else {
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
                                printf("Estoque insuficiente!\n");
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
                                printf("\nData da venda (dd mm aaaa): ");
                                scanf("%d %d %d", &V.D.dataVendaDia, &V.D.dataVendaMes, &V.D.dataVendaAno);
                                getchar();

                                salvarVendas(V);

                                M.quantidade -= V.quantDesejada;
                                fseek(arqMaq, posMaq, SEEK_SET); fflush(arqMaq);
                                fwrite(&M, sizeof(maquinarios), 1, arqMaq);
                                printf("\nVenda registrada com sucesso!\n");
                            }
                        }

                    break;
                case 2:
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
                            printf("\nERRO: Um dos dados nao exite no cadastro!\n");
                        } else {
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
                                printf("Estoque insuficiente!\n");
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
                                printf("\nData da venda (dd mm aaaa): ");
                                scanf("%d %d %d", &V.D.dataVendaDia, &V.D.dataVendaMes, &V.D.dataVendaAno);
                                getchar();

                                salvarVendas(V);

                                P.quantidade -= V.quantDesejada;
                                fseek(arqPec, posPec, SEEK_SET);
                                fwrite(&P, sizeof(pecas), 1, arqPec); fflush(arqPec);
                                printf("\nVenda registrada com sucesso!\n");
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
        case 0:
                printf("\nRetornando...");
            break;

        default:
                printf("\nERRO: escolha uma opcao valida!\n");
            break;
        }
    } while (op != 0);
}

void realizarExclusao() {
    clientesPF PF;
    clientesPJ PJ;
    maquinarios M;
    pecas P;
    // servicos S;
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

    int op, op2, pos, posVen;
    char cpfApagar[12], cnpjApagar[14], codigoApagar[20];

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
                            printf("\n");
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
                                printf("\nDeseja reamente excluir esse cliente? <S/N>: ");

                                if (toupper(getche()) == 'S') {
                                    FILE *temp = fopen("arqTemp.bin", "wb");

                                    if(temp == NULL) {
                                        printf("\nERRO: impossivel criar arquivo temp!\n");
                                    }

                                    rewind(arqPF);
                                    while (fread(&PF, sizeof(clientesPF), 1, arqPF) == 1) {
                                        if(stricmp(cpfApagar, PF.cpf) != 0) {
                                            fwrite(&PF, sizeof(clientesPF), 1, temp);
                                        }
                                    }
                                    fclose(arqPF);
                                    fclose(temp);
                                    remove("arqPF.bin");
                                    rename("arqTemp.bin", "arqPF.bin");
                                    
                                    printf("\nCliente Excluido!\n");
                                    printf("\n");
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
                                printf("\nDeseja reamente excluir esse cliente? <S/N>: ");

                                if(toupper(getche()) == 'S') {
                                    FILE *temp = fopen("arqTemp.bin", "wb");

                                    if (temp == NULL) {
                                        printf("\nERRO: impossivel criar arquivo temp!\n");
                                    }

                                    rewind(arqPJ);
                                    while (fread(&PJ, sizeof(clientesPJ), 1, arqPJ) == 1) {
                                        if (strcmp(cnpjApagar, PJ.cnpj) != 0) {
                                            fwrite(&PJ, sizeof(clientesPJ), 1, temp);
                                        }
                                    }
                                    fclose(arqPJ);
                                    fclose(temp);
                                    remove("arqPJ.bin");
                                    rename("arqTemp.bin", "arqPJ.bin");

                                    printf("\nCliente Excluido!\n");
                                    printf("\n");
                                    system("pause");
                                }
                            } else {
                                printf("\nNao e possivel excluir um cliente com uma compra registrada\n");
                                printf("\n");
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
                printf("\n0 - Sair");
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

                            printf("\nDeseja reamente excluir esse produto? <S/N>: ");

                            if (toupper(getche()) == 'S') {
                                FILE *temp = fopen("arqTemp.bin", "wb");

                                if(temp == NULL) {
                                    printf("\nERRO: impossivel criar arquivo temp!\n");
                                    printf("\n");
                                    system("pause");
                                }

                                rewind(arqMaq);
                                while (fread(&M, sizeof(maquinarios), 1, arqMaq) == 1) {
                                    if (strcmp(codigoApagar, M.codigo) != 0) {
                                        fwrite(&M, sizeof(maquinarios), 1, temp);
                                    }
                                    
                                    fclose(arqMaq);
                                    fclose(temp);
                                    remove("arqMaq.bin");
                                    rename("arqTemp.bin", "arqMaq.bin");

                                    printf("\nProduto Excluido!\n");
                                    printf("\n");
                                    system("pause");
                                } 
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

                            printf("\nDeseja reamente excluir esse produto? <S/N>: ");

                            if (toupper(getche()) == 'S') {
                                FILE *temp = fopen("arqTemp.bin", "wb");

                                if(temp == NULL) {
                                    printf("\nERRO: impossivel criar arquivo temp!\n");
                                }

                                rewind(arqPec);
                                while (fread(&P, sizeof(pecas), 1, arqPec) == 1) {
                                    if (strcmp(codigoApagar, P.codigo) != 0) {
                                        fwrite(&P, sizeof(pecas), 1, temp);
                                    }
                                    
                                    fclose(arqPec);
                                    fclose(temp);
                                    remove("arqPec.bin");
                                    rename("arqTemp.bin", "arqPec.bin");

                                    printf("\nProduto Excluido!\n");
                                    printf("\n");
                                    system("pause");
                                } 
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

void relatorios() {
    clientesPF PF;
    clientesPJ PJ;
    maquinarios M;
    pecas P;
    servicos S;

    FILE *arqPF, *arqPJ, *arqMaq, *arqPec, *arqSer;

    int op, op2;
    do {
        printf("\n--- RELATORIOS ---\n");
        printf("1 - Clientes\n2 - Produtos\n3 - Servicos\n0 - Sair\nEscolha: ");
        scanf("%d", &op);
        getchar();
        system("cls");

        switch (op) {
        case 1:
            printf("\n1 - Clientes PF\n2 - Clientes PJ\nEscolha: ");
            scanf("%d", &op2);
            getchar();
            system("cls");

            if (op2 == 1) {
                arqPF = fopen("arqPF.bin", "rb");
                if (arqPF == NULL) {
                    printf("Erro ao abrir arqPF.bin\n");
                    
                }

                printf("\n--- RELATORIO: CLIENTES PF ---\n");
                while (fread(&PF, sizeof(clientesPF), 1, arqPF) == 1) {
                    printf("\nNome: %s\nEmail: %s\nCPF: %.3s.%.3s.%.3s-%.2s\nTelefone: (%.2s) %.5s-%.4s\nNascimento: %02d/%02d/%04d\n",
                        PF.nome, PF.email,
                        PF.cpf, PF.cpf+3, PF.cpf+6, PF.cpf+9,
                        PF.telefone, PF.telefone+2, PF.telefone+7,
                        PF.D.dia, PF.D.mes, PF.D.ano);
                }

                fclose(arqPF);
            } else if (op2 == 2) {
                arqPJ = fopen("arqPJ.bin", "rb");
                if (arqPJ == NULL) {
                    printf("Erro ao abrir arqPJ.bin\n");
                    
                }

                printf("\n--- RELATORIO: CLIENTES PJ ---\n");
                while (fread(&PJ, sizeof(clientesPJ), 1, arqPJ) == 1) {
                    printf("\nNome Empresarial: %s\nEmail: %s\nCNPJ: %.2s.%.3s.%.3s/%.4s-%2s\nResponsavel: %s\nTelefone: (%.2s) %.5s-%.4s\n",
                        PJ.nomeEmpresarial, PJ.emailEmpresarial,
                        PJ.cnpj, PJ.cnpj+2, PJ.cnpj+5, PJ.cnpj+8, PJ.cnpj+12,
                        PJ.nomeDoResponsavel,
                        PJ.telefoneEmpresarial, PJ.telefoneEmpresarial+2, PJ.telefoneEmpresarial+7);
                }

                fclose(arqPJ);
            }
            break;

        case 2:
            printf("\n1 - Maquinarios\n2 - Pecas\nEscolha: ");
            scanf("%d", &op2);
            getchar();
            system("cls");

            if (op2 == 1) {
                arqMaq = fopen("arqMaquinario.bin", "rb");
                if (arqMaq == NULL) {
                    printf("Erro ao abrir arqMaquinario.bin\n");
                    
                }

                printf("\n--- RELATORIO: MAQUINARIOS ---\n");
                while (fread(&M, sizeof(maquinarios), 1, arqMaq) == 1) {
                    printf("\nNome: %s\nCategoria: %s\nCodigo: %s\nQuantidade: %d\nPreco: R$ %.2f\n",
                        M.nome, M.categoria, M.codigo, M.quantidade, M.preco);
                }

                fclose(arqMaq);
            } else if (op2 == 2) {
                arqPec = fopen("arqPecas.bin", "rb");
                if (arqPec == NULL) {
                    printf("Erro ao abrir arqPecas.bin\n");
                    
                }

                printf("\n--- RELATORIO: PECAS ---\n");
                while (fread(&P, sizeof(pecas), 1, arqPec) == 1) {
                    printf("\nNome: %s\nCategoria: %s\nCodigo: %s\nQuantidade: %d\nPreco: R$ %.2f\n",
                        P.nome, P.categoria, P.codigo, P.quantidade, P.preco);
                }

                fclose(arqPec);
            }
            break;

        case 3:
            printf("\n1 - Servicos para PF\n2 - Servicos para PJ\nEscolha: ");
            scanf("%d", &op2);
            getchar();
            system("cls");

            arqSer = fopen("arqServicos.bin", "rb");
            if (arqSer == NULL) {
                printf("Erro ao abrir arqServicos.bin\n");
                
            }

            if (op2 == 1) {
                printf("\n--- RELATORIO: SERVICOS PF ---\n");
                while (fread(&S, sizeof(servicos), 1, arqSer) == 1) {
                    if (strlen(S.cpfParaContrato) > 0) {
                        printf("\nTipo: %s\nDescricao: %s\nPreco: R$ %.2f\nData: %02d/%02d/%04d\nCPF: %.3s.%.3s.%.3s-%.2s\n",
                            S.tipoServico, S.descricao, S.preco,
                            S.D.dia, S.D.mes, S.D.ano,
                            S.cpfParaContrato, S.cpfParaContrato+3, S.cpfParaContrato+6, S.cpfParaContrato+9);
                    }
                }
            } else if (op2 == 2) {
                printf("\n--- RELATORIO: SERVICOS PJ ---\n");
                while (fread(&S, sizeof(servicos), 1, arqSer) == 1) {
                    if (strlen(S.cnpjParaContrato) > 0) {
                        printf("\nTipo: %s\nDescricao: %s\nPreco: R$ %.2f\nData: %02d/%02d/%04d\nCNPJ: %.2s.%.3s.%.3s/%.4s-%2s\n",
                            S.tipoServico, S.descricao, S.preco,
                            S.D.dia, S.D.mes, S.D.ano,
                            S.cnpjParaContrato, S.cnpjParaContrato+2, S.cnpjParaContrato+5, S.cnpjParaContrato+8, S.cnpjParaContrato+12);
                    }
                }
            }

            fclose(arqSer);
            break;

        case 0:
            printf("\nRetornando...\n");
            break;

        default:
            printf("\nOpcao invalida!\n");
            break;
        }

    } while (op != 0);
}

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
    			//relatorios();
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