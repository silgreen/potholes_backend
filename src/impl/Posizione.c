#include "../lib/struct/Posizione.h"

Posizione creaPosizione(double lat, double lng) {
    Posizione position = (Posizione) malloc(sizeof(struct Posizione_struct));
    position->latitudine = lat;
    position->longitudine = lng;
    return position;
}

void printPosizione(Posizione position) {
    printf("%lf:%lf\n",position->latitudine,position->longitudine);
}

double calcolaDistanza(Posizione position1,Posizione position2) {
    double calcoloLat = pow((position1->latitudine - position2->latitudine),2);
    double calcoloLng = pow((position1->longitudine - position2->longitudine),2);
    return sqrt(calcoloLat + calcoloLng); 
}