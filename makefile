all:
	gcc -Wall -O2 -std=c99 src/master.c lib/stack.c lib/baralho.c lib/queue.c lib/list.c -o exe -L lib/
