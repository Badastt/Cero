#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "stack.h"
#include "baralho.h"
#include "types.h"

stack *initializeStack(int size){
	stack *s = (stack*)malloc(sizeof(stack));
	T *t = (T*)malloc(sizeof(T)*size);
	
	s->itens = t; 
	s->top = -1;
	return s;
}

void pushStack (stack *s, T element){
	if (full (s)){
		printf ("PILHA CHEIA");
		return;
	}
	s->top++;
	s->itens[s->top] = element;
}

T popStack (stack *s){
	if (empty (s)){
		printf ("PILHA VAZIA");
		return ERROR;
	}
	T element = s->itens[s->top];
	s->itens[s->top] = CLEAR;
	s->top--;
	return element;
}

int empty (stack *s){
	if (s->top == -1)
		return 1;
	return 0;
}

int full (stack *s){
	if (s->top == MAX-1)
		return 1;
	return 0;
}
