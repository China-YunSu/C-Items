#include <stdio.h>
#include <windows.h>
#include <time.h>
#include <conio.h>


#define WINSIZE			10

#define MIN_SIZE 		3
#define MAX_SIZE		20

#define WIDTHSIZE 	    20
#define LENGTHSIZE		51

#define TRUE			1
#define FALSE			0

typedef unsigned char boolean;

typedef struct Map_ {
	int length;
	int width;
}Map;

const char *DirecList = "wsad";

const char ChangeStatusList [5][4] = {
	//  w  		  s   	   a 	 	d 
/*w*/    0,       0,       1,       1,
/*s*/    0,       0,       1,       1, 
/*a*/    1,       1,       0,       0,
/*d*/	 1        1,       0,       0,
/*other*/0,       0,	   0,       0,
};

typedef struct snake {
	int Xbody[MAX_SIZE];
	int Ybody[MAX_SIZE];
	int tail;
	int head;
	int speed;
	char status;
	char key;
	boolean win;
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

	for (i = 0; DirecList[i]; i++) {

		if( key == DirecList[i]) {
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

	if (-1 == key_index) {
		return FALSE;
	}
	else {
		return ChangeStatusList[key_index][status_index];
	}

}
boolean eatSelf(Snake *snake) {
	int index = 0;
	for(index = snake->tail - 1; index > snake->head; index--) {
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
		snake->key = getch();
	} 

	if (IsChangeStatus(key,snake->status)) {
		snake->status = key;
	}
	
	switch(snake->status) {
		case 'w' : 	
						snake->Ybody[0]--;
						snake->status = 'w';	
		case  's' :		
						snake->Ybody[0]++;
						snake->status = 's';	
					
		case  'a' :		
						snake->Xbody[0] -= 2;
						snake->status = 'a';	
		
		case  'd' :		
						snake->Xbody[0] += 2;
						snake->status = 'd';					
	}
}

boolean overBoundary(Snake *snake) {
	return (snake->Xbody[0] <= 0 || snake->Xbody[0] >= map.length - 1)
				|| (snake->Ybody[0] <= 0 || snake->Ybody[0] >= map.width);
} 

boolean breakrule(Snake *snake) {
	return overBoundary(snake)|| eatSelf(snake);
}

boolean snakeMove(Snake *snake, Food *food) {
	int index = 0;

	//��������任
	for(index = snake->tail; index > snake->head; index--) {
			
			snake->Xbody[index] = snake->Xbody[index - 1];
			snake->Ybody[index] = snake->Ybody[index - 1];	
	}

	//ͷ
	 headControl(snake);
	
	if(TRUE == breakrule(snake)) {
		return FALSE;
	}
	//����
	printSnake(snake);
	//�߳�ʺ
	if(food->x == snake->Xbody[snake->head] && 
			food->y == snake->Ybody[snake->head]) {
		getfood(food, snake);
		snake->tail++;
	} else {//������β��
		gotoxy(snake->Xbody[snake->tail],snake->Ybody[snake->tail]);
		printf("  ");
	}
	if(snake->tail > WINSIZE) {
		snake->win = TRUE;
		return FALSE;
	}

	return TRUE;
}

void gotoxy(int x, int y) {

    COORD coord = {x,y};

    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);// ��ȡ��׼����豸���

    SetConsoleCursorPosition(handle, coord);//���������ֱ���ָ���ĸ����壬����λ��

}

void showMap(void) {
	int i = 0;

	//��ӡ�ϱ߽�
	gotoxy(0,0);
	for(i = 0; i < map.length / 2; i++) {
		printf("��");
	}
	//���ұ߽�
	for(i = 0; i < map.width; i++) {
		//��߽�
		gotoxy(0,i);
		printf("��");

		//�ұ߽�
		gotoxy(map.length - 1, i);
		printf("��");
	}
	//��ӡ�±߽�
	gotoxy(0, map.width - 1);
	for(i = 0; i < map.length / 2; i++) {
		printf("��");
	}	
}

boolean getfood(Food *food, Snake *snake) {
	int index = 0;
	srand(time(0));
	
	do {
		food->x = (rand() % (map.length / 2 - 2)) * 2 + 2 ;
		food->y = rand() % (map.width - 1) + 1;

		for(index = snake->head; index < snake->tail; index++) {
			if(food->x == snake->Xbody[index] && food->y == snake->Ybody[index]) {
				break;
			}
		}
	}while(index < snake->tail);

	gotoxy(food->x,food->y);
	printf("��");

	return TRUE;
}

void printSnake(Snake *snake) {
	int index;
	for(index = 0; index < snake->tail; index++) {
		gotoxy(snake->Xbody[index],snake->Ybody[index]);
		printf("��");
	}
}

void initSnake(Snake *psnake) {
	int i;	
	for(i = 1; i < psnake->tail; i++) {
		psnake->Xbody[i] = psnake->Xbody[i - 1] - 2;
		psnake->Ybody[i] = psnake->Ybody[i - 1];
	}
}	

int main(void) {
	Snake snake = {
		{LENGTHSIZE / 2 - 1},			// int Xbody[MAX_SIZE];
		{WIDTHSIZE / 2},			// int Ybody[MAX_SIZE];
		MIN_SIZE,					//int tail;//������Ҫ�ռ�
		0,               			// int head;
		100,					// int speed;
		0,
		FALSE,						// boolean win;	
	};
	Food food = {0,0};
	
	initSnake(&snake);
	getfood(&food,&snake);
	printSnake(&snake);
	
	showMap();
	
	while (TRUE == snakeMove(&snake,&food)) {
		Sleep(snake.speed);
	}
	
	gotoxy(map.length / 2,map.width / 2);
	if(snake.win) {
		printf("Win!");	
	} else {
		printf("GAME OVER!");	
	}
	
	gotoxy(map.length ,map.width);

	return 0;
}
