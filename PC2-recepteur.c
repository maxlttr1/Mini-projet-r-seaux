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
/* Paquet <=> struct paquet */  

void traitePaquet(Paquet *p)
{
	char buffer[LONGUEUR_MESSAGE];

	if (strcmp(ADRESSE_EMETTEUR, p->adresse) == 0)
	/* si je suis le destinataire du paquet */
	{
		printf("Je suis le destinataire. \n");
		printf("Le message qui m'est destine : %s \n\n", p->message);
	
	}
	else
		/* sinon */
		printf("Je ne suis pas le destinataire. \n");
		printf("Message pour %s : %s\n\n", p->adresse, p->message);
}

int main (int argc, char **argv)
{
	int    priseReception; //priseEmission, priseReception;
	char   buffer[LONGUEUR_ADRESSE + LONGUEUR_MESSAGE];
	Paquet p;
	
	priseReception = creePriseReception(PORT_RECEPTEUR);
	
	printf("Je recois \n");
	printf("Touche d pour demarrer...\n");
  	while (getchar() != 'd'); /* temporisation */

	printf("PC2 demarre ...\n\n");

	/*boucle en reception*/
	do
	{
		memset (buffer, '\0', sizeof(buffer));

		recoit(priseReception, buffer, sizeof(buffer)-1);

		sscanf(buffer, "%15s%120s", &p.adresse, &p.message);

		traitePaquet(&p);

	} while (1); /* boucle infinie */

  return 0;
}

