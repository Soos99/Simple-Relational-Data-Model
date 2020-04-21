#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "./Hashtable/CSG.h"
#include "./Hashtable/A.h"
#include "./Hashtable/B.h"
#include "./Hashtable/C.h"
#include "./Hashtable/D.h"

void findGradeFromStudentNameAndCourseName() {
    printf("\n\nTesting for What grade did StudentName get in CourseName?\n");
    while (1) {
        char StudentName[255];
        char CourseName[255];

        printf("\nInput for Student Name (quit to stop): ");
        scanf ("%[^\n]%*c", StudentName);

        if (strcmp(StudentName, "quit") == 0)
            break;

        TUPLELISTA toLookUpA = newA(0, StudentName, "*", "*");
        TUPLELISTA resA = lookupA(toLookUpA);
        if (resA == NULL) {
            freeA(toLookUpA);
            printf("Error! not find any student with the name %s\n", StudentName);
            continue;
        }

        printf("Input for Course Name: ");
        scanf ("%[^\n]%*c", CourseName);

        CSGLIST toLookUpCSG = newCSG(CourseName, resA->StudentId, "*");
        CSGLIST resCSG = lookupCSG(toLookUpCSG);
        if (resCSG == NULL) {
            freeA(toLookUpA);
            if (resA != NULL) free(resA);
            freeCSG(toLookUpCSG);
            printf("Error! not find any grade of student %s in course %s\n", StudentName, CourseName);
            continue;
        }

        printf("%s got %s in %s\n", StudentName, resCSG->Grade, CourseName);
        freeA(toLookUpA);
        freeA(resA);
        freeCSG(toLookUpCSG);
        freeCSG(resCSG);
    }   
}

void findPlaceFromStudentNameAndDayAndTime() {
    printf("\n\nTesting for Where is StudentName at Time on Day?\n");
    while (1) {
        char StudentName[255];
        char Day[255];
        char Time[255];

        printf("\nInput for Student Name (quit to stop): ");
        scanf ("%[^\n]%*c", StudentName);

        if (strcmp(StudentName, "quit") == 0)
            break;

        TUPLELISTA toLookUpA = newA(0, StudentName, "*", "*");
        TUPLELISTA resA = lookupA(toLookUpA);
        if (resA == NULL) {
            freeA(toLookUpA);
            printf("Error! not find any student with the name %s\n", StudentName);
            continue;
        }

        CSGLIST toLookUpCSG = newCSG("*", resA->StudentId, "*");
        CSGLIST resCSG = lookupCSG(toLookUpCSG);

        printf("Input for Day: ");
        scanf ("%[^\n]%*c", Day);

        printf("Input for Time: ");
        scanf ("%[^\n]%*c", Time);

        TUPLELISTC resC = NULL;
        for (CSGLIST item = resCSG; item != NULL; item = item->next) {
            TUPLELISTC toLookUpC = newC(item->Course, Day, Time);
            TUPLELISTC temp = lookupC(toLookUpC);
            if (temp != NULL)
                resC = temp;
            freeC(toLookUpC);
        }

        if (resC == NULL) {
            freeA(toLookUpA);
            freeA(resA);
            freeCSG(toLookUpCSG);
            if (resCSG != NULL) freeCSG(resCSG);
            printf("Error! not find any course at %s on %s\n", Time, Day);
            continue;
        }

        TUPLELISTD toLookUpD = newD(resC->Course, "*");
        TUPLELISTD resD = lookupD(toLookUpD);
        if (resD == NULL) {
            freeA(toLookUpA);
            freeA(resA);
            freeCSG(toLookUpCSG);
            if (resCSG != NULL) freeCSG(resCSG);
            freeD(toLookUpD);
            printf("Error! not find place of course %s\n", resC->Course);
            continue;
        }

        printf("%s is in %s at %s on %s\n", StudentName, resD->Room, Time, Day);
        freeA(toLookUpA);
        freeA(resA);
        freeCSG(toLookUpCSG);
        freeCSG(resCSG);
        freeC(resC);
        freeD(toLookUpD);
        freeD(resD);
    }   
}

int main() {
    populateCSG();
    populateA();
    populateB();
    populateC();
    populateD();

    findGradeFromStudentNameAndCourseName();
    findPlaceFromStudentNameAndDayAndTime();

    //free populated tables
    for (int i = 0; i < sizeA; i++) {
        if (tableA[i] != NULL) {
            freeA(tableA[i]);
        }
    }
    for (int i = 0; i < sizeB; i++) {
        if (tableB[i] != NULL) {
            freeB(tableB[i]);
        }
    }
    for (int i = 0; i < sizeC; i++) {
        if (tableC[i] != NULL) {
            freeC(tableC[i]);
        }
    }
    for (int i = 0; i < sizeD; i++) {
        if (tableD[i] != NULL) {
            freeD(tableD[i]);
        }
    }
    for (int i = 0; i < sizeCSG; i++) {
        if (tableCSG[i] != NULL) {
            freeCSG(tableCSG[i]);
        }
    }

    return 0;
}