#ifndef TYPES
#define TYPES

typedef enum tipoCarta {
cartaNormal, cartaBloqueio, cartaReverso, cartaCompra2, cartaMudaCor, cartaCompra4
} tipoCarta;

typedef enum corCarta{
	vermelho, amarelo, verde, azul, preto
} corCarta;

typedef struct {
	int num;
	corCarta cor;
	tipoCarta tipo;
} carta;

typedef carta T;

typedef struct {
	T *itens;
	int top;
} stack;

#endif
