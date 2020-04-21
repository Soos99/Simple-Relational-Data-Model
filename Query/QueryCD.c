#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "../Hashtable/CD.h"
#include "QueryCD.h"

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
    TUPLELISTCD toLookUpCD = lookupCD(tuple);
    if (toLookUpCD == NULL){
        freeCD(tuple);
        printf("Error! Table CD doesn't contain tuple (%s, %s, %s, %s)\n", tuple->Course, tuple->Day, tuple->Room, tuple->Hour);
        return NULL;
    }
    for (int index = 0; index < sizeCD; index++) {
        TUPLELISTCD item = tableCD[index];
        while (item != NULL) {
            if (areEqualCD(tuple, item)) {
                if (query->result[index] == NULL) {
                    query->result[index] = newCD(item->Course,item->Day,item->Room,item->Hour);
                } else {
                    TUPLELISTCD item1 = query->result[index];
                    while (item1->next != NULL)
                        item1 = item1->next;
                    item1->next = newCD(item->Course,item->Day,item->Room,item->Hour);
                }
            }
            item = item->next;
        }
    }
    freeCD(tuple);
    freeCD(toLookUpCD);
    return query;
}

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
    for (int i = 0; i < sizeCD; i++) {
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

void freeQueryCD(QueryCD qcd){
    for (int i = 0; i < sizeCD; i++){
        if (qcd->result[i] != NULL)
            freeCD(qcd->result[i]);
    }
    free(qcd);
}