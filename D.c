#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "D.h"

int strToIntD(char* str) {
    int res = 0;
    for (int i = 0; i < strlen(str); i++)
        res += str[i];
    return res;
}

int hashD(TUPLELISTD tuple) {
    return (strToIntD(tuple->Course) + strToIntD(tuple->Room)) % sizeD;
}

bool areEqualD(TUPLELISTD a, TUPLELISTD b) {
    if (strcmp(a->Course, "*") == 0 || strcmp(b->Course, "*") == 0 || strcmp(a->Course, b->Course) == 0) 
        if (strcmp(a->Room, "*") == 0 || strcmp(b->Room, "*") == 0 || strcmp(a->Room, b->Room) == 0) 
            return true;
    return false;
}

void insertD(TUPLELISTD tuple) {
    if (lookupD(tuple) != NULL) {
        printf("Table B already contains tuple (%s, %s)\n", tuple->Course, tuple->Room);
        return;
    }

    int index = hashD(tuple);
    if (tableD[index] == NULL) {
        tableD[index] = tuple;
        printf("Successfully inserted tuple (%s, %s)\n", tuple->Course, tuple->Room);
        return;
    } else {
        TUPLELISTD item = tableD[index];
        while (item->next != NULL)
            item = item->next;
        item->next = tuple;
        printf("Successfully inserted tuple (%s, %s)\n", tuple->Course, tuple->Room);
        return;
    }
}

void deleteD(TUPLELISTD tuple) {
    if (lookupD(tuple) == NULL) {
        printf("Error! Table A doesn't cotain tuple (%s, %s)\n", tuple->Course, tuple->Room);
        return;
    }

    for (int index = 0; index < sizeD; index++) {
        TUPLELISTD last = NULL;
        TUPLELISTD item = tableD[index];
        while (item != NULL) {
            if (areEqualD(tuple, item)) {
                        // Found a item matched
                        printf("Deleting tuple (%s, %s)\n", item->Course, item->Room);
                        if (last == NULL) {
                            tableD[index] = item->next;
                            free(item);
                            item = tableD[index];
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

TUPLELISTD lookupD(TUPLELISTD tuple) {
    TUPLELISTD res = NULL;
    TUPLELISTD last = NULL;
    for (int index = 0; index < sizeD; index++) {
        TUPLELISTD item = tableD[index];
        while (item != NULL) {
            if (areEqualD(tuple, item)) {
                if (res == NULL) {
                    TUPLELISTD copyItem = newD(item->Course, item->Room);

                    res = copyItem;
                    last = copyItem;
                } else {
                    TUPLELISTD copyItem = newD(item->Course, item->Room);

                    last->next = copyItem;
                    last = copyItem;
                }
            }
            item = item->next;
        }
    }
    return res;
}

TUPLELISTD newD(char *Course, char *Room) {
    TUPLELISTD item = (TUPLELISTD) malloc(sizeof(struct TUPLED));
    item->Course = Course;
    item->Room = Room;
    item->next = NULL;
    return item;
}

void initTableD() {
    for (int i = 0; i < sizeD; i++)
        tableD[i] = NULL;
}

void printTableD() {
    printf("\nPrinting table D:\n");
    for (int i = 0; i < sizeD; i++) {
        if (tableD[i] != NULL) {
            printf("%d ", i);
            TUPLELISTD item = tableD[i];
            while (item != NULL) {
                printf("(%s, %s)", item->Course, item->Room);
                item = item->next;
            }
            printf("\n");
        }
    }
    printf("\n");
}

void tryD() {
    insertD(newD("CS101", "Turing Aud."));
    insertD(newD("EE200", "25 Ohm Hall"));
    insertD(newD("PH100", "Newton Lab."));
    printTableD();

    printf("-----------\n");
    TUPLELISTD item = lookupD(newD("CS101", "*"));
    while (item != NULL) {
        printf("(%s, %s) ", item->Course, item->Room);
        item = item->next;
    }
    printf("\n");
    

    printf("-----------\n");
    deleteD(newD("CS101", "*"));
    printTableD();
}