#include <stdlib.h>
#include <string.h>
#include <unistd.h> 
#include <sys/wait.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <strings.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../include/constants.h"
#include "../include/FDU.h"

void config_socket(int port_S_courant, int port_S_suivant, const char *pc_name, FDU *fdu) {
    int sock_C, sock_S;
    struct sockaddr_in sa_S_courant, sa_S_suivant, sa_S_precedent;
    unsigned int taille_sa;
    int nb_boucle = 1;

    // Taille de la structure sockaddr
    taille_sa = sizeof(struct sockaddr);
    
    //// Création de l'oreille (c.a.d socket serveur courant)
    
    // le socket UDP
    sock_S = socket(PF_INET, SOCK_DGRAM, 0); // UDP
    perror("🔌 socket");

    // Configuration adresse IP et du numéro de port du serveur
    bzero((char *) &sa_S_courant, sizeof(struct sockaddr_in));
    sa_S_courant.sin_family = AF_INET;
    sa_S_courant.sin_addr.s_addr = inet_addr(IP_addr_PC);
    sa_S_courant.sin_port = htons(port_S_courant); 
    
    // Attachement du socket
    bind(sock_S, (struct sockaddr *) &sa_S_courant, sizeof(struct sockaddr));
    perror("🔗 bind");
    
    //// Création de la bouche (c.a.d parle au serveur suivant)

    // le socket UDP, n° port quelconque 
    sock_C = socket(PF_INET, SOCK_DGRAM, 0);
    perror("🗣️ socket");
    
    // Configuration adresse IP et numero de port du serveur suivant
    bzero((char *) &sa_S_suivant, sizeof(struct sockaddr_in));
    sa_S_suivant.sin_family = AF_INET;
    sa_S_suivant.sin_addr.s_addr = inet_addr(IP_addr_PC);
    sa_S_suivant.sin_port = htons(port_S_suivant);

    //// Amorce (le 1er PC envoie le 1er message, à ne faire qu'une seule fois)
    if ((port_S_courant == host0) && (nb_boucle == 1)) {
        printf("🚀 [%s] Sending first message\n", pc_name);
        fflush(stdout);

        if (sendto(sock_C, fdu, sizeof(FDU), 0, (struct sockaddr *) &sa_S_suivant, taille_sa) < 0) {
            perror("❌ sendto failed");
        } else {
            printf("✅ [%s] Message sent to next PC\n", pc_name);
        }

        nb_boucle--; 
    }

    //// Boucle infinie 
    while(1) {
        printf("🔄 [%s] Waiting for message...\n", pc_name);
        fflush(stdout);
        int received = recvfrom(sock_S, fdu, sizeof(FDU), 0, (struct sockaddr *) &sa_S_precedent, &taille_sa);
        if (received < 0) {
            perror("❌ recvfrom failed");
        } else {
            printf("📩 Received FDU from previous PC: Type: %d, Message: %s\n", fdu->type, fdu->message);
            fflush(stdout);
        }

        sleep(2);
        
        // Envoi vers PC suivant 
        if (sendto(sock_C, fdu, sizeof(FDU), 0, (struct sockaddr *) &sa_S_suivant, taille_sa) < 0) {
            perror("❌ sendto failed");
        } else {
            printf("✅ [%s] Message sent to next PC\n", pc_name);
        }
    }

    //// Fin
    close(sock_S);
    close(sock_C);
    exit(EXIT_SUCCESS);
}

