#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define SIZE 255
#define MAX_SEATS 10
// Estado de la reserva
int reserva[5] = {-1,-1,-1,-1, -1};
// Asientos disponibles
int asientos[MAX_SEATS] = {1,1,1,1,1,1,1,1,1,1};
// Descuento vacacional
int vacational[2] = {1,5};
double costos[10];
const char *lineas[] = {"ADO", "FUTURA", "ESTRELLA BLANCA", "PREMIERE PLUS"};
const char *region[] = {"NORTE", "SUR", "ESTE", "OESTE"};
// NORTE ES 1, SUR ES 2, ESTE ES 3, OESTE ES 4
const char *NORTE[] = {"Baja California", "Baja California Sur", "Sonora", "Chihuahua", "Coahuila", "Nuevo León", "Durango", "Zacatecas", "San Luis Potosi"};
const char *SUR[] = {"Chiapas", "Tabasco", "Campeche", "Yucatán", "Quintana Roo", "Oaxaca"};
const char *ESTE[] = {"Tamaulipas", "Veracruz", "Tlaxcala", "Puebla"};
const char *OESTE[] = {"Sinaloa", "Nayarit", "Jalisco", "Colima", "Michoacán", "Guanajuato", "Aguascalientes", "Ciudad de México", "Estado de México", "Morelos"};
const char *HORARIOS[] = {"8:00 AM", "10 AM", "12 PM", "3 PM", "6 PM"};
const char *registroReservas = "reservas.txt";

void construir_cadena(char *buffer, const char *estados[], int num_estados, const char *delimitador) {
    buffer[0] = '\0'; // Asegurarse de limpiar el buffer
    for (int i = 0; i < num_estados; i++) {
        strcat(buffer, estados[i]); // Concatenar el estado al buffer
        if (i < num_estados - 1) {  // No agregar delimitador al último estado
            strcat(buffer, delimitador);
        }
    }
}

// Función para leer el archivo y comparar
void search(const char *nombreArchivo) {
    FILE *archivo = fopen(nombreArchivo, "r");
    if (!archivo) {
        perror("Error al abrir el archivo");
        exit(EXIT_FAILURE);
    }

    char linea[256]; // Buffer para almacenar una línea del archivo
    int numeros[5];  // Arreglo para almacenar los números de cada línea

    while (fgets(linea, sizeof(linea), archivo)) {
        // Convertir la línea en números enteros
        if (sscanf(linea, "%d %d %d %d %d", &numeros[0], &numeros[1], &numeros[2], &numeros[3], &numeros[4]) == 5) {
            // Comparar los primeros 4 números con el arreglo global
            int coincidencia = 1;
            for (int i = 0; i < 4; i++) {
                if (numeros[i] != reserva[i]) {
                    coincidencia = 0;
                    break;
                }
            }

            // Imprimir "Encontrado" si todos coinciden
            if (coincidencia) {
                asientos[numeros[4]] = 0;
            }
        } else {
            printf("Línea no válida: %s", linea);
        }
    }

    fclose(archivo);
}

void registerTicket(const char *nombreArchivo){
    // Abrir el archivo en modo "append" para agregar contenido
    FILE *archivo = fopen(registroReservas, "a");
    if (archivo == NULL) {
        perror("Error al abrir el archivo");
        exit(-1);
    }
    // Escribir los elementos del arreglo en el archivo
    for (int i = 0; i < 5; i++) {
        fprintf(archivo, "%d ", reserva[i]);
    }
    fprintf(archivo, "\n"); // Nueva línea al final

    // Cerrar el archivo
    fclose(archivo);
}

void imprimir_linea(const char *texto, int ancho_total) {
    int longitud_texto = strlen(texto);
    int espacios_derecha = (ancho_total - longitud_texto - 2) / 2; // Resto para bordes
    int espacios_izquierda = ancho_total - longitud_texto - 2 - espacios_derecha;

    printf("*%*s%s%*s*\n", espacios_izquierda, "", texto, espacios_derecha, "");
}

// Función para generar el ticket
void generar_ticket(const char *linea_autobus, const char *region, const char *estado_destino, const char *horario, 
                    int asientos[], double costos[]) {
    const int ancho_ticket = 46;
    double total = 0.0;

    // Encabezado
    printf("\n%.*s\n", ancho_ticket, "**********************************************");
    imprimir_linea("TICKET DE COMPRA", ancho_ticket);
    printf("%.*s\n", ancho_ticket, "**********************************************");

    // Información del viaje
    char info[ancho_ticket];
    snprintf(info, sizeof(info), "Linea de autobus: %s", linea_autobus);
    imprimir_linea(info, ancho_ticket);

    snprintf(info, sizeof(info), "Region: %s", region);
    imprimir_linea(info, ancho_ticket);

    snprintf(info, sizeof(info), "Estado destino: %s", estado_destino);
    imprimir_linea(info, ancho_ticket);

    snprintf(info, sizeof(info), "Horario: %s", horario);
    imprimir_linea(info, ancho_ticket);

    // Detalle de los asientos seleccionados
    printf("%.*s\n", ancho_ticket, "**********************************************");
    imprimir_linea("Asiento(s) seleccionados:", ancho_ticket);
    for (int i = 0; i < MAX_SEATS; i++) {
        if (asientos[i] == -1) {
            snprintf(info, sizeof(info), "Asiento %d: $%.2f", i + 1, costos[i]);
            imprimir_linea(info, ancho_ticket);
            total += costos[i];
        }
    }

    // Total a pagar
    printf("%.*s\n", ancho_ticket, "**********************************************");
    snprintf(info, sizeof(info), "Total a pagar: $%.2f", total);
    imprimir_linea(info, ancho_ticket);
    printf("%.*s\n", ancho_ticket, "**********************************************");

    // Mensaje final
    imprimir_linea("¡Gracias por su compra!", ancho_ticket);
    printf("%.*s\n", ancho_ticket, "**********************************************");
}


int main(int argc, char *argv[]) {
    int disponibleHorario = 0;
    int mi_socket, nuevo, tam;
    struct sockaddr_in mi_estructura;
    char buffer[SIZE];
    const char *lin, *reg, *est, *hor;

    // Configuración del servidor
    mi_estructura.sin_family = AF_INET;
    mi_estructura.sin_port = htons(8080);
    mi_estructura.sin_addr.s_addr = INADDR_ANY;
    memset(&(mi_estructura.sin_zero), '\0', 8);

    mi_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (mi_socket == -1) {
        perror("Error al crear el socket");
        exit(1);
    }

    tam = sizeof(struct sockaddr);
    if (bind(mi_socket, (struct sockaddr *)&mi_estructura, tam) == -1) {
        perror("Error en bind");
        exit(1);
    }

    listen(mi_socket, 5); // Poner el socket en escucha

    while (1) {
        nuevo = accept(mi_socket, (struct sockaddr *)&mi_estructura, &tam);
        if (nuevo == -1) {
            perror("Error en accept");
            continue;
        }

        if (fork() == 0) { // Proceso hijo
            close(mi_socket);
            // Enviar el permiso para desplegar el sistema
            char permiso[] = "1";
            send(nuevo, permiso, strlen(permiso), 0);

            // Estado de reserva
            for (int i = 0; i < 4; i++){
                reserva[i] = -1;
            }
            disponibleHorario = 0;
            // Recibir la selección de la línea de autobuses
            int seleccion = recv(nuevo, buffer, SIZE - 1, 0);
            buffer[seleccion] = '\0';
            printf("El cliente seleccionó la línea de autobuses: %s\n", buffer);
            reserva[0] = atoi(buffer); 
            lin = lineas[reserva[0]-1];
            // Recibir la selección de la ruta
            int seleccionRuta = recv(nuevo, buffer, SIZE - 1, 0);
            buffer[seleccionRuta] = '\0';
            printf("El cliente seleccionó la ruta: %s\n", buffer);
            reserva[1] = atoi(buffer);
            reg = region[reserva[1]-1];
            int num_estados = 0;
            // Enviar los estados para la ruta seleccionada
            switch (reserva[1]) {
                case 1: // NORTE
                    num_estados = sizeof(NORTE) / sizeof(NORTE[0]);
                    construir_cadena(buffer, NORTE, num_estados, "|");
                    //printf("\n%s\n", buffer);
                    send(nuevo, buffer, strlen(buffer), 0);
                    break;
                case 2: // SUR
                    num_estados = sizeof(SUR) / sizeof(SUR[0]);
                    construir_cadena(buffer, SUR, num_estados, "|");
                    //printf("\n%s\n", buffer);
                    send(nuevo, buffer, strlen(buffer), 0);
                    break;
                case 3: // ESTE
                    num_estados = sizeof(ESTE) / sizeof(ESTE[0]);
                    // Envio de los estados
                    construir_cadena(buffer, ESTE, num_estados, "|");
                    //printf("\n%s\n", buffer);
                    send(nuevo, buffer, strlen(buffer), 0);
                    break;
                case 4: // OESTE
                    num_estados = sizeof(OESTE) / sizeof(OESTE[0]);

                    // Envio de los estados
                    construir_cadena(buffer, OESTE, num_estados, "|");
                    //printf("\n%s\n", buffer);
                    send(nuevo, buffer, strlen(buffer), 0);
                    break;
                default:
                    exit(0);
                    break;
            }
            // // Recibir la selección del estado
            int seleccionEstado = recv(nuevo, buffer, SIZE - 1, 0);
            buffer[seleccionEstado] = '\0';
            reserva[2] = atoi(buffer);
            printf("El cliente seleccionó el estado: %d\n", reserva[2]);

            switch (reserva[1]){
            case 1: // Caso del NORTE
                est = NORTE[reserva[2]];
                break;

            case 2: // Caso del SUR
                est = SUR[reserva[2]];
                /* code */
                break;

            case 3: // Caso del ESTE
                est = ESTE[reserva[2]];
                /* code */
                break;
            case 4: // Caso del OESTE
                est = OESTE[reserva[2]];
                /* code */
                break;
            default:
                break;
            }

            // Enviar los horarios disponibles
            int num_horarios = sizeof(HORARIOS) / sizeof(HORARIOS[0]);
            construir_cadena(buffer, HORARIOS, num_horarios, "|");
            //printf("\n%s\n", buffer);
            send(nuevo, buffer, strlen(buffer), 0);
            int seleccionHorario, i;
            while (1){
                // // Recibir la selección del horario del cliente
                seleccionHorario = recv(nuevo, buffer, sizeof(buffer) - 1, 0);
                buffer[seleccionHorario] = '\0';
                reserva[3] = atoi(buffer);
                //printf("El cliente seleccionó el horario: %d\n", reserva[3]);

                // Verificar asientos
                search(registroReservas);
                for (i = 0; i < 10; i++){
                    //printf("Asiento %d esta %d\n", i, asientos[i]);
                    if (asientos[i] == 1){
                        disponibleHorario = 1;
                    }
                }
                send(nuevo, &disponibleHorario, sizeof(disponibleHorario), 0);
                if (disponibleHorario){
                    send(nuevo, asientos, sizeof(int) * 10, 0);
                    break;
                } else {
                    // Restablece el arreglo
                    for (i = 0; i < 10; i++){
                        asientos[i] = 1;
                    }
                }

            }
            // Recibimos los lugares apartados
            recv(nuevo, asientos, 10 * sizeof(int), 0);
            //printf("\n");
            hor = HORARIOS[reserva[3]];
            // for (int i = 0; i < MAX_SEATS; i++){
            //     printf("%d ", asientos[i]);
            // }
            // // Confirmación al cliente
            send(nuevo, &vacational, sizeof(vacational), 0);

            // Recibir los costos
            recv(nuevo, costos, 10 * sizeof(double), 0);
            for (int i = 0; i < 10; i++){
                printf("%.2f\n", costos[i]);
            }

            // registrar los asientos
            for (int i = 0; i < 10; i++){
                if (asientos[i] == -1){
                    reserva[4] = i;
                    registerTicket(registroReservas);
                }
            }
            
            printf("\n\n\n");
            generar_ticket(lin, reg, est, hor, asientos, costos);
            snprintf(buffer, sizeof(buffer), "%s|%s|%s|%s", lin, reg, est, hor);
            send(nuevo, buffer, strlen(buffer), 0);

            close(nuevo);
            exit(0);
        } else { // Proceso padre
            close(nuevo);
        }
    }
    return 0;
}