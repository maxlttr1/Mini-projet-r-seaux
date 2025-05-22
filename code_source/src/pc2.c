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
#include "../include/utils.h" // Nos fonctions
#include "../include/FDU.h" // Structure FDU utilisée pour transporter les messages et tokens

int port_S_courant = host2;
int port_S_suivant = host3;

int main() {
    FDU fdu;
    // Lancement de la configuration réseau et du traitement
    config_socket(port_S_courant, port_S_suivant, hostname2, &fdu);
}