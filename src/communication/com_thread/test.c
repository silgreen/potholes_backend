#include "../../lib/dependencies.h"
#include <pthread.h>
#include <sys/stat.h>

void*funzione_thread1(void*);
void*funzione_thread2(void*);

pthread_mutex_t semaforo = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t condition = PTHREAD_COND_INITIALIZER;


int main(int argc, char const *argv[])
{
    pthread_t thread1,thread2;
    pthread_create(&thread1,NULL,funzione_thread1,NULL);
    pthread_create(&thread2,NULL,funzione_thread2,NULL);
    pthread_join(thread1,NULL);
    return 0;
}

void *funzione_thread1(void *arg) {
    printf("salve sono il thread 1 e sto faticando\n");
    FILE *fp;
    sleep(3);
    pthread_mutex_lock(&semaforo);
    if((fp = fopen("prova.txt","w")) < 0) perror("file non aperto correttamente");
    fprintf(fp,"ciao sono il thread1 e ho scritto qualche cosa");
    fclose(fp);
    pthread_cond_broadcast(&condition);
    pthread_mutex_unlock(&semaforo);
}

void *funzione_thread2(void *arg) {
    printf("thread2 al lavoro:\n");
    FILE *fp;
    char buffer[1024];
    char str[1024];
    struct stat st;
    pthread_mutex_lock(&semaforo);
    fp = fopen("prova.txt","r");
    while (fgetc(fp) == EOF) {
        printf("file vuoto attendi\n");
        pthread_cond_wait(&condition,&semaforo);
    }
    ungetc(fgetc(fp),fp);
    fgets(str,1024,fp);
    printf("%s ",str);
    fclose(fp);
    pthread_mutex_unlock(&semaforo);
}