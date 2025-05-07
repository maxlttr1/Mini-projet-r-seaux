/*
 * primitives.h
 * Prototypes des primitives UDP
 */

#include <sys/types.h>

int creePriseEmission (char *, int);

int creePriseReception (int);

int recoit (int, char *, size_t);

int envoie (int, char *, size_t);

