/*				头文件					*/
# include <windows.h>
# include <stdlib.h>
# include <stdio.h>
# include <conio.h>
# include <time.h>

/*				全局变量			*/ 
int score = 0 ,life = 5 ,difficulty = 500 ;				 //已初始化（得分，生命，难度）
/*				结构体				*/	
struct location
{
	/*
	hand_x			代表的是手的横坐标 手的纵坐标固定是9
	egg_x			代表的是鸡蛋的横坐标
	egg_y			代表的是鸡蛋的纵坐标
	d_hand_x		代表的是手比起之前增加或减少的值	（横坐标）	【hand_x	 + 	d_hand_x		=	手的旧横坐标】
	d_egg_x		代表的是鸡蛋比起之前增加或减少的值 （横坐标）	【egg_x	 + 	d_egg_x		=	蛋的旧横坐标】
	d_egg_y		代表的是鸡蛋比起之前增加或减少的值 （纵坐标）	【egg_y	 +		d_egg_y	    =	蛋的旧纵坐标】
	egg_type		代表鸡蛋种类   1是白色鸡蛋（得分+10），2是黑色鸡蛋（得分+50，生命+1）
	*/
	int	hand_x ,egg_x,egg_y ,d_hand_x, d_egg_x,	d_egg_y,egg_type;

}; 

/*				声明函数			*/
void gotoxy(int x,int y,int width)	;						//光标到指定位置 
void Loading(void); 												//加载界面 
void Setup(void);													//设置界面
void Move(struct location * p_play ); 					//游戏移动 
void Show(void);													//游戏界面  

int main(void)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	long first_time, second_time;

	/*		隐藏光标   39--44行		*/		
	HANDLE hC = GetStdHandle(STD_OUTPUT_HANDLE);	//获得标准输出设备句柄
	CONSOLE_CURSOR_INFO cci;											//定义光标信息结构体 
	GetConsoleCursorInfo(hC, &cci);										//获得当前光标信息 
	cci.bVisible = 0;																//为0时光标不可见
	SetConsoleCursorInfo(hC, &cci);

	system("color 07");											//设置窗口颜色

	Loading();

	system("title 接鸡蛋   ——C语言制作");			//改变窗口标题
	system("mode con: cols=39 lines=19");			//设置窗口大小

    srand((unsigned)time(NULL));							//随机数种子	

	struct location play = {5,(int)(10 * rand() / (RAND_MAX + 1)) ,0,0,0,0,1};	//定义结构体变量 并 初始化
	
	Show();															//显示游戏界面 
	Move(&play);												//画手画蛋

	_getch(); 

	first_time = GetTickCount();						//获取毫秒级数目（便于控制鸡蛋移动速度）

	while(1)
	{
		/*
		hand_x			代表的是手的横坐标 手的纵坐标固定是9  
		egg_x			代表的是鸡蛋的横坐标 
		egg_y			代表的是鸡蛋的纵坐标 
		d_hand_x		代表的是手比起之前增加或减少的值	（横坐标）	【hand_x	 + 	d_hand_x		=	手的旧横坐标】 
		d_egg_x		代表的是鸡蛋比起之前增加或减少的值 （横坐标）	【egg_x	 + 	d_egg_x		=	蛋的旧横坐标】 
		d_egg_y		代表的是鸡蛋比起之前增加或减少的值 （纵坐标）	【egg_y	 +		d_egg_y	    =	蛋的旧纵坐标】
		egg_type		代表鸡蛋种类   1是白色鸡蛋（得分+10），2是黑色鸡蛋（得分+50，生命+1）
		*/
		if(_kbhit())						// 检查当前是否有键盘输入（手和鸡蛋能够同时移动的关键）
		switch(getch())	{
		case 'a' : case 'A' :	
			if( play.hand_x <= 0 )		play.hand_x = 1;			play.hand_x--;
			play.d_hand_x = 1;			Move(&play); 		break;
		case 'd' : case 'D' : 	
			if(play.hand_x >= 9 )		 play.hand_x = 8;			play.hand_x++;
			play.d_hand_x = -1;			Move(&play);		break;	
		case  27 :											//27代表ASCII码中的【Esc】 （进入设置菜单）
			Setup();			system("cls");			Show();		
			first_time =  GetTickCount();		//重新获取毫秒级数目	 
			Move(&play);			break;	
		default:											//按任意非控制键停止
			if (_getch() != 'A' || 'a' || 'D' || 'd')	    first_time = GetTickCount();	//重新获取毫秒级数目	 
			Move(&play);	 			break;	 
			}
		second_time =  GetTickCount();	 
		if (second_time - first_time >= difficulty)  //判断鸡蛋时间（控制移动速度）
		{
			first_time = GetTickCount();
			play.egg_y++;
			play.d_egg_y = -1;
			play.d_hand_x  = play.d_egg_x  = 0;
			Move(&play);
		}
	 	if( play.egg_y == 10 )		//鸡蛋到底时
	 	{	
			/*
			hand_x			代表的是手的横坐标 手的纵坐标固定是9 
			egg_x			代表的是鸡蛋的横坐标 
			egg_y			代表的是鸡蛋的纵坐标 
			d_hand_x		代表的是手比起之前增加或减少的值	（横坐标）	【hand_x	 + 	d_hand_x		=	手的旧横坐标】
			d_egg_x		代表的是鸡蛋比起之前增加或减少的值 （横坐标）	【egg_x	 + 	d_egg_x		=	蛋的旧横坐标】
			d_egg_y		代表的是鸡蛋比起之前增加或减少的值 （纵坐标）	【egg_y	 +		d_egg_y	    =	蛋的旧纵坐标】
			egg_type		代表鸡蛋种类   1是白色鸡蛋（得分+10），2是黑色鸡蛋（得分+50，生命+1）
			*/
			play.d_egg_x = play.egg_x ;										   	//保存笑脸的旧横坐标，便于计算
	 		play.egg_x =(int)(10 *rand()/(RAND_MAX+1));			 //产生随机数并取余		
			play.egg_y = play.d_hand_x = 0;

			play.d_egg_x = play.d_egg_x - play.egg_x;
			play.d_egg_y = 9;

			if ((int)(10 * rand() / (RAND_MAX + 1)) > 7)			//利用随机得出鸡蛋种类
				play.egg_type = 2;
			else
				play.egg_type = 1;

			Move(&play);
		}
		
	 	if( life <= 0 )				//生命低于或等于0时
		{
	
	 		SetConsoleTextAttribute(hConsole,FOREGROUND_RED|FOREGROUND_INTENSITY); 
			gotoxy(0, 5, 1);
			printf(
			" □□□□□□□□□□□□□□□□□□\n"
			" □            GAME OVER!          □\n"
			"  □            按Y继续           □\n"
			"   □           按N结束          □\n"
			"    □□□□□□□□□□□□□□□  \n"
			);
			char judge;
			
			while (1)
			{
				judge = _getch();
				if ( judge == 'Y' || judge == 'y' )
				{
					/*			重新定义		*/	
					life = 5;
					play.hand_x = 5;
					play.egg_x = (int)(10 * rand() / (RAND_MAX + 1));
					play.egg_y = play.d_hand_x = play.d_egg_x = play.d_egg_y = 0;

					system("cls");

					Show();															//显示界面
					Move(&play);												//画手画蛋
					break;
				}
				else if ( judge == 'N' || judge == 'n' )
					exit(1);
			}


		}
	} 	
	return 0;

} 


 /*		定义函数		*/
void gotoxy(int x,int y,int width)									//光标到指定位置 
{
	HANDLE hOut;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);		//获得标准输入输出的句柄
	COORD pos = {x*width,y};										//表示一个字符在控制台屏幕上的坐标(ASCLL码宽度为1 非ASCLL码宽度为2)
	SetConsoleCursorPosition(hOut ,pos);				    //光标定位在对应的位置	
	return;
}
 void Loading(void)														//加载界面 
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); 
	system("title 游戏正在加载"); 
	system("mode con cols=54 lines=5");
	int Loading_a, Loading_b;
	SetConsoleTextAttribute(hConsole,FOREGROUND_BLUE|FOREGROUND_GREEN|FOREGROUND_INTENSITY);
    for( Loading_a = 0; Loading_a <= 100; Loading_a+=4)
    {
    	gotoxy(2,10,1);
		printf("%d%%",Loading_a);
        gotoxy(0,0,1);
        printf("  ==================================================\n" );;
        for(Loading_b=0; Loading_b < Loading_a/4; Loading_b++)
        {
        	gotoxy(Loading_b+1,1,2);							// 字符宽2 高1 （不是ACSLL码） 
            printf( "▉");
       	}
    printf( "\n  ==================================================\n"  );
   	printf("				正在进入游戏");
    Sleep(40);
    }	
    return;
} 
void Setup(void)															//设置界面
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole,FOREGROUND_BLUE|FOREGROUND_GREEN|FOREGROUND_INTENSITY);
	gotoxy(0,16,1) ;
	printf(" ------------------------------------\n");
	printf(" 游戏的难度:1.简单 2.困难 3.复杂 >> ");
	switch(getche())														//有回显的键盘输入
	{	
	case '1':difficulty=500;		break;
	case '2':difficulty=300;		break;
	case '3':difficulty=180;		break;
	default:printf("\n 输入错误 请重试");  	Setup();				//递归 
	}
	printf("\n 设置成功 正在保存..."); 
	Sleep(1000);
	return; 
} 
void Move(struct location * p_play )							//游戏移动
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	/* 

	hand_x			代表的是手的横坐标 手的纵坐标固定是9	
	egg_x			代表的是鸡蛋的横坐标
	egg_y			代表的是鸡蛋的纵坐标
	d_hand_x		代表的是手比起之前增加或减少的值	（横坐标）	【hand_x	 + 	d_hand_x		=	手的旧横坐标】
	d_egg_x		代表的是鸡蛋比起之前增加或减少的值 （横坐标）	【egg_x	 + 	d_egg_x		=	蛋的旧横坐标】
	d_egg_y		代表的是鸡蛋比起之前增加或减少的值 （纵坐标）	【egg_y	 +		d_egg_y	    =	蛋的旧纵坐标】
	egg_type		代表鸡蛋种类   1是白色鸡蛋（得分+10），2是黑色鸡蛋（得分+50，生命+1）

	gotoxy(9,2,1);
	*/ 
	
	if(  p_play->hand_x > 9 || p_play->hand_x < 0 || p_play->egg_x > 9 || p_play->egg_x < 0 || p_play->egg_y > 9 || p_play->egg_y < 0  ) 
		return ;				//检查是否错误，错误则结束函数调用
	
	SetConsoleTextAttribute(hConsole,FOREGROUND_GREEN|FOREGROUND_INTENSITY);
	if(	p_play->hand_x == p_play->egg_x && 9 == p_play->egg_y)         //当手接到鸡蛋时
	{ 
		if( p_play->egg_type == 1)				//当手接到白鸡蛋时
			score+=10;			//得分+10
		else if (p_play->egg_type == 2)		 //当手接到黑鸡蛋时
		{
			score += 50;		 //得分+50
			life += 1;				//生命+1
		}
		gotoxy(8,0,1);
		printf("%2d",score);
		gotoxy(32, 0, 1);
		printf("%2d", life);
	} 
	else if(p_play->egg_y == 9 && p_play->hand_x != p_play->egg_x)		//当手错过鸡蛋时
	{	
			life -= 1;
			printf("\7");
			gotoxy(32,0,1);
			printf("%2d",life);
	} 
	SetConsoleTextAttribute(hConsole, 128);
		/*清除手*/
	gotoxy(9+ p_play->hand_x *2+ p_play->d_hand_x *2,2+9,1);
	printf(" ");
		/*清除鸡蛋*/
	gotoxy(9+ p_play->egg_x *2+ p_play->d_egg_x *2,2+ p_play->egg_y + p_play->d_egg_y,1);
	printf(" ");
		 /*画鸡蛋*/
	gotoxy(9+ p_play->egg_x *2,2+ p_play->egg_y,1);
	putchar(p_play->egg_type);
		/*画手*/
	gotoxy(9+ p_play->hand_x *2,2+9,1);
	putchar(34);
	return;
}
void Show(void)													//游戏界面  
{	
	int show_x ,show_y,show_y2 = 1;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole,FOREGROUND_BLUE|FOREGROUND_GREEN|FOREGROUND_INTENSITY); 		
	printf("  得分 :");
	SetConsoleTextAttribute(hConsole,FOREGROUND_GREEN|FOREGROUND_INTENSITY); 
	printf("%2d ",score);
	SetConsoleTextAttribute(hConsole,FOREGROUND_BLUE|FOREGROUND_GREEN|FOREGROUND_INTENSITY); 
	printf("               生命 :"); 
	SetConsoleTextAttribute(hConsole,FOREGROUND_GREEN|FOREGROUND_INTENSITY);	 
	printf("%2d ",life);
	SetConsoleTextAttribute(hConsole,FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_INTENSITY); 
	gotoxy(7,1,1);
	printf("□□□□□□□□□□□□ \n");	
		for( show_y = 0 ; show_y < 10 ; show_y++ )
		{	gotoxy(7,++show_y2,1);
			SetConsoleTextAttribute(hConsole,FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_INTENSITY); 
			printf("□");
			SetConsoleTextAttribute(hConsole, 128);
			for( show_x = 0 ; show_x < 10 ; show_x++ )
			printf("  ");
			SetConsoleTextAttribute(hConsole,FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_INTENSITY); 
			printf("□\n");
		}
		SetConsoleTextAttribute(hConsole,FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_INTENSITY); 
		gotoxy(7,++show_y2,1);
		printf("□□□□□□□□□□□□ \n");	
		gotoxy(0,14,1) ;
		SetConsoleTextAttribute(hConsole,FOREGROUND_BLUE|FOREGROUND_GREEN|FOREGROUND_INTENSITY);
		printf(
		"       操作指南      |\n"
   	    " 【A】【D】移动接笑脸|\n" 
   	    " 【Esc】进入设置界面 |\n"
			"   &作者 ——奥利奥& |\n"
		);	  
		SetConsoleTextAttribute(hConsole,FOREGROUND_RED|FOREGROUND_INTENSITY);
		gotoxy(22,14,1); 
		printf("|  温馨提示:");	
		gotoxy(22,15,1); 
		printf("|  尿急可按任");
		gotoxy(22,16,1);  
		printf("|  意非控制键");
		gotoxy(22, 17, 1);
		printf("|  暂停. ");
	
	return;
}

/*
完成时间：2016.7.6（第四版）【终极版】 

作者 奥利奥  
QQ 2783608988	C语言资源共享群 519536269
欢迎各位提出宝贵意见  本人感激不尽  

*/
