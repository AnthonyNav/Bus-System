#include <string.h>
#include <stdio.h>
#include <gtk/gtk.h>

// Callback para el botón
void on_button_clicked_routes(GtkButton *button, char *buffer) {
    //printf("Se activó la función\n");
    const char *text = gtk_button_get_label(button);

    if (strcmp(text, "NORTE") == 0) {
        //printf("OPCION NORTE\n");
        buffer[0] = '1'; 
    }
    else if ((strcmp(text, "SUR") == 0)) {
        //printf("OPCION SUR\n");
        buffer[0] = '2';
    }
    else if ((strcmp(text, "ESTE") == 0)) {
        //printf("OPCION ESTE\n");
        buffer[0] = '3';
    }
    else if ((strcmp(text, "OESTE") == 0)) {
        //printf("OPCION OESTE\n");
        buffer[0] = '4';
    }
    else{
        //printf("DEFAULT");
        buffer[0] = 'N';
    }
    //printf("Fin de la funcion\n");
    gtk_main_quit();

}



void routesView(int argc, char *argv[], char *buffer){
    // Definiendo los componentes de la GUI
    GtkBuilder *builder;
    GtkWidget *window;
    GtkButton *button_NORTE;
    GtkButton *button_SUR;
    GtkButton *button_ESTE;
    GtkButton *button_OESTE;

    // Inicializar GTK
    gtk_init(&argc, &argv);

    // Cargar archivo Glade
    builder = gtk_builder_new_from_file("../views/routes.glade");

    // Obtener ventana principal
    window = GTK_WIDGET(gtk_builder_get_object(builder, "routesWindow"));
    if (!window) {
        g_error("Error: No se pudo cargar la ventana principal.");
    }

    // Obtener botón NORTE
    button_NORTE = GTK_BUTTON(gtk_builder_get_object(builder, "NORTE"));
    if (!button_NORTE) {
        g_error("Error: No se pudo cargar el botón 'NORTE'.");
    }

    // Obtener botón SUR
    button_SUR = GTK_BUTTON(gtk_builder_get_object(builder, "SUR"));
    if (!button_SUR) {
        g_error("Error: No se pudo cargar el botón 'SUR'.");
    }

    // Obtener botón ESTE
    button_ESTE = GTK_BUTTON(gtk_builder_get_object(builder, "ESTE"));
    if (!button_ESTE) {
        g_error("Error: No se pudo cargar el botón 'ESTE'.");
    }

    // Obtener botón OESTE
    button_OESTE = GTK_BUTTON(gtk_builder_get_object(builder, "OESTE"));
    if (!button_OESTE) {
        g_error("Error: No se pudo cargar el botón 'OESTE'.");
    }

    // Conectando los signals para llamar a la funcion
    g_signal_connect(button_NORTE, "clicked", G_CALLBACK(on_button_clicked_routes), buffer);

    g_signal_connect(button_SUR, "clicked", G_CALLBACK(on_button_clicked_routes), buffer);

    g_signal_connect(button_ESTE, "clicked", G_CALLBACK(on_button_clicked_routes), buffer);

    g_signal_connect(button_OESTE, "clicked", G_CALLBACK(on_button_clicked_routes), buffer);

    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Mostrar ventana principal
    gtk_widget_show_all(window);

    // Iniciar el bucle principal de GTK
    gtk_main();

}

int main(int argc, char *argv[]) {
    char buffer[255] = {0};
    routesView(argc, argv, buffer);
    printf("La ruta seleccionada fue: %c", buffer[0]);
    return 0;
}
