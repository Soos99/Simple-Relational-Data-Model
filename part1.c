#include <stdlib.h>
#include <stdio.h>

typedef struct TUPLEB *TUPLELISTB;
struct TUPLEB {
    char Course[5];
    char Prerequisite[5];
    TUPLELISTB next;
};
typedef TUPLELISTB HASHTABLEB[197];

typedef struct TUPLEC *TUPLELISTC;
struct TUPLEC {
    char Course[5];
    char Day[2];
    char Hour[7];
    TUPLELISTC next;
};
typedef TUPLELISTC HASHTABLEC[197];

typedef struct TUPLED *TUPLELISTD;
struct TUPLED {
    char Course[5];
    char Room[50];
    TUPLELISTD next;
};
typedef TUPLELISTD HASHTABLED[197];

CSGLIST initializeList() {
    CSGLIST first;
    CSGLIST second;
    CSGLIST third;
    CSGLIST fourth;
    CSGLIST fifth;
    CSGLIST sixth;

    first = (CSGLIST) malloc(sizeof(struct CSG));
    first->Course[5] = "CS101";
    first->StudentId = 12345;
    first->Grade[2] = "A";
    first->next = second;

    second = (CSGLIST) malloc(sizeof(struct CSG));
    second->Course[5] = "CS101";
    second->StudentId = 67890;
    second->Grade[2] = "B";
    second->next = third;
    
    third = (CSGLIST) malloc(sizeof(struct CSG));
    third->Course[5] = "EE200";
    third->StudentId = 12345;
    third->Grade[2] = "C";
    third->next = fourth;

    fourth = (CSGLIST) malloc(sizeof(struct CSG));
    fourth->Course[5] = "EE200";
    fourth->StudentId = 22222;
    fourth->Grade[2] = "B+";
    fourth->next = fifth;

    fifth = (CSGLIST) malloc(sizeof(struct CSG));
    fifth->Course[5] = "CS101";
    fifth->StudentId = 33333;
    fifth->Grade[2] = "A-";
    fifth->next = sixth;

    sixth = (CSGLIST) malloc(sizeof(struct CSG));
    sixth->Course[5] = "PH100";
    sixth->StudentId = 67890;
    sixth->Grade[2] = "C+";
    sixth->next = NULL;
}

void initializeTableA() {
    TUPLELISTA first;
    TUPLELISTA second;
    TUPLELISTA third;

    TUPLELISTA first = (TUPLELISTA) malloc(sizeof(struct TUPLEA));
    first->StudentId = 12345;
    first->Name[30] = "C. Brown";
    first->Address[50] = "12 Apple St.";
    first->Phone[8] = "555-1234";

    TUPLELISTA second = (TUPLELISTA) malloc(sizeof(struct TUPLEA));
    second->StudentId = 67890;
    second->Name[30] = "L. Van Pelt";
    second->Address[50] = "34 Pear Ave.";
    second->Phone[8] = "555-5678";

    TUPLELISTA third = (TUPLELISTA) malloc(sizeof(struct TUPLEA));
    third->StudentId = 22222;
    third->Name[30] = "P. Patty";
    third->Address[50] = "56 Grape Blvd.";
    third->Phone[8] = "555-9999";
}

