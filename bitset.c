// bitset.c
// Řešení IJC-DU1, příklad a), 14.3.2021
// Autor: Dominika Sedileková, FIT
// Přeloženo: gcc version 8.2.0 (GCC)
// použitie inline funkcií aj pri vypnutej optimalizácii

#include "bitset.h"

#ifdef USE_INLINE

    extern unsigned long bitset_size(bitset_t array_name);

    extern void bitset_free(bitset_t array_name);

    extern void bitset_setbit(bitset_t array_name, bitset_index_t index, int expression);

    extern unsigned bitset_getbit(bitset_t array_name, bitset_index_t index);

#endif
