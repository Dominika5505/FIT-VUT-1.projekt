// primes.c
// Řešení IJC-DU1, příklad a), 14.3.2021
// Autor: Dominika Sedileková, FIT
// Přeloženo: gcc version 8.2.0 (GCC)
// výpis posledných 10 prvočísel

#include <time.h>
#include "eratosthenes.h"

// Počet prvočísel, ktoré sa butú vypisovať
#define NUMS_TO_PRINT 10

void printPrimes(bitset_t array)
{
    // Index loopu
    bitset_index_t limit = bitset_size(array) - 1;
    // Index poľa, do ktorého sa budú vkladať prvočíla zostupne
    int prime_array_index = NUMS_TO_PRINT - 1;
    // Počet pročísel
    bitset_index_t prime_count = 0;
    // Pole na uloženie posledných 10 prvočísel
    bitset_index_t last_ten_primes[NUMS_TO_PRINT];

    while (prime_count < NUMS_TO_PRINT) {
        if (!(bitset_getbit(array, limit))) {
            // Vloží prvočíslo do poľa
            last_ten_primes[prime_array_index] = limit;
            prime_array_index--;
            prime_count++;
        }
        limit--;
    }

    // Prvky poľa vytlačí na stdout
    for(int i = 0; i < NUMS_TO_PRINT; i++) {
        printf("%ld\n", last_ten_primes[i]);
    }
}

int main(void)
{
    // Začne časovať začiatok programu
    clock_t start = clock();

    // Vytvorí lokálne pole
    // bitset_create(array, 4294967295); 
    bitset_create(array, 200000000); 
    // bitset_create(array, 30000); 
    // Nájde v poli prvočísla
    Eratosthenes(array);
    // Vytlačí prvočísla
    printPrimes(array);
    // Na stdeer vypíše za aký čas prebehol program
    fprintf(stderr, "Time=%.3g\n", (double)(clock()-start)/CLOCKS_PER_SEC);
}