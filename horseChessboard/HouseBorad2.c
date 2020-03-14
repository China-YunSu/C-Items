#include <stdio.h>
#include <malloc.h>

#include "./myStack.h"
#include "./boolean.h"
#include "./HouseBorad.h"

const HorseStep DRICTION[8] = {
	{-2,1},{-1,2},{1,2},{2,1},
	{2,-1},{1,-2},{-1,-2},{-2,-1}
};

HorseStep *CreatOneStep(int row, int col, int vaule) {
	HorseStep *res = NULL;

	res = (HorseStep*) calloc(sizeof(HorseStep),1);
	
	res->row = row;
	res->col = col;

	return res;
}

boolean IsWithinBoundary(int row, int col) {
	return (row < 8 && row >= 0) && (col < 8 && col >= 0);
}

void RecordCurStep(MY_STACK *localStack, HorseStep *horseStep) {
	push(localStack, horseStep);
}

HorseStep *PreviousStep(MY_STACK *localStack) {
	return (HorseStep *)pop(localStack);
}

void CleanCurStep(ARG *args) {
	HorseStep *previousStep = NULL;

	previousStep = PreviousStep(args->localStack);
	
	args->curStep.row = previousStep->row;
	args->curStep.col = previousStep->col;
	args->vaule--;
	args->borad[args->curStep.row][args->curStep.col] = 0;

	free(previousStep);
}

void ShowHorseChess(int borad[8][8]) {
	int row;
	int col;

	for(row = 0; row < 8; row++) {
		for(col = 0; col < 8; col++) {
			printf("%d ", borad[row][col]);
		}
		printf("\n");
	}		
}

boolean IsGo(const int borad[8][8],int row, int col) {
	return IsWithinBoundary(row, col) && !borad[row][col];
}

void CreatHorseChess(ARG *args) {
	GoStep(args);
	while (64 != args->vaule) {			
		GetNextStep(args);
		GoStep(args);
	}
}
//返回最小步数坐标
void GetNextStep(ARG *args) {
	HorseStep *horseStep = NULL;
	int index = GetMinStep(args);

	horseStep = CreatOneStep(args->curStep.row, args->curStep.col, args->vaule); 
	RecordCurStep(args->localStack, horseStep);
	
	if (index < 0) {
		args->curStep.row = -1;
		args->curStep.col = -1;	 	
	} 
	else {
		args->curStep.row += DRICTION[index].row;
		args->curStep.col += DRICTION[index].col;
	}
	++args->vaule;
}

int GetMinStep(const ARG *args) {
	int row,col;
	int min = -1;
	int count = 0;
	int index = 0;
	int i,k;

	for (i = 0; i < 8; i++) {
		row = args->curStep.row + DRICTION[i].row;
		col = args->curStep.col + DRICTION[i].col;
		if (!IsGo(args->borad,row,col)) {
			continue;
		}

		for (k = 0,count = 0; k < 8; k++) {
			if(IsGo(args->borad,row + DRICTION[k].row,
					col + DRICTION[k].col)) {
				count++;
			}
		}

		if (count && (min == - 1 || count < min)) {
			min = count;
			index = i;
		}
	}

	return min == - 1 ? min : index;
}

void GoStep(ARG *args) {
	if (NULL == args) {
		return;	
	}

	if (args->curStep.row < 0 || args->curStep.col < 0) {
		//异常
		CleanCurStep(args);
		return;
	}
	
	args->borad[args->curStep.row][args->curStep.col] = args->vaule;
}

void FreeALLStep(ARG *args) {
	if (NULL == args) {
		return;
	}

	while (!isStackEmpty(args->localStack)) {
		free(CleanOneStep(args->localStack));
	}
}

int main(int argc, char const *argv[]) {	
	ARG args = {
		NULL,	// MY_STACK *localStack;
		{0},	// int borad[8][8];
		{0,0},	// HorseStep curStep;
		1,  	// int vaule
	};

	initStack(&args.localStack, 64);

	CreatHorseChess(&args);	

	ShowHorseChess(args.borad);		

	FreeALLStep(&args);

	destoryStack(&args.localStack);
	
	return 0;
}