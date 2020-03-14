#ifndef _FILEREAD_H_
#define _FILEREAD_H_
#include <stdio.h>

#include "boolean.h"

#define GRAPHPATH 			".\\Graph.txt"
#define CITYINFORMATIONPATH ".\\CityInformation.txt"

boolean ReadTab(FILE *pf, char *tab);
boolean ReadEnd(FILE *pf);

#endif