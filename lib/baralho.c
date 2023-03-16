#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "stack.h"
#include "baralho.h"
#include "types.h"

void criarBaralho(stack *s){
	for (int i = 0; i < 4; i++){
		for (int j = 19; j > 0; j--)
			pushStack (s, (T){j%10, i, cartaNormal});
		pushStack (s, (T){-1, i, cartaBloqueio});
		pushStack (s, (T){-1, i, cartaBloqueio});
		pushStack (s, (T){-1, i, cartaReverso});
		pushStack (s, (T){-1, i, cartaReverso});
		pushStack (s, (T){-1, i, cartaCompra2});
		pushStack (s, (T){-1, i, cartaCompra2});
		pushStack (s, (T){-1, preto, cartaMudaCor});
		pushStack (s, (T){-1, preto, cartaCompra4});
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

void shuffle (stack *s){
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
