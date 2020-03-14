#include <stdio.h>
#include <string.h>

#include "./include/File.h"
#include "./include/boolean.h"

CityData InputInformation(FILE *pf) {
	CityData cityData ={0} ;

	fscanf(pf,"城市:%s\n",cityData.name);
	
	return cityData;
} 

void GetConnectionData(FILE *pf, int *edgeValue, char *cityName) {
	fscanf(pf,"%dkm-%s", edgeValue, cityName);
}

void GetCityName(FILE *pf, char *cityName) {
	ReadTab(pf, "City:");
	fscanf(pf,"%s",cityName);
}

FILE *OpenConnectionFile() {
	return fopen(GRAPHPATH, "rt");
}

FILE *OpenCityInformationFile() {
	return fopen(CITYINFORMATIONPATH, "rt");
}

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

void WriteTab(FILE *pf, char *name) {
	fprintf(pf, "< %s: ", name);
}


void WriteEnd(FILE *pf) {
	fprintf(pf, ">\n");
}

void WriteSender(FILE *pf, char *name) {
	fprintf(pf, " %s: ", name);
}

void ConnectToFile(FILE *pf, int edgeValue, char *name) {
	fprintf(pf, " %dkm-%s ", edgeValue, name);
}

FILE * OpenSaveMapFile(FILE *pf) {
	return fopen(SAVEMAP,"wt");
}