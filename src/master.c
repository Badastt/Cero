#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
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
	
	printf("\e[1;1H\e[2J");
	
	if (argv[1] == 0)
	while (1 && !acabou){
		if (!flag){	
			flag = 0;
			moverIteradorNumero (itPlayer1, 1);
			for (int i = 0; i < quantidadeLista (maoPlayer1)+1; i++){
				flag = verificaJogada (elementoLista(itPlayer1), ultimoLista(baralhoMesa));
				proximoIterador (itPlayer1);
				if (flag)
					break;
			}
			
			printf ("A carta na mesa é a seguinte:\n\n");
			printCartaMesa (ultimoLista(baralhoMesa));
			printf ("\n");
			printCarta (ultimoLista(baralhoMesa), 0);
			printf ("\n");
			
			moverIteradorNumero (itPlayer1, 1);
			for (int i = 1; i < quantidadeLista (maoPlayer1)+1; i++){
				printCarta (elementoLista(itPlayer1), i);
				proximoIterador (itPlayer1);
			}
			
			if (quantidadeLista (maoPlayer2) > 1)
				printf ("O seu oponente tem %d cartas!!\n", quantidadeLista (maoPlayer2));
			else
				printf ("O seu oponente tem UMA carta!!\n");
			
			moverIteradorNumero (itPlayer1, 1);
			if (flag){
				printf ("Você têm cartas válidas, qual será a sua jogada?? (Digite o número atrás da carta)\n\n");
				scanf (" %d%*c", &posCarta);
				
				moverIteradorNumero (itPlayer1, posCarta);
				
				while (!(verificaJogada(elementoLista(itPlayer1) ,ultimoLista(baralhoMesa)))){
					printf ("O número digitado é inválido, tente novamente:\n\n");
					scanf (" %d%*c", &posCarta);
					moverIteradorNumero (itPlayer1, posCarta);
					}
				
				flag = jogarCarta (itPlayer1, baralhoMesa, posCarta);
				if (flag == 1)
					comprarCartas (maoPlayer2, baralhoCompra, baralhoMesa, 2);
				else if (flag == 2)
					comprarCartas (maoPlayer2, baralhoCompra, baralhoMesa, 4);
					
				
				printf("\e[1;1H\e[2J");
			} else {
				printf ("Você não tem nenhuma jogada válida, uma carta será comprada!!\n");
				printf ("Pressione ENTER para confirmar\n");
				getchar();
				printf("\e[1;1H\e[2J");
				comprarCartas (maoPlayer1, baralhoCompra, baralhoMesa, 1);
			}
		} else {
			if (flag == 1)
				printf ("O seu adversário jogou uma carta +2, então você não pode jogar esse turno e comprou 2 cartas!!!\n");
			else if (flag == 2)
				printf ("O seu adversário jogou uma carta +4, então você não pode jogar esse turno e comprou 4 cartas!!!\n");
			else if (flag == 3)
				printf ("O seu adversário jogou uma carta bloqueio, então você não pode jogar esse turno!!!\n");
			else if (flag == 4)
				printf ("O seu adversário jogou uma carta reverte, então você não pode jogar esse turno!!!\n");
			if (quantidadeLista (maoPlayer2) > 1)
				printf ("O seu oponente tem %d cartas!!\n", quantidadeLista (maoPlayer2));
			else
				printf ("O seu oponente tem UMA carta!!\n");
			printf ("Pressione ENTER para confirmar\n");
				getchar();
			printf("\e[1;1H\e[2J");
			flag = 0;
		}
		
		if (quantidadeLista (maoPlayer1) == 0){
			printf ("DIGA CERO OU NÃO GANHARÁ O JOGO\n");
			char cero[5];
			int j = 0;
			while ((cero[j] = getchar()) != '\n' &&cero[j] != EOF)
				j++;
			cero [4] = '\0';
			
			for(j = 0; j < 4; j++)
				cero[j] = tolower(cero[j]);
			if (strcmp(cero, "cero") == 0){
				printf ("VOCÊ VENCEU!!\n");
				acabou = 1;
				break;
			} else {
				printf ("ERRADO, COMPRE DUAS CARTAS!!\n\n");
				comprarCartas (maoPlayer1, baralhoCompra, baralhoMesa, 2);
			}
		}
		
		//IA:
		if (!flag){
			moverIteradorNumero (itPlayer2, 1);
			for (int i = 0; i < quantidadeLista (maoPlayer2)+1; i++){
				flag = verificaJogada (elementoLista(itPlayer2), ultimoLista(baralhoMesa));
				if (flag){
					printf ("O seu adversário jogou a carta:\n");
					printCarta (elementoLista(itPlayer2), 0);
					printf ("\n\n");
					flag = jogarCartaIA (itPlayer2, baralhoMesa, i+1);
					if (flag == 1)
						comprarCartas (maoPlayer1, baralhoCompra, baralhoMesa, 2);
					else if (flag == 2)
						comprarCartas (maoPlayer1, baralhoCompra, baralhoMesa, 4);
					break;
				} else if (!flag && i == quantidadeLista (maoPlayer2)){
					printf ("O seu adversário não tinha nenhuma carta válida então comprou uma carta\n\n\n\n");
					comprarCartas (maoPlayer2, baralhoCompra, baralhoMesa, 1);
					i++;
				}
				proximoIterador (itPlayer2);
			}
		} else {
			if (flag == 1)
				printf ("Você jogou uma carta +2, então o seu oponente não jogou nesse turno!!!\n");
			else if (flag == 2)
				printf ("Você jogou uma carta +4, então o seu oponente não jogou nesse turno!!!\n");
			else if (flag == 3)
				printf ("Você jogou uma carta bloqueio, então o seu oponente não jogou nesse turno!!!\n");
			else if (flag == 4)
				printf ("Você jogou uma carta reverte, então o turno voltou para você!!!\n");
			flag = 0;
		}
		
		if (quantidadeLista (maoPlayer2) == 0){
			printf ("VOCÊ PERDEU\n");
			acabou = 1;
			break;
		}
	}

destroiPilha (baralhoCompra);
destroyQueue (baralhoMesa);
destroiLista (maoPlayer1);
destroiLista (maoPlayer2);
destroiIterador (itPlayer1);
destroiIterador (itPlayer2);

return 0;}
