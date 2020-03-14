#include <stdio.h>
#include <string.h>

#include "./include/SIMS.h"
#include "./include/boolean.h"
#include "./include/message.h"


boolean menu(StuList *plist) {
	int order;
	char choice[3];

	show();
	while(scanf("%d",&order) && order <= 0 || order > 10) {
		printf("输入错误！\n请重新输入：");
	}

	switch (order) {
		case 1 : readInformation(plist);		 			 break;
		case 2 : sort(plist);								 break;
		case 3 : display(plist);ModifyInformation(plist);	 break;
		case 4 : display(plist);removeOneStudent(plist); 	 break;
		case 5 : display(plist);			 				 break;
		case 6 : display(plist);insertOneStudent(plist)	;	 break;
		case 7 : output(plist);								 break;
		case 8 : pick(plist);				 				 break;
		case 9 : searchStudent(plist);		 				 break;
		case 10 :clear(plist);
	}

	if(order != 1 && order != 5 && order != 7 && order != 8 && order != 9 && order!=10) {
		fflush(stdin);
		printf("是否输出查看?(Yes or No)\n");
		scanf("%3s",choice);
		!strcmp(choice,"Yes") ? display(plist) : 0; 

	}

	fflush(stdin);
	printf("按任意键继续.......");
	getch();

	return order == 10;
}

void show(void) {
	system("cls");
		printf("\n\n	   			                  学生成绩管理系统\n\n");
		
		printf("\t\t*************************************************************************************\n");
		printf("\t\t*                                                                                   *\n");
		printf("\t\t*             1. 录入学生信息                  2. 学生排名                          *\n");
		printf("\t\t*                                                                                   *\n");
		printf("\t\t*             3. 修改学生信息                  4. 学生删除                          *\n");
		printf("\t\t*                                                                                   *\n");
		printf("\t\t*             5. 显示学生成绩                  6. 增添学生                          *\n");
		printf("\t\t*                                                                                   *\n");
		printf("\t\t*             7. 打印学生信息                  8. 筛选学生                          *\n");
		printf("\t\t*                                                                              	    *\n");
		printf("\t\t*             9. 搜索学生                      10.退出系统                          *\n");
		printf("\t\t*                                                                                   *\n");
		printf("\t\t*************************************************************************************\n\n");
		printf("\n\n请输入序号：");
}

boolean getInformation(Student *student) {
	
	if(NULL == student) {
		return FALSE;
	}

	printf("请输入学号:");
	scanf("%8s",student->data.ID);
	printf("请输入姓名:");
	scanf("%7s",student->data.name);
	printf("请输入数学成绩：");
	scanf("%d",&student->data.math);
	printf("请输入C语言成绩：");
	scanf("%d",&student->data.Cprogram);
	printf("请输入英语成绩：");
	scanf("%d",&student->data.English);

	return TRUE;
}

boolean ModifyMessage(Student *local) {
	int order;
	
	if(NULL == local) {
		return FALSE;
	}

	printf("1.修改学号               	2.修改姓名\n");
	printf("3.修改数学成绩            	4.修改C语言成绩\n");
	printf("5.修改英语成绩\n");
	printf("请输入编号：");
	scanf("%d",&order);

	switch (order) {//修改项
		case 1 : printf("请输入修改学号："); scanf("%8s",local->data.ID); return TRUE;
		case 2 : printf("请输入修改姓名："); scanf("%6s",local->data.name); return TRUE;
		case 3 : printf("请输入修改的数学成绩:"); scanf("%d",&(local->data.math)); return TRUE;
		case 4 : printf("请输入修改的C语言成绩:"); scanf("%d",&(local->data.Cprogram)); return TRUE;
		case 5 : printf("请输入修改的英语成绩:"); scanf("%d",&(local->data.English)); return TRUE;
		default :printf("输入错误!请重新输入：\n"); scanf("%d",&order); return FALSE; 
	}
}

int getorder(void) {
	int order;

	printf("1.学号			2.数学成绩\n");
	printf("3.英语成绩		4.C语言成绩\n");
	printf("5.总成绩	\n");
	printf("输入序号：");
	scanf("%d",&order);

	if(order < 0 || order > 5) {
		printf("请输入有效序号!\n");
		order = getorder();
	}

	return order;
}

boolean display(StuList *plist) {
	Student *student;
	int rank = 1;
	
	if(NULL == plist) {
		printf("无学生信息\n");
		return FALSE;
	}

	student = plist->head;
	printf(HEADER1);
	printf(HEADER2);
	printf(HEADER3);
	while(student) {
		dataDeal(&student->data);
		student->data.rank = rank++;
		printf(FORMAT,PRINTLIST1,PRINTLIST2);
		printf(HEADER3);
		student = student->next;
	}
	return TRUE;
}

boolean pick(StuList *plist) {

	int order;
	int rank = 1;
	int standard;
	Data temp = {0};
	Student *index = NULL;
	Student *student = NULL;
	char fileflag = FALSE;
	char filename[20];
	FILE *fp;

	if(NULL == plist || NULL == plist->head) {
		return FALSE;
	}
	printf("按什么筛选?\n");
	printf("1.数学成绩		2.英语成绩\n");
	printf("3.C语言成绩		4.总成绩\n");
	printf("输入序号：");
	scanf("%d",&compare_order);

	while(order < 0 && order > 4) {
		printf("请输入有效序号!\n");
		scanf("%d",&order);
	}
	printf("多少分数以上?");
	scanf("%d",&standard);

	printf("是否文件输出?(Yes or No)\n");
	fflush(stdin);
	scanf("%s",filename);
	if(!strcmp(filename,"Yes")) {
		printf("请输入文件名：");
		scanf("%s",filename);
		if(NULL == (fp = fopen(filename,"w"))) {
			printf("%s打开失败",filename);
		}
		fileflag = TRUE;
	}
	student =(Student*) calloc(sizeof(Student),1);
	switch (compare_order) {
		case 1:  temp.math = standard; 	 	break;
		case 2:  temp.English = standard; 	break;
		case 3:  temp.Cprogram = standard;  break;
		case 4:  temp.scores = standard;    break;
	}
	compare_order++;
	printf(HEADER1);
	printf(HEADER2);
	printf(HEADER3);
	for(index = plist->head; index; index = index->next) {
			if(index->data == temp || compare(index->data,temp)){
				*student = *index;
				student->data.rank = rank++;
				fileflag ? fprintf(fp,FORMAT2,PRINTLIST1,PRINTLIST2):0;
				printf(FORMAT,PRINTLIST1,PRINTLIST2);
				printf(HEADER3);
			}
	}
	fileflag ? fclose(fp):0;
	free(student);

	return 0;
}
