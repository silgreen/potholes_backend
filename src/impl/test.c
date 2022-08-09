#include "../lib/dependencies.h"
#include "../lib/struct/Evento.h"

int main(int argc, char const *argv[])
{

    Posizione p = creaPosizione(10,24);
    Posizione p2 = creaPosizione(32,45);
    Evento ev1 = creaEvento("Buca",p);
    Evento ev2 = creaEvento("Dosso",p2);
    //Evento ev3 = creaEvento("calsda",p2);
    posizioneToString(p);
    printf("l'evento 1 è %s\n",posizioneToString(ev1->posizione));
    printf("l'evento 2 è %s\n",ev2->tipo_evento);
    return 0;
}
