#ifndef BARALHO
#define BARALHO

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "stack.h"
#include "list.h"
#include "queue.h"
#include "types.h"

#define NUM_CARTAS 108
#define MAX NUM_CARTAS

#define ERROR (carta){-1, -1, -1};
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
void jogarCarta (iteradorLista *, fila *, int);
void jogarCartaIA (iteradorLista *, fila *, int);

void printCarta (T, int);
void printCartaMesa (T);

#endif
