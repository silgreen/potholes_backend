#include "../lib/com/potholes_socket_lib.h"

int main(int argc, char const *argv[])
{
    struct sockaddr_in address;

    char *data = "10;10";
    char *tipo_richiesta = "lista";
    char *nickname = "pino";
    char buff[BUFSIZ];

    int fd;
    fd = socket(AF_INET,SOCK_STREAM,0);
    address.sin_family = AF_INET;
    address.sin_port = htons(8080);
    inet_pton(AF_INET,"127.0.0.1",&address.sin_addr);

    connect(fd,(struct sockaddr *)&address,sizeof(address));
    if(send(fd,nickname,sizeof(nickname),0) < 0) perror("errore nell'invio del nickname\n");
    read(fd,buff,BUFSIZ);
    printf("risposta server: %s\n",buff);
    if(strcmp("ok",buff) == 0) {
        memset(buff,0,strlen(buff));
        if(send(fd,tipo_richiesta,sizeof(tipo_richiesta),0) < 0) perror("errore nell'invio della richiesta");
    }
    
    memset(buff,0,strlen(buff));
    read(fd,buff,BUFSIZ);
    if(strcmp("ok",buff) == 0) {
        memset(buff,0,strlen(buff));
        printf("la stringa che sto inviando al server: %s\n",data);
        send(fd,data,strlen(data),0);
        read(fd,buff,sizeof(buff));
        printf("la lista risultante è: %s\n",buff);
    }
    return 0;
}
