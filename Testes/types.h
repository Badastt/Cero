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
} pilha;

struct  nodeFila {
	T item;
	struct nodeFila *proximo;
};
	
typedef struct nodeFila nodeFila;

typedef struct {
	nodeFila *inicio;
	nodeFila *fim;
	unsigned quantidade;
} fila;

struct nodeLista {
	T item;
	struct nodeLista *proximo, *anterior;
};

typedef struct nodeLista nodeLista;

typedef struct {
	nodeLista *sentinela;
	unsigned quantidade;
} lista;

typedef struct {
	nodeLista *posicao;
	lista *lista;
	unsigned numero;
} iteradorLista;

#endif
