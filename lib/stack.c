#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "stack.h"
#include "baralho.h"
#include "types.h"

pilha *inicializarPilha(int size){
	pilha *s = (pilha*)malloc(sizeof(pilha));
	T *t = (T*)malloc(sizeof(T)*size);
	
	s->itens = t; 
	s->top = -1;
	return s;
}

void adicionarPilha (pilha *s, T element){
	if (fullStack (s)){
		printf ("PILHA CHEIA");
		return;
	}
	s->top++;
	s->itens[s->top] = element;
}

T removerPilha (pilha *s){
	if (emptyStack (s)){
		printf ("PILHA VAZIA");
		return ERROR;
	}
	T element = s->itens[s->top];
	s->itens[s->top] = CLEAR;
	s->top--;
	return element;
}

int emptyStack (pilha *s){
	if (s->top == -1)
		return 1;
	return 0;
}

int fullStack (pilha *s){
	if (s->top == MAX-1)
		return 1;
	return 0;
}