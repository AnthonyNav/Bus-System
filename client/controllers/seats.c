#include <string.h>
#include <stdio.h>
#include <gtk/gtk.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>

// Variables globales
GtkWidget *window;
GtkComboBoxText *comboBox;
const char *background = "#641e16";
const char *color = "white";

int asientos[10];

void on_button_clicked_seat(GtkButton *button, char *buffer) {
    const char *text = gtk_button_get_label(button);
    int id = atoi(text) -1;
    if (asientos[id] != -1){
        // Crear un proveedor de CSS
        GtkCssProvider *provider = gtk_css_provider_new();
        // Crear el CSS dinámicamente
        char css[256];
        snprintf(css, sizeof(css),
                "button { background: %s; color: %s; }",
                "#b32000", "black");
        // Cargar el CSS en el proveedor
        gtk_css_provider_load_from_data(provider, css, -1, NULL);
        GtkStyleContext *context = gtk_widget_get_style_context(GTK_WIDGET(button));
                // Aplicar el proveedor al contexto del botón
        gtk_style_context_add_provider(context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);

        // Liberar el proveedor después de aplicarlo
        g_object_unref(provider);
        asientos[id] = -1;
    }
    
}

void on_button_clicked_ready(GtkButton *button, char *buffer) {
    gtk_widget_hide(window);
    gtk_main_quit();
}

void seatsView(int argc, char *argv[], char *buffer) {
    // Definiendo los componentes de la GUI
    GtkBuilder *builder;
    GtkButton *button_seats[10];
    GtkButton *button_Accept;
    int i;

    // Crear un proveedor de CSS
    GtkCssProvider *provider = gtk_css_provider_new();
    // Crear el CSS dinámicamente
    char css[256];
    snprintf(css, sizeof(css),
             "button { background: %s; color: %s; box-shadow:none;}",
             background, color);
    // Cargar el CSS en el proveedor
    gtk_css_provider_load_from_data(provider, css, -1, NULL);

    // Inicializar GTK
    gtk_init(&argc, &argv);

    // Cargar archivo Glade
    builder = gtk_builder_new_from_file("../views/seats.glade");

    // Obtener ventana principal
    window = GTK_WIDGET(gtk_builder_get_object(builder, "seatWindow"));
    if (!window) {
        g_error("Error: No se pudo cargar la ventana principal.");
    }

    char id_button[3];  // Espacio suficiente para almacenar "10\0"
    for (i = 0; i < 10; i++) {
        sprintf(id_button, "%d", i + 1);
        button_seats[i] = GTK_BUTTON(gtk_builder_get_object(builder, id_button));
        if (!button_seats[i]) {
            g_error("Error: No se pudo cargar el asiento: %d", i + 1);
        }
        if (asientos[i] == 1) {
            g_signal_connect(button_seats[i], "clicked", G_CALLBACK(on_button_clicked_seat), buffer);
        } else {
            GtkStyleContext *context = gtk_widget_get_style_context(GTK_WIDGET(button_seats[i]));
            // Aplicar el proveedor al contexto del botón
            gtk_style_context_add_provider(context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
        }
    }

    // Obtener botón continuar o aceptar
    button_Accept = GTK_BUTTON(gtk_builder_get_object(builder, "Aceptar"));
    if (!button_Accept) {
        g_error("Error: No se pudo cargar el botón 'Aceptar'.");
    }

    // Conectar el botón "Aceptar" con la función de callback
    g_signal_connect(button_Accept, "clicked", G_CALLBACK(on_button_clicked_ready), buffer);

    // Conectar la señal de cierre de ventana para salir del bucle GTK
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Mostrar ventana principal
    gtk_widget_show_all(window);

    // Iniciar el bucle principal de GTK
    gtk_main();

    // Liberar el proveedor después de aplicarlo
    g_object_unref(provider);
}

int main(int argc, char *argv[]) {
    int i;
    for (i = 0; i < 10; i++) {
        asientos[i] = 1;
    }

    asientos[5] = 0;
    asientos[2] = 0;
    asientos[7] = 0;

    char buffer[256] = {0};  // Un buffer de ejemplo
    seatsView(argc, argv, buffer);

    printf("\n");
    for ( i = 0; i < 10; i++){
        printf("%d ", asientos[i]);
    }
    
    return 0;
}














// #include <string.h>
// #include <stdio.h>
// #include <gtk/gtk.h>
// #include <unistd.h>
// #include <netinet/in.h>
// #include <arpa/inet.h>
// #include <sys/types.h>
// #include <sys/socket.h>
// #include <stdlib.h>

// // Variables globales
// GtkWidget *window;
// GtkComboBoxText *comboBox;
// const char *background = "#e74c3c";
// const char *color = "white";

// int asientos[10];

// void on_button_clicked_seat(GtkButton *button, char *buffer) {
    
//     gtk_widget_hide(window);
//     gtk_main_quit();
// }

// void on_button_clicked_ready(GtkButton *button, char *buffer) {
    
//     gtk_widget_hide(window);
//     gtk_main_quit();
// }

// void seatsView(int argc, char *argv[], char *buffer) {
//     // Definiendo los componentes de la GUI
//     GtkBuilder *builder;
//     GtkButton *button_seats[10];
//     GtkButton *button_Accept;
//     int i;
//     GtkStyleContext *context; 
//     // Crear un proveedor de CSS
//     GtkCssProvider *provider = gtk_css_provider_new();
//     // Crear el CSS dinámicamente
//     char css[256];
//     snprintf(css, sizeof(css),
//              "button { background-color: %s; color: %s; }",
//              background, color);
//     // Cargar el CSS en el proveedor
//     gtk_css_provider_load_from_data(provider, css, -1, NULL);

//     // Inicializar GTK
//     gtk_init(&argc, &argv);

//     // Cargar archivo Glade
//     builder = gtk_builder_new_from_file("../views/seats.glade");

//     // Obtener ventana principal
//     window = GTK_WIDGET(gtk_builder_get_object(builder, "seatWindow"));
//     if (!window) {
//         g_error("Error: No se pudo cargar la ventana principal.");
//     }
//     char *id_button;
//     for ( i = 0; i < 10; i++){
//         sprintf(id_button, "%d", i+1);
//         button_seats[i] = GTK_BUTTON(gtk_builder_get_object(builder, id_button));
//         if (!button_seats[i]) {
//             g_error("Error: No se pudo cargar el asiento: %d ", i+1);
//         }
//         if(asientos[i] == 1){
//             g_signal_connect(button_seats[i], "clicked", G_CALLBACK(on_button_clicked_seat), buffer);
//         } else {
//             *context = gtk_widget_get_style_context(button_seats[i]);
//             // Aplicar el proveedor al contexto del botón
//             gtk_style_context_add_provider(context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
//         }
//     }

//     // Obtener botón continuar o aceptar
//     button_Accept = GTK_BUTTON(gtk_builder_get_object(builder, "Aceptar"));
//     if (!button_Accept) {
//         g_error("Error: No se pudo cargar el botón 'Aceptar'.");
//     }

//     // Conectar el botón "Aceptar" con la función de callback
//     g_signal_connect(button_ACCEPT, "clicked", G_CALLBACK(on_button_clicked_ready), buffer);

//     // Conectar la señal de cierre de ventana para salir del bucle GTK
//     g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

//     // Mostrar ventana principal
//     gtk_widget_show_all(window);

//     // Iniciar el bucle principal de GTK
//     gtk_main();
//     // Liberar el proveedor después de aplicarlo
//     g_object_unref(provider);
// }

// int main(int argc, char *argv[]){
//     int i;
//     for (i = 0; i < 10; i++){
//         asientos[i] = 1;
//     }

// }
