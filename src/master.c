#ifdef __unix__         
	#define OS "LINUX"
#elif defined(_WIN32) || defined(WIN32) 
	#define OS "WINDOWS"
#endif
//Algumas operações dependem do sistema operacional, por isso, é necessário fazer essa verificação.


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
	//Declaração de Variáveis e Inicialiazações.
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
	//--------------------------------------------------------------------------
	
	printf("\e[1;1H\e[2J");
	printf (OS);
	//Função para limpar a tela em ambiente UNIX.
	
	
	//Loop principal do CERO, ele só termina quando o jogador ou a IA possuir apenas uma carta.
	while (1 && !acabou){
		if (!flag){	
			flag = 0;
			moverIteradorNumero (itPlayer1, 1);
			//Verifica se o jogador possui alguma jogada válida.
			for (int i = 0; i < quantidadeLista (maoPlayer1)+1; i++){
				flag = verificaJogada (elementoLista(itPlayer1), ultimoFila(baralhoMesa));
				proximoIterador (itPlayer1);
				if (flag)
					break;
			}
			
			
			printf ("A carta na mesa é a seguinte:\n\n");
			printCartaMesa (ultimoFila(baralhoMesa));
			printf ("\n");
			printCarta (ultimoFila(baralhoMesa), 0);
			printf ("\n");
			//Utiliza funções para mostrar a carta na mesa de maneira mais visual.
			
			
			moverIteradorNumero (itPlayer1, 1);
			for (int i = 1; i < quantidadeLista (maoPlayer1)+1; i++){
				printCarta (elementoLista(itPlayer1), i);
				proximoIterador (itPlayer1);
			}
			//Printa todas as cartas do jogador.
			
			
			if (quantidadeLista (maoPlayer2) > 1)
				printf ("O seu oponente tem %d cartas!!\n", quantidadeLista (maoPlayer2));
			else
				printf ("O seu oponente tem UMA carta!!\n");
			//Como o jogo não mostra as cartas da IA, é necessário pelo menos falar a quantidade de cartas.
			
			
			moverIteradorNumero (itPlayer1, 1);
			if (flag){
				printf ("Você têm cartas válidas, qual será a sua jogada?? (Digite o número atrás da carta)\n\n");
				if (scanf (" %d%*c", &posCarta));
				else
					return -1;
				
				moverIteradorNumero (itPlayer1, posCarta);
				
				while (!(verificaJogada(elementoLista(itPlayer1) ,ultimoFila(baralhoMesa)))){
					printf ("O número digitado é inválido, tente novamente:\n\n");
					if (scanf (" %d%*c", &posCarta));
					else
						return -1;
					moverIteradorNumero (itPlayer1, posCarta);
					}
				//Caso o jogador tenha alguma jogada válida, o loop não se encerra até que ela seja jogada.
				
				
				flag = jogarCarta (itPlayer1, baralhoMesa, posCarta);
				if (flag == 1)
					comprarCartas (maoPlayer2, baralhoCompra, baralhoMesa, 2);
				else if (flag == 2)
					comprarCartas (maoPlayer2, baralhoCompra, baralhoMesa, 4);
				//Flag é uma variável usada nesse caso para saber o tipo da carta jogada, dessa forma, é possível fazer o oponente comprar cartas caso seja necessário.
					
				
				printf("\e[1;1H\e[2J");
				//Limpa a tela.
			} else {
				printf ("Você não tem nenhuma jogada válida, uma carta será comprada!!\n");
				printf ("Pressione ENTER para confirmar\n");
				getchar();
				printf("\e[1;1H\e[2J");
				comprarCartas (maoPlayer1, baralhoCompra, baralhoMesa, 1);
				//Caso o jogador não tenha nenhuma jogada válida, aguarda o jogador pressionar enter, isso é necessário para que não sejam compradas várias cartas em sequência sem ter um certo tempo para o jogador ver suas cartas.
			}
		} else {
			//Caso flag seja diferente de 0 nesse ponto, isso significa que a IA utilizou uma carta que impende a jogada do jogador.
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
			//Quando o jogador tiver 0 cartas, ele deve digitar CERO, sejam com letras em upper-case ou lower-case, caso contrário, o jogo não acabará e ele precisará comprar 2 cartas.
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
		
		//--------------------------------------------------------------------------
		
		//IA:
		if (!flag){
			moverIteradorNumero (itPlayer2, 1);
			for (int i = 0; i < quantidadeLista (maoPlayer2)+1; i++){
				flag = verificaJogada (elementoLista(itPlayer2), ultimoFila(baralhoMesa));
				//Caso a IA tenha uma carta válida, ela vai jogá-la. 
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
					printf ("O seu adversário não tinha nenhuma carta válida então comprou uma carta\n\n");
					comprarCartas (maoPlayer2, baralhoCompra, baralhoMesa, 1);
					i++;
				}
				proximoIterador (itPlayer2);
			}
		} else {
			//As mesmas regras se aplicam tanto para o jogador quanto para a IA, então ela pode ser impossibilitada de jogar.
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
			if (rand() % 2 == 1){
				printf ("VOCÊ PERDEU\n");
				acabou = 1;
			} else {
				printf ("SEU ADVERSÁRIO ESQUECEU DE FALAR CERO!!!!\n");
				comprarCartas (maoPlayer2, baralhoCompra, baralhoMesa, 2);
			}
		}
	}

//--------------------------------------------------------------------------

//Libera toda a memória que foi alocada para o jogo.
destroiPilha (baralhoCompra);
destroiFila (baralhoMesa);
destroiLista (maoPlayer1);
destroiLista (maoPlayer2);
destroiIterador (itPlayer1);
destroiIterador (itPlayer2);

return 0;}
