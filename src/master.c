#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../lib/types.h"
#include "../lib/stack.h"
#include "../lib/baralho.h"

int main (){
	//carta *baralho = criaBaralho();
	//shuffleCartas (baralho, NUM_CARTAS);
	
	stack *baralho = initializeStack(NUM_CARTAS);
	criarBaralho(baralho);
	
	shuffle (baralho);
	
	//addStack (&pilhaComprar, baralho[0]);
	//addStack (&pilhaComprar, baralho[1]);
	
	//carta Elemento = getStack(baralho);
	//printf ("%d, %s, %s\n", Elemento.num, returnEnumCor(Elemento.cor), returnEnumTipo(Elemento.tipo));
	//Elemento = getStack(&pilhaComprar);
	//printf ("%d, %s, %s\n", Elemento.num, returnEnumCor(Elemento.cor), returnEnumTipo(Elemento.tipo));
	//Elemento = getStack(&pilhaComprar);
	//printf ("%d, %s, %s\n", Elemento.num, returnEnumCor(Elemento.cor), returnEnumTipo(Elemento.tipo));
	
	//for (int i = 0; i < NUM_CARTAS; i++)
	//	printf ("%d, %s, %s\n", baralho->itens[i].num, returnEnumCor(baralho->itens[i].cor), returnEnumTipo(baralho->itens[i].tipo));

return 0;}
