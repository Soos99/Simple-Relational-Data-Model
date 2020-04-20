#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "CSG.h"
#include "C.h"
#include "D.h"
#include "QueryCSG.h"
#include "QueryCD.h"
#include "CD.h"
#define sizeCD 1009

int main() {
    populateCSG();
    printf("\nQuerying Student taking CS101...\n");
    QueryCSG qcsg = select_CSG("CS101",0,"*");
    printQuery(qcsg);
    project_CSG(0,1,0,qcsg);
    populateC();
    populateD();
    join_CR_CDH();
    printTableCD();
    printf("\nGetting Day and Hour of Turing Aud. Building....");
    QueryCD qcd = select_CD("*","*","Turing Aud.","*");
    project_CD(0,1,0,1,qcd);

    for (int i = 0; i < sizeC; i++) {
        if (tableC[i] != NULL) {
            freeC(tableC[i]);
        }
    }
    for (int i = 0; i < sizeD; i++) {
        if (tableD[i] != NULL) {
            freeD(tableD[i]);
        }
    }
    for (int i = 0; i < sizeCSG; i++) {
        if (tableCSG[i] != NULL) {
            freeCSG(tableCSG[i]);
        }
    }
    for (int i = 0; i < sizeCD; i++) {
        if (tableCD[i] != NULL) {
            freeCD(tableCD[i]);
        }
    }
    freeQueryCSG(qcsg);
    freeQueryCD(qcd);
    return 0;

}