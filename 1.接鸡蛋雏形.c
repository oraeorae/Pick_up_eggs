/*                      ͷ�ļ�                        */
#include <windows.h>
#include <stdlib.h>
#include <conio.h>
#include <stdio.h>
#include <time.h>
int score,life,difficulty,f_speed;  //ȫ�ֱ��������÷֣��������Ѷȣ��ٶ� 
/*                    ��������                        */
int Show(int hand_x,int hand_y,int face_x,int face_y);    
void Set_up_the(void); 
void Title_turn(void);    
                           
int main()
{
	const int h_Y = 9;      
	int h_x = 5 , f_y = 0 , f_x , check;
	int speed = 0 ;
	srand((unsigned)time(NULL));  // ��������� -- �������һ��Ҫ����ѭ�����������ѭ�����õ����棬����Ļ��õ�������ͬ�����֡�
	f_x  = (int)(10.0 *rand()/(RAND_MAX+1.0)); //	f_x = rand()%10;   �����������ȡ��
	Title_turn();
	Show(h_x,h_Y,f_x,f_y);       //��ʾ��Ϸ���� 
	while(1) 		//��ֹ��Ϸִ��һ�� 
		{
	if(kbhit())  // ��鵱ǰ�Ƿ��м������룬�����򷵻�һ����0ֵ�����򷵻�0
	switch(getch())
	{ 
	case 'a' : case 'A' :if( h_x > 9 ) h_x = 9;		Show(--h_x,h_Y,f_x,f_y);	/*	break;*/continue;
	case 'd' : case 'D' :if( h_x < 0 ) h_x = 0;   	Show(++h_x,h_Y,f_x,f_y);/*		break;*/continue;
	case  27 : Set_up_the(); break;
	}
	if(++speed%f_speed==0)//���������л����ٶ�
speed=0;srand(time(NULL));

}

		if( check == 1 )
	{
	f_x = (int)(10.0*rand()/(RAND_MAX+1.0));	//	f_x = rand()%10;   �����������ȡ��
	f_y = 0;
	Show(h_x,h_Y,f_x,f_y); 
	}
		


    return 0;
}

int Show(int hand_x,int hand_y,int face_x,int face_y)  //���庯�� 
{
	
	system("cls");  //���� 
	if( hand_x < 0 ) hand_x = 0;
	else if( hand_x > 9 ) hand_x = 9;	
	char a[10][10]={0};
	a[hand_x][hand_y] = 34;
	a[face_x][face_y] = 1 ;
	printf("_ _ _ _ _ �� _ _ _ _ _\n");
		for( hand_y = 0 ; hand_y < 10 ; hand_y++ )
		{
			printf("|");
			for( hand_x = 0 ; hand_x < 10 ; hand_x++ )
				printf("%c ",a[hand_x][hand_y]);
			if( hand_x == face_x &&	hand_x - face_x == 1 )score+=10	;
		
			printf("|");
			if( hand_y == 1 ) printf("	�÷� :%2d",score); 
			if( hand_y == 2 ) printf("	���� :%2d",life); 
			if( hand_y == 3 ) printf("����Esc���������ò˵�"); 
			printf("\n");
		}
	printf("- - - - - �� - - - - -\n");	
	if( face_y > 9 ) return 1; 
	if( face_y >= 0 && face_y <= 9 ) return 0; 
	
}
void Set_up_the(void)
{
	system("cls");//���� 
	while(1)
	{
	printf("\n ��Ϸ���Ѷȣ�1.��2.����3.����>> ");
	switch(getch())
	{	
	case '1':difficulty=1;	printf("���óɹ� ���ڱ���..."); 	Sleep(1000);	break;
	case '2':difficulty=2;	printf("���óɹ� ���ڱ���..."); 	Sleep(1000);	break;
	case '3':difficulty=3;	printf("���óɹ� ���ڱ���..."); 	Sleep(1000);	break;
	default:printf("\n ����������ѡ��...\n");

	}
	return;
	}
}

void Title_turn(void)
{
	system("title A.T.S.F  1.0    ��������������");
	printf("------����ָ��------\n"
   	    	"��A����D���ƶ���Ц��\n" 
   	    	"��Esc���������ý���\n"
   	    	"---���κμ�����---\n"  
			   );		
	if( getch() == 27 )Set_up_the();  //27����ASCII���еġ�Esc�� 
	return;
}
