/*
 * recoit.c
 * Attente d'un datagramme sur une socket UDP
 */

#include <unistd.h>

#include "primitives.h"

int recoit (int prise, char *buffer, size_t taille)
{
    if (read (prise, buffer, taille) >= 0)
	return 0;
    else
	return -1;
}

