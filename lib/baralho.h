#ifndef BARALHO
#define BARALHO

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "stack.h"
#include "types.h"

#define NUM_CARTAS 108
#define MAX NUM_CARTAS

#define ERROR (carta){-1, -1, -1};
#define CLEAR (carta){0, -1, -1};

void criarBaralho(stack *);
char *returnEnumCor (corCarta);
char *returnEnumTipo (tipoCarta);
void shuffle (stack *);
void swapCartas (T *, int, int);

#endif
