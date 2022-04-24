// error.c
// Řešení IJC-DU1, příklad b), 14.3.2021
// Autor: Dominika Sedileková, FIT
// Přeloženo: gcc version 8.2.0 (GCC)
// funkcie na výpis chýb

#include <stdlib.h>
#include "error.h"

// Funkcia vypíše formátované chybové hlásenie
void warning_msg(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);

    fprintf(stderr, "Chyba: ");
    vfprintf(stderr, fmt, args);
    fprintf(stderr, "\n");

    va_end(args);
}

// Funkcia vypíše formátované chybové hlásenie a ukončí program
void error_exit(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);

    fprintf(stderr, "Chyba: ");
    vfprintf(stderr, fmt, args);
    fprintf(stderr, "\n");

    va_end(args);

    exit(1);
}