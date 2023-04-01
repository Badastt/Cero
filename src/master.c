#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../lib/types.h"
#include "../lib/list.h"
#include "../lib/stack.h"
#include "../lib/queue.h"
#include "../lib/baralho.h"

int main (int argc, char *argv[]){
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
	
	int acabou = 0;
	int flag = 0;
	int posCarta = 0;
	
	if (argv[1] == 0)
	while (1 && !acabou){
		flag = 0;
		moverIteradorNumero (itPlayer1, 1);
		for (int i = 0; i < quantidadeLista (maoPlayer1)+1; i++){
			flag = verificaJogada (elementoLista(itPlayer1), ultimoLista(baralhoMesa));
			proximoIterador (itPlayer1);
			if (flag)
				break;
		}
		
		printf ("A carta na mesa é a seguinte:\n");
		printCarta (ultimoLista(baralhoMesa), 0);
		printf ("\n");
		
		moverIteradorNumero (itPlayer1, 1);
		for (int i = 1; i < quantidadeLista (maoPlayer1)+1; i++, proximoIterador (itPlayer1))
			printCarta (elementoLista(itPlayer1), i);
		
		moverIteradorNumero (itPlayer1, 1);
		if (flag){
			printf ("Você têm cartas válidas, qual será a sua jogada?? (Digite o número atrás da carta)\n\n");
			scanf (" %d", &posCarta);
			
			moverIteradorNumero (itPlayer1, posCarta);
			
			while (!(verificaJogada(elementoLista(itPlayer1) ,ultimoLista(baralhoMesa)))){
				printf ("O número digitado é inválido, tente novamente:\n\n");
				scanf (" %d", &posCarta);
				moverIteradorNumero (itPlayer1, posCarta);
				}
			jogarCarta (itPlayer1, baralhoMesa, posCarta);
		} else {
			printf ("Você não tem nenhuma jogada válida, uma carta será comprada!!\n");
			comprarCartas (maoPlayer1, baralhoCompra, baralhoMesa, 1);
		}
		
		if (quantidadeLista (maoPlayer1) == 0){
			printf ("VOCÊ VENCEU!!\n");
			acabou = 1;
		}
	}
	
	
	//for (int i = 0; i < 6; i++){
	//	carta item = removerInicioLista(maoPlayer1);
	//	printf ("%d, %s, %s\n", item.num, returnEnumCor(item.cor), returnEnumTipo(item.tipo));
	//}

return 0;}
