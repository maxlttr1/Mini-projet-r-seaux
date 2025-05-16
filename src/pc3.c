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
#include "../include/utils.h"
#include "../include/FDU.h"

int port_S_courant = host3;
int port_S_suivant = host1;

int main() {
    FDU fdu;
    config_socket(port_S_courant, port_S_suivant, hostname3, &fdu);
}