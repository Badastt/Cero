#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include <gtk/gtk.h>
#include "../lib/types.h"
#include "../lib/list.h"
#include "../lib/stack.h"
#include "../lib/queue.h"
#include "../lib/baralho.h"

const char *values[] = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "0", "Bloqueio", "Reverso"};
const char *suits[] = {"Vermelho", "Verde", "Azul", "Amarelo"};

void deal_card() {
  int value_index = rand() % 13;
  int suit_index = rand() % 4;
  char card[20];
  snprintf(card, 20, "%s %s", values[value_index], suits[suit_index]);
}

void cliqueCarta (GtkWidget *widget, botao *b)
{
    jogarCarta (b->iterador, b->fila, b->iterador->numero);
}

gboolean on_window_delete_event(GtkWidget *widget, GdkEvent *event, gpointer data) {
  gtk_main_quit();
  return TRUE;
}

int main (int argc, char *argv[]){
	pilha *baralhoCompra = inicializarPilha(NUM_CARTAS);
	fila *baralhoMesa = initializeQueue();
	
	lista *maoPlayer1 = inicializarLista();
	lista *maoPlayer2 = inicializarLista();
	iteradorLista *itPlayer1 = inicializarIterador(maoPlayer1);
	iteradorLista *itPlayer2 = inicializarIterador(maoPlayer2);
	
	criarBaralho(baralhoCompra);
	shuffle (baralhoCompra);
	
	comprarCartas (maoPlayer1, baralhoCompra, baralhoMesa, 6);
	comprarCartas (maoPlayer2, baralhoCompra, baralhoMesa, 6);
	
	proximoIterador (itPlayer1);
	proximoIterador (itPlayer2);
	
	primeiraCarta (baralhoCompra, baralhoMesa);
	
	int acabou = 0;
	int flag = 0;
	int posCarta = 0;
	
	printf("\e[1;1H\e[2J");
	
	if (argv[1] == 0){
		while (1 && !acabou){
			if (!flag){	
				flag = 0;
				moverIteradorNumero (itPlayer1, 1);
				for (int i = 0; i < quantidadeLista (maoPlayer1)+1; i++){
					flag = verificaJogada (elementoLista(itPlayer1), ultimoLista(baralhoMesa));
					proximoIterador (itPlayer1);
					if (flag)
						break;
				}
				
				printf ("A carta na mesa é a seguinte:\n\n");
				printCartaMesa (ultimoLista(baralhoMesa));
				printf ("\n");
				printCarta (ultimoLista(baralhoMesa), 0);
				printf ("\n");
				
				moverIteradorNumero (itPlayer1, 1);
				for (int i = 1; i < quantidadeLista (maoPlayer1)+1; i++){
					printCarta (elementoLista(itPlayer1), i);
					proximoIterador (itPlayer1);
				}
				
				if (quantidadeLista (maoPlayer2) > 1)
					printf ("O seu oponente tem %d cartas!!\n", quantidadeLista (maoPlayer2));
				else
					printf ("O seu oponente tem UMA carta!!\n");
				
				moverIteradorNumero (itPlayer1, 1);
				if (flag){
					printf ("Você têm cartas válidas, qual será a sua jogada?? (Digite o número atrás da carta)\n\n");
					if (scanf (" %d%*c", &posCarta));
					else
						return -1;
					
					moverIteradorNumero (itPlayer1, posCarta);
					
					while (!(verificaJogada(elementoLista(itPlayer1) ,ultimoLista(baralhoMesa)))){
						printf ("O número digitado é inválido, tente novamente:\n\n");
						if (scanf (" %d%*c", &posCarta));
						else
							return -1;
						moverIteradorNumero (itPlayer1, posCarta);
						}
					
					flag = jogarCarta (itPlayer1, baralhoMesa, posCarta);
					if (flag == 1)
						comprarCartas (maoPlayer2, baralhoCompra, baralhoMesa, 2);
					else if (flag == 2)
						comprarCartas (maoPlayer2, baralhoCompra, baralhoMesa, 4);
						
					
					printf("\e[1;1H\e[2J");
				} else {
					printf ("Você não tem nenhuma jogada válida, uma carta será comprada!!\n");
					printf ("Pressione ENTER para confirmar\n");
					getchar();
					printf("\e[1;1H\e[2J");
					comprarCartas (maoPlayer1, baralhoCompra, baralhoMesa, 1);
				}
			} else {
				if (flag == 1)
					printf ("O seu adversário jogou uma carta +2, então você não pode jogar esse turno e comprou 2 cartas!!!\n");
				else if (flag == 2)
					printf ("O seu adversário jogou uma carta +4, então você não pode jogar esse turno e comprou 4 cartas!!!\n");
				else if (flag == 3)
					printf ("O seu adversário jogou uma carta bloqueio, então você não pode jogar esse turno!!!\n");
				else if (flag == 4)
					printf ("O seu adversário jogou uma carta reverte, então você não pode jogar esse turno!!!\n");
				if (quantidadeLista (maoPlayer2) > 1)
					printf ("O seu oponente tem %d cartas!!\n", quantidadeLista (maoPlayer2));
				else
					printf ("O seu oponente tem UMA carta!!\n");
				printf ("Pressione ENTER para confirmar\n");
					getchar();
				printf("\e[1;1H\e[2J");
				flag = 0;
			}
			
			if (quantidadeLista (maoPlayer1) == 0){
				printf ("DIGA CERO OU NÃO GANHARÁ O JOGO\n");
				char cero[5];
				int j = 0;
				while ((cero[j] = getchar()) != '\n' &&cero[j] != EOF)
					j++;
				cero [4] = '\0';
				
				for(j = 0; j < 4; j++)
					cero[j] = tolower(cero[j]);
				if (strcmp(cero, "cero") == 0){
					printf ("VOCÊ VENCEU!!\n");
					acabou = 1;
					break;
				} else {
					printf ("ERRADO, COMPRE DUAS CARTAS!!\n\n");
					comprarCartas (maoPlayer1, baralhoCompra, baralhoMesa, 2);
				}
			}
			
			//IA:
			if (!flag){
				moverIteradorNumero (itPlayer2, 1);
				for (int i = 0; i < quantidadeLista (maoPlayer2)+1; i++){
					flag = verificaJogada (elementoLista(itPlayer2), ultimoLista(baralhoMesa));
					if (flag){
						printf ("O seu adversário jogou a carta:\n");
						printCarta (elementoLista(itPlayer2), 0);
						printf ("\n\n");
						flag = jogarCartaIA (itPlayer2, baralhoMesa, i+1);
						if (flag == 1)
							comprarCartas (maoPlayer1, baralhoCompra, baralhoMesa, 2);
						else if (flag == 2)
							comprarCartas (maoPlayer1, baralhoCompra, baralhoMesa, 4);
						break;
					} else if (!flag && i == quantidadeLista (maoPlayer2)){
						printf ("O seu adversário não tinha nenhuma carta válida então comprou uma carta\n\n\n\n");
						comprarCartas (maoPlayer2, baralhoCompra, baralhoMesa, 1);
						i++;
					}
					proximoIterador (itPlayer2);
				}
			} else {
				if (flag == 1)
					printf ("Você jogou uma carta +2, então o seu oponente não jogou nesse turno!!!\n");
				else if (flag == 2)
					printf ("Você jogou uma carta +4, então o seu oponente não jogou nesse turno!!!\n");
				else if (flag == 3)
					printf ("Você jogou uma carta bloqueio, então o seu oponente não jogou nesse turno!!!\n");
				else if (flag == 4)
					printf ("Você jogou uma carta reverte, então o turno voltou para você!!!\n");
				flag = 0;
			}
			
			if (quantidadeLista (maoPlayer2) == 0){
				printf ("VOCÊ PERDEU\n");
				acabou = 1;
				break;
			}
		}
	} else if (!acabou) {
		char *cartaMesa;
		char *caminhoCarta1;
		char *caminhoCarta2;
		char *caminhoCarta3;
		int qtd;
		iteradorLista *it2Player1 = inicializarIterador(maoPlayer1);
		iteradorLista *it3Player1 = inicializarIterador(maoPlayer1);
		botao *botaoCarta1 = inicializaBotao (itPlayer1, baralhoMesa);
		botao *botaoCarta2 = inicializaBotao (it2Player1, baralhoMesa);
		botao *botaoCarta3 = inicializaBotao (it3Player1, baralhoMesa);
		
		
		moverIteradorNumero (itPlayer1, 1);
		moverIteradorNumero (it2Player1, 2);
		moverIteradorNumero (it3Player1, 3);
		
		GtkWidget *window;
		GtkWidget *mesa;
		GtkWidget *centro;
		GtkWidget *overlay;
		GtkWidget *cartaTopo;
		GtkWidget *cartas;
		GtkWidget *carta1Mao;
		GtkWidget *carta2Mao;
		GtkWidget *carta3Mao;
		GtkWidget *carta1MaoImagem;
		GtkWidget *carta2MaoImagem;
		GtkWidget *carta3MaoImagem;
		int i = 0;
		
		gtk_init(&argc, &argv);
		
		//cartaMesa = caminhoCarta(ultimoLista(baralhoMesa));
		caminhoCarta1 = caminhoCarta(elementoLista(itPlayer1));
		caminhoCarta2 = caminhoCarta(elementoLista(it2Player1));
		caminhoCarta3 = caminhoCarta(elementoLista(it3Player1));
		qtd = quantidadeLista (maoPlayer1);
		
		i++;
		cartaMesa = caminhoCarta((carta){i%10, 0, 0});
		
		window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
		gtk_window_set_title(GTK_WINDOW(window), "CERO");
		gtk_container_set_border_width(GTK_CONTAINER(window), 0);
		gtk_window_set_default_size(window, 1366,768);

		g_signal_connect(window, "delete-event", G_CALLBACK(on_window_delete_event), NULL);
		
		carta1Mao = gtk_button_new();
		carta1MaoImagem = gtk_image_new_from_file (caminhoCarta1);
		gtk_button_set_image (GTK_BUTTON (carta1Mao), carta1MaoImagem);
		g_signal_connect(carta1Mao, "clicked", G_CALLBACK(cliqueCarta), botaoCarta1);
		
		if (qtd >= 2){
		carta2Mao = gtk_button_new();
		carta2MaoImagem = gtk_image_new_from_file (caminhoCarta2);
		gtk_button_set_image (GTK_BUTTON (carta2Mao), carta2MaoImagem);
		g_signal_connect(carta2Mao, "clicked", G_CALLBACK(cliqueCarta), botaoCarta2);
		}
		
		if (qtd >= 3){
		carta3Mao = gtk_button_new();
		carta3MaoImagem = gtk_image_new_from_file (caminhoCarta3);
		gtk_button_set_image (GTK_BUTTON (carta3Mao), carta3MaoImagem);
		g_signal_connect(carta3Mao, "clicked", G_CALLBACK(cliqueCarta), botaoCarta3);
		}
		
		cartaTopo = gtk_image_new_from_file(cartaMesa);
		gtk_image_set_from_file (cartaTopo, cartaMesa);
		mesa = gtk_image_new_from_file("data/MESA.png");
		overlay = gtk_overlay_new();
		centro = gtk_overlay_new();
		cartas = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
		
		gtk_container_add(GTK_CONTAINER(window), overlay);
		gtk_overlay_add_overlay(GTK_OVERLAY (overlay), centro);
		gtk_overlay_add_overlay(GTK_OVERLAY (centro), mesa);
		gtk_overlay_add_overlay(GTK_OVERLAY (centro), cartaTopo);
		
		gtk_container_add(GTK_CONTAINER (overlay), cartas);
		
		gtk_box_pack_start(GTK_BOX(cartas), carta1Mao, TRUE, TRUE, 10);
		if (qtd >= 2)
			gtk_box_pack_start(GTK_BOX(cartas), carta2Mao, TRUE, TRUE, 10);
		if (qtd >= 3)
			gtk_box_pack_start(GTK_BOX(cartas), carta3Mao, TRUE, TRUE, 10);
		
		g_object_set(cartas, "halign", GTK_ALIGN_CENTER, NULL);
		g_object_set(cartas, "valign", GTK_ALIGN_END, NULL);
		g_object_set(cartaTopo, "halign", GTK_ALIGN_CENTER,NULL);
		g_object_set(cartaTopo, "valign", GTK_ALIGN_CENTER,NULL);
		g_object_set(mesa,"halign", GTK_ALIGN_CENTER,NULL);
		g_object_set(mesa,"valign", GTK_ALIGN_CENTER,NULL);
		
		gtk_widget_show_all(window);
		gtk_main();
		acabou = 1;
	}

destroiPilha (baralhoCompra);
destroyQueue (baralhoMesa);
destroiLista (maoPlayer1);
destroiLista (maoPlayer2);
destroiIterador (itPlayer1);
destroiIterador (itPlayer2);

return 0;}
