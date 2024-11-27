#include <string.h>
#include <stdio.h>
#include <gtk/gtk.h>

// Callback para el botón
void on_button_clicked(GtkButton *button, char *buffer) {
    //printf("Se activó la función\n");
    const char *text = gtk_button_get_label(button);

    if (strcmp(text, "ADO") == 0) {
        //printf("OPCION ADO\n");
        buffer[0] = '1'; 
    }
    else if ((strcmp(text, "FUTURA") == 0)) {
        //printf("OPCION FUTURA\n");
        buffer[0] = '2';
    }
    else if ((strcmp(text, "ESTRELLA BLANCA") == 0)) {
        //printf("OPCION ESTRELLA\n");
        buffer[0] = '3';
    }
    else if ((strcmp(text, "PREMIERE PLUS") == 0)) {
        //printf("OPCION PREMIERE\n");
        buffer[0] = '4';
    }
    else{
        //printf("DEFAULT");
        buffer[0] = 'N';
    }
    //printf("Fin de la funcion\n");
    gtk_main_quit();

}



void linesView(int argc, char *argv[], char *buffer){
    // Definiendo los componentes de la GUI
    GtkBuilder *builder;
    GtkWidget *window;
    GtkButton *button_ADO;
    GtkButton *button_FUTURA;
    GtkButton *button_ESTRELLA;
    GtkButton *button_PREMIERE;

    // Inicializar GTK
    gtk_init(&argc, &argv);

    // Cargar archivo Glade
    builder = gtk_builder_new_from_file("./views/lines.glade");

    // Obtener ventana principal
    window = GTK_WIDGET(gtk_builder_get_object(builder, "linesWindow"));
    if (!window) {
        g_error("Error: No se pudo cargar la ventana principal.");
    }

    // Obtener botón ADO
    button_ADO = GTK_BUTTON(gtk_builder_get_object(builder, "ADO"));
    if (!button_ADO) {
        g_error("Error: No se pudo cargar el botón 'ADO'.");
    }

    // Obtener botón FUTURA
    button_FUTURA = GTK_BUTTON(gtk_builder_get_object(builder, "FUTURA"));
    if (!button_FUTURA) {
        g_error("Error: No se pudo cargar el botón 'FUTURA'.");
    }

    // Obtener botón ESTRELLA
    button_ESTRELLA = GTK_BUTTON(gtk_builder_get_object(builder, "ESTRELLA"));
    if (!button_ESTRELLA) {
        g_error("Error: No se pudo cargar el botón 'ESTRELLA'.");
    }

    // Obtener botón PREMIERE
    button_PREMIERE = GTK_BUTTON(gtk_builder_get_object(builder, "PREMIERE"));
    if (!button_PREMIERE) {
        g_error("Error: No se pudo cargar el botón 'PREMIERE'.");
    }

    // Conectando los signals para llamar a la funcion
    g_signal_connect(button_ADO, "clicked", G_CALLBACK(on_button_clicked), buffer);

    g_signal_connect(button_FUTURA, "clicked", G_CALLBACK(on_button_clicked), buffer);

    g_signal_connect(button_ESTRELLA, "clicked", G_CALLBACK(on_button_clicked), buffer);

    g_signal_connect(button_PREMIERE, "clicked", G_CALLBACK(on_button_clicked), buffer);

    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Mostrar ventana principal
    gtk_widget_show_all(window);

    // Iniciar el bucle principal de GTK
    gtk_main();

}


int main(int argc, char *argv[]) {
    char buffer[255] = {0};
    linesView(argc, argv, buffer);
    printf("La linea seleccionada fue: %c\n", buffer[0]);
    return 0;
}
