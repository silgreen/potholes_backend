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

Evento stringToEvento(char data[][BUFSIZ]) {
    char nick[BUFSIZ] = {""};
    strcpy(nick,data[0]);
    double lat = strtod(data[1],NULL);
    double lng = strtod(data[2],NULL);
    double delta = strtod(data[3],NULL);
    return creaEvento(calcola_evento(delta),nick,creaPosizione(lat,lng));
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

EventoList mostraEventiVicini(EventoList resultList,Posizione posizione) {
    FILE *fp;
    if((fp = fopen("../../data/events.txt","r")) < 0) perror("errore nell'apertura del file");
    char nickname[BUFSIZ], tipoEvento[BUFSIZ];
    double lat,lng;
    Posizione pos;
    while (fscanf(fp,"%s%s%lf%lf",nickname,tipoEvento,&lat,&lng) != EOF) {
        pos = creaPosizione(lat,lng);
        if(calcolaDistanza(posizione,pos) <= VICINANZA) {
            resultList = inserisciEvento(resultList,creaEvento(tipoEvento,nickname,pos));
        }
        
    }
    fclose(fp);
    return resultList;
}

SendDataThread creaSendDataThread(Posizione pos,int socket) {
    if(pos == NULL ) return NULL;
    SendDataThread tmp = (SendDataThread) malloc(sizeof(struct SendData));
    tmp->posizione = pos;
    tmp->socket = socket;
    return tmp;
}

void deallocaLista(EventoList list) {
    if(list == NULL) return;
    deallocaLista(list->next);
    free(list);
}

char* calcola_evento(double delta) {
    return delta > 0 ? DOSSO : BUCA; 
}

void *mostraEventiViciniThread(void *arg) {
    EventoList lista = NULL; 
    SendDataThread data = (SendDataThread)arg;
    pthread_mutex_t mutexEvento;
    pthread_mutex_init(&mutexEvento,NULL);
    pthread_mutex_lock(&mutexEvento);
    lista = mostraEventiVicini(lista,data->posizione);
    pthread_mutex_unlock(&mutexEvento);
    if(lista != NULL) {
        printEventoList(lista);
        char buffer[BUFSIZ];
        serializzaEventList(lista,buffer);
        if(send(data->socket,buffer,strlen(buffer),0) < 0) perror("invio non riuscito");
        printf("%s\n",buffer);
    } else printf("nessun evento vicino trovato\n");
    close(data->socket);
    printf("disconnessione con il client avvenuta\n");
    free(data);
    deallocaLista(lista);
}

char* eventoToString(Evento evento, char *result) {
    double lat,lng;
    sprintf(result,"%s;%s;%lf;%lf|",evento->nickname,evento->tipo_evento,evento->posizione->latitudine,evento->posizione->longitudine);
    return result;
}

void serializzaEventList(EventoList eventList, char *result) {
    EventoList eventListTemp = eventList;
    char buffer[BUFSIZ];
    while (eventListTemp != NULL) {
        strcat(result,eventoToString(eventListTemp->event,buffer));
        eventListTemp = eventListTemp->next;
        memset(buffer,0,sizeof(buffer));
    }
    free(eventListTemp);
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
