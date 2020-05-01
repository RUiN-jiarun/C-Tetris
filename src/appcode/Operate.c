#include "graphics.h"         
#include <extgraph.h>        
#include <genlib.h>        
#include <simpio.h>        
#include <random.h>        
#include <strlib.h>        
#include <conio.h>        
#include <stdio.h>        
#include <stdlib.h>        
#include <stddef.h>        
#include <windows.h>        
#include <olectl.h>        
#include <stdio.h>        
#include <mmsystem.h>        
#include <wingdi.h>        
#include <ole2.h>        
#include <ocidl.h>        
#include <winuser.h>        
#include <math.h>        
#include "imgui.h"        
           
#define blocksize 0.25         
#define mapx 1.5        
#define mapy 0.6        
#define height 24        
#define width 14        
#define nextstartx 6        
#define nextstarty 5.1        
#define startx 3.25        
#define starty 0.6        
#define timer1 1    	/* �����ʱ�� */    
#define timer2 2        /* ��Ϸ�������� */ 
#define timer3 3        /* ���� */ 
            
int mode[28][5][5]={        
   //1        
   //I        
   {        
   0,0,0,0,0,        
   0,0,0,0,0,        
   0,1,1,1,1,        
   0,2,2,2,2,        
   0,2,2,2,2},        
   //J        
   {        
   0,0,0,0,0,        
   0,1,0,0,0,        
   0,1,1,1,0,        
   0,2,2,2,0,        
   0,2,2,2,0},        
   //L        
   {        
   0,0,0,0,0,        
   0,0,0,1,0,        
   0,1,1,1,0,        
   0,2,2,2,0,        
   0,2,2,2,0},        
   //O        
   {        
   0,0,0,0,0,        
   0,0,1,1,0,        
   0,0,1,1,0,        
   0,0,2,2,0,        
   0,0,2,2,0},        
   //S        
   {        
   0,0,0,0,0,        
   0,0,1,1,0,        
   0,1,1,2,0,        
   0,2,2,2,0,        
   0,2,2,2,0},        
   //T        
   {        
   0,0,0,0,0,        
   0,0,1,0,0,        
   0,1,1,1,0,        
   0,2,2,2,0,        
   0,2,2,2,0},        
   //Z        
   {        
   0,0,0,0,0,        
   0,1,1,0,0,        
   0,2,1,1,0,        
   0,2,2,2,0,        
   0,2,2,2,0},        
   //2        
   //I        
   {        
   0,0,0,0,0,        
   0,0,1,0,0,        
   0,0,1,0,0,        
   0,0,1,0,0,        
   0,0,1,0,0},        
   //J        
   {        
   0,0,0,0,0,        
   0,0,1,1,0,        
   0,0,1,2,0,        
   0,0,1,2,0,        
   0,0,2,2,0},        
   //L        
   {        
   0,0,0,0,0,        
   0,0,1,0,0,        
   0,0,1,0,0,        
   0,0,1,1,0,        
   0,0,2,2,0},        
   //O        
   {        
   0,0,0,0,0,        
   0,0,0,0,0,        
   0,0,1,1,0,        
   0,0,1,1,0,        
   0,0,2,2,0},        
   //S        
   {        
   0,0,0,0,0,        
   0,0,1,0,0,        
   0,0,1,1,0,        
   0,0,2,1,0,        
   0,0,2,2,0},        
   //T        
   {        
   0,0,0,0,0,        
   0,0,1,0,0,        
   0,0,1,1,0,        
   0,0,1,2,0,        
   0,0,2,2,0},        
   //Z        
   {        
   0,0,0,0,0,        
   0,0,0,1,0,        
   0,0,1,1,0,        
   0,0,1,2,0,        
   0,0,2,2,0},        
   //3        
   //I        
   {        
   0,0,0,0,0,        
   0,0,0,0,0,        
   1,1,1,1,0,        
   2,2,2,2,0,        
   2,2,2,2,0},        
   //J        
   {        
   0,0,0,0,0,        
   0,0,0,0,0,        
   0,1,1,1,0,        
   0,2,2,1,0,        
   0,2,2,2,0},        
   //L        
   {        
   0,0,0,0,0,        
   0,0,0,0,0,        
   0,1,1,1,0,        
   0,1,2,2,0,        
   0,2,2,2,0},        
   //O        
   {        
   0,0,0,0,0,        
   0,0,0,0,0,        
   0,1,1,0,0,        
   0,1,1,0,0,        
   0,2,2,0,0},        
   //S        
   {        
   0,0,0,0,0,        
   0,0,0,0,0,        
   0,0,1,1,0,        
   0,1,1,2,0,        
   0,2,2,2,0},        
   //T        
   {        
   0,0,0,0,0,        
   0,0,0,0,0,        
   0,1,1,1,0,        
   0,2,1,2,0,        
   0,2,2,2,0},        
   //Z        
   {        
   0,0,0,0,0,        
   0,0,0,0,0,        
   0,1,1,0,0,        
   0,2,1,1,0,        
   0,2,2,2,0},        
   //4        
   //I        
   {        
   0,0,1,0,0,        
   0,0,1,0,0,        
   0,0,1,0,0,        
   0,0,1,0,0,        
   0,0,2,0,0},        
   //J        
   {        
   0,0,0,0,0,        
   0,0,1,0,0,        
   0,0,1,0,0,        
   0,1,1,0,0,        
   0,2,2,0,0},        
   //L        
   {        
   0,0,0,0,0,        
   0,1,1,0,0,        
   0,2,1,0,0,        
   0,2,1,0,0,        
   0,2,2,0,0},        
   //O        
   {        
   0,0,0,0,0,        
   0,1,1,0,0,        
   0,1,1,0,0,        
   0,2,2,0,0,        
   0,2,2,0,0},        
   //S        
   {        
   0,0,0,0,0,        
   0,1,0,0,0,        
   0,1,1,0,0,        
   0,2,1,0,0,        
   0,2,2,0,0},        
   //T        
   {        
   0,0,0,0,0,        
   0,0,1,0,0,        
   0,1,1,0,0,        
   0,2,1,0,0,        
   0,2,2,0,0},        
   //��Z        
   {        
   0,0,0,0,0,        
   0,0,1,0,0,        
   0,1,1,0,0,        
   0,1,2,0,0,        
   0,2,2,0,0}        
};        
   
int game[height+5][width+4]={        
   0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,        
   0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,        
   0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,        
   0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,        
   0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,        
   0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,        
   0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,        
   0,0,0,0,0,1,1,1,0,0,1,1,1,0,0,0,0,0,        
   0,0,0,0,1,0,0,0,0,1,0,0,0,1,0,0,0,0,        
   0,0,0,0,1,0,1,1,0,1,0,0,0,1,0,0,0,0,        
   0,0,0,0,1,0,0,1,0,1,1,1,1,1,0,0,0,0,        
   0,0,0,0,0,1,1,1,0,1,0,0,0,1,0,0,0,0,        
   0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,        
   0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,        
   0,0,0,0,0,1,0,1,0,0,1,1,1,1,0,0,0,0,        
   0,0,0,0,1,0,1,0,1,0,1,0,0,0,0,0,0,0,        
   0,0,0,0,1,0,1,0,1,0,1,1,1,0,0,0,0,0,        
   0,0,0,0,1,0,1,0,1,0,1,0,0,0,0,0,0,0,        
   0,0,0,0,1,0,0,0,1,0,1,1,1,1,0,0,0,0,        
   0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,        
   0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,        
   0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,        
   0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,        
   0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,        
   0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,        
   0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,        
   0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,        
   0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,        
   0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0        
};        
int over[height+5][width+4]={        
   0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,        
   0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,        
   0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,        
   0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,        
   0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,        
   0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,        
   0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,        
   0,0,0,0,0,1,1,0,0,1,0,0,0,1,0,0,0,0,        
   0,0,0,0,1,0,0,1,0,1,0,0,0,1,0,0,0,0,        
   0,0,0,0,1,0,0,1,0,1,0,0,0,1,0,0,0,0,        
   0,0,0,0,1,0,0,1,0,0,1,0,1,0,0,0,0,0,        
   0,0,0,0,0,1,1,0,0,0,0,1,0,0,0,0,0,0,        
   0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,        
   0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,        
   0,0,0,0,1,1,1,1,0,1,1,1,1,0,0,0,0,0,        
   0,0,0,0,1,0,0,0,0,1,0,0,1,0,0,0,0,0,        
   0,0,0,0,1,1,1,0,0,1,1,1,0,0,0,0,0,0,        
   0,0,0,0,1,0,0,0,0,1,0,1,0,0,0,0,0,0,        
   0,0,0,0,1,1,1,1,0,1,0,0,1,1,0,0,0,0,        
   0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,        
   0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,        
   0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,        
   0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,        
   0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,        
   0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,        
   0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,        
   0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,        
   0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,        
   0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0        
};        
       
long score=0;        	/* �����ݻ��÷� */ 
long linescore=0;       /* ���������÷� */ 
long sumscore=0;        /*�ܷ�*/ 
char charscore[12]={0};      /* �����ַ��� */ 
char charlinescore[12]={0};      
int theworld=0;        /* ʱͣ */ 
	
int first=1;        /* �ж��ǲ��ǵ�һ�� */
int end=0; 
int kick=0;         /* �Ƿ��С���ǽ�� */ 
int keyy=1;       	/* ���� */ 

int play; 
int pause;


void CharEventProcess(char ch);
void KeyboardEventProcess(int key, int event);
void MouseEventProcess(int x, int y, int button, int event);

typedef struct{        
      int x;         
      int y;        
      int type;        /* ��̬���� */ 
      int Dir;         /* ������� */ 
      char* color;        
      int store;       /* �Ƿ��ݴ� */ 
}BLOCK_TYPE;        
       
BLOCK_TYPE curblock={0};        /* ��ǰ���� */ 
BLOCK_TYPE nextblock={0};       /* ��һ������ */ 
BLOCK_TYPE tempblock={nextstartx,nextstarty-4,-1,0,0,0};   	/* �ݴ淽�� */ 
BLOCK_TYPE imagblock={0};    	/* ���񷽿� */ 
       
char*  BlockColor[7]={        
    "myRED",        
    "myBLUE",        
    "myYELLOW",        
    "myGREEN",        
    "ORANGE",        
    "PURPLE",        
    "Cyan"        
};        
       
typedef struct{        
   int a;        	/* �Ƿ���� */ 
   char* color;        
}cc;        

/* map reflect������ͼ�� */       
cc map[height+5][width+4]={0};        /* ����Ϸ�� */ 
cc mapcopy[height+5][width+4]={0};    /* �����洢��Ϸ��״̬ */ 
cc reflect[height+5][width+4]={0};    /* ���ӵ�������ʾ�������Ϸ�� */ 
   
void TEP(int timerID);			/* ��ʱ����Ϣ�ص����� */        
void KEP(int key,int event);	/* ������Ϣ�ص����� */        
void CEP(char c);				/* �ַ���Ϣ�ص����� */
//void MEP(int x, int y, int button, int event);   

int count(void);        		
void erasefakeblock(BLOCK_TYPE a);  
void MapCopy(void);  
void MapReflect(void);  
void MapFakeCopy(void);   
int spin(BLOCK_TYPE a);  
void inputscore(long score, long linescore);      

/* �����������������ж���ײ */  
int count(void)
{        
	int i,j;        
	int cot=0;        
	for(i=2;i<=28;i++){        
	   for(j=2;j<=15;j++){        
	       if(map[i][j].a==1){        
	           cot++;        
	       }        
	   }        
	}        
	return cot;        
}  

/* �����������������ж�reflectͼ�����Ƿ���ײ */ 
int fakecount(void)
{        
	int i,j;        
	int cot=0;        
	for(i=2;i<=28;i++){        
	   for(j=2;j<=15;j++){        
	       if(reflect[i][j].a==1){        
	           cot++;        
	       }        
	   }        
	}        
	return cot;        
}           

/* ������ʾ���� */         
void scoreoutput(void)
{      
	SetPenColor("Dark Gray");      
	StartFilledRegion(1);        
	MovePen(nextstartx-0.05,nextstarty-1.75);        
	DrawLine(GetFontHeight()*24*0.66,0);        
	DrawLine(0,0.4);        
	DrawLine(-(GetFontHeight()*24*0.66),0);        
	DrawLine(0,-0.4);        
	EndFilledRegion();        
	
	itoa(score,charscore,10);      
	itoa(linescore,charlinescore,10);      
	
	SetPointSize(20);      
	SetPenColor("myYELLOW"); 
     
	MovePen(nextstartx,nextstarty-1.5);      
	DrawTextString("SCORE: ");      
	DrawTextString(charscore);      
	MovePen(nextstartx,nextstarty-1.7);      
	DrawTextString("LINE SCORE: ");      
	DrawTextString(charlinescore);      
}      
       
/* ��Ϸ�ػ��ƺ��� */ 
void frame(char* s){        
   int i;        
   SetPenColor("nb");//����         
   StartFilledRegion(1);        
   MovePen(mapx-0.04,mapy-0.04);        
   DrawLine(blocksize*width+0.08,0);        
   DrawLine(0,blocksize*height+0.08);        
   DrawLine(-(blocksize*width+0.08),0);        
   DrawLine(0,-(blocksize*height+0.08));        
   EndFilledRegion();        
   SetPenColor(s);        
   MovePen(mapx-0.04,mapy-0.04);        
   DrawLine(blocksize*width+0.08,0);        
   DrawLine(0,blocksize*height+0.08);        
   DrawLine(-(blocksize*width+0.08),0);        
   DrawLine(0,-(blocksize*height+0.08));        
   MovePen(mapx,mapy);        
   DrawLine(blocksize*width,0);        
   DrawLine(0,blocksize*height);        
   DrawLine(-(blocksize*width),0);        
   DrawLine(0,-(blocksize*height));        
   for(i=1;i<width;i++)
   {        
       MovePen(mapx+i*blocksize,mapy);        
       DrawLine(0,height*blocksize);        
   }        
    for(i=1;i<height;i++)
   {        
       MovePen(mapx,mapy+i*blocksize);
	   DrawLine(width*blocksize,0);        
   }      
    /*drawLabel(5, 4,  "������");
    drawLabel(5, 3.5, "������");
    drawLabel(5, 3,  "������");
    drawLabel(5, 2.5, "z����ʱ����ת");
    drawLabel(5, 2, "x��˳ʱ����ת");
	drawLabel(5, 1.5, "c���ݴ淽��");
	drawLabel(5, 1, "�س�������ʼ��Ϸ  \t\t�ո����ֱ�����  \t\t�˸�������ز˵�");*/
    scoreoutput();      
}        

/* ������ƺ��� */       
void drawblock(int x,int y,char* color)        
{        
   SetPenColor(color);        
   MovePen(mapx+blocksize*(x-1),mapy+blocksize*(y-1));        
   DrawLine(blocksize,0);        
   DrawLine(0,blocksize);        
   DrawLine(-blocksize,0);        
   DrawLine(0,-blocksize);        
   StartFilledRegion(1);        
   MovePen(mapx+blocksize*(x-1)+0.04,mapy+blocksize*(y-1)+0.04);        
   DrawLine(0.17,0);        
   DrawLine(0,0.17);        
   DrawLine(-0.17,0);        
   DrawLine(0,-0.17);        
   EndFilledRegion();         
}    

/* �ײ�����������ƺ��� */ 
void drawfakeblock(int x,int y,char* color)        
{        
   SetPenColor("darknb");        
   MovePen(mapx+blocksize*(x-1),mapy+blocksize*(y-1));        
   DrawLine(blocksize,0);        
   DrawLine(0,blocksize);        
   DrawLine(-blocksize,0);        
   DrawLine(0,-blocksize);        
   StartFilledRegion(1);        
   MovePen(mapx+blocksize*(x-1)+0.04,mapy+blocksize*(y-1)+0.04);        
   DrawLine(0.17,0);        
   DrawLine(0,0.17);        
   DrawLine(-0.17,0);        
   DrawLine(0,-0.17);        
   EndFilledRegion();    

}        
       
/* ��һ��������ʾ���� */ 
void printnext(BLOCK_TYPE a){        
   int i,j;        
   for(i=0;i<5;i++){        
       for(j=0;j<5;j++){        
           if(mode[((a.Dir)*7+a.type)][i][j]==1){                      
               SetPenColor(a.color);        
               MovePen(nextstartx+j*blocksize,nextstarty+(4-i)*blocksize);        
               DrawLine(blocksize,0);        
               DrawLine(0,blocksize);        
               DrawLine(-blocksize,0);        
               DrawLine(0,-blocksize);        
               StartFilledRegion(1);        
               MovePen(nextstartx+j*blocksize+0.04,nextstarty+(4-i)*blocksize+0.04);        
               DrawLine(0.17,0);        
               DrawLine(0,0.17);        
               DrawLine(-0.17,0);        
               DrawLine(0,-0.17);        
               EndFilledRegion();         
           }        
       }        
   }        
}        

/* ������һ���������ʾ */ 
void erasenext(BLOCK_TYPE a){        
   int i,j;        
   for(i=0;i<5;i++){        
       for(j=0;j<5;j++){        
               SetPenColor("Dark Gray");        
               MovePen(nextstartx+j*blocksize,nextstarty+(4-i)*blocksize);        
               DrawLine(blocksize,0);        
               DrawLine(0,blocksize);        
               DrawLine(-blocksize,0);        
               DrawLine(0,-blocksize);        
               StartFilledRegion(1);        
               MovePen(nextstartx+j*blocksize+0.04,nextstarty+(4-i)*blocksize+0.04);        
               DrawLine(0.17,0);        
               DrawLine(0,0.17);        
               DrawLine(-0.17,0);        
               DrawLine(0,-0.17);        
               EndFilledRegion();              
       }        
   }        
}        

/* �ݴ淽����ʾ���� */    
void printtemp(BLOCK_TYPE a){        
   int i,j;        
   for(i=0;i<5;i++){        
       for(j=0;j<5;j++){        
           if(mode[((a.Dir)*7+a.type)][i][j]==1){                      
               SetPenColor(a.color);        
               MovePen(nextstartx+j*blocksize,(nextstarty-4)+(4-i)*blocksize);        
               DrawLine(blocksize,0);        
               DrawLine(0,blocksize);        
               DrawLine(-blocksize,0);        
               DrawLine(0,-blocksize);        
               StartFilledRegion(1);        
               MovePen(nextstartx+j*blocksize+0.04,(nextstarty-4)+(4-i)*blocksize+0.04);        
               DrawLine(0.17,0);        
               DrawLine(0,0.17);        
               DrawLine(-0.17,0);        
               DrawLine(0,-0.17);        
               EndFilledRegion();         
           }        
       }        
   }        
}        

/* �����ݴ淽�����ʾ */
void erasetemp(BLOCK_TYPE a){        
   int i,j;        
   for(i=0;i<5;i++){        
       for(j=0;j<5;j++){        
               SetPenColor("Dark Gray");        
               MovePen(nextstartx+j*blocksize,(nextstarty-4)+(4-i)*blocksize);        
               DrawLine(blocksize,0);        
               DrawLine(0,blocksize);        
               DrawLine(-blocksize,0);        
               DrawLine(0,-blocksize);        
               StartFilledRegion(1);        
               MovePen(nextstartx+j*blocksize+0.04,(nextstarty-4)+(4-i)*blocksize+0.04);        
               DrawLine(0.17,0);        
               DrawLine(0,0.17);        
               DrawLine(-0.17,0);        
               DrawLine(0,-0.17);        
               EndFilledRegion();              
       }        
   }        
}        

/* ��ǰ�����������Ϸ�� */ 
void addblock(BLOCK_TYPE a){        
   int i,j;        
   for(i=0;i<5;i++){        
       for(j=0;j<5;j++){        
           if(mode[((a.Dir)*7+a.type)][i][j]==1){        
               map[a.y+(4-i)+1][a.x+j+1].a=1;        
               map[a.y+(4-i)+1][a.x+j+1].color=a.color;        
           }        
                 
       }        
   }        
}        

/* ��ǰ�����������������Ϸ�� */ 
void addfakeblock(BLOCK_TYPE a){        
   int i,j;        
   for(i=0;i<5;i++){        
       for(j=0;j<5;j++){        
           if(mode[((a.Dir)*7+a.type)][i][j]==1){        
               reflect[a.y+(4-i)+1][a.x+j+1].a=1;        
               reflect[a.y+(4-i)+1][a.x+j+1].color=a.color;        
           }        
                 
       }        
   }        
}        

/* �����жϺ��� */ 
void fake(void){  
	int num1,num2;		/* num1��ӳ����ǰ���ϱ���䷽�������num2��ӳ������ */ 
	int flag=1;    		/* �Ƿ���Ҫ�ж���ײ��1���жϣ��ж���ϸ÷����Ϊ0 */ 
	int i,j;        
	   
	MapCopy(); 			/* ����mapͼ�� */ 
	MapReflect();  		/* ��ʾ��reflectͼ���� */ 
	//erasefakeblock(imagblock);  
	erasefakeblock(curblock);  
	imagblock=curblock;    /* ���񷽿�ȡ����ǰ���� */ 
	for(j=1;j<imagblock.y;j++)
	{        
        if(reflect[imagblock.y-j+1][imagblock.x+1].a==1 || reflect[imagblock.y-j+1][imagblock.x+2].a==1 || reflect[imagblock.y-j+1][imagblock.x+3].a==1 || reflect[imagblock.y-j+1][imagblock.x+4].a==1 || reflect[imagblock.y-j+1][imagblock.x+5].a==1)        
         {        
             j--;        
             break;        
         }        
    }        			/* ���ѭ�������жϷ�������ĸ߶ȣ���������ж���������λ�õ��ٶ� */ 
        j--;        
        imagblock.y-=j;        
        addfakeblock(imagblock);        
        
		while(flag){ 			/* �ж��Ƿ���ײ */       
           num1=fakecount();        
           MapFakeCopy();       /* �浵 */ 
           erasefakeblock(imagblock);        
           imagblock.y--;        
           addfakeblock(imagblock);        
           num2=fakecount();        
           if(num1!=num2){        
               imagblock.y++;        
               MapReflect();        /* ����ײ����ص� */ 
               addfakeblock(imagblock);        
               flag=0;        
           }        
     }        
}  

/* �����Ϸ�� */    
void printmap(void){        
   int i,j;        
   fake();  
   frame("BLACK");
   if(!end){
	   	for(i=24;i>=1;i--){        
	       for(j=1;j<=14;j++){        
	           if(reflect[i+1][j+1].a==1){        
	               drawfakeblock(j,i,imagblock.color);        
	           }        
	       }        
	   }  
          

	for(i=24;i>=1;i--){        
       for(j=1;j<=14;j++){        
           if(map[i+1][j+1].a==1){        
               drawblock(j,i,map[i+1][j+1].color);        
           }        
       }        
   }  
   }                         
}        

/* �ѷ������Ϸ�����Ƴ� */           
void eraseblock(BLOCK_TYPE a){        
   int i,j;        
   for(i=0;i<5;i++){        
       for(j=0;j<5;j++){        
           if(mode[a.Dir*7+a.type][i][j]==1){        
               map[a.y+(4-i)+1][a.x+j+1].a=0;        
               map[a.y+(4-i)+1][a.x+j+1].color="nb";        
           }      
   
       }        
   }        
       
}      

/* �������񷽿� */ 
void erasefakeblock(BLOCK_TYPE a){        
       int i,j;        
       for(i=0;i<5;i++){        
           for(j=0;j<5;j++){        
               if(mode[a.Dir*7+a.type][i][j]==1){        
                   reflect[a.y+(4-i)+1][a.x+j+1].a=0;        
                   reflect[a.y+(4-i)+1][a.x+j+1].color="nb";        
               }      
       
           }        
       }        
           
   }         

/* ������ͼ�������� */           
void erasemap(void){        
   int i,j;        
   for(i=1;i<=24;i++){        
       for(j=1;j<=14;j++){        
           drawblock(j,i,"nb");        
       }        
   }        
           
   frame("BLACK");        
}        
       
int rounds=0;    		/* �� */    
int typeran[7]={0};       /* ����� */ 
int cir=1;          

/* ������������� */ 
void createblockgroup(void){        
   Randomize();        
   int i,w,t;        
   nextblock.x=(nextstartx-mapx)/blocksize;        
   nextblock.y=(nextstarty-mapy)/blocksize;        
   if(rounds==6||cir==1){        
       for(i=0;i<7;i++){        
           typeran[i]=i;        
       }        
       for(i=0;i<7;i++){        
           w=RandomInteger(0,6);        
           t=typeran[i];        
           typeran[i]=typeran[w];        
           typeran[w]=t;        
       }        
       rounds=0;        
       cir++;        
    }        
    nextblock.type=typeran[rounds++];       
	nextblock.store=0;     
    nextblock.Dir=0;        
    switch(nextblock.type){        
       case 0:nextblock.color=BlockColor[5];break;        
       case 1:nextblock.color=BlockColor[6];break;        
       case 2:nextblock.color=BlockColor[2];break;        
       case 3:nextblock.color=BlockColor[4];break;        
       case 4:nextblock.color=BlockColor[0];break;        
       case 5:nextblock.color=BlockColor[1];break;        
       case 6:nextblock.color=BlockColor[3];break;        
       default:break;         
   }        
}        

/* ��Ϸ��� */           
void Game(){        
   //InitGraphics();        
   Randomize();        
   int i=0;        

   cancelMouseEvent();
   cancelCharEvent();
   cancelKeyboardEvent(); 
     
   registerTimerEvent(TEP);        
   registerKeyboardEvent(KEP);     
   registerCharEvent(CEP); 
   //registerMouseEvent(MEP);
   
   DefineColor("PURPLE",0.541,0.169,0.886);        
   DefineColor("myYELLOW",1,0.84,0);        
   DefineColor("myGREEN",0.42,0.56,0.14);        
   DefineColor("ORANGE",1,0.49,0.25);        
   DefineColor("myBLUE",0.01,0.2,0.8);        
   DefineColor("myRED",0.89,0.09,0.05);        
   DefineColor("nb",0.79,0.92,0.85);        
   DefineColor("darknb",0.69,0.80,0.73);        
       
   SetPenColor("Dark Gray");	//����         
   StartFilledRegion(1);        
   MovePen(0,0);        
   DrawLine(100,0);        
   DrawLine(0,100);        
   DrawLine(-100,0);        
   DrawLine(0,-100);        
   EndFilledRegion();        
           
   for(i=2;i<=15;i++){        
       map[1][i].a=1;        
       map[1][i].color="Dark Gray";        
   }        
           
   frame("BLACK"); 
   
   cancelTimer(timer2);                           
   startTimer(timer3,100);  
   
   if(pause)
   {
   		cancelKeyboardEvent();
   		cancelCharEvent();
   		cancelTimerEvent();
	}      
}        

/* ��ͼ�ָ������浵�ĵ�ͼͶ�䵽map�� */           
void MapRestore(void){        
   int i,j;        
   for(i=0;i<29;i++){        
       for(j=0;j<18;j++){        
           map[i][j].a=mapcopy[i][j].a;        
           map[i][j].color=mapcopy[i][j].color;        
       }        
   }        
}        

/* mapͼ�㸴�ƣ��浵�� */ 
void MapCopy(void){        
   int i,j;        
   for(i=0;i<29;i++){        
       for(j=0;j<18;j++){        
           mapcopy[i][j].a=map[i][j].a;        
           mapcopy[i][j].color=map[i][j].color;        
       }        
   }        
}        

/* ���浵��ͼͶ�䵽reflectͼ�� */ 
void MapReflect(void){        
	int i,j;        
	for(i=0;i<29;i++){        
	   for(j=0;j<18;j++){        
	       reflect[i][j].a=mapcopy[i][j].a;        
	       reflect[i][j].color=mapcopy[i][j].color;        
	   }        
	}        
}        

/* reflectͼ�㸴�ƣ��浵�� */ 
void MapFakeCopy(void){        
	int i,j;        
	for(i=0;i<29;i++){        
	   for(j=0;j<18;j++){        
	       mapcopy[i][j].a=reflect[i][j].a;        
	       mapcopy[i][j].color=reflect[i][j].color;        
	   }        
	}        
}     

int spin(BLOCK_TYPE a){        
	int num1,num2;        
	int result=0;        
	       
	num1=count();        
	eraseblock(a);        
	MapCopy();        
	a.x++;        
	addblock(a);        
	num2=count();        
	
	if(num1!=num2)        
	   result++;        
	MapRestore();        
	a.x-=2;        
	addblock(a);        
	num2=count();        
	
	if(num1!=num2)        
	   result++;        
 	MapRestore();        
	a.x++;        
	a.y--;        
	addblock(a);        
	num2=count();        
	
	if(num1!=num2)        
	   result++;        
	MapRestore();        
	a.y+=2;        
	addblock(a);        
	num2=count();        
	
	if(num1!=num2)        
	   result++;        
	MapRestore();        
	a.y--;        
	addblock(a);        
	
	if(result==4)        
	   return 1;        
	else       
	   return 0;        
       
}        

/* ������һ������ */   
void next(void){        
	int num1,num2;        
	int i,j,k;        
	int sum=0;        
	int piece=0;        
	       
	if(curblock.y==24 && first==0){        
	   cancelTimer(timer1);  
	   end = 0;      
	   erasenext(nextblock);        
	   for(i=0;i<29;i++){        
	       for(j=0;j<18;j++){        
	           map[i][j].a=0;        
	           map[i][j].color="nb";        
	       }        
	   }        
	   printmap();
	   //end = 0;        
	   startTimer(timer2,800);    
	   inputscore(score,linescore);  
	}        
	       
	for(i=2;i<=25;i++){        
	   for(j=2;j<=15;j++){        
	       if(map[i][j].a==1){        
	           sum++;        
	       }        
	   }        
	   if(sum==14){       
	       piece++;        
	   }        
	   sum=0;        
	}        
	if(!first){      
		if(spin(curblock)&&piece==0&&curblock.type==5){        
		   if(kick){        
		       score+=100;        
		   }        
		   else{        
		       score+=400;        
		   }        
		}        
		else if(spin(curblock)&&piece==1&&curblock.type==5){        
		   if(kick){        
		       score+=200;        
		   }        
		   else{        
		       score+=800;         
		   }        
		}        
		else if(spin(curblock)&&piece==2&&curblock.type==5){        
		   if(kick){        
		       score+=400;        
		   }        
		   else{        
		       score+=1200;         
		   }        
		}        
		else if(spin(curblock)&&piece==3&&curblock.type==5){        
		   score+=1600;        
		}        
	}      
	piece=0;      
	for(i=2;i<=25;i++){        
	   for(j=2;j<=15;j++){        
	       if(map[i][j].a==1){        
	           sum++;        
	       }        
	   }        
	   if(sum==14){      
	    if(piece==0){      
	        score+=100;      
	    }      
	    else if(piece==1||piece==2){      
	        score+=200;      
	    }      
	       else if(piece==3){        
	           score+=300;        
	       }         
	       for(j=2;j<=15;j++){        
	           map[i][j].a=0;        
	           map[i][j].color="nb";        
	       }        
	       for(k=i;k<=25;k++){        
	           for(j=2;j<=15;j++){        
	               map[k][j]=map[k+1][j];        
	           }        
	       }        
	       i--;        
	       piece++;        
	   }        
	   sum=0;        
	}       
	  
	erasenext(nextblock);        
	curblock=nextblock;      
	fake();     
	curblock.x=6;        
	curblock.y=24;        
	addblock(curblock);        
	printmap();        
	createblockgroup();        
	printnext(nextblock);        
	linescore+=piece;        
	scoreoutput();      
	tempblock.store=0;   

}        

/* ������Ϣ�ص����� */ 
void KEP(int key,int event)        
{        
	int i,j;        
	int num1,num2;        
	int flag=1;        
	       
	kick=0;        
	       
	switch(event){        
    case KEY_DOWN:        
        switch(key){        
            case VK_ESCAPE:					/* esc������������Ϸ */ 
					end = 0;					
					startTimer(timer2,800);
					first = 1;
			break;
			
			case VK_BACK:					/* �˸������������һ���� */ 
				cancelTimer(timer1);
				cancelTimer(timer2);
				cancelTimer(timer3);
				erasemap();
	                  for(i=0;i<29;i++){        
			           for(j=0;j<18;j++){        
			                       
			                   map[28-i][j].color="Dark Gray";        
			                   map[28-i][j].a=0;        
			                       
			               }        
			           }        
					   frame("BLACK");
	                printmap();
				play = 0;
				first = 1;
				//inputscore(score);
				registerMouseEvent(MouseEventProcess);      	// ���
				registerCharEvent(CharEventProcess); 			// �ַ�
				registerKeyboardEvent(KeyboardEventProcess);	// ����
			break;		

			case VK_RETURN:      			/* �س���������ʼ��Ϸ */ 
	      		if(first){          
	                
					cancelTimer(timer2);
	                erasemap();
	                  for(i=0;i<29;i++){        
			           for(j=0;j<18;j++){        
			                       
			                   map[28-i][j].color="Dark Gray";        
			                   map[28-i][j].a=0;        
			                       
			               }        
			           }        
			              
					           
					   frame("BLACK");

	                printmap();
					cancelTimer(timer3);          
	                next();        
	                first = 0; 
					score = 0;
					linescore = 0;         
	            }          
	            else{        
					next();        
	            }        
	            startTimer(timer1,500);         
            break;      
			
			case VK_DOWN:        			/* ���¡����������� */ 
               num1=count();        
               MapCopy();        
               erasemap();        
               eraseblock(curblock);        
               curblock.y--;        
               addblock(curblock);        
               num2=count();        
               if(num1!=num2){        
                   curblock.y++;        
                   MapRestore();        
                   printmap();        
                   score++;        
                   next();        
               }        
               printmap();        
               break;        
            case VK_SPACE:        		/* �ո񡪡�ֱ����� */ 
               for(j=1;j<curblock.y;j++){        
                   if(map[curblock.y-j+1][curblock.x+1].a==1||map[curblock.y-j+1][curblock.x+2].a==1||map[curblock.y-j+1][curblock.x+3].a==1||map[curblock.y-j+1][curblock.x+4].a==1)        
                   {        
                       j--;        
                       break;        
                   }        
               }        
               erasemap();        
               eraseblock(curblock);        
               j--;        
               curblock.y-=j;        
               addblock(curblock);        
               while(flag){        
                   num1=count();        
                   MapCopy();        
                   erasemap();        
                   eraseblock(curblock);        
                   curblock.y--;        
                   addblock(curblock);        
                   num2=count();        
                   if(num1!=num2){        
                       curblock.y++;        
                       MapRestore();        
                       addblock(curblock);        
                       flag=0;        
                   }        
               }       
        
               printmap();        
               score+=2;        
               next();        
               break;        
            case VK_LEFT:        	/* ���󡪡����� */ 
               num1=count();        
               MapCopy();        
               erasemap();        
               eraseblock(curblock);        
               curblock.x--;        
               addblock(curblock);        
               num2=count();        
               if(num1!=num2){        
                   curblock.x++;        
                   MapRestore();        
                   addblock(curblock);        
                   printmap();        
               }       
               printmap();        
               break;        
            case VK_RIGHT:        /* ���ҡ������� */ 
               num1=count();        
               MapCopy();        
               erasemap();        
               eraseblock(curblock);        
               curblock.x++;        
               addblock(curblock);        
               num2=count();        
               if(num1!=num2){        
                   curblock.x--;        
                   MapRestore();        
                   addblock(curblock);        
                   printmap();        
               }        
               printmap();        
               break;        
                       
            default:break;        
       }        
    case KEY_UP:        
       break;        
	}        
}        
   
int FLAG=1;        

/* ��ʱ����Ϣ�ص����� */ 
void TEP(int timerID)        
{        
	int num1,num2;        
	int i,j;        
	char* Color;        
	       
	kick=0;        
	switch(timerID){        
	    case timer1:        	/* �����ʱ�� */ 
	       if(theworld){        /* ���ʱͣ */ 
	           next();        
	           theworld=0;        
	       }        
	       num1=count();        
	       MapCopy();        
	       erasemap();        
	       eraseblock(curblock);        
	       curblock.y--;        
	       addblock(curblock);        
	       num2=count();        
	       if(num1!=num2){        
	           curblock.y++;        
	           MapRestore();        
	           theworld++;        
	                   
	       }        
	       printmap();        
	                           
	       break;        
	           
	    case timer2:          /* �������� */ 
	       //first = 1;
		   if(!end){
		       	//cancelKeyboardEvent();
				//cancelCharEvent();
				//cancelTimerEvent();
		       Color=BlockColor[RandomInteger(0,6)];        
		       erasenext(nextblock);        
		       if(FLAG==1){        
		       erasemap();        
		       frame("Dark Gray");        
		       for(i=0;i<29;i++){        
		           for(j=0;j<18;j++){        
		               if(game[i][j]==1){        
		                   map[28-i][j].color=Color;        
		                   map[28-i][j].a=game[i][j];        
		               }        
		               else{        
		                   map[28-i][j].color="nb";        
		                   map[28-i][j].a=game[i][j];        
		               }        
		           }        
		       }        
		       printmap();        
		       FLAG=2;        
		       }        
		       else{        
		       erasemap();        
		       frame("Dark Gray");        
			       for(i=0;i<29;i++){        
			           for(j=0;j<18;j++){        
			               if(over[i][j]==1){        
			                   map[28-i][j].color=Color;        
			                   map[28-i][j].a=over[i][j];        
			               }        
			               else{        
			                   map[28-i][j].color="nb";        
			                   map[28-i][j].a=over[i][j];        
			               }        
			           }        
			       }        
		       printmap();        
		       FLAG=1;        
		   		}
			}
	   break;        
	           
	   case timer3:        	/* �������� */ 
	       erasenext(nextblock);      
		   erasetemp(tempblock);      
	       createblockgroup();        
	       printnext(nextblock);        
	       break;        
	           
	   default:break;         
	}        
}        

void CEP(char c)      
{      
	int i,j;          
	int num1,num2;          
	int flag=1;         
	int swap;      
	char* swapC;       
      
	kick=0;          
   
	switch(c){      
//	case 'r':
//		Game();
//	break;
	case 'c':      					/* C�������ݴ� */ 
      if(!tempblock.store)      
      {      
      if(tempblock.type==-1){      
          eraseblock(curblock);      
          tempblock.type=curblock.type;      
          tempblock.color=curblock.color;      
          printtemp(tempblock);      
          curblock=nextblock;      
          curblock.x=6;      
          curblock.y=24;      
          erasenext(nextblock);      
          createblockgroup();      
          printnext(nextblock);      
          addblock(curblock);      
          erasemap();      
          printmap();      
          tempblock.store=1;      
     }      
     else{      
        eraseblock(curblock);      
        erasetemp(tempblock);      
        swap=curblock.type;      
        curblock.type=tempblock.type;      
        tempblock.type=swap;      
        swapC=curblock.color;      
        curblock.color=tempblock.color;      
        tempblock.color=swapC;      
        curblock.x=6;      
        curblock.y=24;      
        addblock(curblock);      
        printtemp(tempblock);      
        printmap();      
        tempblock.store=1;      
         }      
     }      
 	break;      

	case 'z':    				/* Z��������ʱ����ת */  
	num1=count();          
	eraseblock(curblock);          
	MapCopy();          
	switch(curblock.type){          
        case 1:case 2:case 4:case 5:case 6:     /* JLSTZ�� */     
                switch(curblock.Dir){ 			/* �����ж� */         
                    case 0:          			/* ԭ���� */ 
                        eraseblock(curblock);          
                        curblock.Dir=3;          
                        addblock(curblock);          
                        num2=count();          
                        if(num1!=num2){          
                            kick=1;          
                        eraseblock(curblock);          
                        MapRestore();          
                        curblock.x++;          
                        addblock(curblock);          
                        num2=count();          
                        if(num1!=num2){          
                            eraseblock(curblock);          
                            MapRestore();          
                            curblock.y++;          
                            addblock(curblock);          
                            num2=count();          
                            if(num1!=num2){          
                                eraseblock(curblock);          
                                MapRestore();          
                                curblock.x--;          
                                curblock.y-=3;          
                                addblock(curblock);          
                                num2=count();          
                                if(num1!=num2){          
                                    eraseblock(curblock);          
                                    MapRestore();          
                                    curblock.x++;          
                                    addblock(curblock);          
                                    num2=count();          
                                    if(num1!=num2){          
                                        eraseblock(curblock);          
                                        MapRestore();          
                                        curblock.x--;          
                                        curblock.y+=2;          
                                        curblock.Dir=0;          
                                        addblock(curblock);          
                                        erasemap();          
                                        printmap();          
                                        break;          
                                    }          
                                        erasemap();          
                                    printmap();          
                                    theworld=0;          
                                    break;          
                                }          
                                    erasemap();          
                                printmap();          
                                theworld=0;          
                                break;          
                            }          
                                erasemap();          
                            printmap();          
                            theworld=0;          
                            break;          
                        }          
                        erasemap();          
                            printmap();          
                            theworld=0;          
                            break;          
                    }          
                    erasemap();          
                            printmap();          
                            theworld=0;          
                            break;          
                    case 1:          			/* ˳ʱ��ת90�ȵ�״̬ */ 
                        eraseblock(curblock);          
                        curblock.Dir--;          
                        addblock(curblock);          
                        num2=count();          
                        if(num1!=num2){          
                            kick=1;          
                        eraseblock(curblock);          
                        MapRestore();          
                        curblock.x++;          
                        addblock(curblock);          
                        num2=count();          
                        if(num1!=num2){          
                            eraseblock(curblock);          
                            MapRestore();          
                            curblock.y--;          
                            addblock(curblock);          
                            num2=count();          
                            if(num1!=num2){          
                                eraseblock(curblock);          
                                MapRestore();          
                                curblock.x--;          
                                curblock.y+=3;          
                                addblock(curblock);          
                                num2=count();          
                                if(num1!=num2){          
                                    eraseblock(curblock);          
                                    MapRestore();          
                                    curblock.x++;          
                                    addblock(curblock);          
                                    num2=count();          
                                    if(num1!=num2){          
                                        eraseblock(curblock);          
                                        MapRestore();          
                                        curblock.x--;          
                                        curblock.y-=2;          
                                        curblock.Dir++;          
                                        addblock(curblock);          
                                            erasemap();          
                                        printmap();          
                                        break;          
                                    }          
                                        erasemap();          
                                    printmap();          
                                    theworld=0;          
                                    break;          
                                }          
                                    erasemap();          
                                printmap();          
                                theworld=0;          
                                break;          
                            }          
                            erasemap();          
                            printmap();          
                            theworld=0;          
                            break;          
                        }          
                        erasemap();          
                            printmap();          
                            theworld=0;          
                            break;          
                    }          
                    erasemap();          
                            printmap();          
                            theworld=0;          
                            break;          
                    case 2:          			/* ˳ʱ��ת180�ȵ�״̬ */ 
                        eraseblock(curblock);          
                        curblock.Dir--;          
                        addblock(curblock);          
                        num2=count();          
                        if(num1!=num2){          
                            kick=1;          
                        eraseblock(curblock);          
                        MapRestore();          
                        curblock.x--;          
                        addblock(curblock);          
                        num2=count();          
                        if(num1!=num2){          
                            eraseblock(curblock);          
                            MapRestore();          
                            curblock.y++;          
                            addblock(curblock);          
                            num2=count();          
                            if(num1!=num2){          
                                eraseblock(curblock);          
                                MapRestore();          
                                curblock.x++;          
                                curblock.y-=3;          
                                addblock(curblock);          
                                num2=count();          
                                if(num1!=num2){          
                                    eraseblock(curblock);          
                                    MapRestore();          
                                    curblock.x--;          
                                    addblock(curblock);          
                                    num2=count();          
                                    if(num1!=num2){          
                                        eraseblock(curblock);          
                                        MapRestore();          
                                        curblock.x++;          
                                        curblock.y+=2;          
                                        curblock.Dir++;          
                                        addblock(curblock);          
                                            erasemap();          
                                        printmap();          
                                        break;          
                                    }          
                                        erasemap();          
                                    printmap();          
                                    theworld=0;          
                                    break;          
                                }          
                                    erasemap();          
                                printmap();          
                                theworld=0;          
                                break;          
                            }          
                                erasemap();          
                            printmap();          
                            theworld=0;          
                            break;          
                        }          
                        erasemap();          
                            printmap();          
                            theworld=0;          
                            break;          
                    }          
                    erasemap();          
                            printmap();          
                            theworld=0;          
                            break;          
                    case 3:          			/* ˳ʱ��ת270�ȵ�״̬ */ 
                        eraseblock(curblock);          
                        curblock.Dir--;          
                        addblock(curblock);          
                        num2=count();          
                        if(num1!=num2){          
                            kick=1;          
                        eraseblock(curblock);          
                        MapRestore();          
                        curblock.x++;          
                        addblock(curblock);          
                        num2=count();          
                        if(num1!=num2){          
                            eraseblock(curblock);          
                            MapRestore();          
                            curblock.y--;          
                            addblock(curblock);          
                            num2=count();          
                            if(num1!=num2){          
                                eraseblock(curblock);          
                                MapRestore();          
                                curblock.x--;          
                                curblock.y+=3;          
                                addblock(curblock);          
                                num2=count();          
                                if(num1!=num2){          
                                    eraseblock(curblock);          
                                    MapRestore();          
                                    curblock.x++;          
                                    addblock(curblock);          
                                    num2=count();          
                                    if(num1!=num2){          
                                        eraseblock(curblock);          
                                        MapRestore();          
                                        curblock.x--;          
                                        curblock.y-=2;          
                                        curblock.Dir++;          
                                        addblock(curblock);          
                                            erasemap();          
                                        printmap();          
                                        break;          
                                    }          
                                        erasemap();          
                                    printmap();          
                                    theworld=0;          
                                    break;          
                                }          
                                    erasemap();          
                                printmap();          
                                theworld=0;          
                                break;          
                            }          
                                erasemap();          
                            printmap();          
                            theworld=0;          
                            break;          
                        }          
                        erasemap();          
                            printmap();          
                            theworld=0;          
                            break;          
                    }          
                    erasemap();          
                            printmap();          
                            theworld=0;          
                            break;          
                    default:break;          
                }          
                      
            break;          
        case 0:          				/* I�� */ 
            switch(curblock.Dir){       /* �����ж� */   
                    case 0:          
                        eraseblock(curblock);          
                        curblock.Dir=3;          
                        curblock.y--;          
                        addblock(curblock);          
                        num2=count();          
                        if(num1!=num2){          
                            kick=1;          
                        eraseblock(curblock);          
                        MapRestore();          
                        curblock.x--;          
                        addblock(curblock);          
                        num2=count();          
                        if(num1!=num2){          
                            eraseblock(curblock);          
                            MapRestore();          
                            curblock.x+=3;          
                            addblock(curblock);          
                            num2=count();          
                            if(num1!=num2){          
                                eraseblock(curblock);          
                                MapRestore();          
                                curblock.x-=3;          
                                curblock.y+=2;          
                                addblock(curblock);          
                                num2=count();          
                                if(num1!=num2){          
                                    eraseblock(curblock);          
                                    MapRestore();          
                                    curblock.x+=3;          
                                    curblock.y-=3;          
                                    addblock(curblock);          
                                    num2=count();          
                                    if(num1!=num2){          
                                        eraseblock(curblock);          
                                        MapRestore();          
                                        curblock.x-=2;          
                                        curblock.y+=2;          
                                        curblock.Dir=0;          
                                        addblock(curblock);          
                                        erasemap();          
                                        printmap();          
                                        break;          
                                    }          
                                        erasemap();          
                                    printmap();          
                                    theworld=0;          
                                    break;          
                                }          
                                    erasemap();          
                                printmap();          
                                theworld=0;          
                                break;          
                            }          
                            erasemap();          
                            printmap();          
                            theworld=0;          
                            break;          
                        }          
                        erasemap();          
                        printmap();          
                        theworld=0;          
                        break;          
                    }          
                    erasemap();          
                            printmap();          
                            theworld=0;          
                            break;          
                    case 1:          
                        eraseblock(curblock);          
                        curblock.Dir--;          
                        curblock.x--;          
                        addblock(curblock);          
                        num2=count();          
                        if(num1!=num2){          
                            kick=1;          
                        eraseblock(curblock);          
                        MapRestore();          
                        curblock.x+=2;          
                        addblock(curblock);          
                        num2=count();          
                        if(num1!=num2){          
                            eraseblock(curblock);          
                            MapRestore();          
                            curblock.x-=3;          
                            addblock(curblock);          
                            num2=count();          
                            if(num1!=num2){          
                                eraseblock(curblock);          
                                MapRestore();          
                                curblock.x+=3;          
                                curblock.y++;          
                                addblock(curblock);          
                                num2=count();          
                                if(num1!=num2){          
                                    eraseblock(curblock);          
                                    MapRestore();          
                                    curblock.x-=3;          
                                    curblock.y-=3;          
                                    addblock(curblock);          
                                    num2=count();          
                                    if(num1!=num2){          
                                        eraseblock(curblock);          
                                        MapRestore();          
                                        curblock.x+=2;          
                                        curblock.y+=2;          
                                        curblock.Dir++;          
                                        addblock(curblock);          
                                            erasemap();          
                                        printmap();          
                                        break;          
                                    }          
                                        erasemap();          
                                    printmap();          
                                    theworld=0;          
                                    break;          
                                }          
                                    erasemap();          
                                printmap();          
                                theworld=0;          
                                break;          
                            }          
                                erasemap();          
                            printmap();          
                            theworld=0;          
                            break;          
                        }          
                        erasemap();          
                            printmap();          
                            theworld=0;          
                            break;          
                    }          
                    erasemap();          
                            printmap();          
                            theworld=0;          
                            break;          
                    case 2:          
                        eraseblock(curblock);          
                        curblock.y++;          
                        curblock.Dir--;          
                        addblock(curblock);          
                        num2=count();          
                        if(num1!=num2){          
                            kick=1;          
                        eraseblock(curblock);          
                        MapRestore();          
                        curblock.x++;          
                        addblock(curblock);          
                        num2=count();          
                        if(num1!=num2){          
                            eraseblock(curblock);          
                            MapRestore();          
                            curblock.x-=3;          
                            addblock(curblock);          
                            num2=count();          
                            if(num1!=num2){          
                                eraseblock(curblock);          
                                MapRestore();          
                                curblock.x+=3;          
                                curblock.y-=2;          
                                addblock(curblock);          
                                num2=count();          
                                if(num1!=num2){          
                                    eraseblock(curblock);          
                                    MapRestore();          
                                    curblock.x-=3;          
                                    curblock.y+=3;          
                                    addblock(curblock);          
                                    num2=count();          
                                    if(num1!=num2){          
                                        eraseblock(curblock);          
                                        MapRestore();          
                                        curblock.x+=2;          
                                        curblock.y-=2;          
                                        curblock.Dir++;          
                                        addblock(curblock);          
                                            erasemap();          
                                        printmap();          
                                        break;          
                                    }          
                                        erasemap();          
                                    printmap();          
                                    theworld=0;          
                                    break;          
                                }          
                                    erasemap();          
                                printmap();          
                                theworld=0;          
                                break;          
                            }          
                                erasemap();          
                            printmap();          
                            theworld=0;          
                            break;          
                        }          
                        erasemap();          
                            printmap();          
                            theworld=0;          
                            break;          
                    }          
                    erasemap();          
                            printmap();          
                            theworld=0;          
                            break;          
                    case 3:          
                        eraseblock(curblock);          
                        curblock.x++;          
                        curblock.Dir--;          
                        addblock(curblock);          
                        num2=count();          
                        if(num1!=num2){          
                            kick=1;          
                        eraseblock(curblock);          
                        MapRestore();          
                        curblock.x-=2;          
                        addblock(curblock);          
                        num2=count();          
                        if(num1!=num2){          
                            eraseblock(curblock);          
                            MapRestore();          
                            curblock.x+=3;          
                            addblock(curblock);          
                            num2=count();          
                            if(num1!=num2){          
                                eraseblock(curblock);          
                                MapRestore();          
                                curblock.x-=3;          
                                curblock.y--;          
                                addblock(curblock);          
                                num2=count();          
                                if(num1!=num2){          
                                    eraseblock(curblock);          
                                    MapRestore();          
                                    curblock.x+=3;          
                                    curblock.y+=3;          
                                    addblock(curblock);          
                                    num2=count();          
                                    if(num1!=num2){          
                                        eraseblock(curblock);          
                                        MapRestore();          
                                        curblock.x-=2;          
                                        curblock.y-=2;          
                                        curblock.Dir++;          
                                        addblock(curblock);          
                                            erasemap();          
                                        printmap();          
                                        break;          
                                    }          
                                        erasemap();          
                                    printmap();          
                                    theworld=0;          
                                    break;          
                                }          
                                    erasemap();          
                                printmap();          
                                theworld=0;          
                                break;          
                            }          
                                erasemap();          
                            printmap();          
                            theworld=0;          
                            break;          
                        }          
                        erasemap();          
                            printmap();          
                            theworld=0;          
                            break;          
                    }          
                    erasemap();          
                            printmap();          
                            theworld=0;          
                            break;          
                    default:break;          
                }          
                      
            break;          
        case 3:          			/* O�Σ�����Ҫ�жϷ��� */ 
            addblock(curblock);      
            break;          
        default:break;          
    }          
    break;          
  	
	case 'x':    					/* X������˳ʱ����ת */  
	num1=count();          
            eraseblock(curblock);          
            MapCopy();          
            switch(curblock.type){          
                case 1:case 2:case 4:case 5:case 6:          
                        switch(curblock.Dir){          
                            case 0:          
                                eraseblock(curblock);          
                                curblock.Dir++;          
                                addblock(curblock);          
                                num2=count();          
                                if(num1!=num2){          
                                kick=1;          
                                eraseblock(curblock);          
                                MapRestore();          
                                curblock.x--;          
                                addblock(curblock);          
                                num2=count();          
                                if(num1!=num2){          
                                    eraseblock(curblock);          
                                    MapRestore();          
                                    curblock.y++;          
                                    addblock(curblock);          
                                    num2=count();          
                                    if(num1!=num2){          
                                        eraseblock(curblock);          
                                        MapRestore();          
                                        curblock.x++;          
                                        curblock.y-=3;          
                                        addblock(curblock);          
                                        num2=count();          
                                        if(num1!=num2){          
                                            eraseblock(curblock);          
                                            MapRestore();          
                                            curblock.x--;          
                                            addblock(curblock);          
                                            num2=count();          
                                            if(num1!=num2){          
                                                eraseblock(curblock);          
                                                MapRestore();          
                                                curblock.x++;          
                                                curblock.y+=2;          
                                                curblock.Dir--;          
                                                addblock(curblock);          
                                                erasemap();          
                                                printmap();          
                                                break;          
                                            }          
                                            erasemap();          
                                            printmap();          
                                            theworld=0;          
                                            break;          
                                        }          
                                        erasemap();          
                                        printmap();          
                                        theworld=0;          
                                        break;          
                                    }          
                                    erasemap();          
                                    printmap();          
                                    theworld=0;          
                                    break;          
                                }          
                                erasemap();          
                                printmap();          
                                theworld=0;          
                                break;          
                            }          
                            erasemap();          
                            printmap();          
                            theworld=0;          
                            break;          
                            case 1:          
                                eraseblock(curblock);          
                                curblock.Dir++;          
                                addblock(curblock);          
                                num2=count();          
                                if(num1!=num2){          
                                kick=1;          
                                eraseblock(curblock);          
                                MapRestore();          
                                curblock.x++;          
                                addblock(curblock);          
                                num2=count();          
                                if(num1!=num2){          
                                    eraseblock(curblock);          
                                    MapRestore();          
                                    curblock.y--;          
                                    addblock(curblock);          
                                    num2=count();          
                                    if(num1!=num2){          
                                        eraseblock(curblock);          
                                        MapRestore();          
                                        curblock.x--;          
                                        curblock.y+=3;          
                                        addblock(curblock);          
                                        num2=count();          
                                        if(num1!=num2){          
                                            eraseblock(curblock);          
                                            MapRestore();          
                                            curblock.x++;          
                                            addblock(curblock);          
                                            num2=count();          
                                            if(num1!=num2){          
                                                eraseblock(curblock);          
                                                MapRestore();          
                                                curblock.x--;          
                                                curblock.y-=2;          
                                                curblock.Dir--;          
                                                addblock(curblock);          
                                                erasemap();          
                                                printmap();          
                                                break;          
                                            }          
                                                erasemap();          
                                            printmap();          
                                            theworld=0;          
                                            break;          
                                        }          
                                            erasemap();          
                                        printmap();          
                                        theworld=0;          
                                        break;          
                                    }          
                                        erasemap();          
                                    printmap();          
                                    theworld=0;          
                                    break;          
                                }          
                                erasemap();          
                                    printmap();          
                                    theworld=0;          
                                    break;          
                            }          
                            erasemap();          
                                    printmap();          
                                    theworld=0;          
                                    break;          
                            case 2:          
                                eraseblock(curblock);          
                                curblock.Dir++;          
                                addblock(curblock);          
                                num2=count();          
                                if(num1!=num2){          
                                kick=1;          
                                eraseblock(curblock);          
                                MapRestore();          
                                curblock.x++;          
                                addblock(curblock);          
                                num2=count();          
                                if(num1!=num2){          
                                    eraseblock(curblock);          
                                    MapRestore();          
                                    curblock.y++;          
                                    addblock(curblock);          
                                    num2=count();          
                                    if(num1!=num2){          
                                        eraseblock(curblock);          
                                        MapRestore();          
                                        curblock.x--;          
                                        curblock.y-=3;          
                                        addblock(curblock);          
                                        num2=count();          
                                        if(num1!=num2){          
                                            eraseblock(curblock);          
                                            MapRestore();          
                                            curblock.x++;          
                                            addblock(curblock);          
                                            num2=count();          
                                            if(num1!=num2){          
                                                eraseblock(curblock);          
                                                MapRestore();          
                                                curblock.x--;          
                                                curblock.y+=2;          
                                                curblock.Dir--;          
                                                addblock(curblock);          
                                                    erasemap();          
                                                printmap();          
                                                break;          
                                            }          
                                                erasemap();          
                                            printmap();          
                                            theworld=0;          
                                            break;          
                                        }          
                                            erasemap();          
                                        printmap();          
                                        theworld=0;          
                                        break;          
                                    }          
                                        erasemap();          
                                    printmap();          
                                    theworld=0;          
                                    break;          
                                }          
                                erasemap();          
                                    printmap();          
                                    theworld=0;          
                                    break;          
                            }          
                            erasemap();          
                                    printmap();          
                                    theworld=0;          
                                    break;          
                            case 3:          
                                eraseblock(curblock);          
                                curblock.Dir=0;          
                                addblock(curblock);          
                                num2=count();          
                                if(num1!=num2){          
                                kick=1;          
                                eraseblock(curblock);          
                                MapRestore();          
                                curblock.x--;          
                                addblock(curblock);          
                                num2=count();          
                                if(num1!=num2){          
                                    eraseblock(curblock);          
                                    MapRestore();          
                                    curblock.y--;          
                                    addblock(curblock);          
                                    num2=count();          
                                    if(num1!=num2){          
                                        eraseblock(curblock);          
                                        MapRestore();          
                                        curblock.x++;          
                                        curblock.y+=3;          
                                        addblock(curblock);          
                                        num2=count();          
                                        if(num1!=num2){          
                                            eraseblock(curblock);          
                                            MapRestore();          
                                            curblock.x--;          
                                            addblock(curblock);          
                                            num2=count();          
                                            if(num1!=num2){          
                                                eraseblock(curblock);          
                                                MapRestore();          
                                                curblock.x++;          
                                                curblock.y-=2;          
                                                curblock.Dir=3;          
                                                addblock(curblock);          
                                                    erasemap();          
                                                printmap();          
                                                break;          
                                            }          
                                                erasemap();          
                                            printmap();          
                                            theworld=0;          
                                            break;          
                                        }          
                                            erasemap();          
                                        printmap();          
                                        theworld=0;          
                                        break;          
                                    }          
                                        erasemap();          
                                    printmap();          
                                    theworld=0;          
                                    break;          
                                }          
                                erasemap();          
                                    printmap();          
                                    theworld=0;          
                                    break;          
                            }          
                            erasemap();          
                                    printmap();          
                                    theworld=0;          
                                    break;          
                            default:break;          
                        }          
                              
                    break;          
                case 0:          
                    switch(curblock.Dir){          
                            case 0:          
                                eraseblock(curblock);          
                                curblock.Dir++;          
                                curblock.x++;          
                                addblock(curblock);          
                                num2=count();          
                                if(num1!=num2){          
                                kick=1;          
                                eraseblock(curblock);          
                                MapRestore();          
                                curblock.x-=2;          
                                addblock(curblock);          
                                num2=count();          
                                if(num1!=num2){          
                                    eraseblock(curblock);          
                                    MapRestore();          
                                    curblock.x+=3;          
                                    addblock(curblock);          
                                    num2=count();          
                                    if(num1!=num2){          
                                        eraseblock(curblock);          
                                        MapRestore();          
                                        curblock.x-=3;          
                                        curblock.y--;          
                                        addblock(curblock);          
                                        num2=count();          
                                        if(num1!=num2){          
                                            eraseblock(curblock);          
                                            MapRestore();          
                                            curblock.x+=3;          
                                            curblock.y+=3;          
                                            addblock(curblock);          
                                            num2=count();          
                                            if(num1!=num2){          
                                                eraseblock(curblock);          
                                                MapRestore();          
                                                curblock.x-=2;          
                                                curblock.y-=2;          
                                                curblock.Dir--;          
                                                addblock(curblock);          
                                                erasemap();          
                                                printmap();          
                                                break;          
                                            }          
                                                erasemap();          
                                            printmap();          
                                            theworld=0;          
                                            break;          
                                        }          
                                            erasemap();          
                                        printmap();          
                                        theworld=0;          
                                        break;          
                                    }          
                                        erasemap();          
                                    printmap();          
                                    theworld=0;          
                                    break;          
                                }          
                                erasemap();          
                                    printmap();          
                                    theworld=0;          
                                    break;          
                            }          
                             erasemap();          
                             printmap();          
                             theworld=0;          
                             break;          
                            case 1:          
                                eraseblock(curblock);          
                                curblock.y--;          
                                curblock.Dir++;          
                                addblock(curblock);          
                                num2=count();          
                                if(num1!=num2){          
                                    kick=1;          
                                eraseblock(curblock);          
                                MapRestore();             
                                curblock.x--;          
                                addblock(curblock);          
                                num2=count();          
                                if(num1!=num2){          
                                    eraseblock(curblock);          
                                    MapRestore();          
                                    curblock.x+=3;          
                                    addblock(curblock);          
                                    num2=count();          
                                    if(num1!=num2){          
                                        eraseblock(curblock);          
                                        MapRestore();          
                                        curblock.x-=3;          
                                        curblock.y+=2;          
                                        addblock(curblock);          
                                        num2=count();          
                                        if(num1!=num2){          
                                            eraseblock(curblock);          
                                            MapRestore();          
                                            curblock.x+=3;          
                                            curblock.y-=3;          
                                            addblock(curblock);          
                                            num2=count();          
                                            if(num1!=num2){          
                                                eraseblock(curblock);          
                                                MapRestore();          
                                                curblock.x-=2;          
                                                curblock.y+=2;          
                                                curblock.Dir--;          
                                                addblock(curblock);          
                                                    erasemap();          
                                                printmap();          
                                                break;          
                                            }          
                                                erasemap();          
                                            printmap();          
                                            theworld=0;          
                                            break;          
                                        }          
                                            erasemap();          
                                        printmap();          
                                        theworld=0;          
                                        break;          
                                    }          
                                        erasemap();          
                                    printmap();          
                                    theworld=0;          
                                    break;          
                                }          
                                erasemap();          
                                    printmap();          
                                    theworld=0;          
                                    break;          
                            }          
                            erasemap();          
                                    printmap();          
                                    theworld=0;          
                                    break;          
                            case 2:          
                                eraseblock(curblock);          
                                curblock.x--;          
                                curblock.Dir++;          
                                addblock(curblock);          
                                num2=count();          
                                if(num1!=num2){          
                                    kick=1;          
                                eraseblock(curblock);          
                                MapRestore();          
                                curblock.x+=2;          
                                addblock(curblock);          
                                num2=count();          
                                if(num1!=num2){          
                                    eraseblock(curblock);          
                                    MapRestore();          
                                    curblock.x-=3;          
                                    addblock(curblock);          
                                    num2=count();          
                                    if(num1!=num2){          
                                        eraseblock(curblock);          
                                        MapRestore();          
                                        curblock.x+=3;          
                                        curblock.y++;          
                                        addblock(curblock);          
                                        num2=count();          
                                        if(num1!=num2){          
                                            eraseblock(curblock);          
                                            MapRestore();          
                                            curblock.x-=3;          
                                            curblock.y-=3;          
                                            addblock(curblock);          
                                            num2=count();          
                                            if(num1!=num2){          
                                                eraseblock(curblock);          
                                                MapRestore();          
                                                curblock.x+=2;          
                                                curblock.y+=2;          
                                                curblock.Dir--;          
                                                addblock(curblock);          
                                                    erasemap();          
                                                printmap();          
                                                break;          
                                            }          
                                                erasemap();          
                                            printmap();          
                                            theworld=0;          
                                            break;          
                                        }          
                                            erasemap();          
                                        printmap();          
                                        theworld=0;          
                                        break;          
                                    }          
                                        erasemap();          
                                    printmap();          
                                    theworld=0;          
                                    break;          
                                }          
                                erasemap();          
                                    printmap();          
                                    theworld=0;          
                                    break;          
                            }          
                            erasemap();          
                                    printmap();          
                                    theworld=0;          
                                    break;          
                            case 3:          
                                eraseblock(curblock);          
                                curblock.y++;          
                                curblock.Dir=0;          
                                addblock(curblock);          
                                num2=count();          
                                if(num1!=num2){          
                                    kick=1;          
                                eraseblock(curblock);          
                                MapRestore();          
                                curblock.x++;          
                                addblock(curblock);          
                                num2=count();          
                                if(num1!=num2){          
                                    eraseblock(curblock);          
                                    MapRestore();          
                                    curblock.x-=3;          
                                    addblock(curblock);          
                                    num2=count();          
                                    if(num1!=num2){          
                                        eraseblock(curblock);          
                                        MapRestore();          
                                        curblock.x+=3;          
                                        curblock.y-=2;          
                                        addblock(curblock);          
                                        num2=count();          
                                        if(num1!=num2){          
                                            eraseblock(curblock);          
                                            MapRestore();          
                                            curblock.x-=3;          
                                            curblock.y+=3;          
                                            addblock(curblock);          
                                            num2=count();          
                                            if(num1!=num2){          
                                                eraseblock(curblock);          
                                                MapRestore();          
                                                curblock.x+=2;          
                                                curblock.y-=2;          
                                                curblock.Dir=3;          
                                                addblock(curblock);          
                                                    erasemap();          
                                                printmap();          
                                                break;          
                                            }          
                                                erasemap();          
                                            printmap();          
                                            theworld=0;          
                                            break;          
                                        }          
                                            erasemap();          
                                        printmap();          
                                        theworld=0;          
                                        break;          
                                    }          
                                        erasemap();          
                                    printmap();          
                                    theworld=0;          
                                    break;          
                                }          
                                erasemap();          
                                    printmap();          
                                    theworld=0;          
                                    break;          
                            }          
                            erasemap();          
                                    printmap();          
                                    theworld=0;          
                                    break;          
                            default:break;          
                        }          
                              
                    break;          
                case 3:          
                    addblock(curblock);      
                    break;          
                default:break;          
            }          
            break;          
        
  break;      
        
  default:break;      
}    
}      

/* ���������û���Ϣ */ 
void inputscore(long score, long linescore){
	
	FILE *fp;
	
	if((fp=fopen("rank.txt","a"))==NULL)
	{
		printf("File open error!\n");
		exit(0);
	}
	
	// ����
	//scanf("%d",score);
	sumscore=score+linescore;
	fprintf(fp,"%d",sumscore);
	fputc('\n',fp);
	
	if(fclose(fp)){
		printf("Can not close the file!\n");
		exit(0);
	}
}


