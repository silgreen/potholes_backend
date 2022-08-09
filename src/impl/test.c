#include "../lib/dependencies.h"
#include "../lib/struct/Posizione.h"

int main(int argc, char const *argv[])
{
    Posizione p = creaPosizione(10,24);
    Posizione p2 = creaPosizione(32,45);
    double distanza = calcolaDistanza(p,p2);
    printf("la distanza è %lf\n",distanza);
    return 0;
}
