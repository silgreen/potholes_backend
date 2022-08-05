#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h> 
#include <arpa/inet.h>

typedef struct EventoClient {
    long latitudine;
    long longitudine;
    char *client_nickname;
    time_t timestamp;
    double valore;
}EventoClient;
