#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include "server.h"
#include "proxy.h"

static int connectTo(const char *domain, const char *port);

int start_server(int port) {
    printf("Starting server on port %d...\n", port);
    int server_fd, conection;
    struct sockaddr_in address;

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) return -1;

    int opt = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);     

    conection = bind(server_fd, (struct sockaddr *)&address, sizeof(address));
    if (conection == -1) {
        fprintf(stderr, "Port %d was busy", port);
        close(server_fd);
        return -1;
    }
    printf("Server is listening\n");
    listen(server_fd, 10);

    while(1) {
        int client_fd = accept(server_fd, NULL, NULL);
        if (client_fd == -1) {
            printf("Error accepting connection\n");
            continue;
        }

        char buffer[3000] = {0};
        char originalHost[256] = {0};
        char response[3000] = {0};
        char domain[256] = "Host: ";
        char newReq[3000] = {0};


        int bytes = read(client_fd, buffer, sizeof(buffer) - 1);
        if (bytes <= 0) {
            printf("Error reading from client: %d\n", bytes);
            close(client_fd);
            continue;
        }

        printf("Message: %s \n", buffer);

        if (readRequest(buffer, client_fd, originalHost, domain, sizeof(domain), newReq, sizeof(newReq)) == 1) {
            printf("There was an error while processing the request");
            close(client_fd);
            return 1;
        }
        
        int dest_fd = connectTo(domain+6, "80");
        if (dest_fd == -1) {
            printf("There was an error while connecting to the server");
            close(client_fd);
            return 1;
        }

        if (sendRequest(buffer, dest_fd, client_fd, response, domain) == 1) {
            printf("There was an error while making the request");
            close(client_fd);
            return 1;
        }
    
        write(client_fd, response, strlen(response));
        close(client_fd);
    }
    

    close(server_fd);

    return 0;
}

static int connectTo(const char *domain, const char *port) {
    struct addrinfo hints = {0}, *res;
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    if (getaddrinfo(domain, port, &hints, &res) != 0) return 1;

    int fd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    if (fd == -1) return -1;

    if (connect(fd, res->ai_addr, res->ai_addrlen) == -1) {
        close(fd);
        freeaddrinfo(res);
        return -1;
    }

    freeaddrinfo(res);
    return fd;
}