#ifndef PROXY_H
#define PROXY_H

int readRequest(char *request, int client_fd, char *originalHost);
int sendRequest(const char *request, int client_fd);

#endif