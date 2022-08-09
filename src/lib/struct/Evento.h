#include "../dependencies.h"
#include "Posizione.h"
#define BUCA "Buca"
#define DOSSO "Dosso"

/* Definizione strutture */
typedef struct Evento_struct 
{
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
bool hasNext(EventoList list);
EventoList next(EventoList list);
Evento creaEvento(char *tipo_evento,Posizione posizione);
bool inserisciEvento(Evento evento,EventoList evento_list);
char *eventoToString(Evento evento);
EventoList mostraEventiVicini(EventoList evento_list,Posizione posizione);
