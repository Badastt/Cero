#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../lib/aux.h"

int main (){
	carta *baralho = criaBaralho();
	shuffleCartas (baralho, NUM_CARTAS);
	
	
	
	stack pilhaComprar;
	initializeStack (&pilhaComprar);
	
	addStack (&pilhaComprar, baralho[0]);
	addStack (&pilhaComprar, baralho[1]);
	
	carta Elemento = getStack(&pilhaComprar);
	printf ("%d, %s, %s\n", Elemento.num, returnEnumCor(Elemento.cor), returnEnumTipo(Elemento.tipo));
	Elemento = getStack(&pilhaComprar);
	printf ("%d, %s, %s\n", Elemento.num, returnEnumCor(Elemento.cor), returnEnumTipo(Elemento.tipo));
	Elemento = getStack(&pilhaComprar);
	printf ("%d, %s, %s\n", Elemento.num, returnEnumCor(Elemento.cor), returnEnumTipo(Elemento.tipo));
	
	//for (int i = 0; i < NUM_CARTAS; i++)
	//	printf ("%d, %s, %s\n", baralho[i].num, returnEnumCor(baralho[i].cor), returnEnumTipo(baralho[i].tipo));

return 0;}