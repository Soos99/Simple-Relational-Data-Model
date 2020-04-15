#ifndef C_h
#define C_h

#define sizeC 1009

typedef struct TUPLEC *TUPLELISTC;
struct TUPLEC {
    char *Course;
    char *Day;
    char *Hour;
    TUPLELISTC next;
};
typedef TUPLELISTC HASHTABLEC[sizeC];

TUPLELISTC newC(char *, char *, char *);
void insertC(TUPLELISTC);
void deleteC(TUPLELISTC);
TUPLELISTC lookupC(TUPLELISTC);
HASHTABLEC tableC;
void initTableC();
void printTableC();

#endif