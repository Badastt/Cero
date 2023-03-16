all:
	gcc -Wall -Werror -O2 -std=c99 src/master.c lib/stack.c lib/baralho.c -o exe -L lib/
