#ifndef WIP
#define WIP

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "baralho.h"
#include "types.h"

stack *initializeStack(int);
void pushStack (stack *, T);
T popStack (stack *);
int empty (stack *);
int full (stack *);

#endif
