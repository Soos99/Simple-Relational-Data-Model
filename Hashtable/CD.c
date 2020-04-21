#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "C.h"
#include "D.h"
#include "CD.h"

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

void freeCD(TUPLELISTCD cd){
    if (cd->next)
        freeCD(cd->next);
    free(cd);
}