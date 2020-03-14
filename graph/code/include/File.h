#ifndef _FILE_
#define _FILE_ 

#include <stdio.h>

#include "boolean.h"

typedef  struct CityData {
	char name[16];
}CityData;

#define GRAPHPATH 			".\\Graph.txt"
#define CITYINFORMATIONPATH ".\\CityInformation.txt"
#define SAVEMAP 			"ModifyMap.txt"

CityData InputInformation(FILE *pf);
void GetConnectionData(FILE *pf, int *edgeValue, char *cityName);
void GetCityName(FILE *pf, char *cityName);
FILE *OpenConnectionFile();
FILE *OpenCityInformationFile();
boolean ReadTab(FILE *pf, char *tab);
boolean ReadEnd(FILE *pf);
void WriteTab(FILE *pf, char *name);
void WriteEnd(FILE *pf);
void WriteSender(FILE *pf, char *name);
void ConnectToFile(FILE *pf, int edgeValue, char *name);
FILE * OpenSaveMapFile(FILE *pf);

#endif
