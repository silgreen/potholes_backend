#include "../lib/struct/Evento.h"
#define VICINANZA 10

EventoList creaEventoList(Evento evento) {
    if(evento != NULL) {
        EventoList ev = (EventoList) malloc(sizeof(struct EventoList_struct));
        ev->event = evento;
        ev->next = NULL;
        return ev;
    }
    return NULL;
}

Evento creaEvento(char *tipo_evento,char *nickname,Posizione position) {
    if(position != NULL && (strcmp(tipo_evento,BUCA) == 0) || strcmp(tipo_evento,DOSSO) == 0) {
        Evento evento = (Evento) malloc(sizeof(struct Evento_struct));
        evento->posizione = position;
        strcpy(evento->tipo_evento,tipo_evento);
        strcpy(evento->nickname,nickname);
        return evento;
    } 
    perror("creazione evento non riuscita");
    return NULL;
}

void printEvento(Evento evento) {
    if(evento == NULL) return;
    printf("%s | ",evento->nickname);
    printf("%s | ",evento->tipo_evento);
    printPosizione(evento->posizione);
}

EventoList inserisciEvento(EventoList list, Evento evento) {
    if(list == NULL) return creaEventoList(evento);
    list->next = inserisciEvento(list->next,evento);
    return list;
}

void printEventoList(EventoList eventoList) {
    if(eventoList == NULL) return;
    printEvento(eventoList->event);
    printEventoList(eventoList->next);
}

EventoList mostraEventiVicini(EventoList eventoList,EventoList resultList,Posizione position) {
    if(eventoList != NULL && position != NULL) {
        if(calcolaDistanza(eventoList->event->posizione,position) <= VICINANZA) {
        resultList = inserisciEvento(resultList,eventoList->event);
        }
        resultList = mostraEventiVicini(eventoList->next,resultList,position);
    }
    return resultList;
}

