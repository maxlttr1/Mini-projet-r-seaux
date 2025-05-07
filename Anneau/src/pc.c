#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <strings.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../include/FDU.h"
 
#define IP_addr_PC "127.0.0.1" // Adresse IP des PCs

void creation(int port_S_courant, int port_S_suivant, FDU *fdu) {
    int sock_C, sock_S;
    struct sockaddr_in sa_S_courant, sa_S_suivant, sa_S_precedent;
    unsigned int taille_sa;
	int nb_boucle = 1;

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
		sendto(sock_C, fdu, sizeof(*fdu), 0, (struct sockaddr *) &sa_S_suivant, taille_sa);
		nb_boucle--; 
	}
	
	
	//// boucle infinie 
	
	while(1)
	{
		// Reception sur Oreille courante
		recvfrom(sock_S, fdu, sizeof(*fdu), 0, (struct sockaddr *) &sa_S_precedent, &taille_sa);
		
		// Traitement (ICI : juste affichage)
		printf("Message reçu de PC precedent : %s\n", fdu->message);
		sleep(1);
		
		// Envoi vers PC suivant 
		sendto(sock_C, fdu, sizeof(*fdu), 0, (struct sockaddr *) &sa_S_suivant, taille_sa);
	}
	
	
    //// Fin

	close(sock_S);
	close(sock_C);
    exit(EXIT_SUCCESS);
}

