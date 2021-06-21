/*		头文件			*/
# include <windows.h>
# include <stdlib.h>
# include <stdio.h>
# include <conio.h>
# include <time.h>

/*		全局变量		*/ 
int score = 0 ,life = 0 ,difficulty = 500 ;  //已初始化（得分，生命，难度）

/*		声明函数		*/
void gotoxy(int x,int y,int width)	;						//光标到指定位置 
void Loading(void); 										//加载界面 
void Setup(void);											//设置界面
void Move(int * move_6); 									//游戏移动 
void Show(void);											//游戏界面  



int main(void)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	int * play_show = malloc(sizeof(int) * 4);		//分配动态内存
	long first_time, second_time;

	/*	隐藏光标   26--31行*/		
	HANDLE hC = GetStdHandle(STD_OUTPUT_HANDLE);	//获得标准输出设备句柄
	CONSOLE_CURSOR_INFO cci;						//定义光标信息结构体 
	GetConsoleCursorInfo(hC, &cci);					//获得当前光标信息 
	cci.bVisible = 0;								//为0时光标不可见
	SetConsoleCursorInfo(hC, &cci);
	

	system("color 07");								//设置窗口颜色

	Loading();

	system("title 接鸡蛋   ——C语言制作");			//改变窗口标题
	system("mode con: cols=39 lines=19");			//设置窗口大小

    srand((unsigned)time(NULL));					//随机数种子	

	/*
	move_6[0]代表的是手的横坐标 手的纵坐标固定是9
	move_6[1]代表的是笑脸的横坐标
	move_6[2]代表的是笑脸的纵坐标
	move_6[3]代表的是手比起之前增加或减少的值 （横坐标）
	move_6[4]代表的是笑脸比起之前增加或减少的值 （横坐标）
	move_6[5]代表的是笑脸比起之前增加或减少的值 （纵坐标）
	*/
												
	play_show[0] = 5;
	play_show[1] =(int)(10 *rand()/(RAND_MAX+1));		
	play_show[2] = 0;
	play_show[3] = 0;
	play_show[4] = 0;
	play_show[5] = 0;
	
	Show();										//显示游戏界面 
	Move(play_show);							//画手画蛋
	_getch(); 

	first_time = GetTickCount();				//获取毫秒级数目
	while(1)
	{
		if(_kbhit())		// 检查当前是否有键盘输入，若有则返回一个非0值，否则返回0
		switch(getch())	{
		case 'a' : case 'A' :	
			if( *(play_show+0) <= 0 ) *(play_show+0) = 1;	  
			(*(play_show+0))--;  	
			play_show[3] = 1;
			Move(play_show); 	
			break;
		case 'd' : case 'D' : 	
			if( *(play_show+0) >= 9 ) *(play_show+0) = 8;     
			( *(play_show+0))++;	
			play_show[3] = -1; 
			Move(play_show);	 		
			break;	
		case  27 :								//27代表ASCII码中的【Esc】 
			Setup();		
			system("cls");		
			Show();		
			first_time =  GetTickCount();		//重新获取毫秒级数目	 
			Move(play_show);
			break;	
		default:
			if(_getch()!='A'||'a'||'D'||'d')	    first_time =  GetTickCount();	 
			Move(play_show);	 	 
			break;	 
			}
		second_time =  GetTickCount();	 
		if( second_time - first_time >= difficulty )  //判断鸡蛋时间（移动速度）
		{
			first_time =GetTickCount();
			(*(play_show+2))++;
			(*(play_show+5))=-1;
			Move(play_show);	
		}
	 	if( *(play_show+2) == 10 )	
	 	{	
	 		system("cls");
	 		system("color 07"); 
	 		play_show[1] =(int)(10 *rand()/(RAND_MAX+1));		 //产生随机数并取余		
			play_show[2] = 0;
			play_show[3] = 0;
			play_show[4] = 0;
			play_show[5] = 0;
	 		Show();      
			Move(play_show);
		}
	 	if( life <= 0 )	
		{
	 		system("cls");
	 		system("color 07"); 
	 		SetConsoleTextAttribute(hConsole,FOREGROUND_RED|FOREGROUND_INTENSITY); 
			printf(
			"									  \n"
			"									  \n"
			"									  \n"
			"									  \n"
			" □□□□□□□□□□□□□□□□□□\n"
			" □            GAME OVER!          □\n"
			" □□□□□□□□□□□□□□□□□□\n"
			);
			_getch();
			break;
		}
	} 	
	free(play_show);								//释放动态内存
	play_show = NULL;
	return 0;

} 


 /*		定义函数		*/
void gotoxy(int x,int y,int width)  
{
	HANDLE hOut;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE); //获得标准输入输出的句柄
	COORD pos = {x*width,y};			//表示一个字符在控制台屏幕上的坐标(ASCLL码宽度为1 非ASCLL码宽度为2)
	SetConsoleCursorPosition(hOut ,pos);    //光标定位在对应的位置	
	return;
}
 void Loading(void)
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
        	gotoxy(Loading_b+1,1,2);// 字符宽2 高1 （不是ACSLL码） 
            printf( "▉");
       	}
    printf( "\n  ==================================================\n"  );
   	printf("				正在进入游戏");
    Sleep(40);
    }	
    return;
} 
void Setup(void)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole,FOREGROUND_BLUE|FOREGROUND_GREEN|FOREGROUND_INTENSITY);
	gotoxy(0,16,1) ;
	printf(" ------------------------------------\n");
	printf(" 游戏的难度:1.简单 2.困难 3.复杂 >> ");
	switch(getche())
	{	
	case '1':difficulty=500;		break;
	case '2':difficulty=300;		break;
	case '3':difficulty=200;		break;
	default:printf("\n 输入错误 请重试");  	Setup();	//递归 
	}
	printf("\n 设置成功 正在保存..."); 
	Sleep(1000);
	return; 
} 
void Move(int * move_6)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	/* 
	move_6[0]代表的是手的横坐标 手的纵坐标固定是9 
	move_6[1]代表的是笑脸的横坐标
	move_6[2]代表的是笑脸的纵坐标
	move_6[3]代表的是手比起之前增加或减少的值 （横坐标） 
	move_6[4]代表的是笑脸比起之前增加或减少的值 （横坐标）
	move_6[5]代表的是笑脸比起之前增加或减少的值 （纵坐标）
	gotoxy(9,2,1);
	*/ 
	
	if( move_6[0] > 9 || move_6[0] < 0 || move_6[1] > 9 || move_6[1] < 0 || move_6[2] > 9 || move_6[2] < 0  ) return ;
	
	SetConsoleTextAttribute(hConsole,FOREGROUND_GREEN|FOREGROUND_INTENSITY);
	if( move_6[0] == move_6[1] && 9 == move_6[2] )			
	{ 
	score+=10;
	gotoxy(8,0,1);
	printf("%2d",score);
	} 
	else if( move_6[2] == 9 && move_6[0] != move_6[1] )	
	{	
	life-=1;
	printf("\7");
	gotoxy(32,0,1);
	printf("%2d",life);
	} 
	SetConsoleTextAttribute(hConsole, 128);
		/*清除手*/
	gotoxy(9+move_6[0]*2+move_6[3]*2,2+9,1);
	printf(" ");
		/*清除笑脸*/
	gotoxy(9+move_6[1]*2+move_6[4]*2,2+move_6[2]+move_6[5],1);
	printf(" ");
		 /*画笑脸*/
	gotoxy(9+move_6[1]*2,2+move_6[2],1);
	putchar(1);
		/*画手*/
	gotoxy(9+move_6[0]*2,2+9,1);
	putchar(34);
	return;
}
void Show(void)
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
		);	  
		SetConsoleTextAttribute(hConsole,FOREGROUND_RED|FOREGROUND_INTENSITY);
		gotoxy(22,14,1); 
		printf("|  温馨提示:");	
		gotoxy(22,15,1); 
		printf("|  尿急可按任");
		gotoxy(22,16,1);  
		printf("|  意键暂停. ");
	
	return;
}

/*
完成时间：2016.6.25（第二版） 

作者 奥利奥  
QQ 2783608988	C语言资源共享群 519536269
欢迎各位提出宝贵意见  本人感激不尽  



本版本改正了数组溢出问题和一些逻辑问题
采用画图案的方法减少了闪烁


本版本缺点：
每当开始掉下鸡蛋的时候，屏幕会闪烁一次





*/
