#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h> 
#include <arpa/inet.h>
#define SOGLIA "3"

void invia_soglia(int socket);
