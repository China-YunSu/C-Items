#ifndef _SIMS_
#define _SMIS_

#include <stdio.h>
#include <math.h>

#include "boolean.h"//Ã·π©boolean
#include "myLink.h"

typedef   link Student;
typedef   list StuList; 
typedef   USER_TYPE  Data;

int compare_order;

Student *newOneStudent(void);
boolean readInformation(list *plist);
int compare(Data data1, Data data2);
boolean sort(StuList *plist);
boolean dataDeal(Data *student);
void swap(Data *one, Data *another);
boolean insertOneStudent(StuList *plist);
boolean searchStudent(StuList *plist);
boolean ModifyInformation(StuList *plist);
boolean removeOneStudent(StuList *plist);
boolean clear(StuList *plist);
boolean equal (Student *phead, Student* data);
void output(StuList *plist);

#endif