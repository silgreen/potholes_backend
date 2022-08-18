#include "../lib/com/potholes_socket_lib.h"

void *invia_messaggio_client(void *arg);
void gestisci_richiesta(int socket);

int main(int argc, char const *argv[])
{   
    char buffer[BUFSIZ]; 
    char nickname[BUFSIZ];
    Evento ev = NULL;
    Posizione pos = NULL;
    int server_fd,new_socket,delta,addr_len;
    int option = 1;
    struct sockaddr_in address;
    pthread_t thread;
    double lat,lng;
    char str2[BUFSIZ];
    
    
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
    while (true)
    {  
        
        if((new_socket = accept(server_fd,NULL,NULL)) < 0) perror("errore durante l'accept");
        if((read(new_socket,buffer,BUFSIZ)) < 0) perror("errore durante la lettura");
        char *str;
        FILE *fp;
        str = strtok(buffer,";");
        if((fp = fopen("temp.txt","w")) < 0) perror("errore apertura file");

        while (str != NULL) {
            fprintf(fp,"%s ",str);
            str = strtok(NULL,";");
        }
        fclose(fp);

        sprintf(buffer,"%lf:%lf",12.345,12.34);
        send(new_socket,buffer,strlen(buffer),0);
        close(new_socket);
/*
        if((fp = fopen("temp.txt","r")) < 0) perror("errore apertura file");
        while((fscanf(fp,"%s%lf%lf%d",nickname,&lat,&lng,&delta)) != EOF) {
            fclose(fp);
            ev = creaEvento(calcola_evento(delta),nickname,creaPosizione(lat,lng));
            printEvento(ev);

            if((send(new_socket,ev->tipo_evento,strlen(ev->tipo_evento),0)) < 0) perror("invio non riuscito");
            close(new_socket);

            if ((fp = fopen("../../data/events.txt","a")) < 0) perror("errore apertura file");
            fprintf(fp,"%s %s %lf %lf\n",ev->nickname,ev->tipo_evento,ev->posizione->latitudine,ev->posizione->longitudine);
        }
        fclose(fp);

        if ((fp = fopen("../../data/events.txt","r")) < 0) perror("errore apertura file");
        char c;
        while(c = getc(fp) != "\n") {
            putc(c,stdout);
        }
        
    */

        
        //if(pthread_create(&thread,NULL,invia_soglia,&new_socket) < 0) perror("errore nella creazione del thread");

    }
}

void gestisci_richiesta(int socket) {
    pthread_t thread;
    char lettura_richiesta[1024];
    read(socket,lettura_richiesta,sizeof(lettura_richiesta));

    if(strcmp(lettura_richiesta,"soglia") == 0) {
        pthread_create(thread,NULL,invia_soglia,&socket);

    } else if(strcmp(lettura_richiesta,"lista") == 0) {
        
    } else if (strcmp(lettura_richiesta,"evento") == 0) {

    } else printf("operazione non supportata\n");

}

char* calcola_evento(double delta) {
    return delta > 0 ? DOSSO : BUCA; 
}

void init_address(struct sockaddr_in *address) {
    address->sin_family = AF_INET;
    address->sin_port = htons(8080);
    address->sin_addr.s_addr = INADDR_ANY;
}

void *invia_soglia(void *arg) {
    int socket = *(int*)arg;
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

