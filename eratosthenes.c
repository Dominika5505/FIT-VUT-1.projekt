// eratothenes.c
// Řešení IJC-DU1, příklad a), 14.3.2021
// Autor: Dominika Sedileková, FIT
// Přeloženo: gcc version 8.2.0 (GCC)
// funkcia na nájdenie prvočísel v bitovom poli

#include "eratosthenes.h"

void Eratosthenes(bitset_t array) 
{
    // nastaví 0 a 1 na 1 (0 a 1 nie sú prvočísla)
    bitset_setbit(array, 0, 1);
    bitset_setbit(array, 1, 1);

    // Limity pre cykly
    unsigned long N = sqrt(bitset_size(array));
    unsigned long limit = bitset_size(array);

    for (bitset_index_t i = FIRST_PRIME; i < N; i++) {
        
        if (!(bitset_getbit(array, i))) {

            // Ak nájde prvočíslo, jeho násobky nastaí na 1 (nie sú prvočísla)
            for (bitset_index_t j = i * i; j < limit; j += i) {    
                bitset_setbit(array, j, 1);
            }

        } 
    }
}