#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h> 
#include <arpa/inet.h>
#include "../struct/Evento.h"
#define SOGLIA "3"
#define BUCA "Buca"
#define DOSSO "Dosso"

void invia_soglia(int socket);
char* calcola_evento(double delta);
char* mostra_eventi_vicini(Evento event); 

