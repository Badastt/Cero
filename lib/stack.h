#ifndef STACK
#define STACK

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "baralho.h"
#include "types.h"

pilha *inicializarPilha(int);
void adicionarPilha (pilha *, T);
T removerPilha (pilha *);
int pilhaVazia (pilha *);
int pilhaCheia (pilha *);
void destroiPilha (pilha *);

#endif
