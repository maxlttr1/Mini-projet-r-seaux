#include <stdlib.h>
#include <string.h>
#include"../include/pc.h"
#include"../include/FDU.h"

static const int ports[] = {8000, 8001, 8002};

int main() {
    
    FDU fdu; 

    fdu.type = Token;
    fdu.addr_source = ports[0];
    fdu.addr_dest = ports[1];
    strcpy(fdu.message, "Salut !");
    
    creation(ports[0], ports[1], &fdu);
    creation(ports[1], ports[2], &fdu);
    creation(ports[2], ports[0], &fdu);
}