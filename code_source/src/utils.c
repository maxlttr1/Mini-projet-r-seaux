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

#include "../include/constants.h" // Définitions des constantes comme host1, host2
#include "../include/FDU.h"  // Structure FDU utilisée pour transporter les messages et les jetons

// Fonction appelée lorsqu'on reçoit un jeton (type == Token): permet à l'utilisateur d'envoyer un message s'il le souhaite
void traitement_token(FDU *fdu, int port_S_courant) {
    printf("🪙 Le type est Token\n");
    fflush(stdout);

    char send_mess[10];
    printf("Voulez-vous envoyer un message (oui/non) ? \n");
    fflush(stdout);
    fgets(send_mess, sizeof(send_mess), stdin);
    send_mess[strcspn(send_mess, "\n")] = 0;  // Remove trailing newline

    if (strcmp(send_mess, "oui") == 0) {
        char msg[100];
        printf("Entrez votre message : \n");
        fflush(stdout);
        fgets(msg, sizeof(msg), stdin);
        msg[strcspn(msg, "\n")] = 0;

        // Préparation de la structure FDU pour l'envoi du message
        fdu->type = Message;
        strcpy(fdu->message, msg);

        // Saisie du destinataire
        char dest_str[10];
        int dest;
        printf("Entrez votre destinataire (1 / 2 / 3) : \n");
        fflush(stdout);
        fgets(dest_str, sizeof(dest_str), stdin);
        sscanf(dest_str, "%d", &dest);

        // Conversion logique du numéro de destinataire en port
        if (dest == 1) {
            dest = host1;
        } else if (dest == 2) {
            dest = host2;
        } else if (dest == 3) {
            dest = host3;
        }

        fdu->addr_dest = dest;
        fdu->addr_source = port_S_courant;
    }

}

// Fonction appelée lorsqu'on reçoit un message: vérifie si le message est destiné à ce PC
void traitement_message(FDU *fdu, int port_S_courant) {
    printf("📨 Le type est Message, je regarde l'adresse :\n");
    fflush(stdout);
    if (fdu->addr_dest == port_S_courant) {
        printf("✅ Message reçu de PC precedent : %s\n", fdu->message);
        fflush(stdout);
        fdu->type = Token;
        traitement_token(fdu, port_S_courant);
    } else {
        printf("❌ Le Message n'est pas pour moi\n");
        fflush(stdout);
    }
}

// Configuration des sockets UDP pour la communication entre les PC: gère à la fois l'écoute et l'envoi des messages
void config_socket(int port_S_courant, int port_S_suivant, const char *pc_name, FDU *fdu) {
    int sock_C, sock_S;
    struct sockaddr_in sa_S_courant, sa_S_suivant, sa_S_precedent;
    unsigned int taille_sa;
    int nb_boucle = 1;

    // Taille de la structure sockaddr
    taille_sa = sizeof(struct sockaddr);
    
    //// Création de l'oreille (c.a.d socket serveur courant)
    
    //// Création du socket serveur (pour écouter les messages entrants)
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
    
    //// Création du socket client (pour envoyer les messages au suivant)
    sock_C = socket(PF_INET, SOCK_DGRAM, 0);
    perror("🗣️ socket");
    
    // Configuration adresse IP et numero de port du serveur suivant
    bzero((char *) &sa_S_suivant, sizeof(struct sockaddr_in));
    sa_S_suivant.sin_family = AF_INET;
    sa_S_suivant.sin_addr.s_addr = inet_addr(IP_addr_PC);
    sa_S_suivant.sin_port = htons(port_S_suivant);

    //// Amorce (le 1er PC envoie le 1er message, à ne faire qu'une seule fois)
    if ((port_S_courant == host1) && (nb_boucle == 1)) {
        sleep(5);
        printf("🚀 [%s] Envoi du 1er message\n", pc_name);
        fflush(stdout);

        if (sendto(sock_C, fdu, sizeof(FDU), 0, (struct sockaddr *) &sa_S_suivant, taille_sa) < 0) {
            perror("❌ sendto failed");
        } else {
            printf("✅ [%s] Message envoyé au PC suivant\n", pc_name);
        }

        nb_boucle--; 
    }

    //// Boucle principale : écoute, traitement, réémission
    while(1) {
        printf("🔄 [%s] En attente d'un message...\n", pc_name);
        fflush(stdout);
        int received = recvfrom(sock_S, fdu, sizeof(FDU), 0, (struct sockaddr *) &sa_S_precedent, &taille_sa);
        if (received < 0) {
            perror("❌ recvfrom failed");
        }

        // Appel du bon traitement selon le type
        if (fdu->type == Token) {
            traitement_token(fdu, port_S_courant);
        } else {
            traitement_message(fdu, port_S_courant);
        }

        sleep(2);
        
        // Envoi vers PC suivant 
        if (sendto(sock_C, fdu, sizeof(FDU), 0, (struct sockaddr *) &sa_S_suivant, taille_sa) < 0) {
            perror("❌ sendto failed");
        } else {
            printf("✅ [%s] Message envoyé au PC suivant\n", pc_name);
        }
    }

    //// Libération des sockets
    close(sock_S);
    close(sock_C);
    exit(EXIT_SUCCESS);
}

