#include "../lib/com/potholes_socket_lib.h"

void *invia_messaggio_client(void *arg);
void *gestisci_richiesta(void *arg);
void convert_lat_lng(char data[][BUFSIZ],double *lat,double *lng);
void deserialize_data(char data[][BUFSIZ],char *token);
Evento stringToEvento(char data[][BUFSIZ],double *lat,double *lng,double *delta);
void *insertEventoFile(void *arg);

int main(int argc, char const *argv[])
{   
    Evento ev = NULL;
    Posizione pos = NULL;
    char buffer[BUFSIZ]; 
    char nickname[BUFSIZ];
    int server_fd,new_socket,addr_len;
    int option = 1;
    struct sockaddr_in address;
    pthread_t thread;
    double lat,lng,delta;
    
    
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

    while (true) {  
        if((new_socket = accept(server_fd,NULL,NULL)) < 0) perror("errore durante l'accept");
        if((pthread_create(&thread,NULL,gestisci_richiesta,&new_socket)) < 0) perror("errore nella creazione del thread");
        //deserialize_data(data,buffer);
        //ev = stringToEvento(data,&lat,&lng,&delta);
        //printEvento(ev);
        /*

            if ((fp = fopen("../../data/events.txt","a")) < 0) perror("errore apertura file");
            fprintf(fp,"%s %s %lf %lf\n",ev->nickname,ev->tipo_evento,ev->posizione->latitudine,ev->posizione->longitudine);
        }
        fclose(fp);
        
        //if(pthread_create(&thread,NULL,invia_soglia,&new_socket) < 0) perror("errore nella creazione del thread");
        */

    }
}

void *insertEventoFile(void *arg) {
    Evento evento = (Evento) arg;
    FILE *fp;
    pthread_mutex_lock(&mutex);
    printf("sono il thread che gestisce %s\n",evento->nickname);
    sleep(5);
    if ((fp = fopen("../../data/events.txt","a")) < 0) perror("errore apertura file");
            fprintf(fp,"%s %s %lf %lf\n",evento->nickname,evento->tipo_evento,evento->posizione->latitudine,evento->posizione->longitudine);
    fclose(fp);
    pthread_mutex_unlock(&mutex);
    printf("il thread che gestisce %s ha finito\n",evento->nickname);
}

void *gestisci_richiesta(void *arg) {
    pthread_t thread;
    int socket = *(int*)arg;
    char buffer[BUFSIZ] = {""};
    char *resp = "ok";
    read(socket,buffer,sizeof(buffer));
    
    if(strcmp(buffer,"soglia") == 0) {
        invia_soglia(socket);

    } else if(strcmp(buffer,"lista") == 0) {
        
    } else if (strcmp(buffer,"evento") == 0) {
        double lat,lng,delta;
        char data[4][BUFSIZ] = {""};
        send(socket,resp,strlen(resp),0);
        memset(buffer,0,strlen(buffer));
        read(socket,buffer,sizeof(buffer));
        printf("il contenuto del buffer prima di deserialize %s\n",buffer);
        deserialize_data(data,buffer);
        Evento ev = NULL; 
        ev = stringToEvento(data,&lat,&lng,&delta);
        send(socket,ev->tipo_evento,strlen(ev->tipo_evento),0);
        close(socket);
        pthread_create(&thread,NULL,insertEventoFile,ev);
        
    } else printf("operazione non supportata %s\n",buffer);
}

char* calcola_evento(double delta) {
    return delta > 0 ? DOSSO : BUCA; 
}

void init_address(struct sockaddr_in *address) {
    address->sin_family = AF_INET;
    address->sin_port = htons(8080);
    address->sin_addr.s_addr = INADDR_ANY;
}

void invia_soglia(int socket) {
    char buffer[10];
    strcpy(buffer,SOGLIA);

    if(send(socket,buffer,sizeof(buffer),0) < 0) perror("errore nell'invio della soglia");
    printf("soglia inviata al client\n");
    close(socket);
}

void *invia_messaggio_client(void *arg) {
    char msg[] = "ciao come stai";
    int socket = *(int*)arg;
    if(send(socket,msg,sizeof(msg),0) < 0) {
        perror("errore nell'invio del messaggio\n");
    }
    printf("messaggio inviato\n");
    close(socket);
}

Evento stringToEvento(char data[][BUFSIZ],double *lat,double *lng,double *delta) {
    char nick[BUFSIZ] = {""};
    strcpy(nick,data[0]);
    *lat = strtod(data[1],NULL);
    *lng = strtod(data[2],NULL);
    *delta = strtod(data[3],NULL);
    printf("salve sono stringToEvento e ho finito\n");
    memset(data,0,sizeof(data[0][0])*4*BUFSIZ); //azzeramento matrice
    return creaEvento(calcola_evento(*delta),nick,creaPosizione(*lat,*lng));
}

void deserialize_data(char data[][BUFSIZ],char *token) {
    char *strtoken = strtok(token,";");
    size_t i = 0;
    while (strtoken != NULL) {
            strcpy(data[i++],strtoken);
            strtoken = strtok(NULL,";");
        }
        printf("matrice riempita con deserialize\n");
}

