#include <stdio.h>
#include <time.h>
#include <conio.h>

#define MIN_SIZE 		3
#define MAX_SIZE		12


#define WIDTHSIZE 	    20
#define LENGTHSIZE		50

#define TRUE			1
#define FALSE			0

typedef unsigned char boolean;

typedef struct Map_ {
	int length;
	int width;
}Map;

const char *StatusList = "wsda";

const char ChangeStatusList [5][4] = {
	//  w  		  s   	   d 	 	a 
/*w*/    0,       0,       1,       1,
/*s*/    0,       0,       1,       1, 
/*d*/	 1,       1,       0,       0,
/*a*/    1,       1,       0,       0,
/*other*/0,       0,	   0,       0,

};

typedef struct snake {
	int Xbody[MAX_SIZE + 1];
	int Ybody[MAX_SIZE + 1];
	int tail;
	int speed;
	char status;
}Snake;

typedef struct food {
	int x;
	int y;
}Food;

const Map map = {LENGTHSIZE, WIDTHSIZE};

void gotoxy(int x, int y); 
void showMap(void);
void printSnake(Snake *snake);
void headControl(Snake *snake);
void snakeMove(Snake *snake, Food *food); 
boolean overBoundary(Snake *snake);
void initSnake(Snake **psnake);
boolean breakrule(Snake *snake);
boolean getfood(Food *food, Snake * snake);
void gameOver(Snake  **snake);
void eatFood(Snake *snake, Food *food);

int getIndex(char key) {
	int i = 0;

	for (i = 0; StatusList[i]; i++) {

		if( key == StatusList[i]) {
			return i;
		}
	}

	return i;
}

boolean IsChangeStatus(int key, int status) {
	int key_index = 0;
	int status_index = 0;

	key_index = getIndex(key);
	status_index = getIndex(status);

	return ChangeStatusList[key_index][status_index];
}

boolean eatSelf(Snake *snake) {
	int index = 0;
	for(index = snake->tail - 1; index > 0; index--) {
		if((snake->Xbody[0] == snake->Xbody[index] &&
		 snake->Ybody[0] == snake->Ybody[index])) {
			return TRUE;
		}
	}
	return FALSE;
}

void headControl(Snake *snake) {
	char key;
	
	if(kbhit()) {
		key = getch();

        if (IsChangeStatus(key,snake->status)) {
			snake->status = key;
		}
	} 
	
	switch(snake->status) {
		case  'w' : 	
					snake->Ybody[0]--;
					break;	
		case  's' :		
					snake->Ybody[0]++;
					break;	
						
		case  'a' :		
					snake->Xbody[0] -= 2;
					break;	
		
		case  'd' :		
					snake->Xbody[0] += 2;
					break;				
	}
}

void eatFood(Snake *snake, Food *food) {
        if(food->x == snake->Xbody[0] && 
			food->y == snake->Ybody[0]) {
		    getfood(food, snake);
			snake->tail++;
	    }
	    else  if(food->x == snake->Xbody[snake->tail] && 
			food->y == snake->Ybody[snake->tail]){
		  	//食物与多余尾巴重叠，不做任何事。
		}
		else {
			gotoxy(snake->Xbody[snake->tail],snake->Ybody[snake->tail]);
		  	printf("  ");	//擦除多余尾巴
		}
}

boolean overBoundary(Snake *snake) {
	return (snake->Xbody[0] <= 0 || snake->Xbody[0] >= map.length - 3)
				|| (snake->Ybody[0] <= 0 || snake->Ybody[0] >= map.width - 1);
} 

boolean breakrule(Snake *snake) {
	return overBoundary(snake)|| eatSelf(snake);
}

void snakeMove(Snake *snake, Food *food) {
	int index = 0;

	//蛇身坐标变换
	for(index = snake->tail; index > 0; index--) {
			
			snake->Xbody[index] = snake->Xbody[index - 1];
			snake->Ybody[index] = snake->Ybody[index - 1];	
	}
	//头
	 headControl(snake);
	
	 eatFood(snake, food);
}

void gotoxy(int x, int y) {

    COORD coord = {x,y};

    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);// 获取标准输出设备句柄

    SetConsoleCursorPosition(handle, coord);//两个参数分别是指定哪个窗体，具体位置

}

void showMap(void) {
	int i = 0;

	//打印上边界
	gotoxy(0,0);
	for(i = 0; i < map.length / 2; i++) {
		printf("■");
	}
	//左右边界
	for(i = 1; i < map.width - 1; i++) {
		//左边界
		gotoxy(0,i);
		printf("■");
		//右边界
		gotoxy(map.length - 2, i);
		printf("■");
	}
	//打印下边界
	gotoxy(0, map.width - 1);
	for(i = 0; i < map.length / 2; i++) {
		printf("■");
	}	
}

boolean getfood(Food *food, Snake *snake) {
	int index = 0;
	srand(time(0));
	
	do {
		food->x = (rand() % (map.length / 2 - 2) + 1) * 2;
		food->y = rand() % (map.width - 2) + 1;

		for(index = 0; index < snake->tail; index++) {
			if(food->x == snake->Xbody[index] && food->y == snake->Ybody[index]) {
				break;
			}
		}
	}while(index < snake->tail);

	gotoxy(food->x,food->y);
	printf("■");

	return TRUE;
}

void printSnake(Snake *snake) {
	int index;

	for(index = 0; index < snake->tail; index++) {
		gotoxy(snake->Xbody[index],snake->Ybody[index]);
		printf("■");
	}
}

void initSnake(Snake  **psnake) {
	int i = 0;	
    Snake *res = (Snake *) calloc(sizeof(Snake), 1);

    res->tail = MIN_SIZE;
    res->speed = 100;
    res->Xbody[0] = LENGTHSIZE / 2 - 1;		
	res->Ybody[0] = WIDTHSIZE / 2;

	for(i = 1; i < res->tail; i++) {
		res->Xbody[i] = res->Xbody[i - 1] - 2;
		res->Ybody[i] = res->Ybody[i - 1];
	}

    *psnake = res;
}	

void gameOver(Snake  **snake) {
    gotoxy(map.length / 2,map.width / 2);

	if ( MAX_SIZE == (*snake)->tail) {
		printf("Win!");	
	} else {
		printf("GAME OVER!");	
	}
	
	gotoxy(map.length ,map.width);

	free(*snake);
	*snake = NULL; 
}

boolean isAlive(Snake *snake) {
	return FALSE == breakrule(snake) && snake->tail < MAX_SIZE;
}

int main(void) {
	Snake *snake = NULL;
	Food food = {0};
	
	initSnake(&snake);

	getfood(&food, snake); 
	
	showMap();
 	
 	printSnake(snake);
	
	do {
		snake->status = getch();	
	} while(NULL == strchr("wds", snake->status));
 	
	while (isAlive(snake)) {
        snakeMove(snake,&food);

	 	printSnake(snake);
		
		Sleep(snake->speed);
	}
	
    gameOver(&snake);
	
	return 0;
}
