#include "../lib/com/potholes_socket_lib.h"

int main(int argc, char const *argv[])
{
    struct sockaddr_in address;

    char *data = "alfonso;12.323;33.33;11";
    char buff[BUFSIZ];

    int fd;
    fd = socket(AF_INET,SOCK_STREAM,0);
    address.sin_family = AF_INET;
    address.sin_port = htons(8080);
    inet_pton(AF_INET,"127.0.0.1",&address.sin_addr);

    connect(fd,(struct sockaddr *)&address,sizeof(address));
    send(fd,data,strlen(data),0);
    read(fd,buff,BUFSIZ);
    printf("%s",buff);
    close(fd);
    return 0;
}
