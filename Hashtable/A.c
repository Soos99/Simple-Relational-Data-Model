#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "A.h"

int strToIntA(char* str) {
    int res = 0;
    for (int i = 0; i < strlen(str); i++)
        res += str[i];
    return res;
}

int hashA(TUPLELISTA tuple) {
    return (tuple->StudentId + strToIntA(tuple->Name) + strToIntA(tuple->Address) + strToIntA(tuple->Phone)) % sizeA;
}

bool areEqualA(TUPLELISTA a, TUPLELISTA b) {
    if (a->StudentId == 0 || b->StudentId == 0 || a->StudentId == b->StudentId)
        if (strcmp(a->Name, "*") == 0 || strcmp(b->Name, "*") == 0 || strcmp(a->Name, b->Name) == 0)
            if (strcmp(a->Address, "*") == 0 || strcmp(b->Address, "*") == 0 || strcmp(a->Address, b->Address) == 0) 
                if (strcmp(a->Phone, "*") == 0 || strcmp(b->Phone, "*") == 0 || strcmp(a->Phone, b->Phone) == 0) 
                    return true;
    return false;
}

void insertA(TUPLELISTA tuple) {
    if (lookupA(tuple) != NULL) {
        printf("Table A already contains tuple (%d, %s, %s, %s)\n", tuple->StudentId, tuple->Name, tuple->Address, tuple->Phone);
        return;
    }

    int index = hashA(tuple);
    if (tableA[index] == NULL) {
        tableA[index] = tuple;
        printf("Successfully inserted tuple(%d, %s, %s, %s)\n", tuple->StudentId, tuple->Name, tuple->Address, tuple->Phone);
        return;
    } else {
        TUPLELISTA item = tableA[index];
        while (item->next != NULL)
            item = item->next;
        item->next = tuple;
        printf("Successfully inserted tuple (%d, %s, %s, %s)\n", tuple->StudentId, tuple->Name, tuple->Address, tuple->Phone);
        return;
    }
}

void deleteA(TUPLELISTA tuple) {
    TUPLELISTA toLookUp = lookupA(tuple);
    if (toLookUp == NULL) {
        printf("Error! Table A doesn't cotain tuple (%d, %s, %s, %s)\n", tuple->StudentId, tuple->Name, tuple->Address, tuple->Phone);
        return;
    }

    for (int index = 0; index < sizeA; index++) {
        TUPLELISTA last = NULL;
        TUPLELISTA item = tableA[index];
        while (item != NULL) {
            if (areEqualA(tuple, item)) {
                        // Found a item matched
                        printf("Deleting tuple (%d, %s, %s, %s)\n", item->StudentId, item->Name, item->Address, item->Phone);
                        if (last == NULL) {
                            tableA[index] = item->next;
                            freeA(item);
                            item = tableA[index];
                            continue;
                        } else {
                            last->next = item->next;
                            freeA(item);
                            item = last->next;
                            continue;
                        }
                    }
            last = item;
            item = item->next;
        }
    }
    freeA(toLookUp);
}

TUPLELISTA lookupA(TUPLELISTA tuple) {
    TUPLELISTA res = NULL;
    TUPLELISTA last = NULL;
    for (int index = 0; index < sizeA; index++) {
        TUPLELISTA item = tableA[index];
        while (item != NULL) {
            if (areEqualA(tuple, item)) {
                if (res == NULL) {
                    TUPLELISTA copyItem = newA(item->StudentId, item->Name, item->Address, item->Phone);

                    res = copyItem;
                    last = copyItem;
                } else {
                    TUPLELISTA copyItem = newA(item->StudentId, item->Name, item->Address, item->Phone);

                    last->next = copyItem;
                    last = copyItem;
                }
            }
            item = item->next;
        }
    }
    return res;
}

TUPLELISTA newA(int StudentId, char *Name, char *Address, char *Phone) {
    TUPLELISTA item = (TUPLELISTA) malloc(sizeof(struct TUPLEA));
    item->StudentId = StudentId;
    item->Name = Name;
    item->Address = Address;
    item->Phone = Phone;
    item->next = NULL;
    return item;
}

void initTableA() {
    for (int i = 0; i < sizeA; i++)
        tableA[i] = NULL;
}

void printTableA() {
    printf("\nPrinting table A:\n");
    for (int i = 0; i < sizeA; i++) {
        if (tableA[i] != NULL) {
            printf("%d ", i);
            TUPLELISTA item = tableA[i];
            while (item != NULL) {
                printf("(%d, %s, %s, %s) ", item->StudentId, item->Name, item->Address, item->Phone);
                item = item->next;
            }
            printf("\n");
        }
    }
    printf("\n");
}

void populateA() {
    printf("\nInitializing table A\n");
    insertA(newA(12345, "C. Brown", "12 Apple St.", "555-1234"));
    insertA(newA(67890, "L. Van Pelt", "34 Pear Ave.", "555-5678"));
    insertA(newA(22222, "P. Patty", "56 Grape Blvd.", "555-9999"));
}

void tryA() {
    populateA();
    printTableA();

    printf("------\n");
    TUPLELISTA toLookUp = newA(12345, "*", "*", "*");
    TUPLELISTA item = lookupA(toLookUp);
    TUPLELISTA copy = item;
    while (item != NULL) {
        printf("(%d, %s, %s, %s) ", item->StudentId, item->Name, item->Address, item->Phone);
        item = item->next;
    }
    printf("\n");

    printf("------\n");
    TUPLELISTA toDelete = newA(12345, "*", "*", "*");
    deleteA(toDelete);
    printTableA();

    for (int i = 0; i < sizeA; i++) {
        if (tableA[i] != NULL) {
            freeA(tableA[i]);
        }
    }
    if (copy != NULL) freeA(copy);
    freeA(toDelete);
    freeA(toLookUp);
}
void freeA(TUPLELISTA a){
    if (a->next)
        freeA(a->next);
    free(a);
}