# Mindly — Assistente de Suporte Técnico em C

Mindly é um assistente de suporte técnico em linha de comando que usa uma árvore de decisão para diagnosticar problemas comuns de computadores e periféricos e sugerir soluções passo a passo.

## Funcionalidades

- Suporte a impressoras (tinta, atolamentos, conexão).
- Diagnóstico de problemas de inicialização, vídeo e energia em PCs.
- Verificação de conectividade Wi‑Fi e problemas de roteador.
- Diagnóstico básico de rede (adaptadores, cabos).
- Verificação de teclado e mouse (hardware e drivers).

## Como funciona

O sistema carrega uma base de conhecimento (`banco_dados.txt`) e constrói uma árvore binária de decisão em memória. Cada nó representa uma pergunta; a resposta do usuário (`sim`/`nao`) determina o caminho (`sim` ou `nao`) até uma folha que contém uma `SOLUCAO`.

Fluxo básico:

1. O programa carrega `banco_dados.txt`.
2. Exibe a pergunta atual ao usuário.
3. Avança pela árvore conforme as respostas até encontrar uma solução.

## Requisitos

- Compilador C (GCC recomendado).
- Windows, Linux ou macOS.

## Compilar e executar

Exemplo de comandos com GCC (PowerShell no Windows):

```powershell
gcc principal.c arvore.c -o mindly.exe
# Executar
.\mindly.exe
```

Exemplo em Linux/macOS:

```bash
gcc principal.c arvore.c -o mindly
./mindly
```

Observações:

- Caso o projeto já inclua toda a árvore no código-fonte, talvez não seja necessário compilar `arvore.c` separadamente — verifique os arquivos do repositório.

## Estrutura de arquivos

- `principal.c` — controlador do menu, entrada do usuário e fluxo principal.
- `arvore.c` — funções de manipulação da árvore (criação, carregamento recursivo, liberação).
- `model.h` — definições de `struct` (nó e mapeamento).
- `banco_dados.txt` — base de conhecimento em texto simples.

## Formato do `banco_dados.txt`

O arquivo contém perguntas, ramos e soluções. Exemplo simplificado:

```
[Impressora]
A impressora está ligada?
Sim: Verifique níveis de tinta.
Nao: Verifique conexão de energia.
#

SOLUCAO: Substituir cartucho.
#
```

Regras rápidas:

- Use `#` para indicar o fim de um ramo.
- Use a tag `SOLUCAO:` no início da linha para marcar uma solução final.

## Como adicionar diagnósticos

Edite apenas o arquivo `banco_dados.txt` seguindo o formato acima — não é necessário recompilar o código se o carregamento for dinâmico.

## Autores

- Guilherme — https://github.com/Guize1234
- Sofia — https://github.com/sofiafrantzz
- Vinícius — https://github.com/ViniciosRafael

---
Projeto desenvolvido para a disciplina de Estruturas de Dados.