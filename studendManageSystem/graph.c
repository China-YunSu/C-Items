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
		printf("�������\n���������룺");
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
		printf("�Ƿ�����鿴?(Yes or No)\n");
		scanf("%3s",choice);
		!strcmp(choice,"Yes") ? display(plist) : 0; 

	}

	fflush(stdin);
	printf("�����������.......");
	getch();

	return order == 10;
}

void show(void) {
	system("cls");
		printf("\n\n	   			                  ѧ���ɼ�����ϵͳ\n\n");
		
		printf("\t\t*************************************************************************************\n");
		printf("\t\t*                                                                                   *\n");
		printf("\t\t*             1. ¼��ѧ����Ϣ                  2. ѧ������                          *\n");
		printf("\t\t*                                                                                   *\n");
		printf("\t\t*             3. �޸�ѧ����Ϣ                  4. ѧ��ɾ��                          *\n");
		printf("\t\t*                                                                                   *\n");
		printf("\t\t*             5. ��ʾѧ���ɼ�                  6. ����ѧ��                          *\n");
		printf("\t\t*                                                                                   *\n");
		printf("\t\t*             7. ��ӡѧ����Ϣ                  8. ɸѡѧ��                          *\n");
		printf("\t\t*                                                                              	    *\n");
		printf("\t\t*             9. ����ѧ��                      10.�˳�ϵͳ                          *\n");
		printf("\t\t*                                                                                   *\n");
		printf("\t\t*************************************************************************************\n\n");
		printf("\n\n��������ţ�");
}

boolean getInformation(Student *student) {
	
	if(NULL == student) {
		return FALSE;
	}

	printf("������ѧ��:");
	scanf("%8s",student->data.ID);
	printf("����������:");
	scanf("%7s",student->data.name);
	printf("��������ѧ�ɼ���");
	scanf("%d",&student->data.math);
	printf("������C���Գɼ���");
	scanf("%d",&student->data.Cprogram);
	printf("������Ӣ��ɼ���");
	scanf("%d",&student->data.English);

	return TRUE;
}

boolean ModifyMessage(Student *local) {
	int order;
	
	if(NULL == local) {
		return FALSE;
	}

	printf("1.�޸�ѧ��               	2.�޸�����\n");
	printf("3.�޸���ѧ�ɼ�            	4.�޸�C���Գɼ�\n");
	printf("5.�޸�Ӣ��ɼ�\n");
	printf("�������ţ�");
	scanf("%d",&order);

	switch (order) {//�޸���
		case 1 : printf("�������޸�ѧ�ţ�"); scanf("%8s",local->data.ID); return TRUE;
		case 2 : printf("�������޸�������"); scanf("%6s",local->data.name); return TRUE;
		case 3 : printf("�������޸ĵ���ѧ�ɼ�:"); scanf("%d",&(local->data.math)); return TRUE;
		case 4 : printf("�������޸ĵ�C���Գɼ�:"); scanf("%d",&(local->data.Cprogram)); return TRUE;
		case 5 : printf("�������޸ĵ�Ӣ��ɼ�:"); scanf("%d",&(local->data.English)); return TRUE;
		default :printf("�������!���������룺\n"); scanf("%d",&order); return FALSE; 
	}
}

int getorder(void) {
	int order;

	printf("1.ѧ��			2.��ѧ�ɼ�\n");
	printf("3.Ӣ��ɼ�		4.C���Գɼ�\n");
	printf("5.�ܳɼ�	\n");
	printf("������ţ�");
	scanf("%d",&order);

	if(order < 0 || order > 5) {
		printf("��������Ч���!\n");
		order = getorder();
	}

	return order;
}

boolean display(StuList *plist) {
	Student *student;
	int rank = 1;
	
	if(NULL == plist) {
		printf("��ѧ����Ϣ\n");
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
	printf("��ʲôɸѡ?\n");
	printf("1.��ѧ�ɼ�		2.Ӣ��ɼ�\n");
	printf("3.C���Գɼ�		4.�ܳɼ�\n");
	printf("������ţ�");
	scanf("%d",&compare_order);

	while(order < 0 && order > 4) {
		printf("��������Ч���!\n");
		scanf("%d",&order);
	}
	printf("���ٷ�������?");
	scanf("%d",&standard);

	printf("�Ƿ��ļ����?(Yes or No)\n");
	fflush(stdin);
	scanf("%s",filename);
	if(!strcmp(filename,"Yes")) {
		printf("�������ļ�����");
		scanf("%s",filename);
		if(NULL == (fp = fopen(filename,"w"))) {
			printf("%s��ʧ��",filename);
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
