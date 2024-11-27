#include <string.h>
#include <stdio.h>
#include <gtk/gtk.h>

GtkComboBoxText *comboBox;
GtkWidget *window;

int reserva[4] = {-1,-1,-1,-1};
// Callback para el botón
void on_button_clicked_routes(GtkButton *button, char *buffer) {
    int selection = gtk_combo_box_get_active(GTK_COMBO_BOX(comboBox));
    //printf("posicion %d", selection);
    reserva[2] = selection;
    gtk_widget_hide(window);
    gtk_main_quit();
}


void destinationsView(int argc, char *argv[], char *buffer, char ESTADO[][30], int num_estados){
    // Definiendo los componentes de la GUI
    GtkBuilder *builder;
    GtkButton *button_ACCEPT;
    
    // Inicializar GTK
    gtk_init(&argc, &argv);

    // Cargar archivo Glade
    builder = gtk_builder_new_from_file("../views/destination.glade");

    // Obtener ventana principal
    window = GTK_WIDGET(gtk_builder_get_object(builder, "destWindow"));
    if (!window) {
        g_error("Error: No se pudo cargar la ventana principal.");
    }
    // Obtener el combo box para la seleccion de destinos
    comboBox = GTK_COMBO_BOX_TEXT(gtk_builder_get_object(builder, "destinations_list"));
    if (!comboBox) {
        g_error("Error: No se pudo cargar el combobox .");
    }
    // Rellena el combobox
    for (int i = 0; i < num_estados; i++) {
        gtk_combo_box_text_append_text(comboBox, ESTADO[i]);
    }

    gtk_combo_box_set_active(GTK_COMBO_BOX(comboBox), 0);

    // Obtener botón continuar o aceptar
    button_ACCEPT = GTK_BUTTON(gtk_builder_get_object(builder, "continue"));
    if (!button_ACCEPT) {
        g_error("Error: No se pudo cargar el botón 'NORTE'.");
    }

    // Conectando los signals para llamar a la funcion
    g_signal_connect(button_ACCEPT, "clicked", G_CALLBACK(on_button_clicked_routes), buffer);

    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Mostrar ventana principal
    gtk_widget_show_all(window);

    // Iniciar el bucle principal de GTK
    gtk_main();

}

int main(int argc, char *argv[]) {
    char buffer[255] = {0};
    char ESTADO[][30] = {"Baja California", "Baja California Sur", "Sonora", "Chihuahua", "Coahuila", "Nuevo León", "Durango", "Zacatecas", "San Luis Potosí"};
    int num_estados = sizeof(ESTADO) / sizeof(ESTADO[0]);
    destinationsView(argc, argv, buffer, ESTADO, num_estados);
    // printf("La ruta seleccionada fue: %c", buffer[0]);
    return 0;
}