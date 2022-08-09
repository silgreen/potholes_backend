typedef struct Posizione_struct
{
    long latitudine;
    long longitudine;
};

typedef struct Posizione_struct *Posizione;

Posizione creaPosizione(long lat,long lng);
char *posizioneToString(Posizione pos);

