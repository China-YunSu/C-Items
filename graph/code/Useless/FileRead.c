#include <stdio.h>
#include <string.h>

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
