// ppm.h
// Řešení IJC-DU1, příklad b), 14.3.2021
// Autor: Dominika Sedileková, FIT
// Přeloženo: gcc version 8.2.0 (GCC)
// ...popis příkladu - poznámky, omezení, atd

#include "bitset.h"

// Limit veľkosti dát obrázku
#define SIZE_LIMIT (8000 * 8000 * 3)

// Štruktúra obrázku
struct ppm {
    unsigned xsize;
    unsigned ysize;
    char data[];
};

struct ppm * ppm_read(const char * filename);

void ppm_free(struct ppm *p);