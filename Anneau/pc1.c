#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <strings.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#include "FDU.h"


// Formation de la couche basse de l'anneau (emulation couche physique)
// Chaque PC muni de 2 sockets :
// -> 1 oreille : socket serveur pour recevoir du PC precedent
// -> 1 bouche : socket client pour envoyer vers le PC suivant 
// Tous les PCs sur la boucle locale => différencies que pas leur port serveur
// Par ex. 3 PC, faire : 
//		port 8000 -> port 8001 -> port 8002 (-> reboucle sur port 8000)
//		circulation d'un message d'un PC à l'autre
// 		amorce : PC port 8000 envoie le tout 1er message  
// 		Executer d'abord les pc2 et pc3, et en dernier le pc1   
 
#define IP_addr_PC "127.0.0.1" // Adresse IP des PCs
#define port_S_courant 8000 // Port serveur courant (oreille courante)
#define port_S_suivant 8001 // Port serveur suivant (oreille suivante)

int main()
{
    int sock_C, sock_S;
    struct sockaddr_in sa_S_courant, sa_S_suivant, sa_S_precedent;
    unsigned int taille_sa;
    char message[10] = "Salut";
	int nb_boucle = 1;

    struct FDU fdu;

    fdu.type = Token;
    fdu.addr_source = 8000;
    fdu.addr_dest = 8001;
    strcpy(fdu.message, "Salut");


    printf("Type: %s\n", fdu.type);
    printf("Message: %s\n", fdu.message);
    printf("Source Address: %d\n", fdu.addr_source);
    printf("Destination Address: %d\n", fdu.addr_dest);

    


    // Taille de la structure sockaddr
    taille_sa = sizeof(struct sockaddr);
	

    //// Création de l'oreille (c.a.d socket serveur courant)
	
	// le socket UDP
    sock_S = socket(PF_INET, SOCK_DGRAM, 0); // UDP
    perror("socket ");

    // Configuration adresse IP et du numéro de port du serveur
    bzero((char *) &sa_S_courant, sizeof(struct sockaddr_in));
    sa_S_courant.sin_family = AF_INET;
    sa_S_courant.sin_addr.s_addr = inet_addr(IP_addr_PC);
    sa_S_courant.sin_port = htons(port_S_courant); 
	
    // Attachement du socket
    bind(sock_S, (struct sockaddr *) &sa_S_courant, sizeof(struct sockaddr));
    perror("bind ");
	
	
	//// Creation de la bouche (c.a.d parle au serveur suivant)

    // le socket UDP, n° port quelconque 
    sock_C = socket(PF_INET, SOCK_DGRAM, 0);
    perror("socket");
	
    // Configuration adresse IP et numero de port du serveur suivant
    bzero((char *) &sa_S_suivant, sizeof(struct sockaddr_in));
    sa_S_suivant.sin_family = AF_INET;
    sa_S_suivant.sin_addr.s_addr = inet_addr(IP_addr_PC);
    sa_S_suivant.sin_port = htons(port_S_suivant);

    
	//// Amorce (PC port 8000 envoie le 1er message, à ne faire qu'une seule fois)
	
	
	if ( (port_S_courant == 8000) && (nb_boucle == 1) )
	{
		sendto(sock_C, message, 10 * sizeof(char), 0, (struct sockaddr *) &sa_S_suivant, taille_sa);
		nb_boucle--; 
	}
	
	
	//// boucle infinie 
	
	while(1)
	{
		// Reception sur Oreille courante
		recvfrom(sock_S, message, 10 * sizeof(char), 0, (struct sockaddr *) &sa_S_precedent, &taille_sa);
		
		// Traitement (ICI : juste affichage)
		printf("Message reçu de PC precedent : %s\n", message);
		sleep(1);
		
		// Envoi vers PC suivant 
		sendto(sock_C, message, 10 * sizeof(char), 0, (struct sockaddr *) &sa_S_suivant, taille_sa);
	}
	
	
    //// Fin

	close(sock_S);
	close(sock_C);
    exit(EXIT_SUCCESS);
}
