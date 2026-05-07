#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "server.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <port>\n", argv[0]);
        return 1;
    }
    int port = atoi(argv[1]);
    if (start_server(port) != 0) {
        fprintf(stderr, "Failed to start server on port %d\n", port);
        return 1;
    }
    return 0;
}