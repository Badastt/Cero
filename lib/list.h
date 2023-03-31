#ifndef LIST
#define LIST

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "baralho.h"
#include "types.h"

lista *inicializarLista();
void adicionarInicioLista (lista *, T);
void adicionarFimLista (lista *, T);
T removerInicioLista (lista *);
T removerFimLista (lista *);
int vaziaLista (lista *);
void destroiLista (lista *);
int quantidadeLista (lista *);

iteradorLista *inicializarIterador (lista *);

void adicionarAntes (lista *, iteradorLista *, T);
void adicionarDepois (lista *, iteradorLista *, T);
iteradorLista retira (lista *, iteradorLista *);

void proximoIterador (iteradorLista *);
void anteriorIterador (iteradorLista *);

T elementoLista (iteradorLista *);

#endif