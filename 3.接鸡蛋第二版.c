/*		ͷ�ļ�			*/
# include <windows.h>
# include <stdlib.h>
# include <stdio.h>
# include <conio.h>
# include <time.h>

/*		ȫ�ֱ���		*/ 
int score = 0 ,life = 0 ,difficulty = 500 ;  //�ѳ�ʼ�����÷֣��������Ѷȣ�

/*		��������		*/
void gotoxy(int x,int y,int width)	;						//��굽ָ��λ�� 
void Loading(void); 										//���ؽ��� 
void Setup(void);											//���ý���
void Move(int * move_6); 									//��Ϸ�ƶ� 
void Show(void);											//��Ϸ����  



int main(void)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	int * play_show = malloc(sizeof(int) * 4);		//���䶯̬�ڴ�
	long first_time, second_time;

	/*	���ع��   26--31��*/		
	HANDLE hC = GetStdHandle(STD_OUTPUT_HANDLE);	//��ñ�׼����豸���
	CONSOLE_CURSOR_INFO cci;						//��������Ϣ�ṹ�� 
	GetConsoleCursorInfo(hC, &cci);					//��õ�ǰ�����Ϣ 
	cci.bVisible = 0;								//Ϊ0ʱ��겻�ɼ�
	SetConsoleCursorInfo(hC, &cci);
	

	system("color 07");								//���ô�����ɫ

	Loading();

	system("title �Ӽ���   ����C��������");			//�ı䴰�ڱ���
	system("mode con: cols=39 lines=19");			//���ô��ڴ�С

    srand((unsigned)time(NULL));					//���������	

	/*
	move_6[0]��������ֵĺ����� �ֵ�������̶���9
	move_6[1]�������Ц���ĺ�����
	move_6[2]�������Ц����������
	move_6[3]��������ֱ���֮ǰ���ӻ���ٵ�ֵ �������꣩
	move_6[4]�������Ц������֮ǰ���ӻ���ٵ�ֵ �������꣩
	move_6[5]�������Ц������֮ǰ���ӻ���ٵ�ֵ �������꣩
	*/
												
	play_show[0] = 5;
	play_show[1] =(int)(10 *rand()/(RAND_MAX+1));		
	play_show[2] = 0;
	play_show[3] = 0;
	play_show[4] = 0;
	play_show[5] = 0;
	
	Show();										//��ʾ��Ϸ���� 
	Move(play_show);							//���ֻ���
	_getch(); 

	first_time = GetTickCount();				//��ȡ���뼶��Ŀ
	while(1)
	{
		if(_kbhit())		// ��鵱ǰ�Ƿ��м������룬�����򷵻�һ����0ֵ�����򷵻�0
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
		case  27 :								//27����ASCII���еġ�Esc�� 
			Setup();		
			system("cls");		
			Show();		
			first_time =  GetTickCount();		//���»�ȡ���뼶��Ŀ	 
			Move(play_show);
			break;	
		default:
			if(_getch()!='A'||'a'||'D'||'d')	    first_time =  GetTickCount();	 
			Move(play_show);	 	 
			break;	 
			}
		second_time =  GetTickCount();	 
		if( second_time - first_time >= difficulty )  //�жϼ���ʱ�䣨�ƶ��ٶȣ�
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
	 		play_show[1] =(int)(10 *rand()/(RAND_MAX+1));		 //�����������ȡ��		
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
			" ������������������������������������\n"
			" ��            GAME OVER!          ��\n"
			" ������������������������������������\n"
			);
			_getch();
			break;
		}
	} 	
	free(play_show);								//�ͷŶ�̬�ڴ�
	play_show = NULL;
	return 0;

} 


 /*		���庯��		*/
void gotoxy(int x,int y,int width)  
{
	HANDLE hOut;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE); //��ñ�׼��������ľ��
	COORD pos = {x*width,y};			//��ʾһ���ַ��ڿ���̨��Ļ�ϵ�����(ASCLL����Ϊ1 ��ASCLL����Ϊ2)
	SetConsoleCursorPosition(hOut ,pos);    //��궨λ�ڶ�Ӧ��λ��	
	return;
}
 void Loading(void)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); 
	system("title ��Ϸ���ڼ���"); 
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
        	gotoxy(Loading_b+1,1,2);// �ַ���2 ��1 ������ACSLL�룩 
            printf( "��");
       	}
    printf( "\n  ==================================================\n"  );
   	printf("				���ڽ�����Ϸ");
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
	printf(" ��Ϸ���Ѷ�:1.�� 2.���� 3.���� >> ");
	switch(getche())
	{	
	case '1':difficulty=500;		break;
	case '2':difficulty=300;		break;
	case '3':difficulty=200;		break;
	default:printf("\n ������� ������");  	Setup();	//�ݹ� 
	}
	printf("\n ���óɹ� ���ڱ���..."); 
	Sleep(1000);
	return; 
} 
void Move(int * move_6)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	/* 
	move_6[0]��������ֵĺ����� �ֵ�������̶���9 
	move_6[1]�������Ц���ĺ�����
	move_6[2]�������Ц����������
	move_6[3]��������ֱ���֮ǰ���ӻ���ٵ�ֵ �������꣩ 
	move_6[4]�������Ц������֮ǰ���ӻ���ٵ�ֵ �������꣩
	move_6[5]�������Ц������֮ǰ���ӻ���ٵ�ֵ �������꣩
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
		/*�����*/
	gotoxy(9+move_6[0]*2+move_6[3]*2,2+9,1);
	printf(" ");
		/*���Ц��*/
	gotoxy(9+move_6[1]*2+move_6[4]*2,2+move_6[2]+move_6[5],1);
	printf(" ");
		 /*��Ц��*/
	gotoxy(9+move_6[1]*2,2+move_6[2],1);
	putchar(1);
		/*����*/
	gotoxy(9+move_6[0]*2,2+9,1);
	putchar(34);
	return;
}
void Show(void)
{	
	int show_x ,show_y,show_y2 = 1;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole,FOREGROUND_BLUE|FOREGROUND_GREEN|FOREGROUND_INTENSITY); 		
	printf("  �÷� :");
	SetConsoleTextAttribute(hConsole,FOREGROUND_GREEN|FOREGROUND_INTENSITY); 
	printf("%2d ",score);
	SetConsoleTextAttribute(hConsole,FOREGROUND_BLUE|FOREGROUND_GREEN|FOREGROUND_INTENSITY); 
	printf("               ���� :"); 
	SetConsoleTextAttribute(hConsole,FOREGROUND_GREEN|FOREGROUND_INTENSITY);	 
	printf("%2d ",life);
	SetConsoleTextAttribute(hConsole,FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_INTENSITY); 
	gotoxy(7,1,1);
	printf("������������������������ \n");	
		for( show_y = 0 ; show_y < 10 ; show_y++ )
		{	gotoxy(7,++show_y2,1);
			SetConsoleTextAttribute(hConsole,FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_INTENSITY); 
			printf("��");
			SetConsoleTextAttribute(hConsole, 128);
			for( show_x = 0 ; show_x < 10 ; show_x++ )
			printf("  ");
			SetConsoleTextAttribute(hConsole,FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_INTENSITY); 
			printf("��\n");
		}
		SetConsoleTextAttribute(hConsole,FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_INTENSITY); 
		gotoxy(7,++show_y2,1);
		printf("������������������������ \n");	
		gotoxy(0,14,1) ;
		SetConsoleTextAttribute(hConsole,FOREGROUND_BLUE|FOREGROUND_GREEN|FOREGROUND_INTENSITY);
		printf(
		"       ����ָ��      |\n"
   	    " ��A����D���ƶ���Ц��|\n" 
   	    " ��Esc���������ý��� |\n"
		);	  
		SetConsoleTextAttribute(hConsole,FOREGROUND_RED|FOREGROUND_INTENSITY);
		gotoxy(22,14,1); 
		printf("|  ��ܰ��ʾ:");	
		gotoxy(22,15,1); 
		printf("|  �򼱿ɰ���");
		gotoxy(22,16,1);  
		printf("|  �����ͣ. ");
	
	return;
}

/*
���ʱ�䣺2016.6.25���ڶ��棩 

���� ������  
QQ 2783608988	C������Դ����Ⱥ 519536269
��ӭ��λ����������  ���˸м�����  



���汾������������������һЩ�߼�����
���û�ͼ���ķ�����������˸


���汾ȱ�㣺
ÿ����ʼ���¼�����ʱ����Ļ����˸һ��





*/
