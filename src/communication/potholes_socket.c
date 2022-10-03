#include "../lib/com/potholes_socket_lib.h"

/*
    TODO finisci il progetto!
*/

int main(int argc, char const *argv[])
{   
    char buffer[BUFSIZ]; 
    char nickname[BUFSIZ];
    int new_socket;
    struct sockaddr_in client_addr;
    pthread_t thread;
    double lat,lng,delta;
    int server_fd = init_server();

    printf("\n******* Benvenuto in PotHolesServer *************\n");
    printf("** L'app che ti permette di rilevare buche e dossi **\n");

    while (true) {
        socklen_t client_addr_len = sizeof(struct sockaddr_in);  
        if((new_socket = accept(server_fd,(struct sockaddr *)&client_addr,&client_addr_len)) < 0) perror("errore durante l'accept");
        printf("nuova connessione stabilita con %s\n",inet_ntoa(client_addr.sin_addr));
        if((pthread_create(&thread,NULL,gestisci_richiesta,&new_socket)) < 0) perror("errore nella creazione del thread");
    }
}

int init_server() {
    int server_fd;
    struct sockaddr_in address;
    int option = 1;
    int addr_len;

    if((server_fd = socket(AF_INET,SOCK_STREAM,0)) < 0) {
        perror("creazione socket non riuscita");
        return EXIT_FAILURE;
    }
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option));

    init_address(&address);
    addr_len = sizeof(address);

    if(bind(server_fd,(struct sockaddr *)&address,addr_len) < 0) {
        perror("binding socket non riuscita");
        return EXIT_FAILURE;
    }

    listen(server_fd,5);
    return server_fd;
}

void init_address(struct sockaddr_in *address) {
    address->sin_family = AF_INET;
    address->sin_port = htons(8080);
    address->sin_addr.s_addr = INADDR_ANY;
}

void invia_soglia(int socket) {
    char buffer[BUFSIZ] = {""};
    strcpy(buffer,"3\n");

    if(send(socket,buffer,strlen(buffer),0) < 0) perror("errore nell'invio della soglia");
    printf("soglia inviata al client\n");
}

void deserialize_data(char data[][BUFSIZ],char *token) {
    char *strtoken = strtok(token,";");
    size_t i = 0;
    while (strtoken != NULL) {
            strcpy(data[i++],strtoken);
            strtoken = strtok(NULL,";");
        }
}

void *insertEventoFile(void *arg) {
    Evento evento = (Evento) arg;
    FILE *fp;
    pthread_mutex_lock(&mutex);
    if ((fp = fopen("../../data/events.txt","a")) < 0) perror("errore apertura file");
        fprintf(fp,"%s %s %lf %lf\n",evento->nickname,evento->tipo_evento,evento->posizione->latitudine,evento->posizione->longitudine);
    fclose(fp);
    pthread_mutex_unlock(&mutex);
    free(evento);
    printf("Inserito nuovo evento all'interno del file events.txt\n");
    printf("**************************************\n");
}

void leggiClient(int socket, char *client) {
    char buffer[BUFSIZ] = {""};
    if(read(socket,buffer,BUFSIZ) < 0) perror("errore nella lettura del nickname del client\n");
    printf("richiesta in arrivo dal client %s",buffer);
    buffer[strlen(buffer) -1] = '\0';
    strcpy(client,buffer);
}

void inviaRespOk(int socket) {
    char *resp = "ok\n";
    if(send(socket,resp,strlen(resp),0) < 0) perror("errore nell'invio della risposta al client\n");
    printf("invio il codice di successo %s",resp);
}

void leggiRichiesta(int socket, char *richiesta) {
    char buffer[BUFSIZ] = {""};
    if(read(socket,buffer,BUFSIZ) < 0) perror("errore nella lettura della richiesta del client\n");
    buffer[strlen(buffer) -1] = '\0';
    strcpy(richiesta,buffer);
    printf("tipo richiesta: %s\n",richiesta);
}

void leggiPosizioneClient(int socket,char* posizioneClient) {
    char buffer[BUFSIZ] = {""};
    if(read(socket,buffer,BUFSIZ) < 0) perror("errore nella lettura dei dati inviati dal client\n");
    posizioneClient[strlen(posizioneClient) - 1] = '\0';
    printf("la posizione del client in listathread %s",buffer);
    strcpy(posizioneClient,buffer);
}

void leggiEventoClient(int socket, char* eventoClient) {
    char buffer[BUFSIZ] = {""};
    if(read(socket,buffer,sizeof(buffer)) < 0) perror("errore nella lettura dell'evento del client\n");
    eventoClient[strlen(eventoClient) - 1] = '\0';
    strcpy(eventoClient,buffer);
}

void inviaListaThread(int socket) {
    char datiClient[4][BUFSIZ];
    char posizioneClient[BUFSIZ] = {""};
    pthread_t thread;
    leggiPosizioneClient(socket,posizioneClient);
    deserialize_data(datiClient,posizioneClient);
    SendDataThread dataThread = creaSendDataThread(datiClient[0],creaPosizione(strtod(datiClient[1],NULL),strtod(datiClient[2],NULL)),socket);
    pthread_create(&thread,NULL,mostraEventiViciniThread,dataThread);
}

Evento initEvento(int socket) {
    char data[4][BUFSIZ] = {""};
    char eventoClient[BUFSIZ] = {""};
    leggiEventoClient(socket,eventoClient);
    deserialize_data(data,eventoClient);
    return stringToEvento(data);
}

void inviaEvento(int socket, Evento evento) {
    char tipo_evento[BUFSIZ] = {""};
    strcpy(tipo_evento,evento->tipo_evento);
    strcat(tipo_evento,"\n");
    if(send(socket,tipo_evento,strlen(tipo_evento),0) < 0) perror("invio evento non riuscito");
    close(socket);
    printf("tipo evento inviato al client: %s",tipo_evento);
    printf("disconessione con %s avvenuta\n",evento->nickname);
}

void scriviEventoSuFile(Evento evento) {
    pthread_t thread;
    pthread_create(&thread,NULL,insertEventoFile,evento);
}

void *gestisci_richiesta(void *arg) {
    int socket = *(int*)arg;
    char client[BUFSIZ] = {""};
    char richiesta[BUFSIZ] = {""};
    
    leggiClient(socket,client);
    inviaRespOk(socket);
    leggiRichiesta(socket,richiesta);
    if(strcmp(richiesta,"soglia") == 0) {
        invia_soglia(socket);
        printf("disconnessione con %s avvenuta\n",client);
        printf("**************************************\n");
    } else if(strcmp(richiesta,REQ_LISTA) == 0) {
        inviaRespOk(socket);
        inviaListaThread(socket);
        printf("disconnessione con %s avvenuta\n",client);
    } else if (strcmp(richiesta,REQ_EVENTO) == 0) {
        inviaRespOk(socket);
        Evento evento = initEvento(socket);
        inviaEvento(socket,evento);
        scriviEventoSuFile(evento);
    } else {
        printf("operazione non supportata\n");
        close(socket);
        printf("disconnessione con %s avvenuta\n",client);
        printf("**************************************\n");
    };
}