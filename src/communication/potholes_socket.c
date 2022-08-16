#include "../lib/com/potholes_socket_lib.h"

void *invia_messaggio_client(void *arg);
void gestisci_richiesta(int socket);

int main(int argc, char const *argv[])
{   
    char buffer[1024];
    char ok[3] = "OK"; 
    int server_fd,new_socket,val_read,addr_len;
    struct sockaddr_in address;
    pthread_t thread;
    
    
    if((server_fd = socket(AF_INET,SOCK_SEQPACKET,0)) < 0) {
        perror("creazione socket non riuscita");
        return EXIT_FAILURE;
    }

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
        if(read(new_socket,buffer,sizeof(buffer)) < 0) perror("errore in lettura");
        if(strcmp(buffer,"soglia") == 0) {
            send(new_socket,ok,sizeof(ok),0);
        } 
        char *msg = "a fess e mammt";
        memset(buffer,0,sizeof(buffer));
        read(new_socket,buffer,sizeof(buffer));
        printf("%s\n",buffer);
        send(new_socket,msg,strlen(msg),0);
        close(new_socket);
        
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

