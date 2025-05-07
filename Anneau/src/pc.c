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

// void init() {
    
// }

void traitement_token(FDU *fdu, int port_S_courant, int id) {

    
}

void traitement_message(FDU *fdu, int port_S_courant, int id) {
    
}

void creation(int id, int port_S_courant, int port_S_suivant, FDU *fdu, int nb_boucle) {
    int sock_C, sock_S;
    struct sockaddr_in sa_S_courant, sa_S_suivant, sa_S_precedent;
    unsigned int taille_sa;
	
    printf("PC %d -> Port_courant: %d, Port_suivant: %d, nb_boucle: %d\n", id, port_S_courant, port_S_suivant, nb_boucle);

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
	
    // Uniquement pour le 1er message du PC1
	if ( (port_S_courant == 8000) && (nb_boucle == 1) ) {
        fdu->type = Message;
        printf("PC %d : J'envoie un message\n", id);
		sendto(sock_C, fdu, sizeof(*fdu), 0, (struct sockaddr *) &sa_S_suivant, taille_sa);
		nb_boucle = 0; 

    } else {
        printf("sdlqkflksdlfksd\n");
        while(1) {
            // Reception sur Oreille courante
            recvfrom(sock_S, fdu, sizeof(*fdu), 0, (struct sockaddr *) &sa_S_precedent, &taille_sa);
            printf("Message reçu de l'adresse: %s, port: %d\n", inet_ntoa(sa_S_precedent.sin_addr), ntohs(sa_S_precedent.sin_port));

            
            // Traitement
            if (fdu->type == Token) {
                traitement_token(fdu, port_S_courant, id);
                printf("Le port est : %d, le port du fdu est : %d\n", port_S_courant, fdu->addr_dest);



                printf("PC %d : 🪙 Le type est Token, je passe le FDU\n", id);
                fflush(stdout);

                char send_mess[3];
                printf("Voulez-vous envoyer un message (oui/non) ? \n");
                fflush(stdout);
                scanf("%s", send_mess);

                if(strcmp(send_mess, "oui") == 0) {
                    // Envoi du message
                    char msg[100];
                    printf("Entrez votre message : \n");
                    fflush(stdout);
                    scanf("%s", msg);
                    fdu->type = Message;
                    strcpy(fdu->message, msg);

                    int dest;
                    printf("Entrez votre destinataire (0 / 1 / 2) : \n");
                    fflush(stdout);
                    scanf("%d", &dest);
                    
                    switch (dest) {
                    case 0:
                        dest = 8000; break;
                    case 1:
                        dest = 8001; break;
                    case 2:
                        dest = 8002; break;
                    }
                    
                    fdu->addr_dest = dest;
                    fdu->addr_source = port_S_courant; 
                }
            } else {
                traitement_message(fdu, port_S_courant, id);
                printf("Le port est: %d, le port du fdu est: %d\n", port_S_courant, fdu->addr_dest);

    
                printf("PC %d : 📨 Le type est Message, je regarde l'adresse:\n", id);
                fflush(stdout);
                if (fdu->addr_dest == port_S_courant) {
                    printf("PC %d : ✅ Message reçu de PC precedent : %s\n", id , fdu->message);
                    fflush(stdout);            
                    fdu->type = Token;
                } else {
                    printf("PC %d : ❌ Le Message n'est pas pour moi\n", id);
                    fflush(stdout);
                }
            }
            
            sleep(1);
            printf("\n");
            
            // Envoi vers PC suivant 
            sendto(sock_C, fdu, sizeof(*fdu), 0, (struct sockaddr *) &sa_S_suivant, taille_sa);
        }
    }
	
    //// Fin

	close(sock_S);
	close(sock_C);
    exit(EXIT_SUCCESS);
}

