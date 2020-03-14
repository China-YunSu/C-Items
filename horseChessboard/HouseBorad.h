#ifndef _HOUSEBORAD_H_
#define _HOUSEBORAD_H_ 

#include "./myStack.h"
#include "./boolean.h"

typedef struct HorseStep {
	int row;
	int col;
}HorseStep;

typedef struct ARG {	
	MY_STACK *localStack;
	int borad[8][8];
	HorseStep curStep;
	int vaule;
}ARG;

HorseStep *CreatOneStep(int row, int col, int vaule);
boolean IsWithinBoundary(int row, int col);
void RecordCurStep(MY_STACK *localStack, HorseStep *horseStep);
void CleanCurStep(ARG *args);
void ShowHorseChess(int borad[8][8]);
boolean IsGo(const int borad[8][8],int row, int col);
void CreatHorseDriction(ARG *args);
void GetNextStep(ARG *args);
void GoStep(ARG *args);
void FreeALLStep(ARG *args);
HorseStep *CleanOneStep(MY_STACK *localStack);

#endif