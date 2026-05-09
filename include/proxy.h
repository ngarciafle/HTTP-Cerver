#ifndef
#DEFINE PROXY.H

int readRequest(char *request, int client_fd);
int sendRequest(const char *request, int client_fd);

#endif