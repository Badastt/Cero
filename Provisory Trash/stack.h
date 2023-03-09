#include "baralho.h"
#ifndef STACK
#define STACK

typedef carta T;

struct nodeStack {
	carta element;
	struct nodeStack *next;
};

typedef struct nodeStack nodeStack;

typedef struct {
	nodeStack *top;
	unsigned quantidade;
} stack;

void initializeStack(stack *);
void addStack (stack *, T);
void removeStack (stack *);
int empty (stack *);
T getStack (stack *s);





#endif