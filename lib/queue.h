#ifndef QUEUE
#define QUEUE

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "baralho.h"
#include "types.h"

fila *initializeQueue();
void adicionarFila (fila *, T);
T removeQueue (fila *);
T ultimoLista (fila *);
int quantidadeFila (fila *f);
int emptyQueue (fila *);
void destroyQueue (fila *);

#endif