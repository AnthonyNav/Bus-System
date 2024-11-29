#include <string.h>
#include <stdio.h>
#include <gtk/gtk.h>

GtkWidget *window;
int descuento[2] = {0, 0}; // Descuento acumulado: [0] child/old, [1] vacation
const int desChild = 10;   // Porcentaje
const int desOld = 15;

GtkLabel *price;
GtkLabel *desc;
GtkLabel *total;
GtkCheckButton *checkChild;
GtkCheckButton *checkOld;

int reserva[4] = {1, 1, 6, 3};

void changeValues() {
    int priceTicket = reserva[0] * reserva[2] * 10 + 40; // Calcular precio base
    int descTicket = descuento[0] + descuento[1];        // Calcular descuento acumulado
    double totalTicket = priceTicket * (1 - (descTicket / 100.0));

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
    GtkBuilder *builder = gtk_builder_new_from_file("../views/confirmation.glade");
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
        changeValues();
    }
    

    // Mostrar ventana principal
    gtk_widget_show_all(window);

    // Iniciar el bucle principal de GTK
    gtk_main();
}

int main(int argc, char *argv[]) {
    char buffer[255] = {0};
    int vacation = 1; // Ejemplo: descuento por vacaciones activado
    confirmationView(argc, argv, buffer, vacation, 3, 5);
    printf("%d   %d", descuento[0], descuento[1]);
    return 0;
}



