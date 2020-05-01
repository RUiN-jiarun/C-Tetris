#include "graphics.h"
#include "extgraph.h"
#include "genlib.h"
#include "simpio.h"
#include "conio.h"
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h> 
#include <winsock2.h>


#include <windows.h>
#include <olectl.h>
#include <mmsystem.h>
#include <wingdi.h>
#include <ole2.h>
#include <ocidl.h>
#include <winuser.h>

#include "imgui.h"
#include "Operate.h" 

// ״̬������ȫ��
extern int	STATE;


// ȫ�ֱ���
static double winwidth, winheight;   // ���ڳߴ�
static int    start = 0; // ��ʼ��ť�Ƿ����ж����� 
static int    help = 0; // ������ť�Ƿ����ж����� 
static int    login = 0; // ¼�밴ť�Ƿ����ж����� 
static int	  highscore = 0; // ���а�ť�Ƿ����ж����� 

extern int    play = 0;
extern int    pause = 0; 

// �û���Ϣ 
typedef struct inf{
	char name[20];
	int score;
	char score_string[20];
}info;

info rank[4];

// ��������
void DisplayClear(void); 
// ��ʱ����������
void startTimer(int id,int timeinterval);
// �û�����ʾ����
void display(void); 
// �˵������� 
void Menu();
// ������ģ��
void Title();
// �ı��༭ģ�� 
void Text();
// �û���Ϣ����ģ�� 
void inputrank(char* s);
// ���а���ʾģ�� 
void Rank();
 

// �û����ַ��¼���Ӧ����
extern void CharEventProcess(char ch)
{
	uiGetChar(ch); // GUI�ַ�����
	display(); //ˢ����ʾ
}

// �û��ļ����¼���Ӧ����
extern void KeyboardEventProcess(int key, int event)
{
	uiGetKeyboard(key,event); // GUI��ȡ����
	display(); // ˢ����ʾ
}

// �û�������¼���Ӧ����
extern void MouseEventProcess(int x, int y, int button, int event)
{
	uiGetMouse(x,y,button,event); //GUI��ȡ���
	display(); // ˢ����ʾ
}


// �û����������
void Main() 
{
	// ��ʼ�����ں�ͼ��ϵͳ
	SetWindowTitle("Tetris");
	
    InitGraphics();
    
    DefineColor("PURPLE",0.25,0.875,0.8);                
	DefineColor("myBLUE",0.01,0.2,0.8);        
    DefineColor("myRED",0.89,0.09,0.05);        
    DefineColor("nb",0.79,0.92,0.85);        
    DefineColor("darknb",0.69,0.80,0.73); 
	
	// ��ô��ڳߴ�
    winwidth = GetWindowWidth();
    winheight = GetWindowHeight();
    
    // ȷ����ˢ��С 
	SetPointSize(20);

	// ע��ʱ����Ӧ����
	registerMouseEvent(MouseEventProcess);      	// ���
	registerCharEvent(CharEventProcess); 			// �ַ�
	registerKeyboardEvent(KeyboardEventProcess);	// ����
	
	
}


// �˵������� 
void Menu()
{
	double fH = GetFontHeight();
	double h = fH*2;  
	double x = winwidth/8;  
	double y = winheight/2-h; 
	double w = winwidth/5; 

 
	Title(); 
	SetPointSize(20);
	if ( button(GenUIID(0), x, y, w, h, start ? "����" : "��ʼ��Ϸ") )
		start = ! start;
	
	if( button(GenUIID(0), x, y-2*h, w, h, "�˳�") )
		exit(-1);

	if( start ) {
		if( button(GenUIID(0), x + w*1.2, y, w, h, "���¼��") )
			login = ! login;
		if( button(GenUIID(0), x + w*1.2, y - 1*h*2, w, h, "����") )
			help = ! help; 

		if( button(GenUIID(0), x + w*1.2, y - 2*h*2, w, h, "���а�") )	 
			highscore = ! highscore;
 	}
	
	if( login )	
	{
		DisplayClear();
		Text();
	}

	if( help ) 
	{
		DisplayClear();
		SetPenColor("nb"); 
		SetPointSize(50);
		SetFont("Bradley Hand ITC");
		drawBox(2.5, 4, 4, 1, 1, "��   ��", "P", "myBlue");
		SetPointSize(20);
		drawLabel(x + w*0.5,  y, "������\t\t  ������\t\t  ����������");
		drawLabel(x + w*0.5,  y - h, "z����ʱ����ת  \t\tx��˳ʱ����ת  \t\tc���ݴ淽��");
		drawLabel(x + w*0.5,  y - 2 * h, "�س�������ʼ��Ϸ  \t\t�ո����ֱ�����  \t\t�˸�������ز˵� \t\tEsc����������Ϸ");
		if( button(GenUIID(0), x + w*2.4, y - 2*h*2, w, h, "����") ) 
		help = 0; 
	}
	 
	if( highscore )
	{
		DisplayClear();
		Rank();
		
	}
	
}


void display()
{
	// ����
	DisplayClear();
			
	// ���˵�
	Menu();
	
}

// ������ģ��
void Title()
{
	SetPenColor("nb"); 
	SetPointSize(100);
	SetFont("Bradley Hand ITC"); 
	drawBox(2, 4, 5, 1.8, 1, "T E T R I S", "P", "myBlue");
} 
 
// �ı��༭ģ�� 
void Text()
{
	static char name[80] = "player";

	static char results[200] = "";


	double fH = GetFontHeight();
	double h = fH*2; 			// �ؼ��߶�
	double w = winwidth/4;		// �ؼ����
	double x = winwidth/15;
	double y = winheight/2-h;

	double x1 = winwidth/8;  
 
	double w1 = winwidth/5;
	
	SetPenColor("nb"); 
	SetPointSize(100);
	SetFont("Bradley Hand ITC"); 
	drawBox(2, 4, 5, 1.8, 1, "T E T R I S", "P", "myBlue");

	SetPointSize(20);
	SetPenColor("Blue"); 
	drawLabel(x-fH/2-TextStringWidth("����"), (y-=h*1.2)+fH*0.7, "����");
	if( textbox(GenUIID(0), x, y, w, h, name, sizeof(name)) )
	{	
		sprintf(results,"�������: %s", name);

	}
	
	//SaveGraphicsState();
	if( button(GenUIID(0), x1 + w1*2.4, y - 2.5*h, w1, h, "����") ) 
		login = 0; 
	
	if( button(GenUIID(0), x1 + w1*2.4, y - 1*h, w1, h, "����")) 	// ������������Ϸ���� 
	{
		inputrank(name);
		play = 1;

	}
	
	if (play)
	{
		DisplayClear();
		//cancelMouseEvent();
		//cancelKeyboardEvent();
		//cancelCharEvent();
		//cancelTimerEvent();
		Game();
		
	}

	//SetPenColor("Red"); 
	//drawLabel(x, y-=fH*1.2, results);
	
	

}


// �û���Ϣ����ģ�� 
void inputrank(char* s){
	
	FILE *fp;
	
	if((fp=fopen("rank.txt","a"))==NULL)
	{
		printf("File open error!\n");
		exit(0);
	}
	
	// ����
	scanf("%s",s);
	fputs(s,fp);
	fputc(10,fp);
	
	if(fclose(fp)){
		printf("Can not close the file!\n");
		exit(0);
	}
}

// ���а���ʾģ�� 
void Rank()
{
	readrank();
	DrawChart(); 
	drawButtons(); 
}

// ������ģ�� 
void DrawChart(){
	SetPenColor("nb");
	MovePen(4.5,5.45);
	SetPointSize(55);
	SetFont("����");
	drawBox(2.75, 5.00 , 4 , 0.85 , 1 , "���а� ", 'P', "myBlue");//���а����
	
	SetPenSize(1);
	SetPointSize(30);
	SetPenColor("PURPLE");
	drawBox(2.75, 4.00 , 1 , 1 , 1 , "1", 'L', "myBlue");
	SetPenColor("nb");
	drawBox(2.75, 3.00 , 1 , 1 , 1 , "2", 'L', "myBlue");
	SetPenColor("PURPLE");
	drawBox(2.75, 2.00 , 1 , 1 , 1 , "3", 'L', "myBlue");
	
	SetPenColor("PURPLE");
	drawBox(3.75, 4.00 , 2 , 1 , 1 , rank[0].name, 'L', "myBlue");
	SetPenColor("nb");
	drawBox(3.75, 3.00 , 2 , 1 , 1 , rank[1].name, 'L', "myBlue");
	SetPenColor("PURPLE");
	drawBox(3.75, 2.00 , 2 , 1 , 1 , rank[2].name, 'L', "myBlue");
	
	SetPenColor("PURPLE");
	drawBox(5.75, 4.00 , 1 , 1 , 1 , rank[0].score_string, 'L', "myBlue");
	SetPenColor("nb");
	drawBox(5.75, 3.00 , 1 , 1 , 1 , rank[1].score_string, 'L', "myBlue");
	SetPenColor("PURPLE");
	drawBox(5.75, 2.00 , 1 , 1 , 1 , rank[2].score_string, 'L', "myBlue");
	
	SetPenColor("nb");
	drawRectangle(2.75, 0.8, 4 , 1.2, 1);
}

// ���а���淵�ذ�ť
void drawButtons()
{
	// ��ô��ڳߴ�
    winwidth = GetWindowWidth();
    winheight = GetWindowHeight();
    SetPointSize(20);
    SetStyle(0);
	if( button(GenUIID(0), 4.05, 1.1, 1.35, 0.4, "����") )
	{
		DisplayClear();
		highscore = 0;

		Menu();
	}
}

// �û����ݶ�ȡģ�� 
void readrank(){
	FILE *fp;
	int i=0, j=0, k=0;
	info tmp;
	fp=fopen("rank.txt","r");
	while(!feof(fp)){
		fscanf(fp,"%s %d",rank[i].name, &rank[i].score);
		itoa(rank[i].score,rank[i].score_string,10);   		//10����ʮ���� 
		if(i==2){
			for(k=0;k<3;k++){
				for(j=k+1;j<3;j++){
					if(rank[k].score<rank[j].score){
						tmp=rank[k];
						rank[k]=rank[j];
						rank[j]=tmp;
					}
				}
			}
		}
		if(i==3){
			if(rank[3].score>=rank[0].score){
				rank[2]=rank[1];
				rank[1]=rank[0];
				rank[0]=rank[3];
			}
			else if(rank[3].score<rank[0].score&&rank[3].score>rank[1].score){
				rank[2]=rank[1];
				rank[1]=rank[3];
			}
			else if(rank[3].score<rank[1].score&&rank[3].score>rank[2].score){
				rank[2]=rank[3];
			}
			i--;
		}
		i++;
	}
}

