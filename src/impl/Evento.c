#include "../lib/struct/Evento.h"

Evento creaEvento(char *tipo_evento,Posizione position) {
    if(position != NULL && (strcmp(tipo_evento,BUCA) == 0) || strcmp(tipo_evento,DOSSO) == 0) {
        Evento evento = (Evento) malloc(sizeof(struct Evento_struct));
        evento->posizione = position;
        strcpy(evento->tipo_evento,tipo_evento);
        return evento;
    } 
    perror("creazione evento non riuscita");
    return NULL;
}

char *eventoToString(Evento evento) {
    if(evento != NULL) {
        char *result;
        char type[32];
        //char *position = posizioneToString(evento->posizione);
        strcpy(type,evento->tipo_evento);
        sprintf(result,"%s | []",type);
        return result;
    }
    perror("Illegal Argument Exception");
    return NULL;
}

bool hasNext(EventoList list) {
    return list->next != NULL;
}

