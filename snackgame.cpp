#include<iostream>
#include <windows.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#define MAXLENGH=255
#define VIEWWIDTH 40
#define VIEWHEIGH 20
using namespace std;
struct snack{//tao object snack va food
	int x;
	int y;
}snack,food;
void ShowConsoleCursor(bool showFlag){//tat hien hien con tro
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO     cursorInfo;

    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag; // set the cursor visibility
    SetConsoleCursorInfo(out, &cursorInfo);
}
void gotoxy(int x, int y){//di chuyen con tro den vi tri x,y
  static HANDLE h = NULL;  
  if(!h)
    h = GetStdHandle(STD_OUTPUT_HANDLE);
  COORD c = { x, y };  
  SetConsoleCursorPosition(h,c);
}
void createView(){//khoi tao khung tro choi
	for(int i=0;i<=VIEWWIDTH;i++){
		cout<<"#";
	}
	for(int i=1;i<VIEWHEIGH;i++){
		gotoxy(0,i);cout<<"#";
		gotoxy(VIEWWIDTH,i);cout<<"#";
	}
	gotoxy(0,VIEWHEIGH);
	for(int i=0;i<=VIEWWIDTH;i++){
		cout<<"#";
	}
}
void drawSnack(){
	gotoxy(snack.x,snack.y);
	cout<<"0";
}
void deleteSnack(){
	gotoxy(snack.x,snack.y);
	cout<<" ";
}
int randomNumber(int minNumber,int maxNumber){//ham lay gia tri ngau nhien tu min->max
	return rand() % (maxNumber - minNumber + 1) + minNumber;;
}
void createFood(){
	food.x=randomNumber(1,39);
	food.y=randomNumber(1,19);
	gotoxy(food.x,food.y);
	cout<<"+";
}
void deleteFood(){
	gotoxy(food.x,food.y);
	cout<<" ";
}
void eatFood(){//kiem tra an food
	if(food.x==snack.x&&food.y==snack.y){
		deleteFood();
		createFood();
	}
}
int main(){
	ShowConsoleCursor(false);//tat hien thi con tro?
	srand (time(NULL));
	int speedV=100;//toc do di ngang
	int speedH=50;//toc do di doc
	snack.x=20;
	snack.y=10;
	char keyPress;
	bool left=1,right=0,up=0,down=0;
	createView();
	createFood();
	while(1){
		if(kbhit()){
        	keyPress = getch();
        	int c=keyPress;
        	switch(c){//75:left 80:down 77:right 72:up
	        	case 75:
	        		right=0;left=1;up=0;down=0;break;
        		case 80:
	        		right=0;left=0;up=0;down=1;break;
        		case 77:
	        		right=1;left=0;up=0;down=0;break;
        		case 72:
	        		right=0;left=0;up=1;down=0;break;
        		default: break;
	        }
        }
        if(left){//kiem tra di qua trai
        	deleteSnack();
        	snack.x-=1;
        	if(snack.x<1)snack.x=39;//kiem tra ngoai khung
        	drawSnack();
        }
        if(down){//kiem tra di xuong
        	deleteSnack();
        	snack.y++;
        	if(snack.y>19)snack.y=1;//kiem tra ngoai khung
        	drawSnack();
        }
        if(right){//kiem tra di qua phai
        	deleteSnack();
        	snack.x+=1;
        	if(snack.x>39)snack.x=1;//kiem tra ngoai khung
        	drawSnack();
        }
        if(up){//kiem tra di len
        	deleteSnack();
        	snack.y--;
	        if(snack.y<1)snack.y=19;//kiem tra ngoai khung
        	drawSnack();
        }
        eatFood();
        if(left||right)Sleep(speedH);//toc do di theo chieu ngang
        if(up||down)Sleep(speedV);//toc do di theo chieu doc
	}	
}
