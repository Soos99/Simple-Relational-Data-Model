#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "C.h"

int strToIntC(char* str) {
    int res = 0;
    for (int i = 0; i < strlen(str); i++)
        res += str[i];
    return res;
}

int hashC(TUPLELISTC tuple) {
    return (strToIntC(tuple->Course) + strToIntC(tuple->Day) + strToIntC(tuple->Hour)) % sizeC;
}

bool areEqualC(TUPLELISTC a, TUPLELISTC b) {
    if (strcmp(a->Course, "*") == 0 || strcmp(b->Course, "*") == 0 || strcmp(a->Course, b->Course) == 0) 
        if (strcmp(a->Day, "*") == 0 || strcmp(b->Day, "*") == 0 || strcmp(a->Day, b->Day) == 0) 
            if (strcmp(a->Hour, "*") == 0 || strcmp(b->Hour, "*") == 0 || strcmp(a->Hour, b->Hour) == 0) 
                return true;
    return false;
}

void insertC(TUPLELISTC tuple) {
    if (lookupC(tuple) != NULL) {
        printf("Table B already contains tuple (%s, %s, %s)\n", tuple->Course, tuple->Day, tuple->Hour);
        return;
    }

    int index = hashC(tuple);
    if (tableC[index] == NULL) {
        tableC[index] = tuple;
        printf("Successfully inserted tuple (%s, %s, %s)\n", tuple->Course, tuple->Day, tuple->Hour);
        return;
    } else {
        TUPLELISTC item = tableC[index];
        while (item->next != NULL)
            item = item->next;
        item->next = tuple;
        printf("Successfully inserted tuple (%s, %s, %s)\n", tuple->Course, tuple->Day, tuple->Hour);
        return;
    }
}

void deleteC(TUPLELISTC tuple) {
    if (lookupC(tuple) == NULL) {
        printf("Error! Table A doesn't cotain tuple (%s, %s, %s)\n", tuple->Course, tuple->Day, tuple->Hour);
        return;
    }

    for (int index = 0; index < sizeC; index++) {
        TUPLELISTC last = NULL;
        TUPLELISTC item = tableC[index];
        while (item != NULL) {
            if (areEqualC(tuple, item)) {
                // Found a item matched
                printf("Deleting tuple (%s, %s, %s)\n", item->Course, item->Day, item->Hour);
                if (last == NULL) {
                    tableC[index] = item->next;
                    free(item);
                    item = tableC[index];
                    continue;
                } else {
                    last->next = item->next;
                    free(item);
                    item = last->next;
                    continue;
                }
            }
            last = item;
            item = item->next;
        }
    }
}

TUPLELISTC lookupC(TUPLELISTC tuple) {
    TUPLELISTC res = NULL;
    TUPLELISTC last = NULL;
    for (int index = 0; index < sizeC; index++) {
        TUPLELISTC item = tableC[index];
        while (item != NULL) {
            if (areEqualC(tuple, item)) {
                if (res == NULL) {
                    TUPLELISTC copyItem = newC(item->Course, item->Day, item->Hour);

                    res = copyItem;
                    last = copyItem;
                } else {
                    TUPLELISTC copyItem = newC(item->Course, item->Day, item->Hour);

                    last->next = copyItem;
                    last = copyItem;
                }
            }
            item = item->next;
        }
    }
    return res;
}

TUPLELISTC newC(char *Course, char *Day, char *Hour) {
    TUPLELISTC item = (TUPLELISTC) malloc(sizeof(struct TUPLEC));
    item->Course = Course;
    item->Day = Day;
    item->Hour = Hour;
    item->next = NULL;
    return item;
}

void initTableC() {
    for (int i = 0; i < sizeC; i++)
        tableC[i] = NULL;
}

void printTableC() {
    printf("\nPrinting table C:\n");
    for (int i = 0; i < sizeC; i++) {
        if (tableC[i] != NULL) {
            printf("%d ", i);
            TUPLELISTC item = tableC[i];
            while (item != NULL) {
                printf("(%s, %s, %s)", item->Course, item->Day, item->Hour);
                item = item->next;
            }
            printf("\n");
        }
    }
    printf("\n");
}

void populateC() {
    insertC(newC("CS101", "M", "9AM"));
    insertC(newC("CS101", "W", "9AM"));
    insertC(newC("CS101", "F", "9AM"));
    insertC(newC("EE200", "Tu", "10AM"));
    insertC(newC("EE200", "W", "1PM"));
    insertC(newC("EE200", "Th", "10AM"));
}

void tryC() {
    populateC();
    printTableC();

    printf("-----------\n");
    TUPLELISTC item = lookupC(newC("CS101", "*", "*"));
    while (item != NULL) {
        printf("(%s, %s, %s) ", item->Course, item->Day, item->Hour);
        item = item->next;
    }
    printf("\n");
    

    printf("-----------\n");
    deleteC(newC("CS101", "*", "*"));
    printTableC();
}