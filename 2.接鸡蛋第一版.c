/*		头文件		*/
# include <windows.h>
# include <stdlib.h>
# include <stdio.h>
# include <conio.h>
# include <time.h>
#include <time.h>
int score,life = 5,difficulty = 500 ;  //全局变量——得分，生命，难度 

void Show(int hand_x,int hand_y,int face_x,int face_y);		//显示游戏界面  
void Setup(void);	//设置

int main(void)
{
	    
    system("mode con: cols=60 lines=20");		//设置窗口大小
    system("title 接鸡蛋   ——C语言制作");		//改变窗口标题 
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	const int h_Y = 9;
	int h_x = 5 , f_y = 0 , f_x /* first_time,second_time*/;
	long first_time,second_time;
	srand((unsigned)time(NULL));  // 随机数种子

	f_x  = (int)(10.0 *rand()/(RAND_MAX+1.0)); //	f_x = rand()%10;   产生随机数并取余
	Show(h_x,h_Y,f_x,f_y);       //显示游戏界面 
	printf(
	"\n\n		□□□□操作指南□□□□\n"
   	    "		□【A】【D】移动接笑脸□\n" 
   	    "		□【Esc】进入设置界面 □ \n"
		"		□      按任何键开始  □\n"
		"		□□□□□□□□□□□□\n"
		);
	getch(); 

		first_time = GetTickCount();/* time(NULL);*/
	while(1)
	{
		if(kbhit())		// 检查当前是否有键盘输入，若有则返回一个非0值，否则返回0
		switch(getch())	{
			case 'a' : case 'A' :	if( h_x < 0 ) h_x = 1;	    Show(--h_x,h_Y,f_x,f_y); 		break;
			case 'd' : case 'D' : 	if( h_x > 9 ) h_x = 8; 		Show(++h_x,h_Y,f_x,f_y);		break;
			case  27 : Setup();		system("cls");		first_time =  GetTickCount();	 Show(h_x,h_Y,f_x,f_y); 	 break;	 //27代表ASCII码中的【Esc】 
			}
		second_time =  GetTickCount();
		if( second_time - first_time >= difficulty )
			first_time =GetTickCount() ,Show(h_x,h_Y,f_x,++f_y);
	 	if( f_y == 9 )	f_x  = (int)(10.0 *rand()/(RAND_MAX+1.0)),f_y = 0;
	 	if( life == 0 )	
		{
	 	system("cls");
	 	SetConsoleTextAttribute(hConsole,FOREGROUND_RED|FOREGROUND_INTENSITY); 
		printf(
		" □□□□□□□□□□□□□□□□□□□□□□□□□□□□□\n"
		" □	   		GAME OVER！			 □\n"
		" □□□□□□□□□□□□□□□□□□□□□□□□□□□□□\n"
		);
		getch();
		break;
	} 	}
	
	return 0;

} 
void Show(int hand_x,int hand_y,int face_x,int face_y)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	char a[10][10]={0};
	a[hand_x][hand_y] = 34;
	a[face_x][face_y] = 1 ;
	if(hand_x == face_x && hand_y==face_y)			score+=10;
	else if( face_y == 9 && hand_x != face_x )		life-=1,printf("\7");	
	system("cls");	//清屏
	SetConsoleTextAttribute(hConsole,FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_INTENSITY); 
	printf("		□□□□□□□□□□□□ \n");	
		for( hand_y = 0 ; hand_y < 10 ; hand_y++ )
		{	 
			SetConsoleTextAttribute(hConsole,FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_INTENSITY); 
			printf("		□");
			SetConsoleTextAttribute(hConsole, 128 );
			for( hand_x = 0 ; hand_x < 10 ; hand_x++ )
			printf("%c ",a[hand_x][hand_y]);
			SetConsoleTextAttribute(hConsole,FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_INTENSITY); 
			printf("□");
			SetConsoleTextAttribute(hConsole,FOREGROUND_BLUE|FOREGROUND_GREEN|FOREGROUND_INTENSITY); 
			if( hand_y == 1 ) printf("	得分 :%2d",score); 
			if( hand_y == 2 ) printf("	生命 :%2d",life); 	
			printf("\n");
		}
			
		 SetConsoleTextAttribute(hConsole,FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_INTENSITY); 
		printf("		□□□□□□□□□□□□ \n");	
	  SetConsoleTextAttribute(hConsole,FOREGROUND_BLUE|FOREGROUND_GREEN|FOREGROUND_INTENSITY);
	return;
}
void Setup(void)
{
	printf("\n 游戏的难度：1.简单2.困难3.复杂>> ");
	switch(getche())
	{	
	case '1':difficulty=500;	printf("\n 设置成功 正在保存..."); 	Sleep(1000);	break;
	case '2':difficulty=300;	printf("\n 设置成功 正在保存..."); 	Sleep(1000);	break;
	case '3':difficulty=200;	printf("\n 设置成功 正在保存..."); 	Sleep(1000);	break;
	default:printf("\n 输入错误 请重试");  	Setup();	//递归 
	}
	return; 

} 




/*
完成时间：2016.6.3（第一版） 

缺点总结：

 1.既然用控制台api，画图案直接用api设置光标位置重绘
 不要直接清屏  会闪烁
 （goto_xy函数） 
 
 2. 生成随机数 没必要用浮点数
 浮点数慢 ，虽然在这里影响不大
 【 24行  47行 】 
 
 3.该换行换行 不要挤在一起
 【 46行 】 
 
 4.这里 只有变量赋值的操作是不同的
 所以switch里面修改变量就可以了
 后面2句写在switch外面
 【 100行 到 102行 】 

 5.数组溢出 【 40行 .41行】

*/
