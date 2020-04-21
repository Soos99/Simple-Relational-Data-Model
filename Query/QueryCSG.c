#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "../Hashtable/CSG.h"
#include "QueryCSG.h"

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
    CSGLIST toLookUpCSG = lookupCSG(tuple);
    if (toLookUpCSG == NULL){
        freeCSG(tuple);
        printf("Error! Table CSG doesn't contain tuple (%s, %d, %s)\n", tuple->Course, tuple->StudentId, tuple->Grade);
        return NULL;
    }
    for (int index = 0; index < sizeCSG; index++) {
        CSGLIST item = tableCSG[index];
        while (item != NULL) {
            if (areEqualCSG(tuple, item)) {
                if (query->result[index] == NULL) {
                    query->result[index] = newCSG(item->Course,item->StudentId,item->Grade);
                } else {
                    CSGLIST item1 = query->result[index];
                    while (item1->next != NULL)
                        item1 = item1->next;
                    item1->next = newCSG(item->Course,item->StudentId,item->Grade);
                }
            }
            item = item->next;
        }
    }
    freeCSG(tuple);
    freeCSG(toLookUpCSG);
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

void freeQueryCSG(QueryCSG csg){
    for (int i = 0; i < sizeCSG; i++){
        if (csg->result[i]){
            freeCSG(csg->result[i]);
        }
    }
    free(csg);
}