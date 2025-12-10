# Mindly - Assistente de Suporte Tecnico em C

O Mindly e um sistema baseado em CLI (Linha de Comando) que utiliza estruturas de dados do tipo Arvore de Decisao para diagnosticar e resolver problemas tecnicos comuns de computadores e perifericos.

O objetivo e tornar o suporte tecnico acessivel atraves de um guia passo a passo interativo, ideal para ambientes domesticos ou corporativos.

## Funcionalidades

O sistema carrega uma base de conhecimento dinamica e e capaz de diagnosticar problemas nos seguintes topicos:

* Impressora: Problemas de tinta, papel e conexao.
* PC/Computador: Falhas de inicializacao, video e energia.
* WiFi: Quedas de conexao e problemas de roteador.
* Rede: Configuracao de adaptador e cabos.
* Teclado/Mouse: Falhas de hardware e drivers.

## Como Funciona (Estrutura de Dados)

O projeto utiliza uma Arvore Binaria de Decisao.

1. O sistema le o arquivo banco_dados.txt.
2. Cada pergunta e um No da arvore.
3. Dependendo da resposta do usuario (sim ou nao), o programa percorre os ponteiros no->sim ou no->nao.
4. O percurso termina quando o sistema encontra uma folha contendo a tag SOLUCAO.

## Como Compilar e Rodar

Como o projeto inclui o arquivo da arvore diretamente no codigo principal, a compilacao e simples.

### Pre-requisitos
* Compilador C (GCC recomendado).
* Sistema operacional Windows ou Linux.

### Passo a Passo

1. Clone o repositorio:
   git clone https://github.com/Guize1234/Mindly.git
   cd Mindly

2. Compile o codigo:
   gcc principal.c -o mindly

3. Execute:
   * No Windows:
     ./mindly.exe
   * No Linux/Mac:
     ./mindly

## Estrutura dos Arquivos

* principal.c: Gerencia o menu, entrada do usuario e inicia o diagnostico.
* arvore.c: Contem a logica de manipulacao da arvore (criar no, carregar recursivamente, liberar memoria).
* model.h: Define as structs (No e Mapeamento).
* banco_dados.txt: Base de conhecimento do sistema. Arquivo de texto que contem todas as perguntas e respostas estruturadas.

## Como adicionar novos diagnosticos

Voce pode expandir o Mindly editando apenas o arquivo banco_dados.txt, sem precisar recompilar o codigo.

Formato do arquivo:

[topico]
Pergunta inicial?
Pergunta se a resposta for SIM?
Solucao se SIM para a anterior.
#
#
Pergunta se a resposta for NAO?
...

* Use # para indicar o fim de um ramo.
* Use SOLUCAO: para entregar uma resposta final.

---
Projeto desenvolvido para a disciplina de Estrutura de Dados.