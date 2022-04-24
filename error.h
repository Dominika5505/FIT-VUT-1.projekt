// error.h
// Řešení IJC-DU1, příklad b), 14.3.2021
// Autor: Dominika Sedileková, FIT
// Přeloženo: gcc version 8.2.0 (GCC)

#include <stdio.h>
#include <stdarg.h>

void warning_msg(const char *fmt, ...);
void error_exit(const char *fmt, ...);