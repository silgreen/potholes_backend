#include "../lib/com/potholes_socket_lib.h"

int main(int argc, char const *argv[])
{
    struct sockaddr_in address;

    char buffer[1024];
    char richiesta[] = "soglia";

    int fd;
    fd = socket(AF_INET,SOCK_STREAM,0);
    address.sin_family = AF_INET;
    address.sin_port = htons(8080);
    inet_pton(AF_INET,"172.17.159.17",&address.sin_addr);

    connect(fd,(struct sockaddr *)&address,sizeof(address));

    if(send(fd,richiesta,sizeof(richiesta),0) < 0) perror("errore in invio socket");
    if(read(fd,buffer,sizeof(buffer)) < 0) perror("errore in lettura socket");
    if(strcmp(buffer,"OK") == 0) {
        printf("%s\n",buffer);
        char *msg = "salve sono il client";
        send(fd,msg,strlen(msg),0);
    }
    memset(buffer,0,sizeof(buffer));
    read(fd,buffer,sizeof(buffer));
    close(fd);
    return 0;
}
