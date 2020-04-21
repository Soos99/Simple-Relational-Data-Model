#ifndef QueryCD_h
#define QueryCD_h
#include "../Hashtable/CD.h"


struct ListTableCD {
    TUPLELISTCD result[sizeCD];
};
typedef struct ListTableCD *QueryCD;

QueryCD newQueryCD();
QueryCD select_CD(char *Course, char *Day, char *Room, char *Hour);
void project_CD(int projectCourse, int projectDay, int projectRoom, int projectHour, QueryCD table);
void freeQueryCD(QueryCD cd);

#endif
