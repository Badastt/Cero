#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "stack.h"
#include "baralho.h"
#include "types.h"

void criarBaralho(pilha *p){
	for (int i = 0; i < 4; i++){
		for (int j = 19; j > 0; j--)
			adicionarPilha (p, (T){j%10, i, cartaNormal});
		adicionarPilha (p, (T){-1, i, cartaBloqueio});
		adicionarPilha (p, (T){-1, i, cartaBloqueio});
		adicionarPilha (p, (T){-1, i, cartaReverso});
		adicionarPilha (p, (T){-1, i, cartaReverso});
		adicionarPilha (p, (T){-1, i, cartaCompra2});
		adicionarPilha (p, (T){-1, i, cartaCompra2});
		adicionarPilha (p, (T){-1, preto, cartaMudaCor});
		adicionarPilha (p, (T){-1, preto, cartaCompra4});
	}
}

char *returnEnumCor (corCarta cor){
	switch (cor){
		case vermelho: return "Vermelho";
		case amarelo: return "Amarelo";
		case verde: return "Verde";
		case azul: return "Azul";
		case preto: return "Preto";
		default: return "ERRO";
	}
}

char *returnEnumTipo (tipoCarta tipo){
	switch (tipo){
		case cartaNormal: return "Numero";
		case cartaBloqueio: return "Bloqueio";
		case cartaReverso: return "Reverso";
		case cartaCompra2: return "+2";
		case cartaMudaCor: return "MudaCor";
		case cartaCompra4: return "+4";
		default: return "ERRO";
	}
}

void shuffle (pilha *s){
	srand(time(NULL));
	int qtd = s->top+1;
	for (int i = 0, j = 0; i < qtd; i++){
		j = i + rand()%(qtd-i);
		swapCartas (s->itens, i, j);
	}
}

void swapCartas (T vetor[], int i, int j){
	T aux;
	aux = vetor[i];
	vetor[i] = vetor[j];
	vetor[j] = aux;
}

void comprarCartas (lista *l, pilha *p, fila *f, int qtd){
	if (qtd){
		for (int i = 0; i < qtd; i++){
			if (emptyStack (p))
				recolherCartas (p, f);
			adicionarFimLista (l, removerPilha (p));
		}
	} else
		adicionarFimLista (l, removerPilha (p));
}

void recolherCartas (pilha *p, fila *f){
	while (quantidadeFila (f) != 1){
		T carta = removeQueue(f);
		if (carta.tipo == cartaCompra4 || carta.tipo == cartaMudaCor)
			carta.cor = preto;
		adicionarPilha (p, carta);
	}
	shuffle (p);
}

int verificaJogada (T cartaJogada, T cartaTopo){
    if (cartaJogada.cor == cartaTopo.cor)
		return 1;
	if (cartaJogada.num == cartaTopo.num && cartaJogada.tipo == cartaNormal)
		return 1;
	if (cartaJogada.tipo == cartaTopo.tipo && cartaJogada.tipo != cartaNormal)
		return 1;
	if (cartaJogada.tipo == cartaMudaCor || cartaJogada.tipo == cartaCompra4)
		return 1;
	return 0;
}

void printCarta (T carta, int num){
	if (num){	
		switch (carta.cor){
		case vermelho:
		printf ("%d - \033[1;41m%s   ",num, returnEnumCor(carta.cor));
		break;
		case verde:
		printf ("%d - \033[1;42m%s      ",num, returnEnumCor(carta.cor));
		break;
		case azul:
		printf ("%d - \033[1;44m%s       ",num, returnEnumCor(carta.cor));
		break;
		case amarelo:
		printf ("%d - \033[1;43m%s    ",num, returnEnumCor(carta.cor));
		break;
		case preto:
		printf ("%d - \033[1;45m%s      ",num, returnEnumCor(carta.cor));
		break;
		}
		if(carta.tipo == cartaNormal)
			printf("%d\033[1;0m\n", carta.num);
		else
			printf("%s\033[1;0m\n",returnEnumTipo(carta.tipo));
	} else {
		switch (carta.cor){
		case vermelho:
		printf ("    \033[1;41m%s   ", returnEnumCor(carta.cor));
		break;
		case verde:
		printf ("    \033[1;42m%s      ", returnEnumCor(carta.cor));
		break;
		case azul:
		printf ("    \033[1;44m%s       ", returnEnumCor(carta.cor));
		break;
		case amarelo:
		printf ("    \033[1;43m%s    ", returnEnumCor(carta.cor));
		break;
		case preto:
		printf ("    \033[1;45m%s      ", returnEnumCor(carta.cor));
		break;
		}
		if(carta.tipo == cartaNormal)
			printf("%d\033[1;0m\n", carta.num);
		else
			printf("%s\033[1;0m\n",returnEnumTipo(carta.tipo));
	}
}

void primeiraCarta (pilha *p, fila *f){
	T carta = removerPilha (p);
	while (carta.cor == preto){
		adicionarPilha (p, carta);
		shuffle (p);
		carta = removerPilha (p);
	}
	adicionarFila (f, carta);
}

int jogarCarta (iteradorLista *i, fila *f, int num){
	moverIteradorNumero (i, num);
	T carta = elementoLista(i);
	int tipo = 0;
	if (carta.tipo == cartaCompra4 || carta.tipo == cartaMudaCor){
		char cor;
		printf ("Escolha a cor da carta, digite:\n\033[1;41mR  -  Vermelho\033[1;0m\n\033[1;42mG  -  Verde\033[1;0m\n\033[1;44mB  -  Azul\033[1;0m\n\033[1;43mY  -  Amarelo\033[1;0m\n");
		if (scanf (" %c%*c", &cor));
		else
			return -1;
		if (cor == 'R' || cor == 'r')
			carta.cor = vermelho;
		if (cor == 'G' || cor == 'g')
			carta.cor = verde;
		if (cor == 'B' || cor == 'b')
			carta.cor = azul;
		if (cor == 'Y' || cor == 'y')
			carta.cor = amarelo;
	}
	if (carta.tipo == cartaCompra2)
		tipo = 1;
	else if (carta.tipo == cartaCompra4)
		tipo = 2;
	else if (carta.tipo == cartaBloqueio)
		tipo = 3;
	else if (carta.tipo == cartaReverso)
		tipo = 4;
	retira (i);
	adicionarFila (f, carta);
	return tipo;
}

int jogarCartaIA (iteradorLista *i, fila *f, int num){
	moverIteradorNumero (i, num);
	T carta = elementoLista(i);
	int flag = 0;
	int tipo = 0;
	if (carta.tipo == cartaCompra4 || carta.tipo == cartaMudaCor){
		moverIteradorNumero (i, 1);
		for (int j = 0; j < quantidadeLista (i->lista); j++, proximoIterador (i)){
			T verificaCarta = elementoLista(i);
			if (verificaCarta.cor != preto){
				flag = 1;
				carta.cor = verificaCarta.cor;
				j = quantidadeLista (i->lista);
			}
		}
		
		if (!flag)
			carta.cor = rand()%4;
		printf ("O seu adversário escolheu mudar a cor para %s!!\n", returnEnumCor(carta.cor));
	}
	moverIteradorNumero (i, num);
	if (carta.tipo == cartaCompra2)
		tipo = 1;
	else if (carta.tipo == cartaCompra4)
		tipo = 2;
	else if (carta.tipo == cartaBloqueio)
		tipo = 3;
	else if (carta.tipo == cartaReverso)
		tipo = 4;
	retira (i);
	adicionarFila (f, carta);
	return tipo;
}

void printCartaMesa (T carta){
	switch (carta.cor){
		case vermelho:
			if (carta.tipo == cartaNormal)
				printf ("\033[1;41m     \033[1;0\n\033[1;41m     \033[1;0\n\033[1;41m  %d  \033[1;0\n\033[1;41m     \033[1;0\n\033[1;41m     \033[1;0\n", carta.num);
			if (carta.tipo == cartaCompra2)
				printf ("\033[1;41m     \033[1;0\n\033[1;41m     \033[1;0\n\033[1;41m + 2 \033[1;0\n\033[1;41m     \033[1;0\n\033[1;41m     \033[1;0\n");
			if (carta.tipo == cartaCompra4)
				printf ("\033[1;41m     \033[1;0\n\033[1;41m     \033[1;0\n\033[1;41m + 4 \033[1;0\n\033[1;41m     \033[1;0\n\033[1;41m     \033[1;0\n");
			if (carta.tipo == cartaBloqueio)
				printf ("\033[1;41m     \033[1;0\n\033[1;41m     \033[1;0\n\033[1;41m  $  \033[1;0\n\033[1;41m     \033[1;0\n\033[1;41m     \033[1;0\n");
			if (carta.tipo == cartaReverso)
				printf ("\033[1;41m     \033[1;0\n\033[1;41m     \033[1;0\n\033[1;41m <-> \033[1;0\n\033[1;41m     \033[1;0\n\033[1;41m     \033[1;0\n");
			if (carta.tipo == cartaMudaCor)
				printf ("\033[1;41m     \033[1;0\n\033[1;41m     \033[1;0\n\033[1;41m     \033[1;0\n\033[1;41m     \033[1;0\n\033[1;41m     \033[1;0\n");
		break;
		case verde:
			if (carta.tipo == cartaNormal)
				printf ("\033[1;42m     \033[1;0\n\033[1;42m     \033[1;0\n\033[1;42m  %d  \033[1;0\n\033[1;42m     \033[1;0\n\033[1;42m     \033[1;0\n", carta.num);
			if (carta.tipo == cartaCompra2)
				printf ("\033[1;42m     \033[1;0\n\033[1;42m     \033[1;0\n\033[1;42m + 2 \033[1;0\n\033[1;42m     \033[1;0\n\033[1;42m     \033[1;0\n");
			if (carta.tipo == cartaCompra4)
				printf ("\033[1;42m     \033[1;0\n\033[1;42m     \033[1;0\n\033[1;42m + 4 \033[1;0\n\033[1;42m     \033[1;0\n\033[1;42m     \033[1;0\n");
			if (carta.tipo == cartaBloqueio)
				printf ("\033[1;42m     \033[1;0\n\033[1;42m     \033[1;0\n\033[1;42m  X  \033[1;0\n\033[1;42m     \033[1;0\n\033[1;42m     \033[1;0\n");
			if (carta.tipo == cartaReverso)
				printf ("\033[1;42m     \033[1;0\n\033[1;42m     \033[1;0\n\033[1;42m <-> \033[1;0\n\033[1;42m     \033[1;0\n\033[1;42m     \033[1;0\n");
			if (carta.tipo == cartaMudaCor)
				printf ("\033[1;42m     \033[1;0\n\033[1;42m     \033[1;0\n\033[1;42m     \033[1;0\n\033[1;42m     \033[1;0\n\033[1;42m     \033[1;0\n");
		break;
		case azul:
			if (carta.tipo == cartaNormal)
				printf ("\033[1;44m     \033[1;0\n\033[1;44m     \033[1;0\n\033[1;44m  %d  \033[1;0\n\033[1;44m     \033[1;0\n\033[1;44m     \033[1;0\n", carta.num);
			if (carta.tipo == cartaCompra2)
				printf ("\033[1;44m     \033[1;0\n\033[1;44m     \033[1;0\n\033[1;44m + 2 \033[1;0\n\033[1;44m     \033[1;0\n\033[1;44m     \033[1;0\n");
			if (carta.tipo == cartaCompra4)
				printf ("\033[1;44m     \033[1;0\n\033[1;44m     \033[1;0\n\033[1;44m + 4 \033[1;0\n\033[1;44m     \033[1;0\n\033[1;44m     \033[1;0\n");
			if (carta.tipo == cartaBloqueio)
				printf ("\033[1;44m     \033[1;0\n\033[1;44m     \033[1;0\n\033[1;44m  X  \033[1;0\n\033[1;44m     \033[1;0\n\033[1;44m     \033[1;0\n");
			if (carta.tipo == cartaReverso)
				printf ("\033[1;44m     \033[1;0\n\033[1;44m     \033[1;0\n\033[1;44m <-> \033[1;0\n\033[1;44m     \033[1;0\n\033[1;44m     \033[1;0\n");
			if (carta.tipo == cartaMudaCor)
				printf ("\033[1;44m     \033[1;0\n\033[1;44m     \033[1;0\n\033[1;44m     \033[1;0\n\033[1;44m     \033[1;0\n\033[1;44m     \033[1;0\n");
		break;
		case amarelo:
			if (carta.tipo == cartaNormal)
				printf ("\033[1;43m     \033[1;0\n\033[1;43m     \033[1;0\n\033[1;43m  %d  \033[1;0\n\033[1;43m     \033[1;0\n\033[1;43m     \033[1;0\n", carta.num);
			if (carta.tipo == cartaCompra2)
				printf ("\033[1;43m     \033[1;0\n\033[1;43m     \033[1;0\n\033[1;43m + 2 \033[1;0\n\033[1;43m     \033[1;0\n\033[1;43m     \033[1;0\n");
			if (carta.tipo == cartaCompra4)
				printf ("\033[1;43m     \033[1;0\n\033[1;43m     \033[1;0\n\033[1;43m + 4 \033[1;0\n\033[1;43m     \033[1;0\n\033[1;43m     \033[1;0\n");
			if (carta.tipo == cartaBloqueio)
				printf ("\033[1;43m     \033[1;0\n\033[1;43m     \033[1;0\n\033[1;43m  X  \033[1;0\n\033[1;43m     \033[1;0\n\033[1;43m     \033[1;0\n");
			if (carta.tipo == cartaReverso)
				printf ("\033[1;43m     \033[1;0\n\033[1;43m     \033[1;0\n\033[1;43m <-> \033[1;0\n\033[1;43m     \033[1;0\n\033[1;43m     \033[1;0\n");
			if (carta.tipo == cartaMudaCor)
				printf ("\033[1;43m     \033[1;0\n\033[1;43m     \033[1;0\n\033[1;43m     \033[1;0\n\033[1;43m     \033[1;0\n\033[1;43m     \033[1;0\n");
		break;
		default:
		break;
	}
}

char *caminhoCarta (T carta){
	switch (carta.cor){
		case vermelho:
		switch (carta.tipo){
			case cartaNormal:
				switch (carta.num){
					case 0: return "data/0_VERMELHO.png";
					case 1: return "data/1_VERMELHO.png";
					case 2: return "data/2_VERMELHO.png";
					case 3: return "data/3_VERMELHO.png";
					case 4: return "data/4_VERMELHO.png";
					case 5: return "data/5_VERMELHO.png";
					case 6: return "data/6_VERMELHO.png";
					case 7: return "data/7_VERMELHO.png";
					case 8: return "data/8_VERMELHO.png";
					case 9: return "data/9_VERMELHO.png";
				}
			case cartaBloqueio: return "data/BLOQUEIO_VERMELHO.png";
			case cartaReverso: return "data/REVERSO_VERMELHO.png";
			case cartaCompra2: return "data/+2_VERMELHO.png";
			case cartaMudaCor: return "data/MUDACOR_VERMELHO.png";
			case cartaCompra4: return "data/+4_VERMELHO.png";
			default: return "ERRO";
		}
		case amarelo:
		switch (carta.tipo){
			case cartaNormal:
				switch (carta.num){
					case 0: return "data/0_AMARELO.png";
					case 1: return "data/1_AMARELO.png";
					case 2: return "data/2_AMARELO.png";
					case 3: return "data/3_AMARELO.png";
					case 4: return "data/4_AMARELO.png";
					case 5: return "data/5_AMARELO.png";
					case 6: return "data/6_AMARELO.png";
					case 7: return "data/7_AMARELO.png";
					case 8: return "data/8_AMARELO.png";
					case 9: return "data/9_AMARELO.png";
				}
			case cartaBloqueio: return "data/BLOQUEIO_AMARELO.png";
			case cartaReverso: return "data/REVERSO_AMARELO.png";
			case cartaCompra2: return "data/+2_AMARELO.png";
			case cartaMudaCor: return "data/MUDACOR_AMARELO.png";
			case cartaCompra4: return "data/+4_AMARELO.png";
			default: return "ERRO";
		}
		case verde:
		switch (carta.tipo){
			case cartaNormal:
				switch (carta.num){
					case 0: return "data/0_VERDE.png";
					case 1: return "data/1_VERDE.png";
					case 2: return "data/2_VERDE.png";
					case 3: return "data/3_VERDE.png";
					case 4: return "data/4_VERDE.png";
					case 5: return "data/5_VERDE.png";
					case 6: return "data/6_VERDE.png";
					case 7: return "data/7_VERDE.png";
					case 8: return "data/8_VERDE.png";
					case 9: return "data/9_VERDE.png";
				}
			case cartaBloqueio: return "data/BLOQUEIO_VERDE.png";
			case cartaReverso: return "data/REVERSO_VERDE.png";
			case cartaCompra2: return "data/+2_VERDE.png";
			case cartaMudaCor: return "data/MUDACOR_VERDE.png";
			case cartaCompra4: return "data/+4_VERDE.png";
			default: return "ERRO";
		}
		case azul:
		switch (carta.tipo){
			case cartaNormal:
				switch (carta.num){
					case 0: return "data/0_AZUL.png";
					case 1: return "data/1_AZUL.png";
					case 2: return "data/2_AZUL.png";
					case 3: return "data/3_AZUL.png";
					case 4: return "data/4_AZUL.png";
					case 5: return "data/5_AZUL.png";
					case 6: return "data/6_AZUL.png";
					case 7: return "data/7_AZUL.png";
					case 8: return "data/8_AZUL.png";
					case 9: return "data/9_AZUL.png";
				}
			case cartaBloqueio: return "data/BLOQUEIO_AZUL.png";
			case cartaReverso: return "data/REVERSO_AZUL.png";
			case cartaCompra2: return "data/+2_AZUL.png";
			case cartaMudaCor: return "data/MUDACOR_AZUL.png";
			case cartaCompra4: return "data/+4_AZUL.png";
			default: return "ERRO";
		}
		case preto:
		switch (carta.tipo){
			case cartaMudaCor: return "data/MUDACOR.png";
			case cartaCompra4: return "data/+4.png";
			default: return "ERRO";
		}
		default: return "ERRO";
	}
}

botao *inicializaBotao (iteradorLista *iterador, fila *fila){
	botao *b = (botao*)malloc(sizeof(botao));
	b->iterador = iterador;
	b->fila = fila;
	return b;
}