#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "CSG.h"

int strToIntCSG(char* str) {
    int res = 0;
    for (int i = 0; i < strlen(str); i++)
        res += str[i];
    return res;
}

int hashCSG(CSGLIST tuple) {
    return (tuple->StudentId + strToIntCSG(tuple->Course)) % sizeCSG;
}

bool areEqualCSG(CSGLIST a, CSGLIST b) {
    if (strcmp(a->Course, "*") == 0 || strcmp(b->Course, "*") == 0 || strcmp(a->Course, b->Course) == 0) 
        if (a->StudentId == 0 || b->StudentId == 0 || a->StudentId == b->StudentId)
            if (strcmp(a->Grade, "*") == 0 || strcmp(b->Grade, "*") == 0 || strcmp(a->Grade, b->Grade) == 0) 
                return true;
    return false;
}

void insertCSG(CSGLIST tuple) {
    if (lookupCSG(tuple) != NULL) {
        printf("Table CSG already contains tuple (%s, %d, %s)\n", tuple->Course, tuple->StudentId, tuple->Grade);
        return;
    }

    int index = hashCSG(tuple);
    if (tableCSG[index] == NULL) {
        tableCSG[index] = tuple;
        printf("Successfully inserted tuple (%s, %d, %s)\n", tuple->Course, tuple->StudentId, tuple->Grade);
        return;
    } else {
        CSGLIST item = tableCSG[index];
        while (item->next != NULL)
            item = item->next;
        item->next = tuple;
        printf("Successfully inserted tuple (%s, %d, %s)\n", tuple->Course, tuple->StudentId, tuple->Grade);
        return;
    }
}

void deleteCSG(CSGLIST tuple) {
    if (lookupCSG(tuple) == NULL) {
        printf("Error! Table CSG doesn't cotain tuple (%s, %d, %s)\n", tuple->Course, tuple->StudentId, tuple->Grade);
        return;
    }

    for (int index = 0; index < sizeCSG; index++) {
        CSGLIST last = NULL;
        CSGLIST item = tableCSG[index];
        while (item != NULL) {
            if (areEqualCSG(tuple, item)) {
                        // Found a item matched
                        printf("Deleting tuple (%s, %d, %s)\n", item->Course, item->StudentId, item->Grade);
                        if (last == NULL) {
                            tableCSG[index] = item->next;
                            free(item);
                            item = tableCSG[index];
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

CSGLIST lookupCSG(CSGLIST tuple) {
    CSGLIST res = NULL;
    CSGLIST last = NULL;
    for (int index = 0; index < sizeCSG; index++) {
        CSGLIST item = tableCSG[index];
        while (item != NULL) {
            if (areEqualCSG(tuple, item)) {
                if (res == NULL) {
                    CSGLIST copyItem = newCSG(item->Course, item->StudentId, item->Grade);

                    res = copyItem;
                    last = copyItem;
                } else {
                    CSGLIST copyItem = newCSG(item->Course, item->StudentId, item->Grade);

                    last->next = copyItem;
                    last = copyItem;
                }
            }
            item = item->next;
        }
    }
    return res;
}

CSGLIST newCSG(char *Course, int StudentId, char *Grade) {
    CSGLIST item = (CSGLIST) malloc(sizeof(struct CSG));
    item->Course = Course;
    item->StudentId = StudentId;
    item->Grade = Grade;
    item->next = NULL;
    return item;
}

void initTableCSG() {
    for (int i = 0; i < sizeCSG; i++)
        tableCSG[i] = NULL;
}

void printTableCSG() {
    for (int i = 0; i < sizeCSG; i++) {
        if (tableCSG[i] != NULL) {
            printf("%d ", i);
            CSGLIST item = tableCSG[i];
            while (item != NULL) {
                printf("(%s, %d, %s) ", item->Course, item->StudentId, item->Grade);
                item = item->next;
            }
            printf("\n");
        }
    }
}

int main() {
    insertCSG(newCSG("CS101", 12345, "A"));
    insertCSG(newCSG("CS101", 67890, "B"));
    insertCSG(newCSG("EE200", 12345, "C"));
    insertCSG(newCSG("EE200", 22222, "B+"));
    insertCSG(newCSG("CS101", 33333, "A-"));
    insertCSG(newCSG("PH100", 67890, "C+"));
    printTableCSG();

    printf("-----------------\n");
    CSGLIST res = lookupCSG(newCSG("CS101", 0, "*"));
    if (res == NULL) {
        printf("Not found\n");
    } else {
        while (res != NULL) {
            printf("(%s, %d, %s) ", res->Course, res->StudentId, res->Grade);
            res = res->next;
        }
        printf("\n");
    }

    printf("-----------------\n");
    deleteCSG(newCSG("CS101", 0, "*"));
    printTableCSG();

    return 0;
}