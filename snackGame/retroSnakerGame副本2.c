#include <stdio.h>
#include <windows.h>
#include <time.h>
#include <conio.h>

#define MIN_SIZE 		3
#define MAX_SIZE		20

#define WIDTHSIZE 	    20
#define LENGTHSIZE		50

#define TRUE			1
#define FALSE			0

typedef unsigned char boolean;

typedef struct Map_ {
	int length;
	int width;
}Map;

const char *StatusList = "wsad";

const char ChangeStatusList [5][4] = {
	//  w  		  s   	   a 	 	d 
/*w*/    0,       0,       1,       1,
/*s*/    0,       0,       1,       1, 
/*a*/    1,       1,       0,       0,
/*d*/	 1,       1,       0,       0,
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
boolean snakeMove(Snake *snake, Food *food); 
boolean overBoundary(Snake *snake);
void initSnake(Snake *psnake);
boolean breakrule(Snake *snake);
boolean getfood(Food *food, Snake * snake);

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
	char key = '0';
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

boolean overBoundary(Snake *snake) {
	return (snake->Xbody[0] <= 0 || snake->Xbody[0] >= map.length - 1)
				|| (snake->Ybody[0] <= 0 || snake->Ybody[0] >= map.width - 1);
} 

boolean breakrule(Snake *snake) {
	return overBoundary(snake)|| eatSelf(snake);
}

boolean snakeMove(Snake *snake, Food *food) {
	int index = 0;

	//蛇身坐标变换
	for(index = snake->tail; index > 0; index--) {
			
			snake->Xbody[index] = snake->Xbody[index - 1];
			snake->Ybody[index] = snake->Ybody[index - 1];	
	}

	//头
	 headControl(snake);
	
	if(TRUE == breakrule(snake)) {
		snake->status = 'e';
         return FALSE;
	}
	//画蛇
	printSnake(snake);
	//蛇吃屎
	if(food->x == snake->Xbody[0] && 
			food->y == snake->Ybody[0]) {
		    getfood(food, snake);
			snake->tail++;
    }
    else  if(food->x == snake->Xbody[snake->tail] && 
		food->y == snake->Ybody[snake->tail]){//虏脕鲁媒戮脡脦虏掳脥
	  
	}
	else {
		gotoxy(snake->Xbody[snake->tail],snake->Ybody[snake->tail]);
	  	printf("  ");	
	}
	
	if(snake->tail >= MAX_SIZE) {
	   snake->status = 'v';
       return FALSE;
	}

	return TRUE;
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

void initSnake(Snake *psnake) {
	int i;	

	for(i = 1; i < psnake->tail; i++) {
		psnake->Xbody[i] = psnake->Xbody[i - 1] - 2;
		psnake->Ybody[i] = psnake->Ybody[i - 1];
	}
	
	printSnake(psnake);

	while (psnake->status == 'a'){
		psnake->status = getch();	
	}
	
}	

int main(void) {
	Snake snake = {
		{LENGTHSIZE / 2 - 1},		// int Xbody[MAX_SIZE];
		{WIDTHSIZE / 2},			// int Ybody[MAX_SIZE];
		MIN_SIZE,					//int tail;//擦除需要空间
		100,						// int speed;
		'a',						// status
	};
	Food food = {0,0};
	
	showMap();

	getfood(&food,&snake);
	
	initSnake(&snake);
	
	while (TRUE == snakeMove(&snake,&food)) {
		Sleep(snake.speed);
	}
	
	gotoxy(map.length / 2,map.width / 2);
	if ( 'v' == snake.status) {
		printf("Win!");	
	} else {
		printf("GAME OVER!");	
	}
	
	gotoxy(map.length ,map.width);

	return 0;
}
