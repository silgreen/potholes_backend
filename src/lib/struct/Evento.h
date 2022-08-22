#include "../dependencies.h"
#include "Posizione.h"
#define BUCA "Buca"
#define DOSSO "Dosso"

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

/***********************************************************/

/* Definizione metodi */
Evento creaEvento(char *tipo_evento,char *nickname,Posizione posizione);
Evento stringToEvento(char data[][BUFSIZ],double *lat,double *lng,double *delta);
EventoList creaEventoList(Evento evento);
EventoList inserisciEvento(EventoList list,Evento evento);
EventoList mostraEventiVicini(EventoList evento_list,EventoList resultList,Posizione posizione);
char* calcola_evento(double delta); 
void printEvento(Evento evento);
void printEventoList(EventoList list);