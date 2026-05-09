#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "server.h"

int start_server(int port) {
    printf("Starting server on port %d...\n", port);
    int server_fd, conection;
    struct sockaddr_in address;

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) {

        return -1;
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);
     
    int opt = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    conection = bind(server_fd, (struct sockaddr *)&address, sizeof(address));
    if (conection == -1) {
        fprintf(stderr, "Port %d was busy", port);
        return -1;
    }
    printf("Server is listening\n");
    
    listen(server_fd, 2);

    int client_fd = accept(server_fd, NULL, NULL);
    char buffer[3000] = {0};
    read(client_fd, buffer, sizeof(buffer) - 1);
    printf("Message: %s \n", buffer);

    char *response = "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 5\n\nHi!!";
    write(client_fd, response, strlen(response));

    close(client_fd);

    return 0;
}
