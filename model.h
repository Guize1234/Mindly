#ifndef MODEL_H //ve se o arquivo já foi incluído antes
#define MODEL_H //definição de que agora ele está incluído

//essa estrutura representa um nó da árvore de decisão
typedef struct No {
    char texto[128];// guarda o texto da pergunta ou da solução
    struct No *sim;//ponteiro para o próximo nó se a resposta for "sim"
    struct No *nao;//ponteiro para o próximo nó se a resposta for "não"
} No;

//estrutura usada para ligar uma palavra chave para a "sua" árvore
typedef struct {
    char palavra_chave[32];//a palavra chave que o usuário digita, tipo wifi, mouse...
    No *raiz_da_arvore;//ponteiro para a raiz da árvore que "tem" esse assunto
} Mapeamento;

#endif //finalização
