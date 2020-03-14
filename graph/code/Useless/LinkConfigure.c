#include "./include/boolean.h"
#include "./include/LinkConfigure.h"

boolean equal(USER_TYPE dataA, USER_TYPE dataB) {	
	return dataA.tab == dataB.tab;
}