#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "server.h"

int start_server(int port) {
    printf("Starting server on port %d...\n", port);
    int server_fd, new_socket, conection;
    struct sockaddr_in address;

    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) {

        return -1;
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    conection = bind(server_fd, (struct sockaddr *)&address, sizeof(direction))
    if (conection == -1) {
        printf("Port %d was busy", port);
        return -1;
    }
    
    listen(server_fd, 2);

    int client_fd = listen(server_fd, NULL, NULL);
    char buffer[3000];
    read(client_fd, buffer, 3000);
    printf("Message: %s \n", buffer);

    return 0;
}
