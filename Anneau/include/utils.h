#include "../include/FDU.h"

#pragma once

void traitement_message(FDU *fdu, int port_S_courant);
void traitement_token(FDU *fdu, int port_S_courant);
void config_socket(int port_S_courant, int port_S_suivant, const char *pc_name, FDU *fdu);