#include <stdlib.h>
#include <string.h>
#include <unistd.h> 
#include <sys/wait.h>
#include "../include/pc.h"
#include "../include/FDU.h"

#define NB_PC 3

static const int ports[] = {8000, 8001, 8002};

int main() {
    FDU fdu;
    fdu.type = Message;
    fdu.addr_source = ports[0];
    fdu.addr_dest = ports[1];
    strcpy(fdu.message, "Salut !");
    
    int nb_boucle;

    // Lancer chaque PC dans un processus séparé
    for (int i = 0; i < NB_PC ; i++) {
        int pid = fork(); 
        if (pid == 0) {
            // Processus fils
            nb_boucle = i + 1; 
            int port_courant = ports[i];
            int port_suivant = ports[(i+1) % 3];
            creation(i, port_courant, port_suivant, &fdu, nb_boucle);
            exit(0);
        }
    }

    // Attendre la fin des processus fils
    for (int i = 0; i < 3; i++) wait(NULL);

}