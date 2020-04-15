#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "CSG.h"
#include "A.h"
#include "B.h"
#include "C.h"
#include "D.h"

void findGradeFromStudentNameAndCourseName() {
    printf("\n\nTesting for What grade did StudentName get in CourseName?\n");
    while (1) {
        char StudentName[255];
        char CourseName[255];

        printf("\nInput for Student Name (quit to stop): ");
        scanf ("%[^\n]%*c", StudentName);

        if (strcmp(StudentName, "quit") == 0)
            break;

        TUPLELISTA resA = lookupA(newA(0, StudentName, "*", "*"));
        if (resA == NULL) {
            printf("Error! not find any student with the name %s\n", StudentName);
            continue;
        }

        printf("Input for Course Name: ");
        scanf ("%[^\n]%*c", CourseName);


        CSGLIST resCSG = lookupCSG(newCSG(CourseName, resA->StudentId, "*"));
        if (resCSG == NULL) {
            printf("Error! not find any grade of student %s in course %s\n", StudentName, CourseName);
            continue;
        } 

        printf("%s got %s in %s\n", StudentName, resCSG->Grade, CourseName);
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

        TUPLELISTA resA = lookupA(newA(0, StudentName, "*", "*"));
        if (resA == NULL) {
            printf("Error! not find any student with the name %s\n", StudentName);
            continue;
        }
        CSGLIST resCSG = lookupCSG(newCSG("*", resA->StudentId, "*"));

        printf("Input for Day: ");
        scanf ("%[^\n]%*c", Day);

        printf("Input for Time: ");
        scanf ("%[^\n]%*c", Time);

        TUPLELISTC resC = NULL;
        for (CSGLIST item = resCSG; item != NULL; item = item->next) {
            TUPLELISTC temp = lookupC(newC(item->Course, Day, Time));
            if (temp != NULL)
                resC = temp;
        }

        if (resC == NULL) {
            printf("Error! not find any course at %s on %s\n", Time, Day);
            continue;
        }

        TUPLELISTD resD = lookupD(newD(resC->Course, "*"));
        if (resD == NULL) {
            printf("Error! not find place of course %s\n", resC->Course);
            continue;
        }

        printf("%s is in %s at %s on %s\n", StudentName, resD->Room, Time, Day);
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

    return 0;
}