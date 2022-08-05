#include "../lib/com/potholes_socket_lib.h"

int main(int argc, char const *argv[])
{
    struct sockaddr_in address;
    int fd, val_read;
    char buffer[1024] = {0};
    char *str = "ciao come stai sono il client\n";
    int c[1] = {120};
    EventoClient event;
    event.client_nickname = "alberto";
    event.latitudine = 111234;
    event.longitudine = 22222;
    event.valore = 1.12;
    event.timestamp = SO_TIMESTAMP;

    

    fd = socket(AF_INET,SOCK_STREAM,0);
    address.sin_family = AF_INET;
    address.sin_port = htons(8080);
    inet_pton(AF_INET,"192.168.65.224",&address.sin_addr);

    connect(fd,(struct sockaddr *)&address,sizeof(address));
    send(fd,str,strlen(str),0);
    send(fd,c,sizeof(int),0);
    printf("messaggio inviato\n");
    val_read = read(fd,buffer,1024);
    printf("%s",buffer);
    close(fd);
    return 0;
}
