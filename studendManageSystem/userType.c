#include <stdlib.h>
#include <stdio.h>

#include "./include/boolean.h"
#include "./include/userType.h"

boolean isSame (USER_TYPE one, USER_TYPE two) {
	if( !(strcmp(one.ID , two.ID))) {
		return TRUE;
	}
	if(one.math == two.math) {
		return TRUE;
	}
	if(one.English == two.English) {
		return TRUE;
	}
	if(one.Cprogram == two.Cprogram) {
		return TRUE;
	}
}
