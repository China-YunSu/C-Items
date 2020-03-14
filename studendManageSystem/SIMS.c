#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./include/userType.h"
#include "./include/SIMS.h"
#include "./include/boolean.h"
#include "./include/myLink.h"
#include "./include/message.h"

boolean equal (Student *dataA, Student* dataB) {

	if(NULL != dataA && NULL != dataB) {
			if(dataA == dataB || isSame(dataA->data,dataB->data)) {
				return TRUE;
			}
		}
	return dataA == dataB;
}

StuList* file(void) {
	FILE *fp;
	FILE *FP;
	char filename[20];
	Data data = {0};
	StuList *plist = (StuList*) calloc(sizeof(StuList),1);

	printf("���䵱ǰĿ¼���ļ���(����+.txt)��");
	scanf("%20s",filename);
	if(NULL == (fp = fopen(filename,"r"))) {
		printf("%s��ȡʧ�ܣ�\n",filename);
		exit(1);
	}

	setLink(plist,1);//����������ȡ����
	fscanf(fp,REFORMAT,RELIST);
	plist->head->data = data;
	while(!feof(fp)) {
		fscanf(fp,REFORMAT,RELIST);
		append(plist,creatOneNode());
		plist->tail->data = data;
	}	
	fclose(fp);

	return plist;
}

StuList* Stdin(int count) {
	StuList *plist = (StuList*) calloc(sizeof(StuList),1);
	Student *student;

	setLink(plist,count);//����������ȡ����
	student = plist->head;
	while(NULL != student) {
		getInformation(student);
		student = student->next;
	}

	return plist;
}

boolean readInformation(StuList *plist) {
	
	int order;
	StuList *temp;
	int count;

	if(NULL == plist ) {
		return FALSE;
	}

	printf("1.�ļ�¼��                2.�ֶ�¼��\n");
	printf("�������:");
	scanf("%d",&order);
	fflush(stdin);
	while(order != 1 && order != 2) {
		printf("��������ȷ��ţ�\n");
		printf("1.�ļ�¼��                2.�ֶ�¼��\n");
		printf("�������:");
		scanf("%d",&order);
		fflush(stdin);
	}
	
	//��ȡ��ʽ���ļ������¼�� 
	if(order == 1) {
		temp = file();
	} else if (order == 2) {
		printf("�����������ѧ��:");
		scanf("%d",&count);
		temp = Stdin(count);
	}
	//�¾�����ϲ�
	if(NULL == plist->head && NULL == plist->tail) {	
		*plist = *temp; 
		free(temp); 
	} else {
			append(plist,temp->head);
			plist->tail = temp->tail;
			plist->count += temp->count - 1;
			freeLink(temp);
			free(temp);
			return FALSE;
		}

	printf("��ȡ�ɹ���\n");	
	return TRUE;
}

Student* newOneStudent(void) {
	Student *student = NULL;
	student = creatOneNode();
	getInformation(student);
	return student;
}

boolean insertOneStudent(StuList *plist) {

	Student found = {0};
	Student *student;
	char choice[2];

	if(NULL == plist || NULL == plist->head) {
		printf("û��¼��ѧ����Ϣ��\n" );
		return FALSE;
	}	

	student = newOneStudent();

	printf("�Ƿ�ָ������? (Y/N)");
	scanf("%1s",choice);
	fflush(stdin);
	if(!strcmp("Y",choice)) {
		display(plist);
		printf("�������˭�ĺ�ߣ�����ѧ��):");	
		scanf("%8s",found.data.ID);
		fflush(stdin);	 
		while(strlen(found.data.ID) < 8 ||
					 TRUE != insertNode(plist,student,&found)) {
		printf("��������ȷ��ѧ��:");
		scanf("%8s",found.data.ID);
		fflush(stdin);
		}	
	} else {
		append(plist,student);
	}
	printf("����ɹ�!\n");
	return TRUE;
}

boolean ModifyInformation(StuList *plist) {
	Student found;
	Student *local;

	if(NULL == plist || NULL == plist->head) {
		printf("û��¼��ѧ����Ϣ��\n" );
		return FALSE;
	}

	printf("�����޸�˭����Ϣ������ѧ��):" );
	scanf("%8s",found.data.ID);
	fflush(stdin);

	while(strlen(found.data.ID) < 8 || NULL == (local = searchNode(plist->head,&found))) {
		printf("�������ѧ��\n����������:");
		scanf("%8s",found.data.ID);
		fflush(stdin);
	}
	while(TRUE != ModifyMessage(local));

	printf("�޸ĳɹ�!\n");
	return TRUE;
}

boolean removeOneStudent(StuList *plist) {
	Student delet = {0};
	Student *local;

	if(NULL == plist || NULL == plist->head) {
		printf("û��¼��ѧ����Ϣ��\n" );
		return FALSE;
	}

	printf("����ɾ��˭?������ѧ�ţ�:" );
	scanf("%8s",delet.data.ID);
	fflush(stdin);
	while(strlen(delet.data.ID) < 8 || TRUE != removeNode(plist,&delet)) {
		printf("��������ȷ��ѧ��:" );
		scanf("%8s",delet.data.ID);	
		fflush(stdin);
	}

	printf("ɾ���ɹ�\n");
	return TRUE;
}

boolean searchStudent(StuList *plist) {
	Student *found;
	Student *student;

	if(NULL == plist || NULL== plist->head) {
		return FALSE;
	}

	found = creatOneNode();
	printf("������Ҫ����ѧ����ѧ�ţ�");
	scanf("%8s",found->data.ID);
	fflush(stdin);
	printf(HEADER1);
	printf(HEADER2);
	printf(HEADER3);
	if(NULL !=(student = searchNode(plist->head,found))) {
		printf(FORMAT,PRINTLIST1,PRINTLIST2);
		free(found);
		printf(HEADER1);
		return TRUE;	
	}

	
	printf("û���ҵ���\n");
	free(found);
	return FALSE;
}

boolean dataDeal(Data *student) {
	if(NULL == student) {
		return FALSE;
	}

	student->scores = student->math + student->English + student->Cprogram;
	student->average =  student->scores/3.0;
	
	return TRUE;
}

boolean clear(StuList *plist) {
	if(NULL == plist || NULL == plist->head) {
		return FALSE;
	}

	freeLink(plist);

	return TRUE;
}

int compare(Data data1, Data data2) {
	switch (compare_order) {
		case 1: return strcmp(data2.ID,data1.ID);
		case 2: return data1.math > data2.math;
		case 3: return data1.English > data2.English;
		case 4: return data1.Cprogram > data2.Cprogram;
		case 5: return data1.scores > data2.scores;
	}

	return 0;
}

boolean sort(StuList *plist) {
	int i;
	Student *index;
	Student *left;
	Student *end;
	int count;
	
	if(NULL == plist || NULL == plist->head) {
		printf("û��¼��ѧ����Ϣ��\n" );
		return FALSE;
	}

	while((compare_order = getorder()) > 5 && compare_order < 1 )
		printf("��������Ч���:\n");

	end = plist->tail;
	count = plist->count;
	for(i = 0; i < plist->count - 1; i++) {
		for(left = plist->head,index = left->next; left && index;
								left = index,index = index->next) {
				if(compare(index->data,left->data) > 0) {
					swap(&index->data,&left->data);
				}
				if(index == end) {
					end = left;
					break;
				}
		}
	}
	printf("������ϣ�\n");
	return TRUE;
}

void swap(Data *one, Data *another) {
	Data temp = *one;	
	*one = *another;
	*another = temp;
}

void output(StuList *plist) {
	char filename[20] = {0};
	FILE *fp = NULL;
	Student *student;

	if(NULL == plist || NULL == plist->head) {
		printf("û��¼��ѧ����Ϣ��\n" );
		return;
	}

	printf("�����ļ���(�ļ���+.txt)��");
	scanf("%20s",filename);
	fflush(stdin);
	if(NULL == (fp = fopen(filename,"w"))) {
		printf("%s��ȡʧ�ܣ�",filename);
		exit(0);
	}

	student = plist->head;
	fprintf(fp,HEADER4);
	while(NULL != student) {
		fprintf(fp,FORMAT2,PRINTLIST1,PRINTLIST2);
		student = student->next;
	}
	printf("����ɹ�\n");
	fclose(fp);
}
