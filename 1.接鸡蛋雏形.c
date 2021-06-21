/*                      头文件                        */
#include <windows.h>
#include <stdlib.h>
#include <conio.h>
#include <stdio.h>
#include <time.h>
int score,life,difficulty,f_speed;  //全局变量——得分，生命，难度，速度 
/*                    声明函数                        */
int Show(int hand_x,int hand_y,int face_x,int face_y);    
void Set_up_the(void); 
void Title_turn(void);    
                           
int main()
{
	const int h_Y = 9;      
	int h_x = 5 , f_y = 0 , f_x , check;
	int speed = 0 ;
	srand((unsigned)time(NULL));  // 随机数种子 -- 这个函数一定要放在循环外面或者是循环调用的外面，否则的话得到的是相同的数字。
	f_x  = (int)(10.0 *rand()/(RAND_MAX+1.0)); //	f_x = rand()%10;   产生随机数并取余
	Title_turn();
	Show(h_x,h_Y,f_x,f_y);       //显示游戏界面 
	while(1) 		//防止游戏执行一次 
		{
	if(kbhit())  // 检查当前是否有键盘输入，若有则返回一个非0值，否则返回0
	switch(getch())
	{ 
	case 'a' : case 'A' :if( h_x > 9 ) h_x = 9;		Show(--h_x,h_Y,f_x,f_y);	/*	break;*/continue;
	case 'd' : case 'D' :if( h_x < 0 ) h_x = 0;   	Show(++h_x,h_Y,f_x,f_y);/*		break;*/continue;
	case  27 : Set_up_the(); break;
	}
	if(++speed%f_speed==0)//控制生产敌机的速度
speed=0;srand(time(NULL));

}

		if( check == 1 )
	{
	f_x = (int)(10.0*rand()/(RAND_MAX+1.0));	//	f_x = rand()%10;   产生随机数并取余
	f_y = 0;
	Show(h_x,h_Y,f_x,f_y); 
	}
		


    return 0;
}

int Show(int hand_x,int hand_y,int face_x,int face_y)  //定义函数 
{
	
	system("cls");  //清屏 
	if( hand_x < 0 ) hand_x = 0;
	else if( hand_x > 9 ) hand_x = 9;	
	char a[10][10]={0};
	a[hand_x][hand_y] = 34;
	a[face_x][face_y] = 1 ;
	printf("_ _ _ _ _ ★ _ _ _ _ _\n");
		for( hand_y = 0 ; hand_y < 10 ; hand_y++ )
		{
			printf("|");
			for( hand_x = 0 ; hand_x < 10 ; hand_x++ )
				printf("%c ",a[hand_x][hand_y]);
			if( hand_x == face_x &&	hand_x - face_x == 1 )score+=10	;
		
			printf("|");
			if( hand_y == 1 ) printf("	得分 :%2d",score); 
			if( hand_y == 2 ) printf("	生命 :%2d",life); 
			if( hand_y == 3 ) printf("按【Esc】进入设置菜单"); 
			printf("\n");
		}
	printf("- - - - - ☆ - - - - -\n");	
	if( face_y > 9 ) return 1; 
	if( face_y >= 0 && face_y <= 9 ) return 0; 
	
}
void Set_up_the(void)
{
	system("cls");//清屏 
	while(1)
	{
	printf("\n 游戏的难度：1.简单2.困难3.复杂>> ");
	switch(getch())
	{	
	case '1':difficulty=1;	printf("设置成功 正在保存..."); 	Sleep(1000);	break;
	case '2':difficulty=2;	printf("设置成功 正在保存..."); 	Sleep(1000);	break;
	case '3':difficulty=3;	printf("设置成功 正在保存..."); 	Sleep(1000);	break;
	default:printf("\n 错误，请重新选择...\n");

	}
	return;
	}
}

void Title_turn(void)
{
	system("title A.T.S.F  1.0    ——奥利奥制作");
	printf("------操作指南------\n"
   	    	"【A】【D】移动接笑脸\n" 
   	    	"【Esc】进入设置界面\n"
   	    	"---按任何键继续---\n"  
			   );		
	if( getch() == 27 )Set_up_the();  //27代表ASCII码中的【Esc】 
	return;
}
