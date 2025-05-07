#include <assert.h>
//#include <curses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "primitives.h"
#include <unistd.h>

#define ADRESSE_DISTANTE "127.0.0.1"
#define ADRESSE_LOCALE "127.0.0.1"
#define PORT_DISTANT 1920
#define PORT_LOCAL 1920
#define LONGUEUR_ADRESSE 16
#define LONGUEUR_MESSAGE 121

typedef struct paquet
{
	char adresse[LONGUEUR_ADRESSE];
	char message[LONGUEUR_MESSAGE];
} Paquet;

void traitePaquet(Paquet *p)
{
	char buffer[LONGUEUR_MESSAGE];

	if (strcmp(ADRESSE_LOCALE, p->adresse) == 0)
	/* si je suis le destinataire du paquet */
	{
		printf("✅ Je suis le destinataire\n");
		printf("📥 Le message qui m'est destine : %s \n\n", p->message);
	
	}
	else {
		/* sinon */
		printf("❌ Je ne suis pas le destinataire\n");
		printf("📥 Message pour %s : %s\n\n", p->adresse, p->message);
	}
}

int main () {
	int socketEmission, socketReception;
	char buffer[LONGUEUR_ADRESSE + LONGUEUR_MESSAGE];
	Paquet p;
	
	int	sizeofbuffer;
	sizeofbuffer = (LONGUEUR_ADRESSE + LONGUEUR_MESSAGE)*sizeof(char);

	socketEmission  = creePriseEmission(ADRESSE_DISTANTE, PORT_DISTANT);
    socketReception  = creePriseReception(PORT_LOCAL);

    printf("🔁 Host started\n");
    printf("Touche d pour demarrer...\n");
  	while (getchar() != 'd'); /* temporisation */

    while (1) {
        //if token available --> prompt for message or no 
        sprintf(buffer, "%15s%120s", ADRESSE_DISTANTE, "blablabla");
        printf("📮 J'envoie le paquet\n");
        envoie(socketEmission, buffer, strlen(buffer));

        sleep(2);

        memset (buffer, '\0', sizeofbuffer);
		recoit(socketReception, buffer, sizeof(buffer)-1);
		sscanf(buffer, "%15s%120s", &p.adresse, &p.message);
		traitePaquet(&p);
    }

	return 0;
}

