#include "../dependencies.h"
#include "../lib/struct/Evento.h"

bool hasNext(EventoList list) {
    return list->next != NULL;
}

