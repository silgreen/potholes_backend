#include "../lib/struct/Evento.h"
#define VICINANZA 10

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

Evento stringToEvento(char data[][BUFSIZ],double *lat,double *lng,double *delta) {
    char nick[BUFSIZ] = {""};
    strcpy(nick,data[0]);
    *lat = strtod(data[1],NULL);
    *lng = strtod(data[2],NULL);
    *delta = strtod(data[3],NULL);
    memset(data,0,sizeof(data[0][0])*4*BUFSIZ); //azzeramento matrice
    return creaEvento(calcola_evento(*delta),nick,creaPosizione(*lat,*lng));
}

EventoList creaEventoList(Evento evento) {
    if(evento != NULL) {
        EventoList ev = (EventoList) malloc(sizeof(struct EventoList_struct));
        ev->event = evento;
        ev->next = NULL;
        return ev;
    }
    return NULL;
}

EventoList inserisciEvento(EventoList list, Evento evento) {
    if(list == NULL) return creaEventoList(evento);
    list->next = inserisciEvento(list->next,evento);
    return list;
}

char* calcola_evento(double delta) {
    return delta > 0 ? DOSSO : BUCA; 
}

void printEvento(Evento evento) {
    if(evento == NULL) return;
    printf("%s | ",evento->nickname);
    printf("%s | ",evento->tipo_evento);
    printPosizione(evento->posizione);
}

void printEventoList(EventoList eventoList) {
    if(eventoList == NULL) return;
    printEvento(eventoList->event);
    printEventoList(eventoList->next);
}
