#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "proxy.h"

static int searchDomain(char *request, char *domain, size_t domainLen);
static int changeHost(char *request, char *domain);

int readRequest(char *request, int client_fd) {
    char domain[256] = {0};
    if (searchDomain(request, domain, sizeof(domain)) == 1) return 1;
    
    if (changeHost(request, domain) == 1) return 1;

    printf("This is the host: %s \n ", request);

    return 0;
}


int sendRequest(const char *request, int client_fd) {
    return 0;
}

static int searchDomain(char *request, char *domain, size_t domainLen) {
    const char *dom = request + 4;
    
    // Get the start of the domain
    const char *temp = strstr(dom, "//");
    if (!temp) return 1;
    dom = temp + 2;
    
    // Set the end of the domain
    char *end = strchr(dom, '/');
    if (!end) return 1;

    size_t len = end - dom;
    if (len >= domainLen) return 1;
    strncpy(domain, dom, len);

    printf("This is the domain: %s \n\n", domain);
    return 0;
}

static int changeHost(char *request, char *domain) {
    char *newReq[3000] = {0};
    // Insserting the domain
    char *host = strstr(request, "Host: ");
    if (!host) return 1;

    char *end = strchr(host, '\n');

    size_t len = host - request;
    size_t lenEnd = len + strlen(end);
    
    if (lenEnd >= sizeof(newReq)) return 1;

    strncpy(newReq, request, len);
    strncpy(newReq, domain, lenHost);
    strncpy(newReq, end, lenEnd);
    printf("The new: %s \n", newReq);
    return 0;
}
