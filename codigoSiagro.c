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
    char nomeEmpresarial[MAXSTR], nomeDoResponsavel[MAXSTR],emailEmpresarial[MAXSTR], cnpj[15], telefoneEpresarial[12];
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
    char cpf[12], cnpj[15], codigo[20];
    int opCliente, opProduto, qtdDesejada;
    float subtotal, totalFinal;
    int formaPagamento, confirmar; 
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
    fread(&P, sizeof(pecas), 1, arqPec);
    while (!feof(arqPec) && stricmp(codigo, P.codigo) != 0) {
        fread(&P, sizeof(pecas), 1, arqPec);
    }

    if(!feof(arqPec)) {
        return(ftell(arqPec) - sizeof(maquinarios));
    } else {
        return -1;
    }
}

int validarSerPF(FILE *arqSer, char cpfParaContrato[]) {
    servicos S;

    rewind(arqSer);
    fread(&S, sizeof(servicos), 1, arqSer);
    while (!feof(arqSer) && stricmp(cpfParaContrato, S.cpfParaContrato) != 0) {
        fread(&S, sizeof(servicos), 1, arqSer);
    }

    if(!feof(arqSer)) {
        return(ftell(arqSer) - sizeof(servicos));
    } else {
        return -1;
    }
}

int validarSerPJ(FILE *arqSer, char cnpjParaContrato[]) {
    servicos S;

    rewind(arqSer);
    fread(&S, sizeof(servicos), 1, arqSer);
    while (!feof(arqSer) && stricmp(cnpjParaContrato, S.cnpjParaContrato) != 0) {
        fread(&S, sizeof(servicos), 1, arqSer);
    }

    if(!feof(arqSer)) {
        return(ftell(arqSer) - sizeof(servicos));
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

    int op, posCPF, posCNPJ, posMaq, posPec, posSerPF, posSerPJ;

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
                    scanf("%d", &op);
                    system("cls");
                    getchar();

                    switch (op) {
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

                                    printf("\nSeu telefone:");
                                    scanf("%11s", PF.telefone);

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

                                    printf("\nO nome do responsavel: ");
                                    fgets(PJ.nomeDoResponsavel, MAXSTR, stdin);
                                    PJ.nomeDoResponsavel[strcspn(PJ.nomeDoResponsavel, "\n")] = '\0';

                                    printf("\nO telefone empresarial:");
                                    scanf("%11s", PJ.telefoneEpresarial);
                                    getchar();
                                    
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
                } while (op !=  0);      
            break;
        case 2:
                do {
                    printf("\n--- CADASTRO DE PRODUTOS ---\n");
                    printf("\n1 - Maquinario");
                    printf("\n2 - Pecas");
                    printf("\n0 - Retornar");
                    printf("\nEscolha: ");
                    scanf("%d", &op);
                    system("cls");
                    getchar();

                    switch (op) {
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

                } while (op != 0);             
            break;
        case 3:
                do {
                    printf("\n--- CADASTRO DE SERVICOS ---\n");
                    printf("\n1 - Cliente PF");
                    printf("\n2 - Cliente PJ");
                    printf("\n0 - Retornar");
                    printf("\nEscolha: ");
                    scanf("%d", &op);
                    system("cls");
                    getchar();

                    switch (op) {
                        case 1:
                                printf("\n--- CADASTRAR SERVICO PARA PF ---\n");
                                printf("\nDigite o cpf para cadastrar o servico: ");
                                scanf("%11s", S.cpfParaContrato);
                                getchar();

                                posSerPF = validarSerPF(arqPec, S.cpfParaContrato);
                                
                                if (posSerPF == -1) {
                                    printf("\nQual o tipo de servico: ");
                                    fgets(S.tipoServico, MAXSTR, stdin);

                                    printf("\nQual a descricao: ");
                                    fgets(S.descricao, MAXSTR, stdin);

                                    printf("\nQual o preco do servico: ");
                                    scanf("%f", &S.preco);

                                    printf("\nQual a data para o servico <dd/mm/aaaa> : ");
                                    scanf("%d%d%d", &S.D.dia, &S.D.mes, &S.D.ano);
                                    getchar();

                                    salvarServico(S);
                                    printf("\nServico cadastrado com sucesso!\n\n");
                                } else {
                                    servicos S_cpf_jaCadastrado;
                                    fseek(arqSer, posSerPF, 0);
                                    fread(&S_cpf_jaCadastrado, sizeof(servicos), 1, arqSer);
                                    printf("\nO CPF digitado: %.3s.%.3s.%.3s-%.2s ja esta com um servico pendente!", S_cpf_jaCadastrado.cpfParaContrato, S_cpf_jaCadastrado.cpfParaContrato+3, S_cpf_jaCadastrado.cpfParaContrato+6, S_cpf_jaCadastrado.cpfParaContrato+9);
                                }                                           
                            break;
                        case 2:
                                printf("\n--- CADASTRAR SERVICO PARA PJ ---\n");
                                printf("\nDigite o cnpj para cadastrar o servico: ");
                                scanf("%14s", S.cnpjParaContrato);
                                getchar();

                                posSerPJ = validarSerPF(arqSer, S.cnpjParaContrato);
                                
                                if (posSerPJ == -1) {
                                    printf("\nQual o tipo de servico: ");
                                    fgets(S.tipoServico, MAXSTR, stdin);

                                    printf("\nQual a descricao: ");
                                    fgets(S.descricao, MAXSTR, stdin);

                                    printf("\nQual o preco do servico: ");
                                    scanf("%f", &S.preco);

                                    printf("\nQual a data para o servico <dd/mm/aaaa> : ");
                                    scanf("%d%d%d", &S.D.dia, &S.D.mes, &S.D.ano);
                                    getchar();

                                    salvarServico(S);
                                    printf("\nServico cadastrado com sucesso!\n\n");
                                } else {
                                    servicos S_cnpj_jaCadastrado;
                                    fseek(arqSer, posSerPJ, 0);
                                    fread(&S_cnpj_jaCadastrado, sizeof(servicos), 1, arqSer);
                                    printf("\nO CNPJ digitado: %.2s.%.3s.%.3s/%.4s-%2s ja esta com um servico pendente!", S_cnpj_jaCadastrado.cnpjParaContrato, S_cnpj_jaCadastrado.cnpjParaContrato+2, S_cnpj_jaCadastrado.cnpjParaContrato+5, S_cnpj_jaCadastrado.cnpjParaContrato+8, S_cnpj_jaCadastrado.cnpjParaContrato+12);
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

            } while (op != 0);

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

                            achou = 0;
                            rewind(arqPF);
                            while (fread(&PF, sizeof(clientesPF), 1, arqPF) == 1 && !achou) {
                                if (stricmp(buscCpf, PF.cpf) == 0) {
                                    printf("\nDados do cliente:");
                                    printf("\nNome: %s \nEmail: %s \nCpf: %.3s.%.3s.%.3s-%.2s \nFone: (%.2s) %.5s-%.4s \nData de nascimento: %02d/%02d/%04d \n", PF.nome, PF.email, PF.cpf, PF.cpf+3, PF.cpf+6, PF.cpf+9, PF.telefone, PF.telefone+2, PF.telefone+7, PF.D.dia, PF.D.mes, PF.D.ano);
                                    achou = 1;
                                }
                            }

                            if (!achou) {
                                printf("\nERRO: nao ha cadastro com o CPF digitado!");
                            }
                        break;
                    case 2:
                            printf("\n--- CLIENTES PJ ---\n");
                            printf("\nUse o cnpj para buscar: ");
                            scanf("%14s", buscCnpj);
                            getchar();

                            achou = 0;
                            rewind(arqPJ);
                            while (fread(&PJ, sizeof(clientesPJ), 1, arqPJ) == 1 && !achou) {
                                if (stricmp(buscCnpj, PJ.cnpj) == 0) {
                                    printf("\nDados da empresa:");
                                    printf("\nNome: %s \nEmail: %s \nCnpj: %.2s.%.3s.%.3s/%.4s-%2s \nResponsavel: %s \nFone: (%.2s) %.5s-%.4s \n", PJ.nomeEmpresarial, PJ.emailEmpresarial, PJ.cnpj, PJ.cnpj+2, PJ.cnpj+5, PJ.cnpj+8, PJ.cnpj+12, PJ.nomeDoResponsavel, PJ.telefoneEpresarial, PJ.telefoneEpresarial+2, PJ.telefoneEpresarial+7);
                                    achou = 1;
                                }
                            }
                            if (!achou) {
                                printf("\nERRO: nao ha cadastro com o CNPJ digitado!");
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

                            achou = 0;
                            rewind(arqMaq);
                            while (fread(&M, sizeof(maquinarios), 1, arqMaq) == 1 && !achou) {
                                if (stricmp(buscCodMaq, M.codigo) == 0) {
                                    printf("\nDados do maquinario:");
                                    printf("\nNome: %s \nCategoria: %s \nCodigo: %s \nQuantidade: %d \nPreco: %.2f\n", M.nome, M.categoria, M.codigo, M.quantidade, M.preco);
                                    achou = 1;
                                }
                            }

                            if (!achou) {
                                printf("\nERRO: nao ha cadastro com o codigo digitado!");
                            }
                        break;
                    case 2:
                            printf("\n--- PECAS ---\n");
                            printf("\nUse o codigo para buscar: ");
                            scanf("%19s", buscCodPec);
                            getchar();

                            achou = 0;
                            rewind(arqPec);
                            while (fread(&P, sizeof(pecas), 1, arqPec) == 1 && !achou) {
                                if (stricmp(buscCodPec, P.codigo) == 0) {
                                    printf("\nDados da peca:");
                                    printf("\nNome: %s \nCategoria: %s \nCodigo: %s \nQuantidade: %d \nPreco: %.2f\n", P.nome, P.categoria, P.codigo, P.quantidade, P.preco);
                                    achou = 1;
                                    
                                }
                            }

                            if (!achou) {
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

                            achou = 0;

                            while (fread(&S, sizeof(servicos), 1, arqSer) == 1 && !achou) {
                                if (stricmp(buscCpfServ, S.cpfParaContrato) == 0) {
                                    printf("\nDados do servico:");
                                    printf("\nTipo de servico: %s \nDescricao: %s \nPreco: %.2f \nData: %02d/%02d/%02d \nCPF: %.3s.%.3s.%.3s-%.2s\n", S.tipoServico, S.descricao, S.preco, S.D.dia, S.D.mes, S.D.ano, S.cpfParaContrato, S.cpfParaContrato+3, S.cpfParaContrato+6, S.cpfParaContrato+9);
                                    achou = 1;
                                }                                           
                            }

                            if (!achou) {
                                printf("\nNao a servicos cadastrados no cpf digitado!\n");
                            }
                        break;
                    case 2:
                            printf("\n--- BUSCA DE SERVICOS EM PJ ---\n");
                            printf("\nDigite o cnpj para cadastrar o servico: ");
                            scanf("%14s", buscCnpjServ);
                            getchar();

                            achou = 0;

                            while (fread(&S, sizeof(servicos), 1, arqSer) == 1 && !achou) {
                                if (stricmp(buscCnpjServ, S.cnpjParaContrato) == 0) {
                                    printf("\nDados do servico:");
                                    printf("\nTipo de servico: %s \nDescricao: %s \nPreco: %.2f \nData: %02d/%02d/%02d \nCNPJ: %.2s.%.3s.%.3s/%.4s-%2s\n", S.tipoServico, S.descricao, S.preco, S.D.dia, S.D.mes, S.D.ano, S.cnpjParaContrato, S.cnpjParaContrato+2, S.cnpjParaContrato+5, S.cnpjParaContrato+8, S.cnpjParaContrato+12);
                                    achou = 1;
                                }                                           
                            }

                            if (!achou) {
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

// TERMINA AQUI A FUNCAO DE BUSCA DE CADASTROS DE USUARIOS, MAQUINARIOS, SERVICOS E PECAS --------------------------------------------
//EDITAR 

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
        printf("\n--- EDICAO ---\n");
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
                printf("\n--- EDICAO DE CLIENTES ---\n");
                printf("\n1 - Clientes PF");
                printf("\n2 - Clientes PJ");
                printf("\n0 - Retornar");
                printf("\nEscolha: ");
                scanf("%d", &op2);
                system("cls");
                getchar();

                switch (op2) {
                case 1:
                        printf("\n--- EDITAR CLIENTES PF ---\n");

                        do {
                            printf("\nInforme o CPF do cliente para as alteracoes: ");
                            scanf("%11s", PF.cpf);
                            getchar();

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
                                    scanf("%d", &op);
                                    system("cls");
                                    getchar();

                                    switch (op) {
                                        case 1:
                                                printf("\nNovo telefone: ");
                                                scanf("%11s", PF.telefone);
                                                getchar();

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
                                                printf("Novo email: ");
                                                fgets(PF.email, MAXSTR, stdin);
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
                                } while (op != 0);
                            }
                            printf("\nDeseja editar outro Cliente? (S/N): ");
                        } while (toupper(getche()) == 'S');
                    break;
                break;
                case 2:
                        printf("\n--- EDITAR CLIENTES PJ ---\n");

                        do {
                            printf("\nInforme o CNPJ do cliente para as alteracoes: ");
                            scanf("%14s", PJ.cnpj);
                            getchar();

                            posCNPJ = validarCNPJ(arqPJ, PJ.cnpj);

                            if (posCNPJ == -1) {
                                printf("ERRO: CNPJ nao encontrado!\n");
                            } else {
                                fseek(arqPJ, posCNPJ, SEEK_SET);
                                fread(&PJ, sizeof(clientesPJ), 1, arqPJ);

                                printf("\n----------------\n");
                                printf("\nNome empresarial: %s", PJ.nomeEmpresarial);
                                printf("\nFone: (%.2s) %.5s-%.4s", PJ.telefoneEpresarial, PJ.telefoneEpresarial+2, PJ.telefoneEpresarial+7);
                                printf("\nEmail: %s", PJ.emailEmpresarial);
                                printf("\nNome do responsavel: %s", PJ.nomeDoResponsavel);
                                printf("\n----------------\n");

                                do {
                                    printf("\nDeseja alterar: \n 1- NOME EMPRESARIAL \n 2- TELEFONE \n 3- EMAIL \n 4- NOME DO RESPONSAVEL \n 0- SAIR DA EDICAO DESTE CLIENTE");
                                    printf("\nEscolha: ");
                                    scanf("%d", &op);
                                    system("cls");
                                    getchar();

                                    switch (op) {
                                        case 1:
                                                printf("\nNovo nome empresarial: ");
                                                fgets(PJ.nomeEmpresarial, MAXSTR, stdin);

                                                fseek(arqPJ, posCNPJ, SEEK_SET);
                                                fwrite(&PJ, sizeof(clientesPJ), 1, arqPJ);

                                                printf("\nNome empresarial atualizado com sucesso!\n");
                                                printf("\nDados salvos: \n");

                                                fseek(arqPJ, posCNPJ, SEEK_SET);
                                                fread(&PJ, sizeof(clientesPJ), 1, arqPJ);

                                                printf("\n----------------\n");
                                                printf("\nNome empresarial: %s", PJ.nomeEmpresarial);
                                                printf("\nFone: (%.2s) %.5s-%.4s", PJ.telefoneEpresarial, PJ.telefoneEpresarial+2, PJ.telefoneEpresarial+7);
                                                printf("\nEmail: %s", PJ.emailEmpresarial);
                                                printf("\nNome do responsavel: %s", PJ.nomeDoResponsavel);
                                                printf("\n----------------\n");

                                            break;

                                        case 2:
                                                printf("Novo telefone: ");
                                                scanf("%11s", PJ.telefoneEpresarial);

                                                fseek(arqPJ, posCNPJ, SEEK_SET);
                                                fwrite(&PJ, sizeof(clientesPJ), 1, arqPJ);

                                                printf("\nTelefone alterado!\n");
                                                printf("\nDados salvos: \n");

                                                fseek(arqPJ, posCNPJ, SEEK_SET);
                                                fread(&PJ, sizeof(clientesPJ), 1, arqPJ);

                                                printf("\n----------------\n");
                                                printf("\nNome empresarial: %s", PJ.nomeEmpresarial);
                                                printf("\nFone: (%.2s) %.5s-%.4s", PJ.telefoneEpresarial, PJ.telefoneEpresarial+2, PJ.telefoneEpresarial+7);
                                                printf("\nEmail: %s", PJ.emailEmpresarial);
                                                printf("\nNome do responsavel: %s", PJ.nomeDoResponsavel);
                                                printf("\n----------------\n");

                                            break;
                                        case 3:
                                                printf("Novo email: ");
                                                fgets(PJ.emailEmpresarial, MAXSTR, stdin);

                                                fseek(arqPJ, posCNPJ, SEEK_SET);
                                                fwrite(&PJ, sizeof(clientesPJ), 1, arqPJ);
                                                
                                                printf("\nEmail alterado!\n");
                                                printf("\nDados salvos: \n");

                                                fseek(arqPJ, posCNPJ, SEEK_SET);
                                                fread(&PJ, sizeof(clientesPJ), 1, arqPJ);

                                                printf("\n----------------\n");
                                                printf("\nNome empresarial: %s", PJ.nomeEmpresarial);
                                                printf("\nFone: (%.2s) %.5s-%.4s", PJ.telefoneEpresarial, PJ.telefoneEpresarial+2, PJ.telefoneEpresarial+7);
                                                printf("\nEmail: %s", PJ.emailEmpresarial);
                                                printf("\nNome do responsavel: %s", PJ.nomeDoResponsavel);
                                                printf("\n----------------\n");

                                            break;
                                        case 4:
                                                printf("Novo nome do responsavel: ");
                                                fgets(PJ.nomeDoResponsavel, MAXSTR, stdin);

                                                fseek(arqPJ, posCNPJ, SEEK_SET);
                                                fwrite(&PJ, sizeof(clientesPJ), 1, arqPJ);

                                                printf("\nNome do responsavel alterado!\n");
                                                printf("\nDados salvos: \n");

                                                fseek(arqPJ, posCNPJ, SEEK_SET);
                                                fread(&PJ, sizeof(clientesPJ), 1, arqPJ);

                                                printf("\n----------------\n");
                                                printf("\nNome empresarial: %s", PJ.nomeEmpresarial);
                                                printf("\nFone: (%.2s) %.5s-%.4s", PJ.telefoneEpresarial, PJ.telefoneEpresarial+2, PJ.telefoneEpresarial+7);
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
                                } while (op != 0);
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
                printf("\n--- EDICAO DE PRODUTOS ---\n");
                printf("\n1 - Maquinario");
                printf("\n2 - Pecas");
                printf("\n0 - Retornar");
                printf("\nEscolha: ");
                scanf("%d", &op2);
                system("cls");
                getchar();

                switch (op2) {
                case 1:
                        printf("\n--- EDITAR MAQUINARIO ---\n");

                        do {
                            printf("\nInforme o CODIGO do maquinario para as alteracoes: ");
                            scanf("%19s", M.codigo);
                            getchar();

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
                                    scanf("%d", &op);
                                    system("cls");
                                    getchar();

                                    switch (op) {
                                        case 1:
                                                printf("\nNovo nome do maquinario: ");
                                                fgets(M.nome, MAXSTR, stdin);

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
                                                printf("Nova categoria: ");
                                                fgets(M.categoria, MAXSTR, stdin);

                                                fseek(arqMaq, posMaq, SEEK_SET);
                                                fwrite(&M, sizeof(maquinarios), 1, arqMaq);
                                                
                                                printf("\nCategoria alterada!\n");
                                                printf("\nDados salvos: \n");

                                                fseek(arqPF, posCPF, SEEK_SET);
                                                fread(&M, sizeof(maquinarios), 1, arqMaq);
                                                
                                                printf("\n----------------\n");
                                                printf("\nNome do maquinario: %s", M.nome);
                                                printf("\nCategoria: %s", M.categoria);
                                                printf("\nQuantidade: %d", M.quantidade);
                                                printf("\nPreco: %.2f", M.preco);
                                                printf("\n----------------\n");

                                            break;
                                        case 3:
                                                printf("Nova quantidade: ");
                                                scanf("%d", &M.quantidade);
                                                getchar();

                                                fseek(arqMaq, posMaq, SEEK_SET);
                                                fwrite(&M, sizeof(maquinarios), 1, arqMaq);
                                                
                                                printf("\nQuantidade alterada!\n");
                                                printf("\nDados salvos: \n");

                                                fseek(arqPF, posCPF, SEEK_SET);
                                                fread(&M, sizeof(maquinarios), 1, arqMaq);
                                                
                                                printf("\n----------------\n");
                                                printf("\nNome do maquinario: %s", M.nome);
                                                printf("\nCategoria: %s", M.categoria);
                                                printf("\nQuantidade: %d", M.quantidade);
                                                printf("\nPreco: %.2f", M.preco);
                                                printf("\n----------------\n");

                                            break;
                                        case 4:
                                                printf("Novo preco: ");
                                                scanf("%f", &M.preco);
                                                getchar();

                                                fseek(arqMaq, posMaq, SEEK_SET);
                                                fwrite(&M, sizeof(maquinarios), 1, arqMaq);
                                                
                                                printf("\nPreco alterado!\n");
                                                printf("\nDados salvos: \n");

                                                fseek(arqPF, posCPF, SEEK_SET);
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
                                } while (op != 0);
                            }
                            printf("\nDeseja editar outro Cliente? (S/N): ");
                        } while (toupper(getche()) == 'S');
                    break;
                break;
                case 2:
                        printf("\n--- EDITAR PECAS ---\n");

                        do {
                            printf("\nInforme o CODIGO da peca para as alteracoes: ");
                            scanf("%19s", P.codigo);
                            getchar();

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
                                    scanf("%d", &op);
                                    system("cls");
                                    getchar();

                                    switch (op) {
                                        case 1:
                                                printf("\nNovo nome da peca: ");
                                                fgets(P.nome, MAXSTR, stdin);

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
                                                printf("Nova categoria: ");
                                                fgets(M.categoria, MAXSTR, stdin);

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
                                                printf("Nova quantidade: ");
                                                scanf("%d", &M.quantidade);
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
                                                printf("Novo preco: ");
                                                scanf("%f", &M.preco);
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
                                } while (op != 0);
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
                printf("\n--- EDICAO DE SERVICOS ---\n");
                printf("\n1 - Cliente PF");
                printf("\n2 - Cliente PJ");
                printf("\n0 - Retornar");
                printf("\nEscolha: ");
                scanf("%d", &op3);
                system("cls");
                getchar();

                switch (op3) {
                case 1:
                        printf("\n--- EDITAR SERVICO PF ---\n");

                        do {
                            printf("\nInforme o CPF do cliente para as alteracoes em servico: ");
                            scanf("%11s", S.cpfParaContrato);
                            getchar();

                            posSerPF = validarSerPF(arqSer, S.cpfParaContrato);

                            if (posSerPF == -1) {
                                printf("ERRO: CPF nao a servicos pendentes!\n");
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
                                    scanf("%d", &op);
                                    system("cls");
                                    getchar();

                                    switch (op) {
                                        case 1:
                                                printf("\nNovo tipo do servico: ");
                                                fgets(S.tipoServico, MAXSTR, stdin);

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
                                                printf("Nova descricao: ");
                                                fgets(S.descricao, MAXSTR, stdin);

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
                                } while (op != 0);
                            }
                            printf("\nDeseja editar outro Cliente? (S/N): ");
                        } while (toupper(getche()) == 'S');
                    break;
                break;
                case 2:
                        printf("\n--- EDITAR SERVICO PJ ---\n");

                        do {
                            printf("\nInforme o CNPJ do cliente para as alteracoes em servico: ");
                            scanf("%14s", S.cnpjParaContrato);
                            getchar();

                            posSerPJ = validarSerPJ(arqSer, S.cnpjParaContrato);

                            if (posSerPJ == -1) {
                                printf("ERRO: CNPJ nao a servicos pendentes!\n");
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
                                    scanf("%d", &op);
                                    system("cls");
                                    getchar();

                                    switch (op) {
                                        case 1:
                                                printf("\nNovo tipo do servico: ");
                                                fgets(S.tipoServico, MAXSTR, stdin);

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
                                                printf("Nova descricao: ");
                                                fgets(S.descricao, MAXSTR, stdin);

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
                                } while (op != 0);
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
	
		fclose(arqPF);
        fclose(arqPJ);
        fclose(arqMaq);
        fclose(arqPec);
        fclose(arqSer);
    } while (op != 0);
}

//FIM EDITAR

//inicio venda
void realizarVenda() {
    maquinarios M;
    pecas P;
    servicos S;
    vendas V;

    int op, op2, pos;
    int vendaValida = 1;

    FILE *arqPF = fopen("arqPF.bin", "rb+");
    FILE *arqPJ = fopen("arqPJ.bin", "rb+");
    FILE *arqMaq = fopen("arqMaquinario.bin", "rb+");
    FILE *arqPec = fopen("arqPecas.bin", "rb+");

    if (arqPF && arqPJ && arqMaq && arqPec) {
        printf("\n--- VENDA ---\n");
        printf("1 - Cliente PF\n2 - Cliente PJ\n0 - Sair\nEscolha: ");
        scanf("%d", &op);
        system("cls");
        getchar();
        V.opCliente = op;

        if (op == 1) {
            printf("Digite o CPF do cliente: ");
            scanf("%11s", V.cpf);
            getchar();
            pos = validarCPF(arqPF, V.cpf);
            if (pos == -1) {
                printf("\nERRO: CPF nao encontrado!\n");
                vendaValida = 0;
            }
        } else if (op == 2) {
            printf("Digite o CNPJ da empresa: ");
            scanf("%14s", V.cnpj);
            getchar();
            pos = validarCNPJ(arqPJ, V.cnpj);
            if (pos == -1) {
                printf("\nERRO: CNPJ nao encontrado!\n");
                vendaValida = 0;
            }
        } else {
            printf("\nRetornando...\n");
            vendaValida = 0;
        }

        if (vendaValida == 1) {
            printf("\n--- Tipo de Venda ---\n1 - Maquinarios\n2 - Pecas\n3 - Servicos\n0 - Sair\nEscolha: ");
            scanf("%d", &op2);
            system("cls");
            getchar();

            if (op2 == 1) {
                printf("Digite o codigo do maquinario: ");
                scanf("%19s", V.codigo);
                getchar();
                pos = validarMaquinario(arqMaq, V.codigo);
                if (pos != -1) {
                    fseek(arqMaq, pos, SEEK_SET);
                    fread(&M, sizeof(maquinarios), 1, arqMaq);
                    printf("Quantidade desejada: ");
                    scanf("%d", &V.qtdDesejada);
                    if (M.quantidade >= V.qtdDesejada) {
                        V.subtotal = V.qtdDesejada * M.preco;
                        printf("\nResumo da venda:\nProduto: %s\nQuantidade: %d\nPreco unitario: R$ %.2f\nSubtotal: R$ %.2f\n",
                               M.nome, V.qtdDesejada, M.preco, V.subtotal);
                    } else {
                        printf("\nEstoque insuficiente. Disponivel: %d\n", M.quantidade);
                        vendaValida = 0;
                    }
                } else {
                    printf("\nMaquinario nao encontrado!\n");
                    vendaValida = 0;
                }
            } else if (op2 == 2) {
                printf("Digite o codigo da peca: ");
                scanf("%19s", V.codigo);
                getchar();
                pos = validarPecas(arqPec, V.codigo);
                if (pos != -1) {
                    fseek(arqPec, pos, SEEK_SET);
                    fread(&P, sizeof(pecas), 1, arqPec);
                    printf("Quantidade desejada: ");
                    scanf("%d", &V.qtdDesejada);
                    if (P.quantidade >= V.qtdDesejada) {
                        V.subtotal = V.qtdDesejada * P.preco;
                        printf("\nResumo da venda:\nProduto: %s\nQuantidade: %d\nPreco unitario: R$ %.2f\nSubtotal: R$ %.2f\n",
                               P.nome, V.qtdDesejada, P.preco, V.subtotal);
                    } else {
                        printf("\nEstoque insuficiente. Disponivel: %d\n", P.quantidade);
                        vendaValida = 0;
                    }
                } else {
                    printf("\nPeca nao encontrada!\n");
                    vendaValida = 0;
                }
            } else if (op2 == 3) {
                printf("Descricao do servico: ");
                fgets(S.descricao, MAXSTR, stdin);
                S.descricao[strcspn(S.descricao, "\n")] = '\0';
                printf("Tipo do servico: ");
                fgets(S.tipoServico, MAXSTR, stdin);
                S.tipoServico[strcspn(S.tipoServico, "\n")] = '\0';
                printf("Preco do servico: ");
                scanf("%f", &S.preco);
                printf("Data do servico (dd mm aaaa): ");
                scanf("%d %d %d", &S.D.dia, &S.D.mes, &S.D.ano);
                getchar();
                if (V.opCliente == 1)
                    strcpy(S.cpfParaContrato, V.cpf);
                else
                    strcpy(S.cnpjParaContrato, V.cnpj);
                salvarServico(S);
                printf("\nServico cadastrado e venda finalizada!\n");
                vendaValida = 0;
            } else {
                printf("\nRetornando...\n");
                vendaValida = 0;
            }
        }

        if (vendaValida == 1) {
            printf("\nForma de pagamento:\n1 - Pix (10%% desconto)\n2 - Boleto (5%% acrescimo)\n3 - Financiamento (10%% acrescimo)\nEscolha: ");
            scanf("%d", &V.formaPagamento);
            if (V.formaPagamento == 1)
                V.totalFinal = V.subtotal * 0.90;
            else if (V.formaPagamento == 2)
                V.totalFinal = V.subtotal * 1.05;
            else if (V.formaPagamento == 3)
                V.totalFinal = V.subtotal * 1.10;
            else {
                printf("\nOpcao invalida. Venda cancelada.\n");
                vendaValida = 0;
            }
        }

        if (vendaValida == 1) {
            printf("Valor final: R$ %.2f\nDeseja finalizar a venda?\n1 - Sim\n2 - Nao\nEscolha: ", V.totalFinal);
            scanf("%d", &V.confirmar);
            if (V.confirmar != 1) {
                printf("\nVenda cancelada pelo usuario.\n");
                vendaValida = 0;
            }
        }

        if (vendaValida == 1) {
            printf("Data da venda (dd mm aaaa): ");
            scanf("%d %d %d", &V.D.dataVendaDia, &V.D.dataVendaMes, &V.D.dataVendaAno);
            if (op2 == 1) {
                M.quantidade -= V.qtdDesejada;
                fseek(arqMaq, pos, SEEK_SET);
                fwrite(&M, sizeof(maquinarios), 1, arqMaq);
            } else if (op2 == 2) {
                P.quantidade -= V.qtdDesejada;
                fseek(arqPec, pos, SEEK_SET);
                fwrite(&P, sizeof(pecas), 1, arqPec);
            }
            printf("\nVenda finalizada com sucesso!\n");
        }

        system("pause");
        fclose(arqPF);
        fclose(arqPJ);
        fclose(arqMaq);
        fclose(arqPec);
    } else {
        printf("\nERRO ao abrir arquivos.\n");
        if (arqPF) fclose(arqPF);
        if (arqPJ) fclose(arqPJ);
        if (arqMaq) fclose(arqMaq);
        if (arqPec) fclose(arqPec);
    }
}

//fim venda
// MAIN DO PROGRAMA INTEIRO DO PROJETO --------------------------------------------

int main() {
    int op;

    do {
        printf("\n--- MENU ---\n");
        printf("\n1 - Cadastro");
        printf("\n2 - Busca");
        printf("\n3 - Editar");
        printf("\n4 - Realizar venda");
        printf("\n5 - Excluir");
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
        case 3:
                editarCadastros();
            break;
        case 4:
                realizarVenda();
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

// TERMINA AQUI O MAIN DO PROGRAMA INTEIRO DO PROJETO --------------------------------------------
