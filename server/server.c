#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define SIZE 255

// NORTE ES 1, SUR ES 2, ESTE ES 3, OESTE ES 4
const char *NORTE[] = {"Baja California", "Baja California Sur", "Sonora", "Chihuahua", "Coahuila", "Nuevo León", "Durango", "Zacatecas", "San Luis Potosi"};
const char *SUR[] = {"Chiapas", "Tabasco", "Campeche", "Yucatán", "Quintana Roo", "Oaxaca"};
const char *ESTE[] = {"Tamaulipas", "Veracruz", "Tlaxcala", "Puebla"};
const char *OESTE[] = {"Sinaloa", "Nayarit", "Jalisco", "Colima", "Michoacán", "Guanajuato", "Aguascalientes", "Ciudad de México", "Estado de México", "Morelos"};


int main(int argc, char *argv[]) {
    int mi_socket, nuevo, tam;
    struct sockaddr_in mi_estructura;
    char buffer[SIZE];

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

            // // Enviar el menú de líneas de autobuses
            // char menu[] = "Seleccione una central de autobuses:\n1. ADO\n2. FUTURA\n3. ESTRELLA BLANCA\n4. PREMIERE\n5. ESTRELLA ROJA\n";
            // send(nuevo, menu, sizeof(menu), 0);

            // Estado de reserva
            int reserva[4] = {-1,-1,-1,-1};
            // Recibir la selección de la línea de autobuses
            int seleccion = recv(nuevo, buffer, SIZE - 1, 0);
            buffer[seleccion] = '\0';
            printf("El cliente seleccionó la línea de autobuses: %s\n", buffer);
            reserva[0] = atoi(buffer);

            // Dependiendo de la selección, enviar las rutas disponibles
            // char *rutas;
            // if (opcion >= 1 && opcion <= 5) {
            //     rutas = "Rutas disponibles: 1. NORTE 2. SUR 3. ESTE 4. OESTE\n";
            // } else {
            //     rutas = "Opción inválida. Conexión cerrada.\n";
            //     send(nuevo, rutas, strlen(rutas), 0);
            //     close(nuevo);
            //     exit(0);
            // }
            // send(nuevo, rutas, strlen(rutas), 0);

            // Recibir la selección de la ruta
            int seleccionRuta = recv(nuevo, buffer, SIZE - 1, 0);
            buffer[seleccionRuta] = '\0';
            printf("El cliente seleccionó la ruta: %s\n", buffer);
            reserva[1] = atoi(buffer);
            int num_estados = 0;
            // Enviar los estados para la ruta seleccionada
            switch (reserva[1]) {
                case 1: // NORTE
                    num_estados = sizeof(NORTE) / sizeof(NORTE[0]);
                    snprintf(buffer, SIZE, "%d", num_estados);
                    send(nuevo, buffer, strlen(buffer), 0);

                    // Envio de los estados
                    for (int i = 0; i < num_estados; i++){
                        snprintf(buffer, SIZE, "%s", NORTE[i]); // Cada cadena seguida de '\n'
                        send(nuevo, buffer, strlen(buffer), 0);
                    }
                    
                    break;
                case 2: // SUR
                    num_estados = sizeof(SUR) / sizeof(SUR[0]);
                    snprintf(buffer, SIZE, "%d", num_estados);
                    send(nuevo, buffer, strlen(buffer), 0);

                    // Envio de los estados
                    for (int i = 0; i < num_estados; i++){
                        snprintf(buffer, SIZE, "%s", SUR[i]); // Cada cadena seguida de '\n'
                        send(nuevo, buffer, strlen(buffer), 0);
                    }
                    break;
                case 3: // ESTE
                    num_estados = sizeof(ESTE) / sizeof(ESTE[0]);
                    snprintf(buffer, SIZE, "%d", num_estados);
                    send(nuevo, buffer, strlen(buffer), 0);

                    // Envio de los estados
                    for (int i = 0; i < num_estados; i++){
                        snprintf(buffer, SIZE, "%s", ESTE[i]); // Cada cadena seguida de '\n'
                        send(nuevo, buffer, strlen(buffer), 0);
                    }
                    break;
                case 4: // OESTE
                    num_estados = sizeof(OESTE) / sizeof(OESTE[0]);
                    snprintf(buffer, SIZE, "%d", num_estados);
                    send(nuevo, buffer, strlen(buffer), 0);

                    // Envio de los estados
                    for (int i = 0; i < num_estados; i++){
                        snprintf(buffer, SIZE, "%s", OESTE[i]); // Cada cadena seguida de '\n'
                        send(nuevo, buffer, strlen(buffer), 0);
                    }
                    break;
                default:
                    exit(0);

                    break;
            }
            // send(nuevo, estados, strlen(estados), 0);
            // // Recibir la selección del estado
            int seleccionEstado = recv(nuevo, buffer, SIZE - 1, 0);
            buffer[seleccionEstado] = '\0';
            reserva[2] = atoi(buffer);
            printf("El cliente seleccionó el estado: %d\n", reserva[2]);

            // // Enviar los horarios disponibles
            // char horarios[] = "Seleccione un horario:\n1. 8 AM\n2. 10 AM\n3. 12 PM\n4. 3 PM\n5. 6 PM\n";
            // send(nuevo, horarios, strlen(horarios), 0);

            // // Recibir la selección del horario del cliente
            // int seleccionHorario = recv(nuevo, buffer, sizeof(buffer) - 1, 0);
            // buffer[seleccionHorario] = '\0';
            // printf("El cliente seleccionó el horario: %s\n", buffer);

            // // Confirmación al cliente
            // send(nuevo, "Su selección ha sido registrada. ¡Gracias!\n", 45, 0);
            printf("\nEl estado de la reserva es: ");
            for (int i = 0; i < 4; i++){
                printf("%d ", reserva[i]);
            }
            
            close(nuevo);
            exit(0);
        } else { // Proceso padre
            close(nuevo);
        }
    }
    return 0;
}