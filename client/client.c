#include <string.h>
#include <stdio.h>
#include <gtk/gtk.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>

#define SIZE 255

// Variables globales
GtkWidget *window;

// Callback para el botón
void on_button_clicked_lines(GtkButton *button, char *buffer) {
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
    gtk_widget_hide(window);
    gtk_main_quit();

}



void linesView(int argc, char *argv[], char *buffer){
    // Definiendo los componentes de la GUI
    GtkBuilder *builder;
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
    g_signal_connect(button_ADO, "clicked", G_CALLBACK(on_button_clicked_lines), buffer);

    g_signal_connect(button_FUTURA, "clicked", G_CALLBACK(on_button_clicked_lines), buffer);

    g_signal_connect(button_ESTRELLA, "clicked", G_CALLBACK(on_button_clicked_lines), buffer);

    g_signal_connect(button_PREMIERE, "clicked", G_CALLBACK(on_button_clicked_lines), buffer);

    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Mostrar ventana principal
    gtk_widget_show_all(window);

    // Iniciar el bucle principal de GTK
    gtk_main();
}

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
    gtk_widget_hide(window);
    gtk_main_quit();
}


void routesView(int argc, char *argv[], char *buffer){
    // Definiendo los componentes de la GUI
    GtkBuilder *builder;
    GtkButton *button_NORTE;
    GtkButton *button_SUR;
    GtkButton *button_ESTE;
    GtkButton *button_OESTE;

    // Inicializar GTK
    gtk_init(&argc, &argv);

    // Cargar archivo Glade
    builder = gtk_builder_new_from_file("./views/routes.glade");

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


// int main(int argc, char *argv[]) {
//     char buffer[255] = {0};
//     linesView(argc, argv, buffer);
//     printf("La linea seleccionada fue: %c\n", buffer[0]);
//     routesView(argc, argv, buffer);
//     printf("La ruta seleccionada fue: %c", buffer[0]);
//     return 0;
// }


int main(int argc, char *argv[]) {
    int mi_socket, tam, numbytes;
    char buffer[SIZE];
    struct sockaddr_in mi_estructura;

    if (argc != 3) {
        printf("Error: modo de empleo: cliente ip puerto\n");
        exit(-1);
    }

    // Configuración del cliente
    mi_estructura.sin_family = AF_INET;
    mi_estructura.sin_port = htons(atoi(argv[2]));
    if (inet_pton(AF_INET, argv[1], &(mi_estructura.sin_addr)) <= 0) {
        perror("Error en la dirección IP");
        exit(-1);
    }
    memset(&(mi_estructura.sin_zero), '\0', 8);

    // Crear socket
    mi_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (mi_socket == -1) {
        perror("Error al crear el socket");
        exit(1);
    }

    // Conectar al servidor
    tam = sizeof(struct sockaddr);
    if (connect(mi_socket, (struct sockaddr *)&mi_estructura, tam) == -1) {
        perror("Error al conectar");
        close(mi_socket);
        exit(1);
    }

    // Recibir permiso para desplegar sistema
    numbytes = recv(mi_socket, buffer, SIZE - 1, 0);
    buffer[numbytes] = '\0';
    // printf("%s", buffer);
    char optionLine[] = "0";
    if (strcmp(buffer, "1") != 0) {
        printf("Se rechazo el permiso");
        exit(1);
    } 
    linesView(argc, argv, optionLine);
    // // Recibir y mostrar menú
    // numbytes = recv(mi_socket, buffer, SIZE - 1, 0);
    // buffer[numbytes] = '\0';
    // printf("%s", buffer);

    // Seleccionar línea de autobuses
    // printf("Seleccione una línea de autobuses (1-5): ");
    // fgets(buffer, SIZE, stdin);

    send(mi_socket, optionLine, strlen(optionLine), 0);

    // Recibir y mostrar rutas
    // numbytes = recv(mi_socket, buffer, SIZE - 1, 0);
    // buffer[numbytes] = '\0';
    // printf("%s", buffer);

    // Seleccionar ruta
    
    // printf("Seleccione una ruta (1-4): ");
    // fgets(buffer, SIZE, stdin);
    char optionRoute[] = "0";
    routesView(argc, argv, optionRoute);
    send(mi_socket, optionRoute, strlen(optionRoute), 0);
    


    // // Recibir y mostrar los estados disponibles para la ruta seleccionada
    // numbytes = recv(mi_socket, buffer, SIZE - 1, 0);
    // buffer[numbytes] = '\0';
    // printf("%s\n", buffer); // Imprimir los estados disponibles

    // // Solicitar la selección de estado al usuario
    // printf("Seleccione un estado: ");
    // fgets(buffer, SIZE, stdin);
    // buffer[strcspn(buffer, "\n")] = '\0'; // Eliminar el salto de línea

    // // Enviar la selección de estado al servidor
    // send(mi_socket, buffer, strlen(buffer), 0);

    // // Recibir y mostrar los horarios disponibles
    // numbytes = recv(mi_socket, buffer, SIZE - 1, 0);
    // buffer[numbytes] = '\0';
    // printf("%s\n", buffer); // Imprimir los horarios disponibles

    // // Solicitar la selección de horario al usuario
    // printf("Seleccione un horario: ");
    // fgets(buffer, SIZE, stdin);
    // buffer[strcspn(buffer, "\n")] = '\0'; // Eliminar el salto de línea

    // // Enviar la selección de horario al servidor
    // send(mi_socket, buffer, strlen(buffer), 0);

    // // Recibir y mostrar la confirmación final
    // numbytes = recv(mi_socket, buffer, SIZE - 1, 0);
    // buffer[numbytes] = '\0';
    // printf("%s\n", buffer); // Imprimir confirmación


    // Cerrar socket
    close(mi_socket);
    return 0;
}
