#include "../lib/com/potholes_socket_lib.h"

int main(int argc, char const *argv[])
{
    struct sockaddr_in address;
    int fd, val_read,val_read2;
    char buffer[1024] = {0};
    char *str = "ciao\nciao\nciao";
    fd = socket(AF_INET,SOCK_STREAM,0);
    address.sin_family = AF_INET;
    address.sin_port = htons(8080);
    inet_pton(AF_INET,"192.168.79.130",&address.sin_addr);

    connect(fd,(struct sockaddr *)&address,sizeof(address));
    write(fd,str,strlen(str));
    val_read = read(fd,buffer,1024);
    printf("%s",buffer);
    close(fd);
    return 0;
}
