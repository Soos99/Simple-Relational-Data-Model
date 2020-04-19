#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "CSG.h"
#include "A.h"
#include "B.h"
#include "C.h"
#include "D.h"
#define sizeCD 1009

struct ListCSG {
    CSGLIST result[sizeCSG];
};

typedef struct ListCSG *QueryCSG;

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

struct ListTableCD {
    TUPLELISTCD result[sizeCD];
};
typedef struct ListTableCD *QueryCD;


QueryCSG newQueryCSG(){
    QueryCSG query = (QueryCSG) malloc(sizeof(struct ListCSG));
    for (int i = 0; i < sizeCSG; i++){
        query->result[i] = NULL;
    }
    return query;
}

QueryCSG select_CSG(char *Course, int StudentId, char *Grade) {
    QueryCSG query = newQueryCSG();
    CSGLIST tuple = newCSG(Course,StudentId,Grade);
    //check null
    if (lookupCSG(tuple) == NULL){
        printf("Error! Table CSG doesn't contain tuple (%s, %d, %s)\n", tuple->Course, tuple->StudentId, tuple->Grade);
        return NULL;
    }
    for (int index = 0; index < sizeCSG; index++) {
        CSGLIST item = tableCSG[index];
        while (item != NULL) {
            if (areEqualCSG(tuple, item)) {
                if (query->result[index] == NULL) {
                    query->result[index] = item;
                } else {
                    CSGLIST item1 = query->result[index];
                    while (item1->next != NULL)
                        item1 = item1->next;
                    item1->next = item;
                }
            }
            item = item->next;
        }
        //printf("\n");
    }
    return query;
}
void printQuery(QueryCSG table){
    if (table->result == NULL) return;
    printf("\nPrinting resulted query:\n");
    for (int i = 0; i < sizeCSG; i++) {
        if (table->result[i] != NULL) {
            //printf("%d ", i);
            CSGLIST item = table->result[i];
            while (item != NULL) {
                printf("(%s, %d, %s) ", item->Course, item->StudentId, item->Grade);
                item = item->next;
            }
            printf("\n");
        }
    }
    printf("\n");
}

void project_CSG(int projectCourse, int projectStudentId, int projectGrade, QueryCSG table){
    if (!projectCourse && !projectStudentId && !projectGrade){
        printf("Error! No attribute is selected...\n");
        return;
    }
    printf("\nProjecting...\n");
    if (projectCourse) {
        printf("Course ");
    }
    if (projectStudentId) {
        if (projectCourse)
            printf("| StudentId ");
        else 
            printf("StudentId ");
    }
    if (projectGrade) {
        if (projectCourse || projectStudentId)
            printf("| Grade");
        else
            printf("Grade");
        
    }
    printf("\n");
    for (int i = 0; i < sizeCSG; i++) {
        if (table->result[i] != NULL) {
            //printf("%d ", i);
            CSGLIST item = table->result[i];
            while (item != NULL) {
                if (projectCourse) {
                    printf("%7s", item->Course);
                }
                 if (projectStudentId) {
                    if (projectCourse)
                        printf("| %9d ", item->StudentId);
                    else
                        printf("%9d ", item->StudentId);
                }
                if (projectGrade) {
                    if (projectCourse || projectStudentId)
                        printf("| %5s",item->Grade);
                    else
                        printf("%5s",item->Grade);
                    
                }
                item = item->next;
            }
            printf("\n");
        }
    }
    printf("\n");
}
int strToIntCD(char* str) {
    int res = 0;
    for (int i = 0; i < strlen(str); i++)
        res += str[i];
    return res;
}

TUPLELISTCD newCD(char *Course, char *Day, char *Room, char *Hour) {
    TUPLELISTCD item = (TUPLELISTCD) malloc(sizeof(struct TUPLECD));
    item->Course = Course;
    item->Day = Day;
    item->Hour = Hour;
    item->Room = Room;
    item->next = NULL;
    return item;
}

int hashCD(TUPLELISTCD tuple) {
    return (strToIntCD(tuple->Course) + strToIntCD(tuple->Day) + strToIntCD(tuple->Hour)) % sizeCD;
}
void insertCD(TUPLELISTCD tuple) {
    int index = hashCD(tuple);
    if (tableCD[index] == NULL) {
        tableCD[index] = tuple;
        return;
    } else {
        TUPLELISTCD item = tableCD[index];
        while (item->next != NULL)
            item = item->next;
        item->next = tuple;
        return;
    }
}
//join table C and D
void join_CR_CDH(){
    for (int index = 0; index < sizeC; index++) {
        TUPLELISTC itemC = tableC[index];
        while (itemC != NULL) {
            for (int index1 = 0; index1 < sizeD; index1++){
                TUPLELISTD itemD = tableD[index1];
                while (itemD != NULL){
                    if (strcmp(itemC->Course,itemD->Course) == 0){
                        TUPLELISTCD itemCD = newCD(itemC->Course,itemC->Day,itemD->Room,itemC->Hour);
                        insertCD(itemCD);
                    }
                    itemD = itemD->next;
                }
            }
            itemC = itemC->next;
        }
    }
    return;
}

void printTableCD(){
    printf("\nPrinting joined table CD:\n");
    printf("Course | Day |     Room    | Hour\n");
    for (int i = 0; i < sizeCD; i++) {
        if (tableCD[i] != NULL) {
            //printf("%d ", i);
            TUPLELISTCD item = tableCD[i];
            while (item != NULL) {
                printf("%7s| %3s | %10s | %s", item->Course, item->Day, item->Room, item->Hour);
                item = item->next;
            }
            printf("\n");
        }
    }
    printf("\n");
}
bool areEqualCD(TUPLELISTCD a, TUPLELISTCD b){
    if (strcmp(a->Course, "*") == 0 || strcmp(b->Course, "*") == 0 || strcmp(a->Course, b->Course) == 0) 
        if (strcmp(a->Day, "*") == 0 || strcmp(b->Day, "*") == 0 || strcmp(a->Day, b->Day) == 0) 
            if (strcmp(a->Hour, "*") == 0 || strcmp(b->Hour, "*") == 0 || strcmp(a->Hour, b->Hour) == 0)
                if (strcmp(a->Room, "*") == 0 || strcmp(b->Room, "*") == 0 || strcmp(a->Room, b->Room) == 0) 
                    return true;
    return false;
}

TUPLELISTCD lookupCD(TUPLELISTCD tuple) {
    TUPLELISTCD res = NULL;
    TUPLELISTCD last = NULL;
    for (int index = 0; index < sizeCD; index++) {
        TUPLELISTCD item = tableCD[index];
        while (item != NULL) {
            if (areEqualCD(tuple, item)) {
                if (res == NULL) {
                    TUPLELISTCD copyItem = newCD(item->Course, item->Day, item->Room, item->Hour);

                    res = copyItem;
                    last = copyItem;
                } else {
                    TUPLELISTCD copyItem = newCD(item->Course, item->Day, item->Room, item->Hour);

                    last->next = copyItem;
                    last = copyItem;
                }
            }
            item = item->next;
        }
    }
    return res;
}

QueryCD newQueryCD(){
    QueryCD query = (QueryCD) malloc(sizeof(struct ListTableCD));
    for (int i = 0; i < sizeCD; i++){
        query->result[i] = NULL;
    }
    return query;
}

QueryCD select_CD(char *Course, char *Day, char *Room, char *Hour) {
    QueryCD query = newQueryCD();
    TUPLELISTCD tuple = newCD(Course,Day,Room,Hour);
    //check null
    if (lookupCD(tuple) == NULL){
        printf("Error! Table CD doesn't contain tuple (%s, %s, %s, %s)\n", tuple->Course, tuple->Day, tuple->Room, tuple->Hour);
        return NULL;
    }
    for (int index = 0; index < sizeCD; index++) {
        TUPLELISTCD item = tableCD[index];
        while (item != NULL) {
            if (areEqualCD(tuple, item)) {
                if (query->result[index] == NULL) {
                    query->result[index] = item;
                } else {
                    TUPLELISTCD item1 = query->result[index];
                    while (item1->next != NULL)
                        item1 = item1->next;
                    item1->next = item;
                }
            }
            item = item->next;
        }
    }
    return query;
}


// void printQuery(QueryCSG table){
//     if (table->result == NULL) return;
//     printf("\nPrinting resulted query:\n");
//     for (int i = 0; i < sizeCSG; i++) {
//         if (table->result[i] != NULL) {
//             //printf("%d ", i);
//             CSGLIST item = table->result[i];
//             while (item != NULL) {
//                 printf("(%s, %d, %s) ", item->Course, item->StudentId, item->Grade);
//                 item = item->next;
//             }
//             printf("\n");
//         }
//     }
//     printf("\n");
// }

void project_CD(int projectCourse, int projectDay, int projectRoom, int projectHour, QueryCD table){
    if (!projectCourse && !projectDay && !projectRoom && !projectHour){
        printf("Error! No attribute is selected...\n");
        return;
    }
    printf("\nProjecting...\n");
    if (projectCourse) {
        printf("Course ");
    }
    if (projectDay) {
        if (projectCourse)
            printf("| Day ");
        else 
            printf("Day ");
    }
    if (projectRoom) {
        if (projectCourse || projectDay)
            printf("| Room");
        else
            printf("Room");
    }
    if (projectHour) {
        if (projectCourse || projectDay || projectRoom)
            printf("| Hour");
        else
            printf("Hour");
    }
    printf("\n");
    for (int i = 0; i < sizeCSG; i++) {
        if (table->result[i] != NULL) {
            //printf("%d ", i);
            TUPLELISTCD item = table->result[i];
            while (item != NULL) {
                if (projectCourse) {
                    printf("%7s", item->Course);
                }
                 if (projectDay) {
                    if (projectCourse)
                        printf("| %3s ", item->Day);
                    else
                        printf("%3s ", item->Day);
                }
                if (projectRoom) {
                    if (projectCourse || projectDay)
                        printf("| %10s",item->Room);
                    else
                        printf("%10s",item->Room);
                    
                }
                if (projectHour) {
                    if (projectCourse || projectDay || projectRoom)
                        printf("| %s",item->Hour);
                    else
                        printf("%s",item->Hour);
                    
                }
                item = item->next;
            }
            printf("\n");
        }
    }
    printf("\n");
}

int main() {
    populateCSG();
    printQuery(select_CSG("CS101",0,"*"));
    project_CSG(0,1,0,select_CSG("CS101",0,"*"));
    populateC();
    populateD();
    join_CR_CDH();
    printTableCD();
    project_CD(0,1,0,1,select_CD("*","*","Turing Aud.","*"));
    return 0;
}