#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "proxy.h"

int readRequest(char *request, int client_fd) {
    const char *dom = request + 4;
    
    // Get the start of the domain
    const char *temp = strstr(dom, "//");
    if (!temp) return 1;
    dom = temp + 2;
    
    // Set the end of the domain
    char *end = strchr(dom, '/');
    if (!end) return 1;
    end[0] = '\0';

    printf("This is the domain: %s \n", dom);

    

    return 0;
}


int sendRequest(const char *request, int client_fd) {
    return 0;
}
