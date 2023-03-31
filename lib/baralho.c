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
			adicionarInicioLista (l, removerPilha (p));
		}
	} else
		adicionarInicioLista (l, removerPilha (p));
}

void recolherCartas (pilha *p, fila *f){
	while (quantidadeFila (f) != 1)
		adicionarPilha (p, removeQueue(f));
	shuffle (p);
}

int verificaJogada (T cartaJogada, T cartaTopo){
    if (cartaJogada.cor == cartaTopo.cor)
		return 1;
	if (cartaJogada.num == cartaTopo.num)
		return 1;
	if (cartaJogada.tipo == cartaTopo.tipo && cartaJogada.tipo != cartaNormal)
		return 1;
	if (cartaJogada.tipo == cartaMudaCor || cartaJogada.tipo == cartaCompra4)
		return 1;
	return 0;
}

void printCarta (T carta){
	printf ("%d, %s, %s\n", carta.num, returnEnumCor(carta.cor), returnEnumTipo(carta.tipo));
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