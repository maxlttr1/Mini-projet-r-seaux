/*
 * envoie.c
 * Emission d'un datagramme sur une socket UDP "connectée"
 */

#include <unistd.h>

#include "primitives.h"

int envoie (int prise, char *buffer, size_t taille)
{
    if (write (prise, buffer, taille) == taille)
	return 0;
    else
	return -1;
}

