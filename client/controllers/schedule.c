

void on_button_clicked_sche(GtkButton *button, char *buffer) {
    int selection = gtk_combo_box_get_active(GTK_COMBO_BOX(comboBox));
    printf("posicion %d", selection);
    reserva[2] = selection;
    gtk_widget_hide(window);
    gtk_main_quit();
}

void scheduleView(int argc, char *argv[], char *buffer, char **HORARIO, int num_horarios) {
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

    // Rellenar el combo box con los horarios
    for (int i = 0; i < num_estados; i++) {
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