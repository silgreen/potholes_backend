#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <pthread.h>
#include "../dependencies.h"
#include "../struct/Evento.h"
#define SOGLIA "3"
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void invia_soglia(int socket);
char* calcola_evento(double delta); 
void init_address(struct sockaddr_in *address);

