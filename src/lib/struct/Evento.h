#include "../dependencies.h"
#include "Posizione.h"

/* Definizione strutture */
typedef struct Evento_struct 
{
    char *tipo_evento;
    Posizione posizione;
};

typedef struct Evento_struct *Evento;

typedef struct EventoList_struct 
{
    Evento event;
    EventoList *next;
};

typedef struct EventoList_struct *EventoList;

/***********************************************************/

/* Definizione metodi */
bool hasNext(EventoList list);
EventoList next(EventoList list);
Evento creaEvento(char *tipo_evento,Posizione posizione);
bool inserisciEvento(Evento evento,EventoList evento_list);
char *eventoListToString(EventoList evento_list);
EventoList mostraEventiVicini(EventoList evento_list,Posizione posizione);
