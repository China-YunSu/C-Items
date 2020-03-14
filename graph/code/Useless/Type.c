#include <stdio.h>
#include <math.h>

#include "./include/Type.h"

char *ToString(int digit) {
	static char str[16] = {0};
	int len = (int ) log(digit);
	 
	String(digit < 0 ? -digit : digit, str);
	str[len + 1] = '\0';

	return str;
}

char *String(unsigned int digit, char *str) {
	if (digit < 10) {
		*str = digit % 10 + '0';
		return str + 1;
	}

	str = String(digit / 10, str);
	*str = digit % 10 + '0';
	
	return str + 1;
}
