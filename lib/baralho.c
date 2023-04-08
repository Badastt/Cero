#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "stack.h"
#include "baralho.h"
#include "types.h"

//Esse arquivo possui as principais funções necessárias para que o CERO funcione corretamente;

void criarBaralho(pilha *p){
	for (int i = 0; i < 4; i++){
		for (int j = 19; j > 0; j--)
			adicionarPilha (p, (T){j%10, i, cartaNormal});
		adicionarPilha (p, (T){-1, i, cartaBloqueio});
		adicionarPilha (p, (T){-1, i, cartaBloqueio});
		adicionarPilha (p, (T){-1, i, cartaReverso});
		adicionarPilha (p, (T){-1, i, cartaReverso});
		adicionarPilha (p, (T){-1, i, cartaCompra2});
		adicionarPilha (p, (T){-1, i, cartaCompra2});
		adicionarPilha (p, (T){-1, preto, cartaMudaCor});
		adicionarPilha (p, (T){-1, preto, cartaCompra4});
	}
	//Essa função cria todas as cartas e as coloca na pilha fornecida.
}

char *returnEnumCor (corCarta cor){
	switch (cor){
		case vermelho: return "Vermelho";
		case amarelo: return "Amarelo";
		case verde: return "Verde";
		case azul: return "Azul";
		case preto: return "Preto";
		default: return "ERRO";
	}
	//Essa função serve para poder printar a cor das cartas de maneira mais fácil utilizando um Enum.
}

char *returnEnumTipo (tipoCarta tipo){
	switch (tipo){
		case cartaNormal: return "Numero";
		case cartaBloqueio: return "Bloqueio";
		case cartaReverso: return "Reverso";
		case cartaCompra2: return "+2";
		case cartaMudaCor: return "MudaCor";
		case cartaCompra4: return "+4";
		default: return "ERRO";
	}
	//Essa função serve para poder printar o tipo das cartas de maneira mais fácil utilizando um Enum.
}

void shuffle (pilha *s){
	srand(time(NULL));
	int qtd = s->top+1;
	for (int i = 0, j = 0; i < qtd; i++){
		j = i + rand()%(qtd-i);
		swapCartas (s->itens, i, j);
	}
	//Essa função é utilizada para embaralhar o baralho. Infelizmente não há forma eficiente de respeitar o TAD e fazer essa função funcionar corretamente, portanto, essa foi a única violação do TAD.
}

void swapCartas (T vetor[], int i, int j){
	T aux;
	aux = vetor[i];
	vetor[i] = vetor[j];
	vetor[j] = aux;
}

void comprarCartas (lista *l, pilha *p, fila *f, int qtd){
	if (qtd){
		for (int i = 0; i < qtd; i++){
			if (pilhaVazia (p))
				recolherCartas (p, f);
			adicionarFimLista (l, removerPilha (p));
			//Caso a pilha do baralho esteja vazia, ele vai recolher todas as cartas da fila que contém as jogadas, menos o topo, e depois vai voltar à sua funcionalidade normal.
		}
	} else
		adicionarFimLista (l, removerPilha (p));
}

void recolherCartas (pilha *p, fila *f){
	while (quantidadeFila (f) != 1){
		T carta = removeFila(f);
		if (carta.tipo == cartaCompra4 || carta.tipo == cartaMudaCor)
			carta.cor = preto;
		adicionarPilha (p, carta);
	}
	shuffle (p);
	//Recolhe as cartas da fila de jogadas e as embaralha.
}

int verificaJogada (T cartaJogada, T cartaTopo){
    if (cartaJogada.cor == cartaTopo.cor)
		return 1;
	if (cartaJogada.num == cartaTopo.num && cartaJogada.tipo == cartaNormal)
		return 1;
	if (cartaJogada.tipo == cartaTopo.tipo && cartaJogada.tipo != cartaNormal)
		return 1;
	if (cartaJogada.tipo == cartaMudaCor || cartaJogada.tipo == cartaCompra4)
		return 1;
	return 0;
}


void primeiraCarta (pilha *p, fila *f){
	T carta = removerPilha (p);
	while (carta.cor == preto){
		adicionarPilha (p, carta);
		shuffle (p);
		carta = removerPilha (p);
	}
	adicionarFila (f, carta);
}
//A primeira carta é colocada na mesa caso seja uma carta com cor, caso a primeira carta seja uma carta de troca de cor. O baralho é embaralhado novamente e uma nova carta é escolhida do topo até que se encontre uma carta normal.

int jogarCartaIA (iteradorLista *i, fila *f, int num){
	moverIteradorNumero (i, num);
	T carta = elementoLista(i);
	int flag = 0;
	int tipo = 0;
	if (carta.tipo == cartaCompra4 || carta.tipo == cartaMudaCor){
		moverIteradorNumero (i, 1);
		for (int j = 0; j < quantidadeLista (i->lista); j++, proximoIterador (i)){
			T verificaCarta = elementoLista(i);
			if (verificaCarta.cor != preto){
				flag = 1;
				carta.cor = verificaCarta.cor;
				j = quantidadeLista (i->lista);
			}
		}
		
		if (!flag)
			carta.cor = rand()%4;
		printf ("O seu adversario escolheu mudar a cor para %s!!\n", returnEnumCor(carta.cor));
	}
	moverIteradorNumero (i, num);
	if (carta.tipo == cartaCompra2)
		tipo = 1;
	else if (carta.tipo == cartaCompra4)
		tipo = 2;
	else if (carta.tipo == cartaBloqueio)
		tipo = 3;
	else if (carta.tipo == cartaReverso)
		tipo = 4;
	retira (i);
	adicionarFila (f, carta);
	return tipo;
}


//Caso seja definido que o programa esteja sendo utilizado em máquina linux as seguintes especificações para impressao são escolhidas:
#ifdef __unix__
//É utilizado o padrão de mudança de cor da impressão do linux "\codigo da cor do texto ou cor do fundo do texto[codigo da cor desejada", tal cor é recebida através da função qual informa a cor da carta.

void printCarta (T carta, int num){
	if (num){	
		switch (carta.cor){
		case vermelho:
		printf ("%d - \033[1;41m%s   ",num, returnEnumCor(carta.cor));
		break;
		case verde:
		printf ("%d - \033[1;42m%s      ",num, returnEnumCor(carta.cor));
		break;
		case azul:
		printf ("%d - \033[1;44m%s       ",num, returnEnumCor(carta.cor));
		break;
		case amarelo:
		printf ("%d - \033[1;43m%s    ",num, returnEnumCor(carta.cor));
		break;
		case preto:
		printf ("%d - \033[1;45m%s      ",num, returnEnumCor(carta.cor));
		break;
		}
		if(carta.tipo == cartaNormal)
			printf("%d\033[1;0m\n", carta.num);
		else
			printf("%s\033[1;0m\n",returnEnumTipo(carta.tipo));
	} else {
		switch (carta.cor){
		case vermelho:
		printf ("    \033[1;41m%s   ", returnEnumCor(carta.cor));
		break;
		case verde:
		printf ("    \033[1;42m%s      ", returnEnumCor(carta.cor));
		break;
		case azul:
		printf ("    \033[1;44m%s       ", returnEnumCor(carta.cor));
		break;
		case amarelo:
		printf ("    \033[1;43m%s    ", returnEnumCor(carta.cor));
		break;
		case preto:
		printf ("    \033[1;45m%s      ", returnEnumCor(carta.cor));
		break;
		}
		if(carta.tipo == cartaNormal)
			printf("%d\033[1;0m\n", carta.num);
		else
			printf("%s\033[1;0m\n", returnEnumTipo(carta.tipo));
	}	
}

//A função joga carta pede ao usuário um input de uma carta válida para ser jogada e retorna o tipo da carta que foi jogada como um inteiro além de atualizar a carta do topo da pilha para	a carta jogada.
int jogarCarta (iteradorLista *i, fila *f, int num){
	moverIteradorNumero (i, num);
	T carta = elementoLista(i);
	int tipo = 0;
	if (carta.tipo == cartaCompra4 || carta.tipo == cartaMudaCor){
		char cor;
		printf ("Escolha a cor da carta, digite:\n\033[1;41mR  -  Vermelho\033[1;0m\n\033[1;42mG  -  Verde\033[1;0m\n\033[1;44mB  -  Azul\033[1;0m\n\033[1;43mY  -  Amarelo\033[1;0m\n");
		if (scanf (" %c%*c", &cor));
		else
			return -1;
		if (cor == 'R' || cor == 'r')
			carta.cor = vermelho;
		else if (cor == 'G' || cor == 'g')
			carta.cor = verde;
		else if (cor == 'B' || cor == 'b')
			carta.cor = azul;
		else if (cor == 'Y' || cor == 'y')
			carta.cor = amarelo;
		else
			carta.cor = rand() % 4;
	}
	if (carta.tipo == cartaCompra2)
		tipo = 1;
	else if (carta.tipo == cartaCompra4)
		tipo = 2;
	else if (carta.tipo == cartaBloqueio)
		tipo = 3;
	else if (carta.tipo == cartaReverso)
		tipo = 4;
	retira (i);
	adicionarFila (f, carta);
	return tipo;
}

//A carta que está no momento na mesa é imprimida para o jogador. É utilizado a mudança de cor do fundo em linux para imprimir um texto que forma uma carta.
void printCartaMesa (T carta){
	switch (carta.cor){
		case vermelho:
			if (carta.tipo == cartaNormal)
				printf ("\033[1;41m     \033[1;0\n\033[1;41m     \033[1;0\n\033[1;41m  %d  \033[1;0\n\033[1;41m     \033[1;0\n\033[1;41m     \033[1;0\n", carta.num);
			if (carta.tipo == cartaCompra2)
				printf ("\033[1;41m     \033[1;0\n\033[1;41m     \033[1;0\n\033[1;41m + 2 \033[1;0\n\033[1;41m     \033[1;0\n\033[1;41m     \033[1;0\n");
			if (carta.tipo == cartaCompra4)
				printf ("\033[1;41m     \033[1;0\n\033[1;41m     \033[1;0\n\033[1;41m + 4 \033[1;0\n\033[1;41m     \033[1;0\n\033[1;41m     \033[1;0\n");
			if (carta.tipo == cartaBloqueio)
				printf ("\033[1;41m     \033[1;0\n\033[1;41m     \033[1;0\n\033[1;41m  $  \033[1;0\n\033[1;41m     \033[1;0\n\033[1;41m     \033[1;0\n");
			if (carta.tipo == cartaReverso)
				printf ("\033[1;41m     \033[1;0\n\033[1;41m     \033[1;0\n\033[1;41m <-> \033[1;0\n\033[1;41m     \033[1;0\n\033[1;41m     \033[1;0\n");
			if (carta.tipo == cartaMudaCor)
				printf ("\033[1;41m     \033[1;0\n\033[1;41m     \033[1;0\n\033[1;41m     \033[1;0\n\033[1;41m     \033[1;0\n\033[1;41m     \033[1;0\n");
		break;
		case verde:
			if (carta.tipo == cartaNormal)
				printf ("\033[1;42m     \033[1;0\n\033[1;42m     \033[1;0\n\033[1;42m  %d  \033[1;0\n\033[1;42m     \033[1;0\n\033[1;42m     \033[1;0\n", carta.num);
			if (carta.tipo == cartaCompra2)
				printf ("\033[1;42m     \033[1;0\n\033[1;42m     \033[1;0\n\033[1;42m + 2 \033[1;0\n\033[1;42m     \033[1;0\n\033[1;42m     \033[1;0\n");
			if (carta.tipo == cartaCompra4)
				printf ("\033[1;42m     \033[1;0\n\033[1;42m     \033[1;0\n\033[1;42m + 4 \033[1;0\n\033[1;42m     \033[1;0\n\033[1;42m     \033[1;0\n");
			if (carta.tipo == cartaBloqueio)
				printf ("\033[1;42m     \033[1;0\n\033[1;42m     \033[1;0\n\033[1;42m  X  \033[1;0\n\033[1;42m     \033[1;0\n\033[1;42m     \033[1;0\n");
			if (carta.tipo == cartaReverso)
				printf ("\033[1;42m     \033[1;0\n\033[1;42m     \033[1;0\n\033[1;42m <-> \033[1;0\n\033[1;42m     \033[1;0\n\033[1;42m     \033[1;0\n");
			if (carta.tipo == cartaMudaCor)
				printf ("\033[1;42m     \033[1;0\n\033[1;42m     \033[1;0\n\033[1;42m     \033[1;0\n\033[1;42m     \033[1;0\n\033[1;42m     \033[1;0\n");
		break;
		case azul:
			if (carta.tipo == cartaNormal)
				printf ("\033[1;44m     \033[1;0\n\033[1;44m     \033[1;0\n\033[1;44m  %d  \033[1;0\n\033[1;44m     \033[1;0\n\033[1;44m     \033[1;0\n", carta.num);
			if (carta.tipo == cartaCompra2)
				printf ("\033[1;44m     \033[1;0\n\033[1;44m     \033[1;0\n\033[1;44m + 2 \033[1;0\n\033[1;44m     \033[1;0\n\033[1;44m     \033[1;0\n");
			if (carta.tipo == cartaCompra4)
				printf ("\033[1;44m     \033[1;0\n\033[1;44m     \033[1;0\n\033[1;44m + 4 \033[1;0\n\033[1;44m     \033[1;0\n\033[1;44m     \033[1;0\n");
			if (carta.tipo == cartaBloqueio)
				printf ("\033[1;44m     \033[1;0\n\033[1;44m     \033[1;0\n\033[1;44m  X  \033[1;0\n\033[1;44m     \033[1;0\n\033[1;44m     \033[1;0\n");
			if (carta.tipo == cartaReverso)
				printf ("\033[1;44m     \033[1;0\n\033[1;44m     \033[1;0\n\033[1;44m <-> \033[1;0\n\033[1;44m     \033[1;0\n\033[1;44m     \033[1;0\n");
			if (carta.tipo == cartaMudaCor)
				printf ("\033[1;44m     \033[1;0\n\033[1;44m     \033[1;0\n\033[1;44m     \033[1;0\n\033[1;44m     \033[1;0\n\033[1;44m     \033[1;0\n");
		break;
		case amarelo:
			if (carta.tipo == cartaNormal)
				printf ("\033[1;43m     \033[1;0\n\033[1;43m     \033[1;0\n\033[1;43m  %d  \033[1;0\n\033[1;43m     \033[1;0\n\033[1;43m     \033[1;0\n", carta.num);
			if (carta.tipo == cartaCompra2)
				printf ("\033[1;43m     \033[1;0\n\033[1;43m     \033[1;0\n\033[1;43m + 2 \033[1;0\n\033[1;43m     \033[1;0\n\033[1;43m     \033[1;0\n");
			if (carta.tipo == cartaCompra4)
				printf ("\033[1;43m     \033[1;0\n\033[1;43m     \033[1;0\n\033[1;43m + 4 \033[1;0\n\033[1;43m     \033[1;0\n\033[1;43m     \033[1;0\n");
			if (carta.tipo == cartaBloqueio)
				printf ("\033[1;43m     \033[1;0\n\033[1;43m     \033[1;0\n\033[1;43m  X  \033[1;0\n\033[1;43m     \033[1;0\n\033[1;43m     \033[1;0\n");
			if (carta.tipo == cartaReverso)
				printf ("\033[1;43m     \033[1;0\n\033[1;43m     \033[1;0\n\033[1;43m <-> \033[1;0\n\033[1;43m     \033[1;0\n\033[1;43m     \033[1;0\n");
			if (carta.tipo == cartaMudaCor)
				printf ("\033[1;43m     \033[1;0\n\033[1;43m     \033[1;0\n\033[1;43m     \033[1;0\n\033[1;43m     \033[1;0\n\033[1;43m     \033[1;0\n");
		break;
		default:
		break;
	}
}

void limpaTela() {
	printf("\e[1;1H\e[2J");
}


//Caso o usuário esteja utilizando windows é necessário um padrão de impressão diferente. As funções utilizam a mesma lógica dos de em linux apenas modificando espaçamento e o que é necessário para troca de cor.
#else
#include <windows.h>

//A biblioteca windows.h, nativa ao sistema windows é importada apensa caso esteja utilizando windows, visto que ela não existe em sistemas linux.

void printCarta (T carta, int num){
	//Declaração das variáveis quais alteram a cor do Prompt de Comando e quais salvam a cor dele antes de terem sido alteradas.
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
	WORD saved_attributes;

	GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
	saved_attributes = consoleInfo.wAttributes;

	if (num){
		switch (carta.cor){
		case vermelho:
		SetConsoleTextAttribute(hConsole, 79);
		printf ("%d - %s   ",num, returnEnumCor(carta.cor));
		break;
		case verde:
		SetConsoleTextAttribute(hConsole, 47);
		printf ("%d - %s      ",num, returnEnumCor(carta.cor));
		break;
		case azul:
		SetConsoleTextAttribute(hConsole, 31);
		printf ("%d - %s       ",num, returnEnumCor(carta.cor));
		break;
		case amarelo:
		SetConsoleTextAttribute(hConsole, 111);
		printf ("%d - %s    ",num, returnEnumCor(carta.cor));
		break;
		case preto:
		SetConsoleTextAttribute(hConsole, 95);
		printf ("%d - %s      ",num, returnEnumCor(carta.cor));
		break;
		}
			if(carta.tipo == cartaNormal)
				printf("%d\n", carta.num);
			else
				printf("%s\n",returnEnumTipo(carta.tipo));
	} else {
		switch (carta.cor){
			case vermelho:
			SetConsoleTextAttribute(hConsole, 79);
			printf ("%s   ", returnEnumCor(carta.cor));
			break;
			case verde:
			SetConsoleTextAttribute(hConsole, 47);
			printf ("%s      ", returnEnumCor(carta.cor));
			break;
			case azul:
			SetConsoleTextAttribute(hConsole, 31);
			printf ("%s       ", returnEnumCor(carta.cor));
			break;
			case amarelo:
			SetConsoleTextAttribute(hConsole, 111);
			printf ("%s    ", returnEnumCor(carta.cor));
			break;
			case preto:
			SetConsoleTextAttribute(hConsole, 95);
			printf ("%s      ", returnEnumCor(carta.cor));
			break;
		}
			if(carta.tipo == cartaNormal)
				printf("%d\n", carta.num);
			else
				printf("%s\n", returnEnumTipo(carta.tipo));
	}
	SetConsoleTextAttribute(hConsole, saved_attributes);
}

//Utiliza-se da mesma lógica de Linux modificando a maneira da impressão com cores adequada ao sistema Windows.
int jogarCarta (iteradorLista *i, fila *f, int num){
	moverIteradorNumero (i, num);
	T carta = elementoLista(i);
	int tipo = 0;
	
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
	WORD saved_attributes;

	GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
	saved_attributes = consoleInfo.wAttributes;
	
	if (carta.tipo == cartaCompra4 || carta.tipo == cartaMudaCor){
		char cor;
		printf ("Escolha a cor da carta, digite:\n");
		SetConsoleTextAttribute(hConsole, 79);
		printf ("R  -  Vermelho\n");
		SetConsoleTextAttribute(hConsole, 47);
		printf ("G  -  Verde\n");
		SetConsoleTextAttribute(hConsole, 31);
		printf ("B  -  Azul\n");
		SetConsoleTextAttribute(hConsole, 111);
		printf ("Y  -  Amarelo\n");
		SetConsoleTextAttribute(hConsole, saved_attributes);
		if (scanf (" %c%*c", &cor));
		else
			return -1;
		if (cor == 'R' || cor == 'r')
			carta.cor = vermelho;
		else if (cor == 'G' || cor == 'g')
			carta.cor = verde;
		else if (cor == 'B' || cor == 'b')
			carta.cor = azul;
		else if (cor == 'Y' || cor == 'y')
			carta.cor = amarelo;
		else
			carta.cor = rand() % 4;
	}
	if (carta.tipo == cartaCompra2)
		tipo = 1;
	else if (carta.tipo == cartaCompra4)
		tipo = 2;
	else if (carta.tipo == cartaBloqueio)
		tipo = 3;
	else if (carta.tipo == cartaReverso)
		tipo = 4;
	retira (i);
	adicionarFila (f, carta);
	return tipo;
}

//Utiliza-se da mesma lógica de Linux modificando a maneira da impressão com cores adequada ao sistema Windows.
void printCartaMesa (T carta){
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
	WORD saved_attributes;

	GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
	saved_attributes = consoleInfo.wAttributes;
	switch (carta.cor){
		case vermelho:
			SetConsoleTextAttribute(hConsole, 79);
			if (carta.tipo == cartaNormal)
				printf ("     \n     \n  %d  \n     \n     \n", carta.num);
			if (carta.tipo == cartaCompra2)
				printf ("     \n     \n + 2 \n     \n     \n");
			if (carta.tipo == cartaCompra4)
				printf ("     \n     \n + 4 \n     \n     \n");
			if (carta.tipo == cartaBloqueio)
				printf ("     \n     \n  X  \n     \n     \n");
			if (carta.tipo == cartaReverso)
				printf ("     \n     \n <-> \n     \n     \n");
			if (carta.tipo == cartaMudaCor)
				printf ("     \n     \n     \n     \n     \n");
			SetConsoleTextAttribute(hConsole, saved_attributes);
		break;
		case verde:
			SetConsoleTextAttribute(hConsole, 47);
			if (carta.tipo == cartaNormal)
				printf ("     \n     \n  %d  \n     \n     \n", carta.num);
			if (carta.tipo == cartaCompra2)
				printf ("     \n     \n + 2 \n     \n     \n");
			if (carta.tipo == cartaCompra4)
				printf ("     \n     \n + 4 \n     \n     \n");
			if (carta.tipo == cartaBloqueio)
				printf ("     \n     \n  X  \n     \n     \n");
			if (carta.tipo == cartaReverso)
				printf ("     \n     \n <-> \n     \n     \n");
			if (carta.tipo == cartaMudaCor)
				printf ("     \n     \n     \n     \n     \n");
			SetConsoleTextAttribute(hConsole, saved_attributes);
		break;
		case azul:
			SetConsoleTextAttribute(hConsole, 31);
			if (carta.tipo == cartaNormal)
				printf ("     \n     \n  %d  \n     \n     \n", carta.num);
			if (carta.tipo == cartaCompra2)
				printf ("     \n     \n + 2 \n     \n     \n");
			if (carta.tipo == cartaCompra4)
				printf ("     \n     \n + 4 \n     \n     \n");
			if (carta.tipo == cartaBloqueio)
				printf ("     \n     \n  X  \n     \n     \n");
			if (carta.tipo == cartaReverso)
				printf ("     \n     \n <-> \n     \n     \n");
			if (carta.tipo == cartaMudaCor)
				printf ("     \n     \n     \n     \n     \n");
			SetConsoleTextAttribute(hConsole, saved_attributes);
		break;
		case amarelo:
			SetConsoleTextAttribute(hConsole, 111);
			if (carta.tipo == cartaNormal)
				printf ("     \n     \n  %d  \n     \n     \n", carta.num);
			if (carta.tipo == cartaCompra2)
				printf ("     \n     \n + 2 \n     \n     \n");
			if (carta.tipo == cartaCompra4)
				printf ("     \n     \n + 4 \n     \n     \n");
			if (carta.tipo == cartaBloqueio)
				printf ("     \n     \n  X  \n     \n     \n");
			if (carta.tipo == cartaReverso)
				printf ("     \n     \n <-> \n     \n     \n");
			if (carta.tipo == cartaMudaCor)
				printf ("     \n     \n     \n     \n     \n");
			SetConsoleTextAttribute(hConsole, saved_attributes);
		break;
		default:
		break;
	}
}

void limpaTela() {
	system("cls");
}


#endif