all: aux.o
	gcc -Wall -Werror -O2 -std=c99 src/master.c aux.o -o exe
	rm *.o

aux.o: lib/aux.h
	gcc -Wall -Werror -O2 -std=c99 -c lib/aux.c

