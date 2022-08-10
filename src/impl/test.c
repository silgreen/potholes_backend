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
    EventoList eventoListVicini = NULL;
    EventoList eventoList = NULL;
    eventoList = inserisciEvento(eventoList,ev2);
    eventoList = inserisciEvento(eventoList,ev3);
    eventoList = inserisciEvento(eventoList,ev4);
    
    eventoListVicini = mostraEventiVicini(eventoList,eventoListVicini,p);
    printEventoList(eventoListVicini);

    return 0;
}
