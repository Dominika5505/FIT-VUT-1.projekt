// bitset.h
// Řešení IJC-DU1, příklad a), 14.3.2021
// Autor: Dominika Sedileková, FIT
// Přeloženo: gcc version 8.2.0 (GCC)
// vytvorenie makier a inline funkcí pre bitové pole

#include <limits.h>
#include <stdlib.h>
#include <assert.h>
#include "error.h"

typedef unsigned long bitset_t[];
typedef unsigned long bitset_index_t;

// Počet bitov unsigned long
#define UL_BIT (sizeof(unsigned long) * CHAR_BIT)

// Upraví vložený index, aby nemenil byte, v ktorom je uložená veľkosť poľa
#define MODIF_INDEX(index) (index + UL_BIT)

// Miesto na uloženie veľkosti bitset poľa v bytoch
#define ARRAY_SIZE_SPOT 1

// Pomocné makro, ktoré tlačí bitové pole na stdout 
#define CHECK_IF_SET(array) \
    for (bitset_index_t i = 0; i < bitset_size(array); i++) { \
        if (bitset_getbit(array, i)) printf("1"); \
        else printf("0"); \
    }\
    printf("\n");


// Vytvára nulované bitové pole
// (size / UL_BIT) -> počet bitov
// ((size % UL_BIT) ? 1 : 0 ) -> ak ostal zvyšok, pripočíta sa 1, aby bol správny počet bitov
// + ARRAY_SIZE_SPOT -> miesto na uloženie veľkosti poľa
#define bitset_create(array_name, size)_Static_assert((size > 0), "bitset_create: Velikost pole musí být větší než 0.\n"); \
    unsigned long array_name[(size / UL_BIT) + ((size % UL_BIT) ? 1 : 0 ) + ARRAY_SIZE_SPOT] = {size};

// Alokuje nulované bitové pole
// (size / UL_BIT) -> počet bitov
// ((size % UL_BIT) ? 1 : 0 ) -> ak ostal zvyšok, pripočíta sa 1, aby bol správny počet bitov
// + ARRAY_SIZE_SPOT -> miesto na uloženie veľkosti poľa
#define bitset_alloc(array_name, size) \
    assert(size > 0); \
    unsigned long *array_name = calloc((size / UL_BIT) + ((size % UL_BIT) ? 1 : 0 ) + ARRAY_SIZE_SPOT, UL_BIT); \
    if (array_name == NULL) { \
        error_exit("bitset_alloc: Chyba alokace paměti"); \
    } array_name[0] = size;


#ifndef USE_INLINE
    // Uvoľní alokované pole
    #define bitset_free(array_name) \
        if(array_name != NULL) free(array_name);

    // Vráti veľkosť poľa z prvého indexu
    #define bitset_size(array_name) array_name[0] 

    // Nastaví bit na určenej pozícii
    #define bitset_setbit(array_name, index, expression) \
        if (index >= bitset_size(array_name)) error_exit("bitset_getbit: Index %lu mimo rozsah 0..%lu", (unsigned long)index, (unsigned long)bitset_size(array_name)); \
        (expression != 0) \
        ? ( array_name[MODIF_INDEX(index) / UL_BIT] |= (1UL << (MODIF_INDEX(index) % UL_BIT)) ) \
        : ( array_name[(MODIF_INDEX(index) / UL_BIT)] &= ~(1UL << (MODIF_INDEX(index) % UL_BIT)) ); 
        
    // Vráti hodnotu bitu na určenej pozícii
    #define bitset_getbit(array_name, index) \
        (index >= bitset_size(array_name)) \
        ? (error_exit("bitset_getbit: Index %lu mimo rozsah 0..%lu", (unsigned long)index, (unsigned long)bitset_size(array_name)), 0) \
        : ((array_name[MODIF_INDEX(index) / UL_BIT] & (1UL << (MODIF_INDEX(index) % UL_BIT )) ? 1U : 0U))


#else

    inline unsigned long bitset_size(bitset_t array_name) 
    { 
        return array_name[0]; 
    }

    inline void bitset_free(bitset_t array_name) 
    { 
        if(array_name != NULL) free(array_name); 
    }

    inline void bitset_setbit(bitset_t array_name, bitset_index_t index, int expression) 
    { 
        (expression != 0) ? (array_name[MODIF_INDEX(index) / UL_BIT] |= (1UL << (MODIF_INDEX(index) % UL_BIT)) ) 
        : (array_name[(MODIF_INDEX(index) / UL_BIT)] &= ~(1UL << (MODIF_INDEX(index) % UL_BIT)) ); 
    }

    inline unsigned bitset_getbit(bitset_t array_name, bitset_index_t index) 
    {
        if (index > bitset_size(array_name)) 
            return (error_exit("bitset_getbit: Index %lu mimo rozsah 0..%lu", (unsigned long)index, (unsigned long)bitset_size(array_name)), 0); 
        return ((array_name[MODIF_INDEX(index) / UL_BIT] & (1UL << (MODIF_INDEX(index) % UL_BIT ))) ? 1U : 0U);
    }

#endif