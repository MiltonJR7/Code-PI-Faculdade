# SIAGRO – Sistema de Gestão de Oficina Agrícola

## Visão Geral

SIAGRO é um sistema desenvolvido em linguagem C com o objetivo de auxiliar no gerenciamento de oficinas agrícolas.  
A aplicação oferece controle sobre clientes, produtos, serviços e vendas, utilizando arquivos binários para armazenamento persistente dos dados.

O sistema funciona em ambiente de terminal e utiliza menus hierárquicos para navegação entre as funcionalidades.

---

## Funcionalidades

### Gestão de Clientes

#### Pessoa Física (PF)
- Cadastro de clientes com validação de CPF
- Consulta de clientes por CPF
- Edição de telefone e e-mail

#### Pessoa Jurídica (PJ)
- Cadastro de empresas com validação de CNPJ
- Consulta de empresas por CNPJ
- Edição de:
  - Nome empresarial
  - Telefone
  - E-mail
  - Responsável legal

---

### Gestão de Produtos

#### Maquinários
- Cadastro de maquinários agrícolas
- Consulta por código identificador
- Edição de informações
- Controle de estoque

#### Peças
- Cadastro de peças
- Consulta por código identificador
- Edição de informações
- Controle de estoque

Todos os produtos utilizam códigos únicos para identificação.

---

### Gestão de Serviços

- Cadastro de serviços
- Consulta por identificador (ID)
- Edição de serviços
- Associação de serviços a clientes por CPF ou CNPJ

---

### Vendas

- Registro de vendas de maquinários, peças e serviços
- Associação da venda a um cliente cadastrado
- Cálculo automático do valor final conforme a forma de pagamento:
  - Pix
  - Boleto
  - Financiamento
- Atualização automática do estoque
- Registro da data da venda

---

## Armazenamento de Dados

O sistema utiliza arquivos binários para persistência das informações:

### Clientes
- `arqPF.bin`
- `arqPJ.bin`

### Produtos
- `arqMaquinario.bin`
- `arqPecas.bin`

### Serviços
- `arqServicos.bin`

### Vendas
- `arqVendas.bin`

As operações de leitura e escrita são realizadas por meio das funções padrão da linguagem C.

---

## Status do Projeto

- Em desenvolvimento
- Funcionalidades principais implementadas
- Melhorias estruturais planejadas

---

## Melhorias Futuras

- Implementação de exclusão de registros
- Modularização do código em arquivos `.h` e `.c`
- Interface de terminal mais intuitiva
- Validações mais robustas de entrada de dados
- Geração de relatórios de vendas
- Refatoração dos menus e organização do fluxo do sistema

---

## Tecnologias Utilizadas

- Linguagem: C (ANSI C)
- Armazenamento: arquivos binários
- Interface: console / terminal

### Bibliotecas utilizadas

```c
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>
#include <windows.h>
