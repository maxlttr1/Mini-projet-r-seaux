#ifndef FDU_H
#define FDU_H

enum TypeFDU {
    Token, 
    Message
};

typedef struct FDU {
    TypeFDU type;
    char message[10];
    int addr_source;
    int addr_dest;
};

#endif