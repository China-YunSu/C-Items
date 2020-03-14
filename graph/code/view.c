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

    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);// 获取标准输出设备句柄

    SetConsoleCursorPosition(handle, coord);//两个参数分别是指定哪个窗体，具体位置

}

boolean UserView(Graph *graph, HashTable *nameIndex) {
	int choose = 0;


	system("cls");
	printf("\t\t	   			          上帝\n\n");
	printf("\t\t*************************************************************************************\n");
	printf("\t\t*                                                                                   *\n");
	printf("\t\t*             1. 查看地图                   2. 查看目的地所有路径                   *\n");
	printf("\t\t*                                                                                   *\n");
	printf("\t\t*             3. 查看中转最少路径           4.查看中转最短路径                      *\n");
	printf("\t\t*                                                                                   *\n");
	printf("\t\t*             5.退出系统                                                            *\n");
	printf("\t\t*************************************************************************************\n\n");
	printf("\n\n请输入序号：");


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
			printf("输入有误，退出\n");
			choose = 5;
	}
	
	printf("按任意键继续......\n");
	getchar();	

	return choose != 5;	
}


int Identity() {
	int choose = 0;
	
	printf("\t\t\t\t\t你是谁呀?\n");
	printf("\t\t\t\t1.上帝");
	printf("\t\t2.小柯\n\n");
	printf("\t\t\t\t您的选择：");
	
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
	printf("\t\t请输入删除城市:");
	scanf("%s%*c",del);
	if (DelOneHead(graph, nameIndex, HashGet(nameIndex, del))) {
		printf("\t\t删除成功！\n");
	} else {
		printf("\t\t不存在城市%s\n",del);
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
	printf("\t\t请输入连接城市A:");
	scanf("%s%*c", cityA);
	printf("\t\t请输入连接城市B:");
	scanf("%s", cityB);
	printf("\t\t请输入城市A<->城市B距离\n");
	scanf("%d%*c",&value);

	if(!AddOneEdge(graph, HashGet(nameIndex, cityA), HashGet(nameIndex, cityB), value)) {
		printf("\t\t城市连接失败，可能城市名输入有误，或者无法找到\n");
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
	printf("\t\t请输入增加城市A:");
	scanf("%s%*c", add.data.cityData.name);
	add.data.tab = graph->nodeCount;
	HashPut(nameIndex, add.data.cityData.name, add.data.tab);
	
	printf("\t\t请输入连接城市个数:");
	scanf("%d%*c", &count);

	if (count > 20) {
		printf("\t\t连接过多,最多连接20\n");
	}

	for (i = 0; i < count; ++i) {
		printf("\t\t请输入连接城市%d:",i + 1);
		scanf("%s", cityB);
		printf("\t\t请输入城市<->城市距离:");
		scanf("%d%*c",&value);

		node[i].data.tab = HashGet(nameIndex, cityB);
		node[i].data.edgeValue = value;
	}

	if (!AddOneNode(graph, add, node, count)) {
		printf("\t\t城市增加、连接失败，可能城市名输入有误，或者无法找到\n");
	}

}

void ShowPath(Graph *graph, HashTable *nameIndex, int way) {
	char cityA[16] = {0};
	char cityB[16] = {0};
	int start = 0;
	int end = 0;

	printf("\t\t请输入起点城市A:");
	scanf("%s%*c", cityA);
	printf("\t\t请输入终点城市B:");
	scanf("%s%*c", cityB);
	//TODO 城市不存在问题
	start = HashGet(nameIndex, cityA);
	end = HashGet(nameIndex, cityB);
	ParseRoute(graph, start, end, way);
}

void ShowBestMap(Graph *graph, HashTable *nameIndex) {
	Graph *MST = NULL;
	int size = 0;

	//TODO 异常生成失败
	size = Kruskal(graph, &MST, nameIndex);
	
	if (size <= 0) {
		printf("最佳布局生成失败");
		free(MST);
		return;
	}
	//TODO 是否生成文件
	ShowMap(MST);
	free(MST);
}

void CancalConnect(Graph *graph, HashTable *nameIndex) {
	char cityA[16] = {0};
	char cityB[16] = {0};
	int value = 0;

	ShowMap(graph);
	printf("\t\t请输入撤销路线城市1:");
	scanf("%s%*c", cityA);
	printf("\t\t请输入撤销路线城市2:");
	scanf("%s%*c", cityB);

	if(!DelOneEdge(graph, HashGet(nameIndex, cityA), HashGet(nameIndex, cityB))) {
		printf("\t\t城市路线撤销失败，可能城市名输入有误，或者无法找到\n");
	}
}

void ModifyCityInformation(Graph *graph, HashTable *nameIndex) {
	char cityA[16] = {0};
	char cityB[16] = {0};
	int choose = 0;
	int value = 0;
	int index = 0;
	printf("\t\t :1.修改城市名字    2.修改城市距离\n\t\t请输入:");
	
	while(scanf("%d%*c",&choose) && choose > 2);
	
	switch (choose) {
		case 1:
			printf("您要修改那个城市：");
			scanf("%s%*c", cityA);
			index = HashGet(nameIndex, cityA);
			printf("请输入城市名：");
			scanf("%s%*c",graph->node[index]->data.cityData.name);
			HashRemove(nameIndex, cityA);
			HashPut(nameIndex, graph->node[index]->data.cityData.name, index);
			break;
		case 2:	
			printf("\t\t请输入起点城市A:");
			scanf("%s%*c", cityA);
			printf("\t\t请输入终点城市B:");
			scanf("%s%*c", cityB);
			printf("\t\t请输入修改城市距离:");
			scanf("%d%*c", &value);
			if (!ModifyNodeInformation(graph, HashGet(nameIndex, cityA), HashGet(nameIndex, cityB), value)){
				printf("\t\t城市信息修改失败，可能城市名输入有误，或者无法找到\n");
			}
			if (!ModifyNodeInformation(graph, HashGet(nameIndex, cityB), HashGet(nameIndex, cityA), value)){
				printf("\t\t城市信息修改失败，可能城市名输入有误，或者无法找到\n");
			}
			break;
		default : printf("\t\t输入有误！\n");
	}
}

void SaveMap(Graph *graph, HashTable *nameIndex) {
	FILE *fp = NULL;
	GraphNode **graphNode = graph->node;
	GraphNode *checkNode = NULL;
	int i = 0;

	if((fp = OpenSaveMapFile(fp)) == NULL) {
		printf("写入存储文件失败\n");
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
	printf("\n\n	   			                  管理员\n\n");
	printf("\t\t*************************************************************************************\n");
	printf("\t\t*                                                                                   *\n");
	printf("\t\t*             1. 查看地图                   2. 删除城市                             *\n");
	printf("\t\t*                                                                                   *\n");
	printf("\t\t*             3. 删除城市连接               4. 连接城市                             *\n");
	printf("\t\t*                                                                                   *\n");
	printf("\t\t*             5. 增加城市                   6. 查看路径                             *\n");
	printf("\t\t*                                                                                   *\n");
	printf("\t\t*             7. 保存地图                   8. 最佳城市布局                         *\n");
	printf("\t\t*                                                                              	    *\n");
	printf("\t\t*             9. 修改城市信息   	    10.退出系统                             *\n");
	printf("\t\t*                                                                                   *\n");
	printf("\t\t*************************************************************************************\n\n");
	printf("\n\n请输入序号：");


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
			printf("输入有误，退出\n");
			choose = 10;
	}
	printf("按任意键继续......\n");
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
			printf("登 录\n");
			gotoxy(45,10);
			printf("账号：\n");
			gotoxy(45,10+2 );
			printf("密码：\n");
			gotoxy(45 + 6, 10 + 0);
			scanf("%s%*c",count);
			gotoxy(45 + 6, 10 +2);
			scanf("%s%*c",password);

			if (!strcmp(masterCount,count) && !strcmp(masterPassword,password)) {
				Master();
				login = 0;
			} else {
				gotoxy(50 , 10 +3);
				printf("输入错误");
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
	char greet[][50] = {"\t\t\t\t欢 迎 来 到 城 市 交 通 图",
						"\t\t\t\t上 帝 等 您 很 久 了",
						"\t\t\t\t人 海 最 贴 心 的 搭 档 在 为 您 服 务",
						"\t\t\t\t让 我 来 诉 说 城 市 的 神 秘 吧",
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
