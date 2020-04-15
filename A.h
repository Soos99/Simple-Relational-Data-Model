#ifndef A_h
#define A_h

#define sizeA 1009

typedef struct TUPLEA *TUPLELISTA;
struct TUPLEA {
    int StudentId;
    char *Name;
    char *Address;
    char *Phone;
    TUPLELISTA next;
};
typedef TUPLELISTA HASHTABLEA[sizeA];

TUPLELISTA newA(int, char *, char *, char*);
void insertA(TUPLELISTA);
void deleteA(TUPLELISTA);
TUPLELISTA lookupA(TUPLELISTA);
HASHTABLEA tableA;
void initTableA();

#endif