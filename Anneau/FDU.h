#ifndef FDU_H
#define FDU_H

typedef struct FDU {
    char type[10];
    char message[10];
    int addr_source;
    int addr_dest;
};

#endif;