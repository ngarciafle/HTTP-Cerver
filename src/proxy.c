#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "proxy.h"

static int searchDomain(char *request, char *domain, size_t domainLen);
static int changeHost(char *request, char *domain, char *newReq, size_t lenNewReq, char *originalHost);
static int cleanRoute(char *newReq, size_t lenDom);

int readRequest(char *request, int client_fd, char *originalHost) {
    char domain[256] = "Host: ";
    char newReq[3000] = {0};
    if (searchDomain(request, domain + 6, sizeof(domain)) == 1) return 1;
    
    if (changeHost(request, domain, newReq, sizeof(newReq), originalHost) == 1) return 1;

    if (cleanRoute(newReq, strlen(domain)) == 1) return 1;

    printf("This is the host: %s \n ", newReq);

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

    // printf("This is the domain: %s \n\n", domain);
    return 0;
}

static int changeHost(char *request, char *domain, char *newReq, size_t lenNewReq, char *originalHost) {
    // Insserting the domain
    char *host = strstr(request, "Host: ");
    if (!host) return 1;

    char *end = strchr(host, '\n');

    //Save original host
    size_t len = end - host;
    originalHost = strncpy(originalHost, host, len);
    originalHost[len] = '\0';
    // printf("The original host: %s \n", originalHost);


    len = host - request;
    size_t lenEnd = len + strlen(end);
    size_t lenHost = strlen(domain);
    
    if (lenEnd >= lenNewReq) return 1;

    char *tmp = newReq;
    strncpy(tmp, request, len);
    tmp += len;
    
    strncpy(tmp, domain, lenHost);
    tmp += lenHost;

    strncpy(tmp, end, lenEnd);
    printf("The new: %s \n\n", newReq);
    return 0;
}

static int cleanRoute(char *newReq, size_t lenDom) {
    char *start = newReq + 4;
    char *end = strstr(start, "/ ");
    memmove(start, end, strlen(end) + 1);
    // printf("Cleaned: %s \n", newReq);
    return 0;
}
