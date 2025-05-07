#pragma once
#include "FDU.h"

void traitement_token(FDU *fdu, int port_S_courant, int id);
void traitement_message(FDU *fdu, int port_S_courant, int id);
void creation(int id, int port_S_courant, int port_S_suivant, FDU *fdu, int nb_boucle);