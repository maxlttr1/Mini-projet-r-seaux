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

int port_S_courant = host1;
int port_S_suivant = host0;

int main() {
    config_socket(port_S_courant, port_S_suivant, hostname2);
}