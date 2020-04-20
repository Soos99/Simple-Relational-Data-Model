#ifndef QueryCSG_h
#define QueryCSG_h
#include "CSG.h"

struct ListCSG {
    CSGLIST result[sizeCSG];
};

typedef struct ListCSG *QueryCSG;

QueryCSG newQueryCSG();
QueryCSG select_CSG(char *Course, int StudentId, char *Grade);
void printQuery(QueryCSG table);
void project_CSG(int projectCourse, int projectStudentId, int projectGrade, QueryCSG table);
void freeQueryCSG(QueryCSG csg);

#endif