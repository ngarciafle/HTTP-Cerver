#ifndef PROXY_H
#define PROXY_H

int readRequest(char *request, int client_fd, char *originalHost, char *domain);
int sendRequest(const char *request, int dest_fd, int client_fd, char *response, char *domain);

#endif