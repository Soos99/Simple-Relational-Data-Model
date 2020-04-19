#ifndef CSG_h
#define CSG_h

#define sizeCSG 1009

typedef struct CSG *CSGLIST;
struct CSG {
    char* Course;
    int StudentId;
    char* Grade;
    CSGLIST next;
};
typedef CSGLIST HASHTABLECSG[sizeCSG];

CSGLIST newCSG(char *, int, char*);
void insertCSG(CSGLIST);
void deleteCSG(CSGLIST);
CSGLIST lookupCSG(CSGLIST);
HASHTABLECSG tableCSG;
bool areEqualCSG(CSGLIST a, CSGLIST b);
void initTableCSG();
void printTableCSG();
void populateCSG();
void tryCSG();

#endif

// INSERT and LOOKUP: for string, * = everything. And for int, 0 = everything