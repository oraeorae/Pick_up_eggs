/*		ͷ�ļ�		*/
# include <windows.h>
# include <stdlib.h>
# include <stdio.h>
# include <conio.h>
# include <time.h>
#include <time.h>
int score,life = 5,difficulty = 500 ;  //ȫ�ֱ��������÷֣��������Ѷ� 

void Show(int hand_x,int hand_y,int face_x,int face_y);		//��ʾ��Ϸ����  
void Setup(void);	//����

int main(void)
{
	    
    system("mode con: cols=60 lines=20");		//���ô��ڴ�С
    system("title �Ӽ���   ����C��������");		//�ı䴰�ڱ��� 
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	const int h_Y = 9;
	int h_x = 5 , f_y = 0 , f_x /* first_time,second_time*/;
	long first_time,second_time;
	srand((unsigned)time(NULL));  // ���������

	f_x  = (int)(10.0 *rand()/(RAND_MAX+1.0)); //	f_x = rand()%10;   �����������ȡ��
	Show(h_x,h_Y,f_x,f_y);       //��ʾ��Ϸ���� 
	printf(
	"\n\n		������������ָ�ϡ�������\n"
   	    "		����A����D���ƶ���Ц����\n" 
   	    "		����Esc���������ý��� �� \n"
		"		��      ���κμ���ʼ  ��\n"
		"		������������������������\n"
		);
	getch(); 

		first_time = GetTickCount();/* time(NULL);*/
	while(1)
	{
		if(kbhit())		// ��鵱ǰ�Ƿ��м������룬�����򷵻�һ����0ֵ�����򷵻�0
		switch(getch())	{
			case 'a' : case 'A' :	if( h_x < 0 ) h_x = 1;	    Show(--h_x,h_Y,f_x,f_y); 		break;
			case 'd' : case 'D' : 	if( h_x > 9 ) h_x = 8; 		Show(++h_x,h_Y,f_x,f_y);		break;
			case  27 : Setup();		system("cls");		first_time =  GetTickCount();	 Show(h_x,h_Y,f_x,f_y); 	 break;	 //27����ASCII���еġ�Esc�� 
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
		" ����������������������������������������������������������\n"
		" ��	   		GAME OVER��			 ��\n"
		" ����������������������������������������������������������\n"
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
	system("cls");	//����
	SetConsoleTextAttribute(hConsole,FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_INTENSITY); 
	printf("		������������������������ \n");	
		for( hand_y = 0 ; hand_y < 10 ; hand_y++ )
		{	 
			SetConsoleTextAttribute(hConsole,FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_INTENSITY); 
			printf("		��");
			SetConsoleTextAttribute(hConsole, 128 );
			for( hand_x = 0 ; hand_x < 10 ; hand_x++ )
			printf("%c ",a[hand_x][hand_y]);
			SetConsoleTextAttribute(hConsole,FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_INTENSITY); 
			printf("��");
			SetConsoleTextAttribute(hConsole,FOREGROUND_BLUE|FOREGROUND_GREEN|FOREGROUND_INTENSITY); 
			if( hand_y == 1 ) printf("	�÷� :%2d",score); 
			if( hand_y == 2 ) printf("	���� :%2d",life); 	
			printf("\n");
		}
			
		 SetConsoleTextAttribute(hConsole,FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_INTENSITY); 
		printf("		������������������������ \n");	
	  SetConsoleTextAttribute(hConsole,FOREGROUND_BLUE|FOREGROUND_GREEN|FOREGROUND_INTENSITY);
	return;
}
void Setup(void)
{
	printf("\n ��Ϸ���Ѷȣ�1.��2.����3.����>> ");
	switch(getche())
	{	
	case '1':difficulty=500;	printf("\n ���óɹ� ���ڱ���..."); 	Sleep(1000);	break;
	case '2':difficulty=300;	printf("\n ���óɹ� ���ڱ���..."); 	Sleep(1000);	break;
	case '3':difficulty=200;	printf("\n ���óɹ� ���ڱ���..."); 	Sleep(1000);	break;
	default:printf("\n ������� ������");  	Setup();	//�ݹ� 
	}
	return; 

} 




/*
���ʱ�䣺2016.6.3����һ�棩 

ȱ���ܽ᣺

 1.��Ȼ�ÿ���̨api����ͼ��ֱ����api���ù��λ���ػ�
 ��Ҫֱ������  ����˸
 ��goto_xy������ 
 
 2. ��������� û��Ҫ�ø�����
 �������� ����Ȼ������Ӱ�첻��
 �� 24��  47�� �� 
 
 3.�û��л��� ��Ҫ����һ��
 �� 46�� �� 
 
 4.���� ֻ�б�����ֵ�Ĳ����ǲ�ͬ��
 ����switch�����޸ı����Ϳ�����
 ����2��д��switch����
 �� 100�� �� 102�� �� 

 5.������� �� 40�� .41�С�

*/
