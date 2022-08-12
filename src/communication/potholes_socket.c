#include "../lib/com/potholes_socket_lib.h"

int main(int argc, char const *argv[])
{
    int server_fd,new_socket,val_read,addr_len;
    struct sockaddr_in address;
    char buffer[2048] = {0};
    
    
    if((server_fd = socket(AF_INET,SOCK_STREAM,0)) < 0) {
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
        new_socket = accept(server_fd,NULL,NULL);   
        invia_soglia(new_socket);
        char *str3 = calcola_evento(4);
        printf("%s %s\n",buffer,str3);
        send(new_socket,str3,strlen(str3),0);
        if((val_read = read(new_socket,buffer,2048)) < 0) perror("lettura non riuscita");
    }
    close(new_socket);
}

void invia_soglia(int socket) {
    if(send(socket,SOGLIA,strlen(SOGLIA),0) < 0) {
        perror("errore nell'invio della soglia\n");
    }
    printf("soglia inviata al client\n");
}

char* calcola_evento(double delta) {
    return delta > 0 ? DOSSO : BUCA; 
}

void init_address(struct sockaddr_in *address) {
    address->sin_family = AF_INET;
    address->sin_port = htons(8080);
    address->sin_addr.s_addr = INADDR_ANY;
}

