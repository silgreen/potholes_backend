#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <pthread.h>
#include "../dependencies.h"
#include "../struct/Evento.h"
#define SOGLIA "3"
#define REQ_SOGLIA "soglia"
#define REQ_LISTA "lista"
#define REQ_EVENTO "evento"

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void invia_soglia(int socket);
void init_address(struct sockaddr_in *address);
void *gestisci_richiesta(void *arg);
void deserialize_data(char data[][BUFSIZ],char *token);
void *insertEventoFile(void *arg);

