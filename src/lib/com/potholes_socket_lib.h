#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "../dependencies.h"
#include "../struct/Evento.h"
#define SOGLIA "3"
#define BUCA "Buca"
#define DOSSO "Dosso"

void invia_soglia(int socket);
char* calcola_evento(double delta); 

