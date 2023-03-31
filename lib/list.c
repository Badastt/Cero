#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "list.h"
#include "baralho.h"
#include "types.h"

lista *inicializarLista(){
	lista *l = (lista*)malloc(sizeof(lista));
	nodeLista *n = (nodeLista*)malloc(sizeof(nodeLista));
	l->sentinela = n;
	l->sentinela->proximo = l->sentinela;
	l->sentinela->anterior = l->sentinela;
	l->sentinela->item = ERROR;
	l->quantidade = 0;
	return l;
}

void adicionarInicioLista (lista *l, T data){
	nodeLista *n = (nodeLista*)malloc(sizeof(nodeLista));
	n->item = data;
	n->proximo = l->sentinela->proximo;
	n->anterior = l->sentinela;
	l->sentinela->proximo = n;
	n->proximo->anterior = n;
	l->quantidade++;
}

void adicionarFimLista (lista *l, T data){
	nodeLista *n = (nodeLista*)malloc(sizeof(nodeLista));
	n->item = data;
	n->proximo = l->sentinela;
	n->anterior = l->sentinela->anterior;
	l->sentinela->proximo = n->anterior->proximo;
	l->sentinela->anterior = n;
	l->quantidade++;
}

T removerInicioLista (lista *l){
	nodeLista *n = l->sentinela->proximo;
	T data = n->item;
	l->sentinela->proximo = l->sentinela->proximo->proximo;
	l->sentinela->proximo->anterior = l->sentinela;
	free (n);
	l->quantidade--;
	return data;
}

T removerFimLista (lista *l){
	nodeLista *n = l->sentinela->anterior;
	if (vaziaLista (l))
		return ERROR;
	T data = n->item;
	l->sentinela->anterior = l->sentinela->anterior->anterior;
	l->sentinela->anterior->proximo = l->sentinela;
	free (n);
	l->quantidade--;
	return data;
}

int vaziaLista (lista *l){
	return l->quantidade == 0;
}

void destroiLista (lista *l){
	while (!vaziaLista (l))
		removerFimLista (l);
	free (l->sentinela);
	free (l);
}

int quantidadeLista (lista *l){
	return l->quantidade;
}

iteradorLista *inicializarIterador (lista *l){
	iteradorLista *i = (iteradorLista*)malloc(sizeof(iteradorLista));
	i->lista = l;
	i->posicao = l->sentinela;
	return i;
}


void adicionarAntes (lista *l, iteradorLista *i, T data){
	
	
}

void proximoIterador (iteradorLista *i){
	if (i->posicao->proximo == i->lista->sentinela)
		i->posicao = i->lista->sentinela->proximo;
	else
		i->posicao = i->posicao->proximo;
}

void anteriorIterador (iteradorLista *i){
	if (i->posicao->anterior == i->lista->sentinela)
		i->posicao = i->lista->sentinela->proximo;
	else
		i->posicao = i->posicao->anterior;
}

T elementoLista (iteradorLista *i){
	return i->posicao->item;
}