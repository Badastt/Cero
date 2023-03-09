#include <stdlib.h>
#include <stdio.h>
#include "stack.h"
#include "baralho.h"

void initializeStack(stack *s){
	s->top = NULL;	
}

void addStack (stack *s, T data){
	nodeStack *n = (nodeStack*)malloc(sizeof(nodeStack));
	n->element = data;
	n->next = s->top;
	s->top = n;
}

void removeStack (stack *s){
	if (!empty(s)){
		nodeStack *n = s->top;
		s->top = n->next;
		free(n);
	}
}

T getStack (stack *s){
	if (!empty(s)){
		T element = s->top->element;
		removeStack (s);
		return element;
	} else
		return ERROR;
}

int empty (stack *s){
	return s->top == NULL;
}