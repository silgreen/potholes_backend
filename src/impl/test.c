#include "../lib/dependencies.h"
#include "../lib/struct/Evento.h"

int main(int argc, char const *argv[])
{

    Posizione p = creaPosizione(10,24);
    Posizione p2 = creaPosizione(32,45);
    Posizione p3 = creaPosizione(11,25);
    Posizione p4 = creaPosizione(33,46);

    Evento ev2 = creaEvento("Dosso",p2);
    Evento ev3 = creaEvento("Dosso",p3);
    Evento ev4 = creaEvento("Buca",p4);

    FILE *fp = fopen("prova.txt","w");
    fprintf(fp,"%s %lf %lf\n",ev3->tipo_evento,ev3->posizione->latitudine,ev3->posizione->longitudine);
    fclose(fp);

    FILE *fpr = fopen("prova.txt","r");
    char str1[256];
    char str2[256];
    char str3[256];

    while (fscanf(fpr,"%s%s%s",str1,str2,str3) > 0)
    {
        printf("%s %s %s\n",str1,str2,str3);
    }
    fclose(fpr);
    

    return 0;
}
