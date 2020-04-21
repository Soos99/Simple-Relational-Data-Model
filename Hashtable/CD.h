#ifndef CD_h
#define CD_h

#define sizeCD 1009

typedef struct TUPLECD *TUPLELISTCD;
struct TUPLECD {
    char* Course;
    char* Room;
    char* Day;
    char* Hour;
    TUPLELISTCD next;
};
typedef TUPLELISTCD HASHTABLECD[sizeCD];
HASHTABLECD tableCD;

TUPLELISTCD newCD(char *Course, char *Day, char *Room, char *Hour);
void join_CR_CDH();
void printTableCD();
bool areEqualCD(TUPLELISTCD a, TUPLELISTCD b);
TUPLELISTCD lookupCD(TUPLELISTCD tuple);
void freeCD(TUPLELISTCD cd);

#endif