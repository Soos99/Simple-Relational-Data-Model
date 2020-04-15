#include <stdlib.h>
#include <stdio.h>

#include "CSG.h"
#include "A.h"
#include "B.h"
#include "C.h"
#include "D.h"

int main() {
    printf("\t\t\t\t\t\tTRY TABLE CSG:\n");
    tryCSG();
    printf("\t------------------------------------------------------------------------------------------------------------\n");


    printf("\t\t\t\t\t\tTRY TABLE A:\n");
    tryA();
    printf("\t------------------------------------------------------------------------------------------------------------\n");

    printf("\t\t\t\t\t\tTRY TABLE B:\n");
    tryB();
    printf("\t------------------------------------------------------------------------------------------------------------\n");
    

    printf("\t\t\t\t\t\tTRY TABLE C:\n");
    tryC();
    printf("\t------------------------------------------------------------------------------------------------------------\n");

    printf("\t\t\t\t\t\tTRY TABLE D:\n");
    tryD();
    printf("\t------------------------------------------------------------------------------------------------------------\n");

    return 0;
}

