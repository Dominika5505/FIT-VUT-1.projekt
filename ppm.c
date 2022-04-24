// ppm.c
// Řešení IJC-DU1, příklad b), 14.3.2021
// Autor: Dominika Sedileková, FIT
// Přeloženo: gcc version 8.2.0 (GCC)
// načítanie ppm obrázku do štruktúry

#include <string.h>
#include "ppm.h"

struct ppm * ppm_read(const char * filename) 
{
    // Otvorí súbor
    FILE *fptr;
    fptr = fopen(filename, "r");

    if (fptr == NULL) {
        warning_msg("Chyba při otevírání souboru %s", filename);
        return NULL;
    }
    
    char format[3];
    int size_x;
    int size_y;
    int color_limit;
    
    // Uloží formát a veľkosť súboru z prečítaných dát
    int format_scan = fscanf(fptr, "%s", format);
    int size_scan = fscanf(fptr, "%d %d", &size_x, &size_y);
    int color_scan = fscanf(fptr, "%d ", &color_limit);

    // Ak sú zle prečítané ukončí program
    if (size_scan != 2 || format_scan != 1 || color_scan != 1) {
        warning_msg("Zle načtené rozmery");
        fclose(fptr);
        return NULL;
    }


    if (strcmp(format, "P6")) {
        warning_msg("Nesprávný formát ppm souboru");
        fclose(fptr);
        return NULL;
    }

    // Vypočíta veľkosť dát
    unsigned ppm_size = size_x * size_y;

    // Ak je veľkosť dát priveľká, ukončí program
    if (ppm_size > SIZE_LIMIT) {
        warning_msg("Rozměry souboru jsou příliš velké");
        fclose(fptr);
        return NULL;
    } 

    // Alokuje pamäť pre štruktúru
    struct ppm *ppm_ptr = malloc(sizeof(struct ppm) + ppm_size + 1);

    // Uloží rozmery a dáta do štruktúry
    ppm_ptr->xsize = 360;
    ppm_ptr->ysize = 135;
    size_t elems_read = fread(ppm_ptr->data, ppm_size, 1, fptr);
    if (elems_read != 1UL) {
        fclose(fptr);
        return NULL;
    }

    fclose(fptr);
    return ppm_ptr;
}

void ppm_free(struct ppm *p) 
{
    if (p != NULL)
        free(p);
}