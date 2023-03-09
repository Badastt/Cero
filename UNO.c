#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_CARTAS 108

typedef enum tipoCarta {
	cartaNormal, cartaBloqueio, cartaReverso, cartaCompra2, cartaMudaCor, cartaCompra4
} tipoCarta;

typedef enum corCarta{
	vermelho, amarelo, verde, azul, preto
} corCarta;

typedef struct {
	int num;
	corCarta cor;
	tipoCarta tipo;
} carta;

carta *criaBaralho();
char *returnEnumCor (corCarta cor);
char *returnEnumTipo (tipoCarta tipo);
void swapCartas (carta vetor[], int i, int j);
void shuffleCartas (carta vetor[], int qtd);

int main (){
	carta *baralho = criaBaralho();
	
	shuffleCartas (baralho, NUM_CARTAS);
	
	for (int i = 0; i < NUM_CARTAS; i++)
		printf ("%d, %s, %s\n", baralho[i].num, returnEnumCor(baralho[i].cor), returnEnumTipo(baralho[i].tipo));



return 0;}

carta *criaBaralho(){
	carta *v = (carta*)malloc(sizeof(carta)*NUM_CARTAS);
	
	int i = 0;
	
	for (int j = 0; j < 4; j++){
		for (int k = 19; k > 0; k--)
			v[i++] = (carta){k%10, j, cartaNormal};
		v[i++] = (carta){-1, j, cartaBloqueio};
		v[i++] = (carta){-1, j, cartaBloqueio};
		v[i++] = (carta){-1, j, cartaReverso};
		v[i++] = (carta){-1, j, cartaReverso};
		v[i++] = (carta){-1, j, cartaCompra2};
		v[i++] = (carta){-1, j, cartaCompra2};
		v[i++] = (carta){-1, preto, cartaMudaCor};
		v[i++] = (carta){-1, preto, cartaCompra4};
	}
	return (v);
}

void swapCartas (carta vetor[], int i, int j){
	carta aux;
	aux = vetor[i];
	vetor[i] = vetor[j];
	vetor[j] = aux;
}

void shuffleCartas (carta vetor[], int qtd){
	srand(time(NULL));
	for (int i = 0, j = 0; i < qtd; i++){
		j = i + rand()%(qtd-i);
		swapCartas (vetor, i, j);
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
