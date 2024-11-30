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
const char *background = "#641e16";
const char *color = "white";
int descuento[2] = {0, 0}; // Descuento acumulado: [0] child/old, [1] vacation
const int desChild = 10;   // Porcentaje
const int desOld = 15;
GtkLabel *price;
GtkLabel *desc;
GtkLabel *total;
GtkCheckButton *checkChild;
GtkCheckButton *checkOld;

// Controlador de reserva [linea, ruta, estado, horario, asiento]
int reserva[4] = {-1,-1,-1,-1};
// Asientos
int asientos[10];
double costos[10];
double totalTicket;

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
// Callback para el boton
void on_button_clicked_dest(GtkButton *button, char *buffer) {
    int selection = gtk_combo_box_get_active(GTK_COMBO_BOX(comboBox));
    // printf("posicion %d", selection);
    reserva[2] = selection;
    gtk_widget_hide(window);
    gtk_main_quit();
}

void destinationsView(int argc, char *argv[], char *buffer, char **ESTADO, int num_estados) {
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

    // Obtener el combo box para la selección de destinos
    comboBox = GTK_COMBO_BOX_TEXT(gtk_builder_get_object(builder, "destinations_list"));
    if (!comboBox) {
        g_error("Error: No se pudo cargar el combobox.");
    }

    // Rellenar el combo box con los estados
    for (int i = 0; i < num_estados; i++) {
        gtk_combo_box_text_append_text(comboBox, ESTADO[i]);
    }

    // Seleccionar el primer elemento del combo box por defecto
    gtk_combo_box_set_active(GTK_COMBO_BOX(comboBox), 0);

    // Obtener botón continuar o aceptar
    button_ACCEPT = GTK_BUTTON(gtk_builder_get_object(builder, "continue"));
    if (!button_ACCEPT) {
        g_error("Error: No se pudo cargar el botón 'continue'.");
    }

    // Conectar el botón "Aceptar" con la función de callback
    g_signal_connect(button_ACCEPT, "clicked", G_CALLBACK(on_button_clicked_dest), buffer);

    // Conectar la señal de cierre de ventana para salir del bucle GTK
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Mostrar ventana principal
    gtk_widget_show_all(window);

    // Iniciar el bucle principal de GTK
    gtk_main();
}

void on_button_clicked_sche(GtkButton *button, char *buffer) {
    int selection = gtk_combo_box_get_active(GTK_COMBO_BOX(comboBox));
    reserva[3] = selection;
    gtk_widget_hide(window);
    gtk_main_quit();
}

void scheduleView(int argc, char *argv[], char *buffer, char **HORARIO, int num_horarios, int flag) {
    // Definiendo los componentes de la GUI
    GtkBuilder *builder;
    GtkButton *button_ACCEPT;

    // Inicializar GTK
    gtk_init(&argc, &argv);

    // Cargar archivo Glade
    builder = gtk_builder_new_from_file("./views/schedule.glade");

    // Obtener ventana principal
    window = GTK_WIDGET(gtk_builder_get_object(builder, "scheWindow"));
    if (!window) {
        g_error("Error: No se pudo cargar la ventana principal.");
    }

    // Obtener el combo box para la selección de los horarios
    comboBox = GTK_COMBO_BOX_TEXT(gtk_builder_get_object(builder, "schedule_list"));
    if (!comboBox) {
        g_error("Error: No se pudo cargar el combobox.");
    }

    if (flag){
        GtkWidget *messageError;
        messageError = GTK_WIDGET(gtk_builder_get_object(builder, "message"));
        if (!messageError) {
        g_error("Error: No se pudo cargar el label de error");
        }

        gtk_label_set_text(GTK_LABEL(messageError), "No hay asientos disponibles\nSeleccione otro horario");
    }
    

    // Rellenar el combo box con los horarios
    for (int i = 0; i < num_horarios; i++) {
        gtk_combo_box_text_append_text(comboBox, HORARIO[i]);
    }

    // Seleccionar el primer elemento del combo box por defecto
    gtk_combo_box_set_active(GTK_COMBO_BOX(comboBox), 0);

    // Obtener botón continuar o aceptar
    button_ACCEPT = GTK_BUTTON(gtk_builder_get_object(builder, "continue"));
    if (!button_ACCEPT) {
        g_error("Error: No se pudo cargar el botón 'continue'.");
    }

    // Conectar el botón "Aceptar" con la función de callback
    g_signal_connect(button_ACCEPT, "clicked", G_CALLBACK(on_button_clicked_sche), buffer);

    // Conectar la señal de cierre de ventana para salir del bucle GTK
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Mostrar ventana principal
    gtk_widget_show_all(window);

    // Iniciar el bucle principal de GTK
    gtk_main();
}

void procesar_cadena(char *cadena, char ***estados, int *num_estados, const char *delimitador) {
    *num_estados = 0;
    *estados = NULL; // Inicializar el puntero a NULL

    char *token = strtok(cadena, delimitador);
    while (token != NULL) {
        *estados = realloc(*estados, (*num_estados + 1) * sizeof(char *)); // Redimensionar memoria
        if (*estados == NULL) {
            perror("Error al asignar memoria");
            exit(1);
        }

        (*estados)[*num_estados] = malloc(strlen(token) + 1); // Reservar memoria para el estado
        if ((*estados)[*num_estados] == NULL) {
            perror("Error al asignar memoria para estado");
            exit(1);
        }

        strcpy((*estados)[*num_estados], token); // Copiar el token
        (*num_estados)++; // Incrementar el contador de estados
        token = strtok(NULL, delimitador); // Obtener el siguiente token
    }
}

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
    builder = gtk_builder_new_from_file("./views/seats.glade");

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

void changeValues() {
    int priceTicket = reserva[0] * reserva[2] * 10 + 40; // Calcular precio base
    int descTicket = descuento[0] + descuento[1];        // Calcular descuento acumulado
    totalTicket = priceTicket * (1 - (descTicket / 100.0));

    char priceText[50], descText[50], totalText[50];
    snprintf(priceText, sizeof(priceText), "$ %d", priceTicket);
    snprintf(descText, sizeof(descText), "$ %d%%", descTicket);
    snprintf(totalText, sizeof(totalText), "$ %.2f", totalTicket);

    gtk_label_set_text(price, priceText);
    gtk_label_set_text(desc, descText);
    gtk_label_set_text(total, totalText);
}

// Callback para el botón
void on_button_clicked_conf(GtkButton *button, gpointer data) {
    descuento[0] = 0;
    gtk_widget_hide(window);
    gtk_main_quit();
}

void on_checkbutton_toggled(GtkCheckButton *check, gpointer user_data) {
    const char *type = (const char *)user_data;

    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(check))) {
        if (strcmp(type, "child") == 0) {
            descuento[0] = desChild; // Descuento infantil
            gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(checkOld), FALSE);
        } else if (strcmp(type, "old") == 0) {
            descuento[0] = desOld; // Descuento para personas mayores
            gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(checkChild), FALSE); 
        }
    } else {
        descuento[0] = 0; // Restablecer descuento
    }
    g_signal_connect(checkChild, "toggled", G_CALLBACK(on_checkbutton_toggled), "child");
    g_signal_connect(checkOld, "toggled", G_CALLBACK(on_checkbutton_toggled), "old");   
    changeValues();
}

void confirmationView(int argc, char *argv[], char *buffer, int vacation, int numSeat, int vacationValue) {
    // Inicializar GTK
    gtk_init(&argc, &argv);

    // Cargar archivo Glade
    GtkBuilder *builder = gtk_builder_new_from_file("./views/confirmation.glade");
    GtkLabel *message;
    // Obtener ventana principal
    window = GTK_WIDGET(gtk_builder_get_object(builder, "confirmation"));
    if (!window) {
        g_error("Error: No se pudo cargar la ventana principal.");
    }

    // Obtener componentes de la interfaz
    GtkHeaderBar *header = GTK_HEADER_BAR(gtk_builder_get_object(builder, "header"));
    char title[50];
    snprintf(title, sizeof(title), "Asiento %d", numSeat);
    gtk_header_bar_set_title(header, title);

    checkChild = GTK_CHECK_BUTTON(gtk_builder_get_object(builder, "checkChild"));
    checkOld = GTK_CHECK_BUTTON(gtk_builder_get_object(builder, "checkOld"));
    message = GTK_LABEL(gtk_builder_get_object(builder, "vacacional"));
    GtkButton *button_Accept = GTK_BUTTON(gtk_builder_get_object(builder, "continuar"));
    price = GTK_LABEL(gtk_builder_get_object(builder, "precio"));
    desc = GTK_LABEL(gtk_builder_get_object(builder, "descuento"));
    total = GTK_LABEL(gtk_builder_get_object(builder, "total"));

    if (!checkChild || !checkOld || !button_Accept || !price || !desc || !total) {
        g_error("Error: No se pudieron cargar todos los componentes de la interfaz.");
    }

    // Asignar señales a los botones
    g_signal_connect(button_Accept, "clicked", G_CALLBACK(on_button_clicked_conf), NULL);
    g_signal_connect(checkChild, "toggled", G_CALLBACK(on_checkbutton_toggled), "child");
    g_signal_connect(checkOld, "toggled", G_CALLBACK(on_checkbutton_toggled), "old");

    if (vacation){
        // Inicializar valores
        descuento[1] = vacationValue; // Descuento por vacaciones
        gtk_label_set_text(message, "Descuento por periodo vacacional");
    }
    changeValues();

    // Mostrar ventana principal
    gtk_widget_show_all(window);

    // Iniciar el bucle principal de GTK
    gtk_main();
}

int main(int argc, char *argv[]) {
    int mi_socket, tam, numbytes, numEst, disp;
    char buffer[SIZE] = {0};
    char **estados = NULL; // Apuntador dinámico para los estados
    char **horarios = NULL; // Apuntador dinámico para los estados
    struct sockaddr_in mi_estructura;
    char choiceSche[2], choiceLine[2], choiceRoute[2], choiceDest[2]; 

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
    // Seleccion de linea de autobus
    linesView(argc, argv);
    if (reserva[0] == -1){
        exit(1);
    }
    sprintf(choiceLine, "%d", reserva[0]);
    printf("Linea: %s", choiceLine);
    send(mi_socket, choiceLine, strlen(choiceLine), 0);

    // Seleccion de rutas
    routesView(argc, argv);
    if (reserva[1] == -1){
        exit(1);
    }
    sprintf(choiceRoute, "%d", reserva[1]);
    printf("Ruta: %s", choiceRoute);
    send(mi_socket, choiceRoute, strlen(choiceRoute), 0);

    // Recibir y mostrar los estados disponibles para la ruta seleccionada
    // numbytes = recv(mi_socket, buffer, SIZE - 1, 0);
    // buffer[numbytes] = '\0';
    // printf("\n Cantidad de estados %s\n", buffer); // Imprimir la cantidad de estados a recibir
    // numEst = atoi(buffer);

    // Recibir los estados concatenados
    numbytes = recv(mi_socket, buffer, SIZE - 1, 0);
    buffer[numbytes] = '\0';
    printf("\nEstados recibidos (raw): %s\n", buffer);

    // Procesar cadena
    int totalEstados = 0;
    procesar_cadena(buffer, &estados, &totalEstados, "|");
    destinationsView(argc, argv, buffer, estados, totalEstados);

    if (reserva[2] == -1){
        exit(1);
    }
    sprintf(choiceDest, "%d", reserva[2]);
    printf("Estado: %s", choiceDest);
    send(mi_socket, choiceDest, strlen(choiceDest), 0);

    // Seleccion de horarios
    // printf("Llego");
    // numbytes = recv(mi_socket, buffer, SIZE - 1, 0);
    // buffer[numbytes] = '\0';
    // printf("\n Cantidad de horarios %s\n", buffer); // Imprimir la cantidad de estados a recibir
    // numEst = atoi(buffer);

    numbytes = recv(mi_socket, buffer, SIZE - 1, 0);
    buffer[numbytes] = '\0';
    printf("\nHorarios recibidos (raw): %s\n", buffer);

    int totalHorarios = 0;
    procesar_cadena(buffer, &horarios, &totalHorarios, "|");
    int flag = 0;
    while (1){
        scheduleView(argc, argv, buffer, horarios, totalHorarios, flag);
        if (reserva[3] == -1){
            exit(1);
        }
        sprintf(choiceSche, "%d", reserva[3]);
        printf("Horario: %s", choiceSche);
        send(mi_socket, choiceSche, strlen(choiceSche), 0);

        // Confirmacion de que hay asientos disponibles
        recv(mi_socket, &disp, sizeof(disp), 0);
        if (disp){
            printf("\nSi hay asientos\n");
            // Recibir de asientos disponibles
            recv(mi_socket, asientos, 10 * sizeof(int), 0);
            printf("Arreglo recibido:\n");

            for (int i = 0; i < 10; i++){
                printf("Asiento %d esta %d\n", i, asientos[i]);
            }
            break;
        }
        flag = 1;
    }
    seatsView(argc, argv, buffer);
    printf("\n");
    for (int i = 0; i < 10; i++){
        printf("%d ", asientos[i]);
    }
    send(mi_socket, asientos, sizeof(int) * 10, 0);
    // Recibir si es temporada vacacional y el porcentaje de descuento
    int vac[2];
    recv(mi_socket, &vac, sizeof(vac), 0);

    for (int i = 0; i < 10; i++){
        if (asientos[i] == -1){
            confirmationView(argc, argv, buffer, vac[0], i+1, vac[1]);
            costos[i] = totalTicket;
            //printf("\nCosto del asiento %d es %.2f", i+1, costos[i]);
        }   
    }

    send(mi_socket, costos, sizeof(double) * 10, 0);

    // printf("\nEstados procesados:\n");
    // for (int i = 0; i < totalEstados; i++) {
    //     printf("Estado %d: %s\n", i + 1, estados[i]);
    //     free(estados[i]); // Liberar memoria de cada estado
    // }

    free(estados); // Liberar memoria del arreglo de punteros

    // Cerrar socket
    close(mi_socket);
    return 0;
}





    // // Destinos
    // destinationsView(argc, argv, buffer, estados, numEst);
    // char choiceDest[2];
    // if (reserva[2] == -1){
    //     exit(1);
    // }
    // sprintf(choiceDest, "%d", reserva[2]);
    // printf("Ruta: %s", choiceDest);
    // send(mi_socket, choiceDest, strlen(choiceDest), 0);

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