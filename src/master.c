#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../lib/types.h"
#include "../lib/list.h"
#include "../lib/stack.h"
#include "../lib/queue.h"
#include "../lib/baralho.h"

int main (){
	pilha *baralhoCompra = inicializarPilha(NUM_CARTAS);
	fila *baralhoMesa = initializeQueue();
	
	lista *maoPlayer1 = inicializarLista();
	lista *maoPlayer2 = inicializarLista();
	iteradorLista *itPlayer1 = inicializarIterador(maoPlayer1);
	iteradorLista *itPlayer2 = inicializarIterador(maoPlayer2);
	
	criarBaralho(baralhoCompra);
	shuffle (baralhoCompra);
	
	comprarCartas (maoPlayer1, baralhoCompra, baralhoMesa, 6);
	comprarCartas (maoPlayer2, baralhoCompra, baralhoMesa, 6);
	
	proximoIterador (itPlayer1);
	proximoIterador (itPlayer2);
	
	primeiraCarta (baralhoCompra, baralhoMesa);
	
	int flag = 0;
	for (int i = 0; i < quantidadeLista (maoPlayer1); i++, proximoIterador (itPlayer1)){
		flag = verificaJogada (elementoLista(itPlayer1), ultimoLista(baralhoMesa));
		if (flag)
			break;
	}
	if (!flag)
		comprarCartas (maoPlayer1, baralhoCompra, baralhoMesa, 1);
	
	for (int i = 0; i < quantidadeLista (maoPlayer1); i++, proximoIterador (itPlayer1)){
		printCarta (elementoLista(itPlayer1));
	}
	
	printf ("\n");
	
	printCarta (ultimoLista(baralhoMesa));
	
	//addQueue (baralhoMesa, popStack(baralhoCompra));
	
	//for (int i = 0; i < 6; i++){
	//	carta item = removerInicioLista(maoPlayer1);
	//	printf ("%d, %s, %s\n", item.num, returnEnumCor(item.cor), returnEnumTipo(item.tipo));
	//}

return 0;}
