#include <stdio.h>
#include <string.h>

#include "./include/HashConfigure.h"

Item ToHashData(char *str) {
	Item data = {0};

	strcpy(data.name, str);
	
	return data;
}
