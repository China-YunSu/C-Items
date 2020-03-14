#ifndef _USER_TYPE_H_
#define _USER_TYPE_H_

#include "boolean.h"

typedef struct information {
	char ID[9];
	char name[7];
	int math;
    int English;
    int Cprogram;
    int scores;
    float average;
    int rank;
}USER_TYPE;

boolean isSame (USER_TYPE one, USER_TYPE two);

#endif
