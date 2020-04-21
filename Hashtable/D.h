#ifndef D_h
#define D_h

#define sizeD 1009

typedef struct TUPLED *TUPLELISTD;
struct TUPLED {
    char *Course;
    char *Room;
    TUPLELISTD next;
};
typedef TUPLELISTD HASHTABLED[sizeD];

TUPLELISTD newD(char *, char *);
void insertD(TUPLELISTD);
void deleteD(TUPLELISTD);
TUPLELISTD lookupD(TUPLELISTD);
HASHTABLED tableD;
void initTableD();
void printTableD();
void populateD();
void tryD();
void freeD(TUPLELISTD);

#endif