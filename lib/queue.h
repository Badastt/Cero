#ifndef QUEUE
#define QUEUE

#include <stdio.h>
#include <stdlib.h>
#include "baralho.h"
#include "types.h"

fila *initializeQueue();
void adicionarFila (fila *, T);
T removeFila (fila *);
T ultimoFila (fila *);
int quantidadeFila (fila *f);
int filaVazia (fila *);
void destroiFila (fila *);

#endif