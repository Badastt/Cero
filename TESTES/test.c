#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "list.h"
#include "types.h"

int main (){
	lista *lista = inicializarLista();
	iteradorLista *it = inicializarIterador(lista);
	
	adicionarFimLista (lista, 1);
	adicionarFimLista (lista, 2);
	adicionarFimLista (lista, 3);
	adicionarFimLista (lista, 4);
	adicionarFimLista (lista, 5);
	adicionarFimLista (lista, 6);
	
	moverIteradorNumero (it, 1);
	printf ("%d %d\n\n", elementoLista(it), it->numero);
	
	moverIteradorNumero (it, 6);
	printf ("%d %d\n\n", elementoLista(it), it->numero);
	
	proximoIterador (it);
	printf ("%d %d\n\n", elementoLista(it), it->numero);
	
	anteriorIterador (it);
	printf ("%d %d\n\n", elementoLista(it), it->numero);
	
	for (int i = 0; i < 100; i++)
		proximoIterador (it);
	printf ("%d %d\n\n", elementoLista(it), it->numero);
	
	moverIteradorNumero (it, 7);
	printf ("%d %d\n\n", elementoLista(it), it->numero);
	
	moverIteradorNumero (it, 6);
	printf ("%d %d\n\n", elementoLista(it), it->numero);
	
	retira (it);
	printf ("%d %d\n\n", elementoLista(it), it->numero);
	
	moverIteradorNumero (it, 6);
	printf ("%d %d\n\n", elementoLista(it), it->numero);
	
	moverIteradorNumero (it, 5);
	printf ("%d %d\n\n", elementoLista(it), it->numero);
	
	return 0;
}