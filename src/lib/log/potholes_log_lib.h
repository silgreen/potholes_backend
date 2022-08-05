#include <time.h>

enum operazione {
    connessione,disconnessione,richiesta //vari tipi di richeste da implementare
};

typedef struct potholes_log
{
    time_t data;
    operazione op;
    char *client;
}potholes_log;

void print_log();
potholes_log init_log(time_t t,operazione op,char *client);
void log(potholes_log *log);
int check_operazione(potholes_log *log);