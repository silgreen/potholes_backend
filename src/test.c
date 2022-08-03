#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void scrive_disconnessione(void *arg) {
    
}

void *scrive_connessione(void *arg) {
    FILE *fp;
    if(!(fp = fopen("./data/events.txt","a")))
        perror("file non aperto correttamente");

    char *str = "ciao come stai";
    fprintf(fp,"%s\n",str);
    fclose(fp);
}

int main(int argc, char const *argv[])
{
    pthread_t thread;
    int status = pthread_create(&thread,NULL,scrive_connessione,NULL);
    printf("%d",status);
    sleep(1);
    return 0;
}

