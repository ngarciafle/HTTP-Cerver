#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "server.h"

int main() {
    int port = -1;
    printf("What port will you choose? (write a letter to exit) \n");
    while(1) {
        scanf("%d", &port);
        if (port < 0 || port > 65536) return 1;
        if (start_server(port) != 0) {
            fprintf(stderr, "Failed to start server on port %d\n", port);
        } 
    }
    return 0;
}