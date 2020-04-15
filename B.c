#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "B.h"

int strToIntB(char* str) {
    int res = 0;
    for (int i = 0; i < strlen(str); i++)
        res += str[i];
    return res;
}

int hashB(TUPLELISTB tuple) {
    return (strToIntB(tuple->Course) + strToIntB(tuple->Prerequisite)) % sizeB;
}

bool areEqualB(TUPLELISTB a, TUPLELISTB b) {
    if (strcmp(a->Course, "*") == 0 || strcmp(b->Course, "*") == 0 || strcmp(a->Course, b->Course) == 0) 
        if (strcmp(a->Prerequisite, "*") == 0 || strcmp(b->Prerequisite, "*") == 0 || strcmp(a->Prerequisite, b->Prerequisite) == 0) 
            return true;
    return false;
}

void insertB(TUPLELISTB tuple) {
    if (lookupB(tuple) != NULL) {
        printf("Table B already contains tuple (%s, %s)\n", tuple->Course, tuple->Prerequisite);
        return;
    }

    int index = hashB(tuple);
    if (tableB[index] == NULL) {
        tableB[index] = tuple;
        printf("Successfully inserted tuple (%s, %s)\n", tuple->Course, tuple->Prerequisite);
        return;
    } else {
        TUPLELISTB item = tableB[index];
        while (item->next != NULL)
            item = item->next;
        item->next = tuple;
        printf("Successfully inserted tuple (%s, %s)\n", tuple->Course, tuple->Prerequisite);
        return;
    }
}

void deleteB(TUPLELISTB tuple) {
    if (lookupB(tuple) == NULL) {
        printf("Error! Table A doesn't cotain tuple (%s, %s)\n", tuple->Course, tuple->Prerequisite);
        return;
    }

    for (int index = 0; index < sizeB; index++) {
        TUPLELISTB last = NULL;
        TUPLELISTB item = tableB[index];
        while (item != NULL) {
            if (areEqualB(tuple, item)) {
                        // Found a item matched
                        printf("Deleting tuple (%s, %s)\n", item->Course, item->Prerequisite);
                        if (last == NULL) {
                            tableB[index] = item->next;
                            free(item);
                            item = tableB[index];
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

TUPLELISTB lookupB(TUPLELISTB tuple) {
    TUPLELISTB res = NULL;
    TUPLELISTB last = NULL;
    for (int index = 0; index < sizeB; index++) {
        TUPLELISTB item = tableB[index];
        while (item != NULL) {
            if (areEqualB(tuple, item)) {
                if (res == NULL) {
                    TUPLELISTB copyItem = newB(item->Course, item->Prerequisite);

                    res = copyItem;
                    last = copyItem;
                } else {
                    TUPLELISTB copyItem = newB(item->Course, item->Prerequisite);

                    last->next = copyItem;
                    last = copyItem;
                }
            }
            item = item->next;
        }
    }
    return res;
}

TUPLELISTB newB(char *Course, char *Prerequisite) {
    TUPLELISTB item = (TUPLELISTB) malloc(sizeof(struct TUPLEB));
    item->Course = Course;
    item->Prerequisite = Prerequisite;
    item->next = NULL;
    return item;
}

void initTableB() {
    for (int i = 0; i < sizeB; i++)
        tableB[i] = NULL;
}

void printTableB() {
    for (int i = 0; i < sizeB; i++) {
        if (tableB[i] != NULL) {
            printf("%d ", i);
            TUPLELISTB item = tableB[i];
            while (item != NULL) {
                printf("(%s, %s)", item->Course, item->Prerequisite);
                item = item->next;
            }
            printf("\n");
        }
    }
}

int main() {
    insertB(newB("CS101", "CS100"));
    insertB(newB("EE200", "EE005"));
    insertB(newB("EE200", "CS100"));
    insertB(newB("CS120", "CS101"));
    insertB(newB("CS121", "CS120"));
    insertB(newB("CS205", "CS101"));
    insertB(newB("CS206", "CS121"));
    insertB(newB("CS206", "CS205"));
    printTableB();

    printf("-----------\n");
    TUPLELISTB item = lookupB(newB("CS101", "*"));
    while (item != NULL) {
        printf("(%s, %s) ", item->Course, item->Prerequisite);
        item = item->next;
    }
    printf("\n");
    

    printf("-----------\n");
    deleteB(newB("CS101", "*"));
    printTableB();

    return 0;
}