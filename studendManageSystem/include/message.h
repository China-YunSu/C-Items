#ifndef _GRAPH_
#define _GRAPH_

#include "boolean.h"
#include "SIMS.h"

#define HEADER1 		" --------------------------------------------------------------------------------\n"
#define HEADER2 		"|   学号   |  姓名  | 数学成绩 | C语言成绩 | 英语成绩 | 总成绩 | 平均分 |  名次  |\n"
#define HEADER3 		"|----------|--------|----------|-----------|----------|--------|--------|--------|\n"
#define HEADER4         "    学号         姓名     数学成绩    C语言成绩   英语成绩   总成绩   平均分   名次\n"
#define FORMAT  		"| %-9s| %-7s|   %-7d|    %-7d|   %-7d|   %-5d| %-7.2f|  %d     |\n"
#define FORMAT2 		"%-9s%-13s%-17d%-16d%-11d%-10d%-10.2f%d\n"
#define PRINTLIST1		 student->data.ID,student->data.name,student->data.math,student->data.Cprogram
#define PRINTLIST2 		student->data.English,student->data.scores,student->data.average,student->data.rank
#define REFORMAT  		"%s %s %d %d %d"
#define RELIST			data.ID,data.name,&data.math,&data.Cprogram,&data.English

boolean menu(StuList *plist);
boolean display(StuList *plist);
boolean getInformation(Student *student);
boolean ModifyMessage(Student *local);
boolean pick(StuList *plist);
void show(void);

#endif 