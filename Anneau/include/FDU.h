#pragma once

enum TypeFDU {
    Token, 
    Message
};

typedef struct FDU {
    enum TypeFDU type;
    char message[100];
    int addr_source;
    int addr_dest;
} FDU;