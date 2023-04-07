all:
	gcc -Wall -O2 -std=c99 src/master.c lib/stack.c lib/baralho.c lib/queue.c lib/list.c -o exe -L lib/ `pkg-config --cflags gtk+-3.0` `pkg-config --libs gtk+-3.0`
