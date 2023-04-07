#ifndef LIST
#define LIST

#include <stdio.h>
#include <stdlib.h>
#include "baralho.h"
#include "types.h"

lista *inicializarLista();
void adicionarInicioLista (lista *, T);
void adicionarFimLista (lista *, T);
T removerInicioLista (lista *);
T removerFimLista (lista *);
int listaVazia (lista *);
void destroiLista (lista *);
int quantidadeLista (lista *);

iteradorLista *inicializarIterador (lista *);

void retira (iteradorLista *);

void proximoIterador (iteradorLista *);
void anteriorIterador (iteradorLista *);

void moverIteradorNumero (iteradorLista *, int);

T elementoLista (iteradorLista *);

void destroiIterador (iteradorLista *);

#endif