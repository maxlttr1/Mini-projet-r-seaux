#include <assert.h>
//#include <curses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "primitives.h"

/* emetteur PC1 ---> recepteur PC2 */

#define ADRESSE_EMETTEUR	"127.0.0.1"
#define ADRESSE_RECEPTEUR	"127.0.0.1"
#define PORT_RECEPTEUR		1920
#define LONGUEUR_ADRESSE	16
#define LONGUEUR_MESSAGE	121

typedef struct paquet
{
	char adresse[LONGUEUR_ADRESSE];
	char message[LONGUEUR_MESSAGE];
} Paquet;


int main (int argc, char **argv)
{
	int priseEmission; //, priseReception;
	char buffer[LONGUEUR_ADRESSE + LONGUEUR_MESSAGE];
	//Paquet p;
	
	int	sizeofbuffer;

	priseEmission  = creePriseEmission(ADRESSE_RECEPTEUR, PORT_RECEPTEUR);

	printf("J'envoie le 1er paquet \n");
	printf("Touche d pour demarrer...\n");
  	while (getchar() != 'd'); /* temporisation */

	sprintf(buffer, "%15s%120s", ADRESSE_RECEPTEUR, "blablabla");
	envoie(priseEmission, buffer, strlen(buffer));
	/* ex. remplissage 1er paquet puis emission */

	printf("PC1 démarre ...\n\n");

	/* boucle en emission */
	
	sizeofbuffer = (LONGUEUR_ADRESSE + LONGUEUR_MESSAGE)*sizeof(char);
	
	do
	{
		printf("Envoyer un autre paquet ? \n");
		printf("Touche e pour continuer...\n");
  		while (getchar() != 'e'); /* temporisation */

		memset (buffer, '\0', sizeofbuffer);

		sprintf(buffer, "%15s%120s", ADRESSE_RECEPTEUR, "nouveauBlabla");

		envoie(priseEmission, buffer, strlen(buffer));

	} while (1);

	return 0;
}

