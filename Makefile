# -*- Makefile -*-
CC = gcc
CFLAGS = -O2 -g -std=c11 -pedantic -Wall -Wextra
LFLAGS = -lm
TARGETS = primes primes-i steg-decode

all: ${TARGETS}

run: ${TARGETS}
	./primes
	./primes-i

primes: primes.o bitset.o error.o eratosthenes.o
	$(CC) $(CFLAGS) primes.o eratosthenes.o bitset.o error.o -o primes ${LFLAGS}

primes-i: primes-i.o bitset-i.o error.o eratosthenes-i.o 
	$(CC) -DUSE_INLINE $(CFLAGS) primes-i.o eratosthenes-i.o bitset-i.o error.o -o primes-i ${LFLAGS}

steg-decode: steg-decode.o ppm.o error.o eratosthenes.o bitset.o
	$(CC) $(CFLAGS) ppm.o error.o steg-decode.o eratosthenes.o bitset.o -o steg-decode ${LFLAGS} 

# Steg-decode

steg-decode.o: steg-decode.c
	$(CC) $(CFLAGS) -c steg-decode.c -o steg-decode.o

ppm.o: ppm.c ppm.h 
	$(CC) $(CFLAGS) -c ppm.c -o ppm.o

# Primes

primes.o: primes.c
	$(CC) $(CFLAGS) -c primes.c -o primes.o

eratosthenes.o: eratosthenes.c eratosthenes.h
	$(CC) $(CFLAGS) -c eratosthenes.c -o eratosthenes.o

bitset.o: bitset.c bitset.h
	$(CC) $(CFLAGS) -c bitset.c -o bitset.o

# Primes-i

primes-i.o: primes.c
	$(CC) -DUSE_INLINE $(CFLAGS) -c primes.c -o primes-i.o

bitset-i.o: bitset.c bitset.h
	$(CC) -DUSE_INLINE $(CFLAGS) -c bitset.c -o bitset-i.o

eratosthenes-i.o: eratosthenes.c eratosthenes.h
	$(CC) -DUSE_INLINE $(CFLAGS) -c eratosthenes.c -o eratosthenes-i.o

error.o: error.c error.h
	$(CC) $(CFLAGS) -c error.c
