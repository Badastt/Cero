#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "queue.h"
#include "baralho.h"
#include "types.h"

fila *initializeQueue(){
	fila *f = (fila*)malloc(sizeof(fila));
	f->inicio = NULL;
	f->fim = NULL;
	return f;
}

void adicionarFila (fila *f, T data){
	nodeFila *n = (nodeFila*)malloc(sizeof(nodeFila));
	n->item = data;
	n->proximo = NULL;
	if (emptyQueue(f)){
		f->inicio = f->fim = n;
	} else {
		f->fim->proximo = n;
		f->fim = n;
	}
	f->quantidade++;
}

T removeQueue (fila *f){
	T item = CLEAR;
	if (!emptyQueue (f)){
		nodeFila *n = f->inicio;
		f->inicio = f->inicio->proximo;
		item = n->item;
		free (n);
		f->quantidade--;
	}
	if (f->inicio == NULL)
		f->fim = NULL;
	return item;
}

T ultimoLista (fila *f){
	return f->fim->item;
}

int quantidadeFila (fila *f){
	return f->quantidade;
}

int emptyQueue (fila *f){
	return f->quantidade == 0;
}

void destroyQueue (fila *f){
	while (!emptyQueue (f))
		removeQueue (f);
	free (f);
}