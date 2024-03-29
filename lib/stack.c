#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "baralho.h"
#include "types.h"

//A pilha é criada utilizando memória sequência, isso permite abordar ela como um vetor
pilha *inicializarPilha(int size){
	pilha *s = (pilha*)malloc(sizeof(pilha));
	T *t = (T*)malloc(sizeof(T)*size);
	
	s->itens = t; 
	s->top = -1;
	return s;
}


void adicionarPilha (pilha *s, T element){
	if (pilhaCheia (s)){
		return;
	}
	s->top++;
	s->itens[s->top] = element;
}


T removerPilha (pilha *s){
	if (pilhaVazia (s)){
		return ERRO;
	}
	T element = s->itens[s->top];
	s->itens[s->top] = CLEAR;
	s->top--;
	return element;
}

//Checa se a pilha está vazia.
int pilhaVazia (pilha *s){
	if (s->top == -1)
		return 1;
	return 0;
}

//Checa se a pilha está cheia.
int pilhaCheia (pilha *s){
	if (s->top == MAXLOCAL-1)
		return 1;
	return 0;
}

//Destroi a pilha.
void destroiPilha (pilha *p){
	free (p->itens);
	free (p);
}