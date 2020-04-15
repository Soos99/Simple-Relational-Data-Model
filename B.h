#ifndef B_h
#define B_h

#define sizeB 1009

typedef struct TUPLEB *TUPLELISTB;
struct TUPLEB {
    char *Course;
    char *Prerequisite;
    TUPLELISTB next;
};
typedef TUPLELISTB HASHTABLEB[sizeB];

TUPLELISTB newB(char *, char *);
void insertB(TUPLELISTB);
void deleteB(TUPLELISTB);
TUPLELISTB lookupB(TUPLELISTB);
HASHTABLEB tableB;
void initTableB();
void printTableB();
void populateB();
void tryB();

#endif