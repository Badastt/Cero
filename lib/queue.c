#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
#include "baralho.h"
#include "types.h"

//A fila foi feita utilizando utilizando memória não-sequencial. 


fila *initializeQueue(){
	fila *f = (fila*)malloc(sizeof(fila));
	f->inicio = NULL;
	f->fim = NULL;
	f->quantidade = 0;
	return f;
}


void adicionarFila (fila *f, T data){
	nodeFila *n = (nodeFila*)malloc(sizeof(nodeFila));
	n->item = data;
	n->proximo = NULL;
	if (filaVazia(f)){
		f->inicio = f->fim = n;
	} else {
		f->fim->proximo = n;
		f->fim = n;
	}
	f->quantidade++;
}


T removeFila (fila *f){
	T item = CLEAR;
	if (!filaVazia (f)){
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

//Retorna o elemento que está no final da fila.
T ultimoFila (fila *f){
	return f->fim->item;
}
//Retorna quantidade de itens na fila.
int quantidadeFila (fila *f){
	return f->quantidade;
}
//Checa se fila está vazia.
int filaVazia (fila *f){
	return f->quantidade == 0;
}
//Destroi a fila.
void destroiFila (fila *f){
	while (!filaVazia (f))
		removeFila (f);
	free (f);
}