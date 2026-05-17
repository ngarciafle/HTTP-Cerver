#ifndef PROXY_H
#define PROXY_H

int readRequest(char *request, int client_fd, char *originalHost, char *domain, size_t domainLen, char *newReq, size_t lenNewReq);
int sendRequest(const char *request, int dest_fd, int client_fd, char *response, char *domain);
int handleConnect(int client_fd, char *request);

#endif