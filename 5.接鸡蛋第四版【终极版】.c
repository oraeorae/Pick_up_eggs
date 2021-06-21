/*				ͷ�ļ�					*/
# include <windows.h>
# include <stdlib.h>
# include <stdio.h>
# include <conio.h>
# include <time.h>

/*				ȫ�ֱ���			*/ 
int score = 0 ,life = 5 ,difficulty = 500 ;				 //�ѳ�ʼ�����÷֣��������Ѷȣ�
/*				�ṹ��				*/	
struct location
{
	/*
	hand_x			��������ֵĺ����� �ֵ�������̶���9
	egg_x			������Ǽ����ĺ�����
	egg_y			������Ǽ�����������
	d_hand_x		��������ֱ���֮ǰ���ӻ���ٵ�ֵ	�������꣩	��hand_x	 + 	d_hand_x		=	�ֵľɺ����꡿
	d_egg_x		������Ǽ�������֮ǰ���ӻ���ٵ�ֵ �������꣩	��egg_x	 + 	d_egg_x		=	���ľɺ����꡿
	d_egg_y		������Ǽ�������֮ǰ���ӻ���ٵ�ֵ �������꣩	��egg_y	 +		d_egg_y	    =	���ľ������꡿
	egg_type		����������   1�ǰ�ɫ�������÷�+10����2�Ǻ�ɫ�������÷�+50������+1��
	*/
	int	hand_x ,egg_x,egg_y ,d_hand_x, d_egg_x,	d_egg_y,egg_type;

}; 

/*				��������			*/
void gotoxy(int x,int y,int width)	;						//��굽ָ��λ�� 
void Loading(void); 												//���ؽ��� 
void Setup(void);													//���ý���
void Move(struct location * p_play ); 					//��Ϸ�ƶ� 
void Show(void);													//��Ϸ����  

int main(void)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	long first_time, second_time;

	/*		���ع��   39--44��		*/		
	HANDLE hC = GetStdHandle(STD_OUTPUT_HANDLE);	//��ñ�׼����豸���
	CONSOLE_CURSOR_INFO cci;											//��������Ϣ�ṹ�� 
	GetConsoleCursorInfo(hC, &cci);										//��õ�ǰ�����Ϣ 
	cci.bVisible = 0;																//Ϊ0ʱ��겻�ɼ�
	SetConsoleCursorInfo(hC, &cci);

	system("color 07");											//���ô�����ɫ

	Loading();

	system("title �Ӽ���   ����C��������");			//�ı䴰�ڱ���
	system("mode con: cols=39 lines=19");			//���ô��ڴ�С

    srand((unsigned)time(NULL));							//���������	

	struct location play = {5,(int)(10 * rand() / (RAND_MAX + 1)) ,0,0,0,0,1};	//����ṹ����� �� ��ʼ��
	
	Show();															//��ʾ��Ϸ���� 
	Move(&play);												//���ֻ���

	_getch(); 

	first_time = GetTickCount();						//��ȡ���뼶��Ŀ�����ڿ��Ƽ����ƶ��ٶȣ�

	while(1)
	{
		/*
		hand_x			��������ֵĺ����� �ֵ�������̶���9  
		egg_x			������Ǽ����ĺ����� 
		egg_y			������Ǽ����������� 
		d_hand_x		��������ֱ���֮ǰ���ӻ���ٵ�ֵ	�������꣩	��hand_x	 + 	d_hand_x		=	�ֵľɺ����꡿ 
		d_egg_x		������Ǽ�������֮ǰ���ӻ���ٵ�ֵ �������꣩	��egg_x	 + 	d_egg_x		=	���ľɺ����꡿ 
		d_egg_y		������Ǽ�������֮ǰ���ӻ���ٵ�ֵ �������꣩	��egg_y	 +		d_egg_y	    =	���ľ������꡿
		egg_type		����������   1�ǰ�ɫ�������÷�+10����2�Ǻ�ɫ�������÷�+50������+1��
		*/
		if(_kbhit())						// ��鵱ǰ�Ƿ��м������루�ֺͼ����ܹ�ͬʱ�ƶ��Ĺؼ���
		switch(getch())	{
		case 'a' : case 'A' :	
			if( play.hand_x <= 0 )		play.hand_x = 1;			play.hand_x--;
			play.d_hand_x = 1;			Move(&play); 		break;
		case 'd' : case 'D' : 	
			if(play.hand_x >= 9 )		 play.hand_x = 8;			play.hand_x++;
			play.d_hand_x = -1;			Move(&play);		break;	
		case  27 :											//27����ASCII���еġ�Esc�� ���������ò˵���
			Setup();			system("cls");			Show();		
			first_time =  GetTickCount();		//���»�ȡ���뼶��Ŀ	 
			Move(&play);			break;	
		default:											//������ǿ��Ƽ�ֹͣ
			if (_getch() != 'A' || 'a' || 'D' || 'd')	    first_time = GetTickCount();	//���»�ȡ���뼶��Ŀ	 
			Move(&play);	 			break;	 
			}
		second_time =  GetTickCount();	 
		if (second_time - first_time >= difficulty)  //�жϼ���ʱ�䣨�����ƶ��ٶȣ�
		{
			first_time = GetTickCount();
			play.egg_y++;
			play.d_egg_y = -1;
			play.d_hand_x  = play.d_egg_x  = 0;
			Move(&play);
		}
	 	if( play.egg_y == 10 )		//��������ʱ
	 	{	
			/*
			hand_x			��������ֵĺ����� �ֵ�������̶���9 
			egg_x			������Ǽ����ĺ����� 
			egg_y			������Ǽ����������� 
			d_hand_x		��������ֱ���֮ǰ���ӻ���ٵ�ֵ	�������꣩	��hand_x	 + 	d_hand_x		=	�ֵľɺ����꡿
			d_egg_x		������Ǽ�������֮ǰ���ӻ���ٵ�ֵ �������꣩	��egg_x	 + 	d_egg_x		=	���ľɺ����꡿
			d_egg_y		������Ǽ�������֮ǰ���ӻ���ٵ�ֵ �������꣩	��egg_y	 +		d_egg_y	    =	���ľ������꡿
			egg_type		����������   1�ǰ�ɫ�������÷�+10����2�Ǻ�ɫ�������÷�+50������+1��
			*/
			play.d_egg_x = play.egg_x ;										   	//����Ц���ľɺ����꣬���ڼ���
	 		play.egg_x =(int)(10 *rand()/(RAND_MAX+1));			 //�����������ȡ��		
			play.egg_y = play.d_hand_x = 0;

			play.d_egg_x = play.d_egg_x - play.egg_x;
			play.d_egg_y = 9;

			if ((int)(10 * rand() / (RAND_MAX + 1)) > 7)			//��������ó���������
				play.egg_type = 2;
			else
				play.egg_type = 1;

			Move(&play);
		}
		
	 	if( life <= 0 )				//�������ڻ����0ʱ
		{
	
	 		SetConsoleTextAttribute(hConsole,FOREGROUND_RED|FOREGROUND_INTENSITY); 
			gotoxy(0, 5, 1);
			printf(
			" ������������������������������������\n"
			" ��            GAME OVER!          ��\n"
			"  ��            ��Y����           ��\n"
			"   ��           ��N����          ��\n"
			"    ������������������������������  \n"
			);
			char judge;
			
			while (1)
			{
				judge = _getch();
				if ( judge == 'Y' || judge == 'y' )
				{
					/*			���¶���		*/	
					life = 5;
					play.hand_x = 5;
					play.egg_x = (int)(10 * rand() / (RAND_MAX + 1));
					play.egg_y = play.d_hand_x = play.d_egg_x = play.d_egg_y = 0;

					system("cls");

					Show();															//��ʾ����
					Move(&play);												//���ֻ���
					break;
				}
				else if ( judge == 'N' || judge == 'n' )
					exit(1);
			}


		}
	} 	
	return 0;

} 


 /*		���庯��		*/
void gotoxy(int x,int y,int width)									//��굽ָ��λ�� 
{
	HANDLE hOut;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);		//��ñ�׼��������ľ��
	COORD pos = {x*width,y};										//��ʾһ���ַ��ڿ���̨��Ļ�ϵ�����(ASCLL����Ϊ1 ��ASCLL����Ϊ2)
	SetConsoleCursorPosition(hOut ,pos);				    //��궨λ�ڶ�Ӧ��λ��	
	return;
}
 void Loading(void)														//���ؽ��� 
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
        	gotoxy(Loading_b+1,1,2);							// �ַ���2 ��1 ������ACSLL�룩 
            printf( "��");
       	}
    printf( "\n  ==================================================\n"  );
   	printf("				���ڽ�����Ϸ");
    Sleep(40);
    }	
    return;
} 
void Setup(void)															//���ý���
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole,FOREGROUND_BLUE|FOREGROUND_GREEN|FOREGROUND_INTENSITY);
	gotoxy(0,16,1) ;
	printf(" ------------------------------------\n");
	printf(" ��Ϸ���Ѷ�:1.�� 2.���� 3.���� >> ");
	switch(getche())														//�л��Եļ�������
	{	
	case '1':difficulty=500;		break;
	case '2':difficulty=300;		break;
	case '3':difficulty=180;		break;
	default:printf("\n ������� ������");  	Setup();				//�ݹ� 
	}
	printf("\n ���óɹ� ���ڱ���..."); 
	Sleep(1000);
	return; 
} 
void Move(struct location * p_play )							//��Ϸ�ƶ�
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	/* 

	hand_x			��������ֵĺ����� �ֵ�������̶���9	
	egg_x			������Ǽ����ĺ�����
	egg_y			������Ǽ�����������
	d_hand_x		��������ֱ���֮ǰ���ӻ���ٵ�ֵ	�������꣩	��hand_x	 + 	d_hand_x		=	�ֵľɺ����꡿
	d_egg_x		������Ǽ�������֮ǰ���ӻ���ٵ�ֵ �������꣩	��egg_x	 + 	d_egg_x		=	���ľɺ����꡿
	d_egg_y		������Ǽ�������֮ǰ���ӻ���ٵ�ֵ �������꣩	��egg_y	 +		d_egg_y	    =	���ľ������꡿
	egg_type		����������   1�ǰ�ɫ�������÷�+10����2�Ǻ�ɫ�������÷�+50������+1��

	gotoxy(9,2,1);
	*/ 
	
	if(  p_play->hand_x > 9 || p_play->hand_x < 0 || p_play->egg_x > 9 || p_play->egg_x < 0 || p_play->egg_y > 9 || p_play->egg_y < 0  ) 
		return ;				//����Ƿ���󣬴����������������
	
	SetConsoleTextAttribute(hConsole,FOREGROUND_GREEN|FOREGROUND_INTENSITY);
	if(	p_play->hand_x == p_play->egg_x && 9 == p_play->egg_y)         //���ֽӵ�����ʱ
	{ 
		if( p_play->egg_type == 1)				//���ֽӵ��׼���ʱ
			score+=10;			//�÷�+10
		else if (p_play->egg_type == 2)		 //���ֽӵ��ڼ���ʱ
		{
			score += 50;		 //�÷�+50
			life += 1;				//����+1
		}
		gotoxy(8,0,1);
		printf("%2d",score);
		gotoxy(32, 0, 1);
		printf("%2d", life);
	} 
	else if(p_play->egg_y == 9 && p_play->hand_x != p_play->egg_x)		//���ִ������ʱ
	{	
			life -= 1;
			printf("\7");
			gotoxy(32,0,1);
			printf("%2d",life);
	} 
	SetConsoleTextAttribute(hConsole, 128);
		/*�����*/
	gotoxy(9+ p_play->hand_x *2+ p_play->d_hand_x *2,2+9,1);
	printf(" ");
		/*�������*/
	gotoxy(9+ p_play->egg_x *2+ p_play->d_egg_x *2,2+ p_play->egg_y + p_play->d_egg_y,1);
	printf(" ");
		 /*������*/
	gotoxy(9+ p_play->egg_x *2,2+ p_play->egg_y,1);
	putchar(p_play->egg_type);
		/*����*/
	gotoxy(9+ p_play->hand_x *2,2+9,1);
	putchar(34);
	return;
}
void Show(void)													//��Ϸ����  
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
			"   &���� ����������& |\n"
		);	  
		SetConsoleTextAttribute(hConsole,FOREGROUND_RED|FOREGROUND_INTENSITY);
		gotoxy(22,14,1); 
		printf("|  ��ܰ��ʾ:");	
		gotoxy(22,15,1); 
		printf("|  �򼱿ɰ���");
		gotoxy(22,16,1);  
		printf("|  ��ǿ��Ƽ�");
		gotoxy(22, 17, 1);
		printf("|  ��ͣ. ");
	
	return;
}

/*
���ʱ�䣺2016.7.6�����İ棩���ռ��桿 

���� ������  
QQ 2783608988	C������Դ����Ⱥ 519536269
��ӭ��λ����������  ���˸м�����  

*/
