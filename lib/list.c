#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "baralho.h"
#include "types.h"

//A lista é duplamente encadeada, com sentinela e circular.
lista *inicializarLista(){
	lista *l = (lista*)malloc(sizeof(lista));
	nodeLista *n = (nodeLista*)malloc(sizeof(nodeLista));
	l->sentinela = n;
	l->sentinela->proximo = l->sentinela;
	l->sentinela->anterior = l->sentinela;
	l->sentinela->item = ERRO;
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
	l->sentinela->anterior = n;
	n->anterior->proximo = n;
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
	if (listaVazia (l))
		return ERRO;
	T data = n->item;
	l->sentinela->anterior = l->sentinela->anterior->anterior;
	l->sentinela->anterior->proximo = l->sentinela;
	free (n);
	l->quantidade--;
	return data;
}

//Checa se lista está vazia.
int listaVazia (lista *l){
	return l->quantidade == 0;
}

//Remove completamente todos os componentes da lista e a destroi.
void destroiLista (lista *l){
	while (!listaVazia (l))
		removerFimLista (l);
	free (l->sentinela);
	free (l);
}

//Retorna quantidade de itens na lista.
int quantidadeLista (lista *l){
	return l->quantidade;
}

iteradorLista *inicializarIterador (lista *l){
	iteradorLista *i = (iteradorLista*)malloc(sizeof(iteradorLista));
	i->lista = l;
	i->posicao = l->sentinela;
	i->numero = 0;
	return i;
}

void proximoIterador (iteradorLista *i){
	i->posicao = i->posicao->proximo;
	if (i->posicao == i->lista->sentinela){
		i->posicao = i->posicao->proximo;
		i->numero = 0;
	}
	i->numero++;
}

void anteriorIterador (iteradorLista *i){
	i->posicao = i->posicao->anterior;
	if (i->posicao == i->lista->sentinela){
		i->posicao = i->posicao->anterior;
		i->numero = quantidadeLista (i->lista)+1;
	}
	i->numero--;
}

//Move o iterador até uma posição fornecida pelo usuário.
void moverIteradorNumero (iteradorLista *i, int num){
	if (num <= 0 || num > quantidadeLista (i->lista))
		return;
	if (i->numero > num)
		while (i->numero != num)
			anteriorIterador(i);
	else if (i->numero < num)
		while (i->numero != num)
			proximoIterador(i);
}

//Remove um elemento na posição em que o iterador está.
void retira (iteradorLista *i){
	nodeLista *n = i->posicao;
	if (listaVazia (i->lista))
		return;
	i->posicao->anterior->proximo = i->posicao->proximo;
	i->posicao->proximo->anterior = i->posicao->anterior;
	i->lista->quantidade--;
	i->posicao = i->lista->sentinela->proximo;
	i->numero = 1;
	free (n);
}

T elementoLista (iteradorLista *i){
	return i->posicao->item;
}

void destroiIterador (iteradorLista *i){
	free (i);
}