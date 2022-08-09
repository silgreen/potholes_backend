#include "../dependencies.h"

typedef struct Posizione_struct
{
    double latitudine;
    double longitudine;
}Posizione_struct;

typedef struct Posizione_struct *Posizione;

Posizione creaPosizione(double lat,double lng);
bool validationLatLng(double lat,double lng);
char *posizioneToString(Posizione pos);
double calcolaDistanza(Posizione pos1,Posizione pos2);

