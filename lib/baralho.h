#ifndef BARALHO
#define BARALHO

#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "list.h"
#include "queue.h"
#include "types.h"

#define NUM_CARTAS 108
#define MAXLOCAL NUM_CARTAS

#define ERRO (carta){-1, -1, -1};
#define CLEAR (carta){0, -1, -1};

void criarBaralho(pilha *);
char *returnEnumCor (corCarta);
char *returnEnumTipo (tipoCarta);
void shuffle (pilha *);
void swapCartas (T *, int, int);
void recolherCartas (pilha *, fila *);
void comprarCartas (lista *, pilha *, fila *, int);
int verificaJogada (T, T);
void primeiraCarta (pilha *, fila *);
int jogarCarta (iteradorLista *, fila *, int);
int jogarCartaIA (iteradorLista *, fila *, int);
void printCarta (T, int);
void printCartaMesa (T);
void limpaTela ();

#endif
