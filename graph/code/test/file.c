#include <stdio.h> 
#include <string.h>

#include "./include/Hash.h"
#include "./include/boolean.h"

 boolean ReadTab(FILE *pf, char *tab) {
	char item[32];
	
	while(fgetc(pf) != '<');
	fscanf(pf, "%s",item);

	return !strcmp(item,tab) ? TRUE : !printf("文件格式错<%s>",item);
}

boolean ReadEnd(FILE *pf) {
	char ch1 = fgetc(pf);
	char ch2 = fgetc(pf);
	return (ch1 == ' ' && ch2 == '>');
}



int main(void) {
	FILE *pf = NULL;
	HashTable *nameIndex = NULL;
	int cnt = 0;
	int i = 0;

	char name[3][8] = {0};
	char nodeName[8] = {0};
	int dis = 0;
	char connectCity[8] = {0};

	InitHashTable(&nameIndex,3);
	
	

	ReadTab(pf,"CityCount:");
	fscanf(pf,"%d",&cnt);

	ReadTab(pf,"City:");
	while (!ReadEnd(pf)) {
		fscanf(pf,"%s",name[i]);
		HashPut(nameIndex,name[i],i);
		++i;
	}
	
	ReadTab(pf,"ConnectPath:");
	for (i = 0; i < cnt; ++i) {
		ReadTab(pf,"City:");
		fscanf(pf,"%s",nodeName);
		while(!ReadEnd(pf)) {
			fscanf(pf,"%dkm-%s",&dis,connectCity);	
			//printf("%s %s %d\n",nodeName,connectCity,dis);
			printf("%s[%d]-%dkm ",connectCity,HashGet(nameIndex,connectCity),dis);
		}
		printf("\n");
	}
	DestoryHashTable(&nameIndex);
	fclose(pf);
}
