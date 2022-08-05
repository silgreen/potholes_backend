#include "../lib/com/potholes_socket_lib.h"

int main(int argc, char const *argv[])
{
    int server_fd,new_socket,val_read,addr_len,client_len;
    struct sockaddr_in address;
    struct sockaddr client;
    EventoClient event;
    char buffer[1024] = {0};
    char *msg = "hello from server\n";
    int n[1];
    
    if((server_fd = socket(AF_INET,SOCK_STREAM,0)) < 0) {
        perror("creazione socket non riuscita");
        return EXIT_FAILURE;
    }
    address.sin_family = AF_INET;
    address.sin_port = htons(8080);
    address.sin_addr.s_addr = INADDR_ANY;
    addr_len = sizeof(address);
    
    if(bind(server_fd,(struct sockaddr *)&address,addr_len) < 0) {
        perror("binding socket non riuscita");
        return EXIT_FAILURE;
    }

    listen(server_fd,5);
    
    //new_socket = accept(server_fd,&client,client_len);
    new_socket = accept(server_fd,NULL,NULL);
    val_read = read(new_socket,buffer,1024);
    val_read = read(new_socket,n,sizeof(int));
    printf("%s %d\n",buffer,n[0]);
    send(new_socket,msg,strlen(msg),0);
}
