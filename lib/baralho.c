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

void jogarCarta (iteradorLista *i, fila *f, int num){
	moverIteradorNumero (i, num);
	T carta = elementoLista(i);
	if (carta.tipo == cartaCompra4 || carta.tipo == cartaMudaCor){
		char cor;
		printf ("Escolha a cor da carta, digite:\n\033[1;41mR  -  Vermelho\033[1;0m\n\033[1;42mG  -  Verde\033[1;0m\n\033[1;44mB  -  Azul\033[1;0m\n\033[1;43mY  -  Amarelo\033[1;0m\n");
		scanf (" %c", &cor);
		if (cor == 'R' || cor == 'r')
			carta.cor = vermelho;
		if (cor == 'G' || cor == 'g')
			carta.cor = verde;
		if (cor == 'B' || cor == 'b')
			carta.cor = azul;
		if (cor == 'Y' || cor == 'y')
			carta.cor = amarelo;
	}
	retira (i);
	adicionarFila (f, carta);
}

void jogarCartaIA (iteradorLista *i, fila *f, int num){
	moverIteradorNumero (i, num);
	T carta = elementoLista(i);
	int flag = 0;
	if (carta.tipo == cartaCompra4 || carta.tipo == cartaMudaCor){
		moverIteradorNumero (i, 1);
		for (int j = 0; j < quantidadeLista (i->lista); j++, proximoIterador (i)){
			flag = verificaJogada (elementoLista(i), ultimoLista(f));
			if (flag)
				if (elementoLista(i).cor != preto)
					carta.cor = elementoLista(i).cor;
		}
		if (!flag)
			carta.cor = rand()%4;
		printf ("O seu adversário escolheu mudar a cor para %s\n", returnEnumCor(carta.cor)); 
	}
	moverIteradorNumero (i, num);
	retira (i);
	adicionarFila (f, carta);
}