#include "../lib/struct/Posizione.h"
#include "../lib/dependencies.h"

bool validationLatLng(double lat, double lng) {
    return (lat >= -90 && lat <= 90) && (lng >= -180 && lng <= 180);
}

Posizione creaPosizione(double lat, double lng) {
    if(!(validationLatLng(lat,lng))) {
        perror("errore nella creazione della posizione\n");
        return NULL;
    }
    Posizione position = (Posizione) malloc(sizeof(struct Posizione_struct));
    position->latitudine = lat;
    position->longitudine = lng;
    return position;
}

char *posizioneToString(Posizione position) {
    char lat[32];
    char lng[32];
    char *result;
    snprintf(lat,32,"%lf",position->latitudine);
    snprintf(lng,32,"%lf",position->longitudine); 
    result = strcat(lat,lng);
    return result;
}

double calcolaDistanza(Posizione position1,Posizione position2) {
    double calcoloLat = pow(position1->latitudine - position2->latitudine,2);
    double calcoloLng = pow(position1->longitudine - position2->longitudine,2);
    return sqrt(calcoloLat + calcoloLng); 
}