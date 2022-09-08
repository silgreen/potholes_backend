#include "../dependencies.h"
#include "Posizione.h"
#include <sys/socket.h>
#include <pthread.h>
#define BUCA "Buca\n"
#define DOSSO "Dosso\n"

/* Definizione strutture */
typedef struct Evento_struct 
{
    char nickname[BUFSIZ];
    char tipo_evento[5];
    Posizione posizione;
}Evento_struct;

typedef struct Evento_struct *Evento;

typedef struct EventoList_struct 
{
    Evento event;
    struct EventoList_struct *next;
}EventoList_struct;

typedef struct EventoList_struct *EventoList;


typedef struct SendData
{
    int socket;
    Posizione posizione;
    char client[BUFSIZ];
}SendData;

typedef struct SendData *SendDataThread;

/***********************************************************/

/* Definizione metodi */
Evento creaEvento(char *tipo_evento,char *nickname,Posizione posizione);
Evento stringToEvento(char data[][BUFSIZ]);
EventoList creaEventoList(Evento evento);
EventoList inserisciEvento(EventoList list,Evento evento);
EventoList mostraEventiViciniDaFile(EventoList resultList,Posizione posizione);
SendDataThread creaSendDataThread(char *client,Posizione pos,int socket);
char* calcola_evento(double delta); 
char* eventoToString(Evento evento,char *result);
void *mostraEventiViciniThread(void *arg);
void printEvento(Evento evento);
void printEventoList(EventoList list);
void deallocaLista(EventoList list);
void serializzaEventList(EventoList eventList,char *result);