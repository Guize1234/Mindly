#include <stdio.h>           
#include <stdlib.h>           
#include <string.h>           
#include <ctype.h>            
#include <locale.h>           

#include "model.h"//arquivo com as estruturas
#include "arvore.c"//inclui diretamente para a árvore


// funções e estruturas que ajudam na questão de textos, digitação e também para a inicialização da árvore
void limpar_string(char *str);
void limpar_buffer_teclado(void);
No* buscar_arvore_por_texto(Mapeamento *mapa, int qtd, char *texto);
void iniciar_diagnostico(No *raiz);

//é uma função responsável por carregar todos os tópicos e as árvores
void carregar_base_conhecimento(Mapeamento *mapa, int *qtd) {
//ou seja, ela preenche o mapeamento com as palavras chave e carrega suas árvores

//mapeamento 0, da impressora
    strcpy(mapa[0].palavra_chave, "impressora");
    carregar_do_arquivo_unico(&mapa[0], "banco_dados.txt");

//mapeamento 1, do PC
    strcpy(mapa[1].palavra_chave, "pc");
    carregar_do_arquivo_unico(&mapa[1], "banco_dados.txt");

//mapeamento 2, do computador
    strcpy(mapa[2].palavra_chave, "computador"); 
    strcpy(mapa[2].palavra_chave, "pc");//tem a temporária para buscar também pela parte do "pc"
    carregar_do_arquivo_unico(&mapa[2], "banco_dados.txt");
    strcpy(mapa[2].palavra_chave, "computador");//ai volta para o nome real

//mapeamento 3, do Wifi
    strcpy(mapa[3].palavra_chave, "wifi");
    carregar_do_arquivo_unico(&mapa[3], "banco_dados.txt");

//mapeamento 4, da rede
    strcpy(mapa[4].palavra_chave, "rede");
    carregar_do_arquivo_unico(&mapa[4], "banco_dados.txt");

//mapeamento 5, do teclado
    strcpy(mapa[5].palavra_chave, "teclado");
    carregar_do_arquivo_unico(&mapa[5], "banco_dados.txt");

    *qtd = 6; //informa quantos tópicos existem
}

int main(void) {
    char problema[128];//vai armazenar o texto que o usuario digitou
    Mapeamento mapa[20];//é um vetor que guarda vários tópicos
    int qtd = 0;//a quanidade de tópicos que foram realmente carregados
    int op; //ele armazena a opção do menu
    No *raiz;//ponteiro para a árvore que fica relacionada pro problema
    int i;

    setlocale(LC_ALL, "Portuguese");//configura a acentuação

    carregar_base_conhecimento(mapa, &qtd);//vai carregar os tópicos

    while (1) {   //menu principal
        printf("\n/---------------------------------/");
        printf("\n|  SISTEMA DE DIAGNOSTICO TECNICO |");
        printf("\n/---------------------------------/");
        printf("\n1 - Descrever um problema");
        printf("\n2 - Ver topicos disponiveis");
        printf("\n3 - Sair");
        printf("\nEscolha uma opcao: ");

        if (scanf("%d", &op) != 1) { //ve se a leitura falhou
            limpar_buffer_teclado();//ele limpa o lixo do teclado
            continue;//vai voltar para o menu
        }
        limpar_buffer_teclado();//remove o "espaço" que sobra

        if (op == 1) {//quando o usuário quer descrever um problema
            printf("\nDescreva seu problema (ex: 'meu wifi caiu'):\n> ");
            if (!fgets(problema, sizeof(problema), stdin)) continue;//vai ler o texto
            limpar_string(problema);//ele converte para letra minúscula e também remove o "espaço" que sobra
            raiz = buscar_arvore_por_texto(mapa, qtd, problema);//encontra árvore que corresponde

            if (raiz != NULL) {//quando achou o tópico
                printf("\n--- INICIANDO DIAGNOSTICO ---\n");
                iniciar_diagnostico(raiz); // passa pelo questionário de diagnóstico
            } else {
                printf("\n Problema nao identificado na base de dados.\n"); //se não encontrou
            }
        }
        else if (op == 2) {//mostra os tópicos carregados
            printf("\n--- TOPICOS CARREGADOS ---\n");
            for (i = 0; i < qtd; i++) {
                if (mapa[i].raiz_da_arvore != NULL)
                    printf(" - %s\n", mapa[i].palavra_chave);//se carregou certo
                else
                    printf(" - %s [ERRO AO CARREGAR]\n", mapa[i].palavra_chave);
            }
        }
        else if (op == 3) { //é a opção de sair
            for (i = 0; i < qtd; i++) liberar_arvore(mapa[i].raiz_da_arvore);//vai lberar a memória
            return 0;//encerra o programa
        }
    }
    return 0;
}

//começa o processo das perguntas e respostas
void iniciar_diagnostico(No *raiz) {
    if (raiz == NULL) return;//caso esteja vazio
    No *atual = raiz;//começa pelo nó raiz
    char resp[16];//vai guardar a resposta do usuário

    while (atual != NULL) {//enquanto tiver os nós
        if (atual->sim == NULL && atual->nao == NULL) { //se for o nó final
            printf("\n%s\n", atual->texto); //vai mostrar a solução
            break;
        }

        //mostra a pergunta
        printf("\n%s\n[s/n]: ", atual->texto);

        if (fgets(resp, sizeof(resp), stdin)) { //le a resposta
            limpar_string(resp); //normaliza o texto

            //vai pro próximo nó dependendo da resposta
            if (strcmp(resp, "sim") == 0 || strcmp(resp, "s") == 0)
                atual = atual->sim; //ramo do sim
            else
                atual = atual->nao; //ramo do não
        }
    }
}

//ele busca no texto do usuário uma ou mais palavras chave
No* buscar_arvore_por_texto(Mapeamento *mapa, int qtd, char *texto) {
    int i;
    for (i = 0; i < qtd; i++) {
        if (strstr(texto, mapa[i].palavra_chave) != NULL) { //quando achou a palavra chave, vai retornar pra árvore que corresponde
            return mapa[i].raiz_da_arvore;
        }
    }
    return NULL;//quando não encontrou nenhum tópico
}

//essa função coloca as letras para minúsculas e remove também as quebras de linha
void limpar_string(char *str) {
    int i;
    for (i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);//converte a letra para minúscula
        if (str[i] == '\n' || str[i] == '\r') str[i] = '\0'; //remove a quebra de linha
    }
}

//ele limpa o que "sobrou" dos caracteres
void limpar_buffer_teclado(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);//vai ler até achar o "espaço"
}
