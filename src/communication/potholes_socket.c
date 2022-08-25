#include "../lib/com/potholes_socket_lib.h"

int init_server();

/*
    TODO 25/08/2022
    2. log completi
    3. modulo client/accendere il server
    4. polish codice
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

void *insertEventoFile(void *arg) {
    Evento evento = (Evento) arg;
    FILE *fp;
    pthread_mutex_lock(&mutex);
    if ((fp = fopen("../../data/events.txt","a")) < 0) perror("errore apertura file");
        fprintf(fp,"%s %s %lf %lf\n",evento->nickname,evento->tipo_evento,evento->posizione->latitudine,evento->posizione->longitudine);
    fclose(fp);
    pthread_mutex_unlock(&mutex);
    free(evento);
}

void *gestisci_richiesta(void *arg) {
    pthread_t thread;
    int socket = *(int*)arg;
    char buffer[BUFSIZ] = {""};
    char *resp = "ok";
    read(socket,buffer,sizeof(buffer));
    char data[4][BUFSIZ] = {""};
    
    if(strcmp(buffer,REQ_SOGLIA) == 0) {
        invia_soglia(socket);
    } else if(strcmp(buffer,REQ_LISTA) == 0) {
        send(socket,resp,strlen(resp),0);
        memset(buffer,0,strlen(buffer));
        read(socket,buffer,sizeof(buffer));
        deserialize_data(data,buffer);
        SendDataThread dataThread = NULL;
        dataThread = creaSendDataThread(creaPosizione(strtod(data[0],NULL),strtod(data[1],NULL)),socket);
        pthread_create(&thread,NULL,mostraEventiViciniThread,dataThread);
    } else if (strcmp(buffer,REQ_EVENTO) == 0) {
        double lat,lng,delta;
        send(socket,resp,strlen(resp),0);
        memset(buffer,0,strlen(buffer));
        read(socket,buffer,sizeof(buffer));
        deserialize_data(data,buffer);
        Evento ev = stringToEvento(data,&lat,&lng,&delta);
        send(socket,ev->tipo_evento,strlen(ev->tipo_evento),0);
        close(socket);
        pthread_create(&thread,NULL,insertEventoFile,ev);
        
    } else printf("operazione non supportata %s\n",buffer);
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

void deserialize_data(char data[][BUFSIZ],char *token) {
    char *strtoken = strtok(token,";");
    size_t i = 0;
    while (strtoken != NULL) {
            strcpy(data[i++],strtoken);
            strtoken = strtok(NULL,";");
        }
        printf("matrice riempita con deserialize\n");
}