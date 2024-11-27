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
GtkComboBoxText *comboBox;

// Controlador de reserva [linea, ruta, estado, horario, asiento]
int reserva[4] = {-1,-1,-1,-1};

// Callback para el botón
void on_button_clicked_lines(GtkButton *button, char *buffer) {
    //printf("Se activó la función\n");
    const char *text = gtk_button_get_label(button);

    if (strcmp(text, "ADO") == 0) {
        //printf("OPCION ADO\n"); 
        reserva[0] = 1;
    }
    else if ((strcmp(text, "FUTURA") == 0)) {
        //printf("OPCION FUTURA\n");
        reserva[0] = 2;
    }
    else if ((strcmp(text, "ESTRELLA BLANCA") == 0)) {
        //printf("OPCION ESTRELLA\n");
        reserva[0] = 3;
    }
    else if ((strcmp(text, "PREMIERE PLUS") == 0)) {
        //printf("OPCION PREMIERE\n");
        reserva[0] = 4;
    }
    else{
        printf("Error: Linea inexistente");
    }
    //printf("Fin de la funcion\n");
    gtk_widget_hide(window);
    gtk_main_quit();

}



void linesView(int argc, char *argv[]){
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
    g_signal_connect(button_ADO, "clicked", G_CALLBACK(on_button_clicked_lines), NULL);

    g_signal_connect(button_FUTURA, "clicked", G_CALLBACK(on_button_clicked_lines), NULL);

    g_signal_connect(button_ESTRELLA, "clicked", G_CALLBACK(on_button_clicked_lines), NULL);

    g_signal_connect(button_PREMIERE, "clicked", G_CALLBACK(on_button_clicked_lines), NULL);

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
    printf("%s\n", text);
    if (strcmp(text, "NORTE") == 0) {
        //printf("OPCION NORTE\n");
        reserva[1] = 1;
    }
    else if ((strcmp(text, "SUR") == 0)) {
        //printf("OPCION SUR\n");
        reserva[1] = 2;
    }
    else if ((strcmp(text, "ESTE") == 0)) {
        //printf("OPCION ESTE\n");
        reserva[1] = 3;
    }
    else if ((strcmp(text, "OESTE") == 0)) {
        //printf("OPCION OESTE\n");
        reserva[1] = 4;
    }
    else{
        printf("ERROR: REGION INEXISTENTE");
    }
    //printf("Fin de la funcion\n");
    gtk_widget_hide(window);
    gtk_main_quit();
}


void routesView(int argc, char *argv[]){
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
    g_signal_connect(button_NORTE, "clicked", G_CALLBACK(on_button_clicked_routes), NULL);

    g_signal_connect(button_SUR, "clicked", G_CALLBACK(on_button_clicked_routes), NULL);

    g_signal_connect(button_ESTE, "clicked", G_CALLBACK(on_button_clicked_routes), NULL);

    g_signal_connect(button_OESTE, "clicked", G_CALLBACK(on_button_clicked_routes), NULL);

    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Mostrar ventana principal
    gtk_widget_show_all(window);

    // Iniciar el bucle principal de GTK
    gtk_main();

}

void on_button_clicked_dest(GtkButton *button, char *buffer) {
    int selection = gtk_combo_box_get_active(GTK_COMBO_BOX(comboBox));
    //printf("posicion %d", selection);
    reserva[2] = selection;
    gtk_widget_hide(window);
    gtk_main_quit();
}


void destinationsView(int argc, char *argv[], char *buffer, char ESTADO[][20], int num_estados){
    // Definiendo los componentes de la GUI
    GtkBuilder *builder;
    GtkButton *button_ACCEPT;
    
    // Inicializar GTK
    gtk_init(&argc, &argv);

    // Cargar archivo Glade
    builder = gtk_builder_new_from_file("./views/destination.glade");

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
    g_signal_connect(button_ACCEPT, "clicked", G_CALLBACK(on_button_clicked_dest), buffer);

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
    int mi_socket, tam, numbytes, numEst;
    char buffer[SIZE] = {0}, estados[15][20];
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
    if (strcmp(buffer, "1") != 0) {
        printf("Se rechazo el permiso");
        exit(1);
    } 
    // Seleccion de linea
    linesView(argc, argv);
    char choiceLine[2];
    if (reserva[0] == -1){
        exit(1);
    }
    // Conversion de numero a cadena
    sprintf(choiceLine, "%d", reserva[0]);
    printf("Linea: %s", choiceLine);
    send(mi_socket, choiceLine, strlen(choiceLine), 0);

    routesView(argc, argv);
    char choiceRoute[2];
    if (reserva[1] == -1){
        exit(1);
    }
    sprintf(choiceRoute, "%d", reserva[1]);
    printf("Ruta: %s", choiceRoute);
    send(mi_socket, choiceRoute, strlen(choiceRoute), 0);

    // // Recibir y mostrar los estados disponibles para la ruta seleccionada
    numbytes = recv(mi_socket, buffer, SIZE - 1, 0);
    buffer[numbytes] = '\0';
    // printf("\n%s\n", buffer); // Imprimir la cantidad de estados a recibir
    numEst = atoi(buffer);

    for (int i = 0; i < numEst; i++) {
        numbytes = recv(mi_socket, buffer, SIZE - 1, 0);
        buffer[numbytes] = '\0';
        //printf("Entrada: %s\n", buffer);
        strcpy(estados[i], buffer);
        //printf("Guardado: %s\n", estados[i]);
    }
    // Destinos
    destinationsView(argc, argv, buffer, estados, numEst);
    char choiceDest[2];
    if (reserva[2] == -1){
        exit(1);
    }
    sprintf(choiceDest, "%d", reserva[2]);
    printf("Ruta: %s", choiceDest);
    send(mi_socket, choiceDest, strlen(choiceDest), 0);

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
