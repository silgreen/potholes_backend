#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "../dependencies.h"
#include "../struct/Evento.h"
#define SOGLIA "3"

void invia_soglia(int socket);
char* calcola_evento(double delta); 
void init_address(struct sockaddr_in *address);

