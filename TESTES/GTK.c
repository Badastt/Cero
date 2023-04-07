#include <gtk/gtk.h>
#include <stdlib.h>
#include <time.h>

GtkWidget *label;
GtkWidget *nova_label;
GtkWidget *imagem;

// Define card values and suits
const char *values[] = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "0", "Bloqueio", "Reverso"};
const char *suits[] = {"Vermelho", "Verde", "Azul", "Amarelo"};

// Function to generate a random card value and suit
void deal_card() {
  int value_index = rand() % 13;
  int suit_index = rand() % 4;
  char card[20];
  snprintf(card, 20, "%s %s", values[value_index], suits[suit_index]);
  gtk_label_set_text(GTK_LABEL(label), card);
}

// Function to handle the delete event of the window
gboolean on_window_delete_event(GtkWidget *widget, GdkEvent *event, gpointer data) {
  gtk_main_quit();
  return TRUE;
}

int main(int argc, char *argv[]) {
  gtk_init(&argc, &argv);

  GtkWidget *window;
  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title(GTK_WINDOW(window), "UNO");
  gtk_container_set_border_width(GTK_CONTAINER(window), 100);
  gtk_window_set_default_size(window, 500,500);
  
  g_signal_connect(window, "delete-event", G_CALLBACK(on_window_delete_event), NULL);


  GtkWidget *overlay;
  GtkWidget *imagem_seta;
  imagem_seta = gtk_image_new_from_file("Mais2_Vermelho.png");
  imagem = gtk_image_new_from_file("mesa_pixel.png");
  overlay = gtk_overlay_new();
  gtk_container_add( GTK_CONTAINER(window), overlay);
  gtk_overlay_add_overlay( GTK_OVERLAY (overlay), imagem);
  gtk_overlay_add_overlay( GTK_OVERLAY (overlay), imagem_seta);
  g_object_set(imagem_seta, "halign", GTK_ALIGN_CENTER,NULL);
  g_object_set(imagem_seta, "valign", GTK_ALIGN_CENTER,NULL);
  g_object_set(imagem,"halign", GTK_ALIGN_CENTER,NULL);
  g_object_set(imagem,"valign", GTK_ALIGN_CENTER,NULL);
  GtkWidget *button_penis = gtk_button_new_with_label("Penis");
  gtk_overlay_add_overlay( GTK_OVERLAY(overlay), button_penis);
  g_object_set(button_penis,"valign",GTK_ALIGN_START,NULL);

  srand(time(NULL));

  gtk_widget_show_all(window);
  gtk_main();

  return 0;
}
