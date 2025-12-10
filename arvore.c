#include <stdio.h>    
#include <stdlib.h>     
#include <string.h>     
#include "model.h"      

//é uma função que vai remover o "espaço" do final escrita porque fgets sempre adiciona ele
void remover_nova_linha(char *str) {
    size_t len = strlen(str);//pega o tamanho atual da string
    if (len > 0 && str[len - 1] == '\n')// verifica se o último caractere é um \n
        str[len - 1] = '\0'; //troca o \n por \0 pra finalizar a string certinho
}

//cria um novo nó da árvore com o texto passado
No* novo_no(char *texto) {
    No *no = (No*)malloc(sizeof(No));//aloca a memória pro nó
    if(!no) exit(1);//se der erro na alocação, vai encerrar o programa
    strcpy(no->texto, texto);//copia o texto pra dentro do nó
    no->sim = NULL;//inicia o ponteiro de "sim" como vazio
    no->nao = NULL;//inicia o ponteiro de "não" como vazio
    return no;//volta o nó prontinho
}

//ele libera toda a memória usada pela árvore de forma recursiva
void liberar_arvore(No *raiz) {
    if (raiz == NULL) return;//se a raiz for nula, não tem nada pra liberar
    liberar_arvore(raiz->sim);//libera a folha do "sim"
    liberar_arvore(raiz->nao);//libera a folha do "não"
    free(raiz);//libera o nó atual
}

// carrega uma árvore inteira lendo do arquivo, também de forma recursiva
No* carregar_recursivo(FILE *arquivo) {
    char buffer[128];//buffer pra armazenar o texto da linha

    if (!fgets(buffer, sizeof(buffer), arquivo))//tenta ler uma linha do arquivo
        return NULL;//se não ler nada, acabou a árvore

    remover_nova_linha(buffer);//tira o \n da linha

//se a linha for "#" ou começar com '[', quer dizer que acabou essa árvore
    if (strcmp(buffer, "#") == 0 || buffer[0] == '[')
        return NULL;

    No *no = novo_no(buffer);//cria um nó com o texto da linha
    no->sim = carregar_recursivo(arquivo);//carrega o ramo "sim"
    no->nao = carregar_recursivo(arquivo);//carrega o ramo "não"
    return no;//volta com a árvore montada
}

//procura no arquivo a palavra chave que corresponde o assunto e carrega a árvore daquele assunto
void carregar_do_arquivo_unico(Mapeamento *mapa, const char *nome_arquivo_db) {
    FILE *arquivo = fopen(nome_arquivo_db, "r");  //abre o arquivo txt pra leitura
    if (arquivo == NULL) {//se não conseguir abrir
        printf("Erro: Banco de dados '%s' nao encontrado.\n", nome_arquivo_db);
        return;
    }

    char buffer[128]; //buffer pra ler o arquivo
    char tag_procurada[64];//onde vamos colocar a palavra chave tipo
    
    //monta a "tag" que queremos procurar no arquivo
    sprintf(tag_procurada, "[%s]", mapa->palavra_chave);

    int encontrou = 0;// auxiliar que diz se achamos alguma palavra cahave ou não

    // percorre o arquivo linha a linha procurando a tag
    while(fgets(buffer, sizeof(buffer), arquivo)) {
        remover_nova_linha(buffer); //limpa \n da linha
        if (strcmp(buffer, tag_procurada) == 0) { // se a linha for a tag que queremos
            encontrou = 1; //marca que achou
            break;// então para de procurar
        }
    }

    if (encontrou) {//se achou a palavra chave
        mapa->raiz_da_arvore = carregar_recursivo(arquivo); //carrega a árvore depois da próxima linha
        //printf("Modulo '%s' carregado.\n", mapa->palavra_chave);
    } else {
        //se não achou vai avisa e deixar a árvore vazia
        printf("Aviso: Topico '%s' nao encontrado no arquivo.\n", mapa->palavra_chave);
        mapa->raiz_da_arvore = NULL;
    }

    fclose(arquivo);//fecha o arquivo sempre no final
}
