#include <stdio.h>
#include <windows.h>
#include <time.h>
#include <conio.h>

#include "./include/ParseRoute.h"
#include "./include/GraphConstruct.h" 
#include "./include/ModifyGraph.h"
#include "./include/File.h"
#include "./include/Hash.h"
#include "./include/ParseRoute.h"
#include "./include/Kruskal.h"

int Identity();
HashTable *Map(Graph **graph);
void DelCity(Graph *graph, HashTable *nameIndex);
void ShowMap(Graph *graph);
void CityConnect(Graph *graph, HashTable *nameIndex);
void AddCity(Graph *graph, HashTable *nameIndex);
void ShowPath(Graph *graph, HashTable *nameIndex,int way);
void ShowBestMap(Graph *graph, HashTable *nameIndex);
void ModifyCityInformation(Graph *graph, HashTable *nameIndex);
void SaveMap(Graph *graph, HashTable *nameIndex);
boolean MasterView(Graph *graph, HashTable *nameIndex);
boolean UserView(Graph *graph, HashTable *nameIndex);
void CancalConnect(Graph *graph, HashTable *nameIndex);
void Master();
void login();
void Geeting();

void User() {
	Graph *graph = NULL;
	HashTable *nameIndex = NULL;
	nameIndex = Map(&graph);

	while (UserView(graph, nameIndex));
}

void gotoxy(int x, int y) {

    COORD coord = {x,y};

    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);// ��ȡ��׼����豸���

    SetConsoleCursorPosition(handle, coord);//���������ֱ���ָ���ĸ����壬����λ��

}

boolean UserView(Graph *graph, HashTable *nameIndex) {
	int choose = 0;


	system("cls");
	printf("\t\t	   			          �ϵ�\n\n");
	printf("\t\t*************************************************************************************\n");
	printf("\t\t*                                                                                   *\n");
	printf("\t\t*             1. �鿴��ͼ                   2. �鿴Ŀ�ĵ�����·��                   *\n");
	printf("\t\t*                                                                                   *\n");
	printf("\t\t*             3. �鿴��ת����·��           4.�鿴��ת���·��                      *\n");
	printf("\t\t*                                                                                   *\n");
	printf("\t\t*             5.�˳�ϵͳ                                                            *\n");
	printf("\t\t*************************************************************************************\n\n");
	printf("\n\n��������ţ�");


	while (scanf("%d%*c",&choose) && choose > 5);
	
	switch (choose) {
		case 1:
			ShowMap(graph);
			break;
		case 2:
			ShowPath(graph, nameIndex,ALLPATH);
			break;	
		case 3:
			ShowPath(graph, nameIndex,MINPATH);
			break;
		case 4:
			ShowPath(graph, nameIndex,MINVALUE);
			break;	
		case 5:
			DestoryGraph(&graph);
			DestoryHashTable(&nameIndex);
			break;
		default:
			printf("���������˳�\n");
			choose = 5;
	}
	
	printf("�����������......\n");
	getchar();	

	return choose != 5;	
}


int Identity() {
	int choose = 0;
	
	printf("\t\t\t\t\t����˭ѽ?\n");
	printf("\t\t\t\t1.�ϵ�");
	printf("\t\t2.С��\n\n");
	printf("\t\t\t\t����ѡ��");
	
	while(scanf("%d%*c",&choose) && choose > 3);
	
	return	choose;
}

HashTable *Map(Graph **graph) {
	HashTable *nameIndex = NULL;
	
	InitGraph(graph, 1024);
	nameIndex = SetGraph(*graph);

	return nameIndex;
}

void DelCity(Graph *graph, HashTable *nameIndex) {
	char del[16] = {0};

	ShowMap(graph);
	printf("\t\t������ɾ������:");
	scanf("%s%*c",del);
	if (DelOneHead(graph, nameIndex, HashGet(nameIndex, del))) {
		printf("\t\tɾ���ɹ���\n");
	} else {
		printf("\t\t�����ڳ���%s\n",del);
	}
}

void ShowMap(Graph *graph) {
	int i = 0;
	GraphNode *node = NULL;

	for (i = 0; i < graph->nodeCount; ++i) {
		node = graph->node[i]->next;
		printf("%s :",graph->node[i]->data.cityData.name);
		while(node != NULL) {
			printf(" %s-%dkm ",graph->node[node->data.tab]->data.cityData.name ,node->data.edgeValue);
			node = node->next;
		}
		printf("\n");
	}
}

void CityConnect(Graph *graph, HashTable *nameIndex) {
	char cityA[16] = {0};
	char cityB[16] = {0};
	int value = 0;

	ShowMap(graph);
	printf("\t\t���������ӳ���A:");
	scanf("%s%*c", cityA);
	printf("\t\t���������ӳ���B:");
	scanf("%s", cityB);
	printf("\t\t���������A<->����B����\n");
	scanf("%d%*c",&value);

	if(!AddOneEdge(graph, HashGet(nameIndex, cityA), HashGet(nameIndex, cityB), value)) {
		printf("\t\t��������ʧ�ܣ����ܳ������������󣬻����޷��ҵ�\n");
	}
}

void AddCity(Graph *graph, HashTable *nameIndex) {
	char cityA[16] = {0};
	char cityB[16] = {0};
	
	int value = 0;
	int count = 0;
	int i = 0;

	GraphNode node[20] = {0}; 		
	GraphNode add = {0};

	ShowMap(graph);
	printf("\t\t���������ӳ���A:");
	scanf("%s%*c", add.data.cityData.name);
	add.data.tab = graph->nodeCount;
	HashPut(nameIndex, add.data.cityData.name, add.data.tab);
	
	printf("\t\t���������ӳ��и���:");
	scanf("%d%*c", &count);

	if (count > 20) {
		printf("\t\t���ӹ���,�������20\n");
	}

	for (i = 0; i < count; ++i) {
		printf("\t\t���������ӳ���%d:",i + 1);
		scanf("%s", cityB);
		printf("\t\t���������<->���о���:");
		scanf("%d%*c",&value);

		node[i].data.tab = HashGet(nameIndex, cityB);
		node[i].data.edgeValue = value;
	}

	if (!AddOneNode(graph, add, node, count)) {
		printf("\t\t�������ӡ�����ʧ�ܣ����ܳ������������󣬻����޷��ҵ�\n");
	}

}

void ShowPath(Graph *graph, HashTable *nameIndex, int way) {
	char cityA[16] = {0};
	char cityB[16] = {0};
	int start = 0;
	int end = 0;

	printf("\t\t������������A:");
	scanf("%s%*c", cityA);
	printf("\t\t�������յ����B:");
	scanf("%s%*c", cityB);
	//TODO ���в���������
	start = HashGet(nameIndex, cityA);
	end = HashGet(nameIndex, cityB);
	ParseRoute(graph, start, end, way);
}

void ShowBestMap(Graph *graph, HashTable *nameIndex) {
	Graph *MST = NULL;
	int size = 0;

	//TODO �쳣����ʧ��
	size = Kruskal(graph, &MST, nameIndex);
	
	if (size <= 0) {
		printf("��Ѳ�������ʧ��");
		free(MST);
		return;
	}
	//TODO �Ƿ������ļ�
	ShowMap(MST);
	free(MST);
}

void CancalConnect(Graph *graph, HashTable *nameIndex) {
	char cityA[16] = {0};
	char cityB[16] = {0};
	int value = 0;

	ShowMap(graph);
	printf("\t\t�����볷��·�߳���1:");
	scanf("%s%*c", cityA);
	printf("\t\t�����볷��·�߳���2:");
	scanf("%s%*c", cityB);

	if(!DelOneEdge(graph, HashGet(nameIndex, cityA), HashGet(nameIndex, cityB))) {
		printf("\t\t����·�߳���ʧ�ܣ����ܳ������������󣬻����޷��ҵ�\n");
	}
}

void ModifyCityInformation(Graph *graph, HashTable *nameIndex) {
	char cityA[16] = {0};
	char cityB[16] = {0};
	int choose = 0;
	int value = 0;
	int index = 0;
	printf("\t\t :1.�޸ĳ�������    2.�޸ĳ��о���\n\t\t������:");
	
	while(scanf("%d%*c",&choose) && choose > 2);
	
	switch (choose) {
		case 1:
			printf("��Ҫ�޸��Ǹ����У�");
			scanf("%s%*c", cityA);
			index = HashGet(nameIndex, cityA);
			printf("�������������");
			scanf("%s%*c",graph->node[index]->data.cityData.name);
			HashRemove(nameIndex, cityA);
			HashPut(nameIndex, graph->node[index]->data.cityData.name, index);
			break;
		case 2:	
			printf("\t\t������������A:");
			scanf("%s%*c", cityA);
			printf("\t\t�������յ����B:");
			scanf("%s%*c", cityB);
			printf("\t\t�������޸ĳ��о���:");
			scanf("%d%*c", &value);
			if (!ModifyNodeInformation(graph, HashGet(nameIndex, cityA), HashGet(nameIndex, cityB), value)){
				printf("\t\t������Ϣ�޸�ʧ�ܣ����ܳ������������󣬻����޷��ҵ�\n");
			}
			if (!ModifyNodeInformation(graph, HashGet(nameIndex, cityB), HashGet(nameIndex, cityA), value)){
				printf("\t\t������Ϣ�޸�ʧ�ܣ����ܳ������������󣬻����޷��ҵ�\n");
			}
			break;
		default : printf("\t\t��������\n");
	}
}

void SaveMap(Graph *graph, HashTable *nameIndex) {
	FILE *fp = NULL;
	GraphNode **graphNode = graph->node;
	GraphNode *checkNode = NULL;
	int i = 0;

	if((fp = OpenSaveMapFile(fp)) == NULL) {
		printf("д��洢�ļ�ʧ��\n");
		exit(0);
	}	

	for (i = 0; i < graph->nodeCount; ++i) {
		WriteTab(fp, "City");
		WriteSender(fp,graphNode[i]->data.cityData.name);
		for(checkNode = graphNode[i]->next; checkNode != NULL; checkNode = checkNode->next) {
			ConnectToFile(fp, checkNode->data.edgeValue,graphNode[checkNode->data.tab]->data.cityData.name);
		}
		WriteEnd(fp);	
	}
	fclose(fp);
}

boolean MasterView(Graph *graph, HashTable *nameIndex) {
	int choose = 0;

	system("cls");
	printf("\n\n	   			                  ����Ա\n\n");
	printf("\t\t*************************************************************************************\n");
	printf("\t\t*                                                                                   *\n");
	printf("\t\t*             1. �鿴��ͼ                   2. ɾ������                             *\n");
	printf("\t\t*                                                                                   *\n");
	printf("\t\t*             3. ɾ����������               4. ���ӳ���                             *\n");
	printf("\t\t*                                                                                   *\n");
	printf("\t\t*             5. ���ӳ���                   6. �鿴·��                             *\n");
	printf("\t\t*                                                                                   *\n");
	printf("\t\t*             7. �����ͼ                   8. ��ѳ��в���                         *\n");
	printf("\t\t*                                                                              	    *\n");
	printf("\t\t*             9. �޸ĳ�����Ϣ   	    10.�˳�ϵͳ                             *\n");
	printf("\t\t*                                                                                   *\n");
	printf("\t\t*************************************************************************************\n\n");
	printf("\n\n��������ţ�");


	while (scanf("%d%*c",&choose) && choose > 10);
	
	switch (choose) {
		case 1:
			ShowMap(graph);
			break;
		case 2:
			DelCity(graph, nameIndex);
			break;	
		case 3:
			CancalConnect(graph, nameIndex);
			break;
		case 4:
			CityConnect(graph, nameIndex);
			break;
		case 5:
			AddCity(graph, nameIndex);
			break;	
		case 6:
			ShowPath(graph, nameIndex,ALLPATH);
			break;
		case 7:
			SaveMap(graph, nameIndex);
			break;
		case 8:
			ShowBestMap(graph, nameIndex);
			break;
		case 9:
			ModifyCityInformation(graph, nameIndex);
			break;
		case 10:
			DestoryGraph(&graph);
			DestoryHashTable(&nameIndex);
			break;
		default:
			printf("���������˳�\n");
			choose = 10;
	}
	printf("�����������......\n");
	getchar();
	return choose != 10;
}

void Master() {
	Graph *graph = NULL;
	HashTable *nameIndex = NULL;
	nameIndex = Map(&graph);

	while (MasterView(graph, nameIndex));
}

void login() {

	system("cls");
	if (Identity() == 2) {
		int cnt = 3;
		int login = 1;
		char masterCount[30] = {"347251652"};
		char masterPassword[30] = {"123456"};
		char count[30] = {0};
		char password[30] = {0};
		
		while (cnt-- && login) {				
			system("cls");
			gotoxy(55,9);
			printf("�� ¼\n");
			gotoxy(45,10);
			printf("�˺ţ�\n");
			gotoxy(45,10+2 );
			printf("���룺\n");
			gotoxy(45 + 6, 10 + 0);
			scanf("%s%*c",count);
			gotoxy(45 + 6, 10 +2);
			scanf("%s%*c",password);

			if (!strcmp(masterCount,count) && !strcmp(masterPassword,password)) {
				Master();
				login = 0;
			} else {
				gotoxy(50 , 10 +3);
				printf("�������");
				Sleep(1000);
			}
		}
	} else {
		User();
	}
	
}

void Geeting() {
	int i = 0;
	int j = 0;
	char greet[][50] = {"\t\t\t\t�� ӭ �� �� �� �� �� ͨ ͼ",
						"\t\t\t\t�� �� �� �� �� �� ��",
						"\t\t\t\t�� �� �� �� �� �� �� �� �� Ϊ �� �� ��",
						"\t\t\t\t�� �� �� �� ˵ �� �� �� �� �� ��",
						};
	system("cls");				
	for (i = 0; i < 4; ++i) {
		for( j =0; greet[i][j]; ++j) {
			printf("%c",greet[i][j]); 
			Sleep(50);
		}
		printf("\n");
		Sleep(500);
	}
	Sleep(1500);
}

int main(int argc, char const *argv[]) {	
	Geeting();
	login();
	return 0;
}
