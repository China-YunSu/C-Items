#include<stdio.h>

#include "./include/boolean.h"
#include "./include/message.h"

int main(void) {

	StuList stulist = {0};

	while(TRUE != menu(&stulist))
		;
	
	return 0;
}
