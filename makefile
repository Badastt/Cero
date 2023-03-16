all: lib/WIP.h lib/baralho.h
	gcc -Wall -Werror -O2 -std=c99 src/master.c -o exe -L lib/ -I lib/
