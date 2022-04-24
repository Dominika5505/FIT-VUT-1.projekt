// steg-code.c
// Řešení IJC-DU1, příklad b), 14.3.2021
// Autor: Dominika Sedileková, FIT
// Přeloženo: gcc version 8.2.0 (GCC)
// dekódovanie správy z ppm obrázka

#include "bitset.h"
#include "eratosthenes.h"
#include "ppm.h"

int main(int argc, char **argv) 
{
    // Ošetrenie počtu argumentov
    if (argc != 2 ) error_exit("Program vyžaduje jeden argument");

    // Vytvorenie a načítanie dát obrázku do štruktúry
    struct ppm *ppm_ptr = ppm_read(argv[1]);
    if (ppm_ptr == NULL) error_exit("Nepodařilo se otevřít soubor %s", argv[1]);

    bitset_index_t ppm_size = ppm_ptr->xsize * ppm_ptr->ysize;

    // Vytvorenie bitového poľa veľkosti obrázka a nájdenie prvočíselných indexov
    bitset_alloc(ppm_primes, ppm_size);
    Eratosthenes(ppm_primes);

    unsigned bit_counter = 0;
    unsigned char c = 0;

    // Loop od prvočísla 23
    for(bitset_index_t i = 23; i < ppm_size; i++) {

        if (!(bitset_getbit(ppm_primes, i))) {
            // Na 8mom bite sa char vytlačí a resetuje na 0
            if (bit_counter == CHAR_BIT) {
                if (c == '\0')
                    break;

                printf("%c", c);
                c &= 0;
                bit_counter = 0;
            }

            // Postupne vkladá bity od LSB do charu
            if (ppm_ptr->data[i] & 1) {
                c |= (1 << (bit_counter % CHAR_BIT));
            } 

            bit_counter++;
        }
    }
    printf("\n");

    // Uvoľnenie alokovaných dát
    bitset_free(ppm_primes);
    ppm_free(ppm_ptr);
}