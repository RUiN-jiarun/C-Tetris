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
#define timer1 1    	/* 下落计时器 */    
#define timer2 2        /* 游戏结束闪动 */ 
#define timer3 3        /* 动画 */ 
            
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
   //反Z        
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
       
long score=0;        	/* 方块垒积得分 */ 
long linescore=0;       /* 消除行数得分 */ 
long sumscore=0;        /*总分*/ 
char charscore[12]={0};      /* 分数字符串 */ 
char charlinescore[12]={0};      
int theworld=0;        /* 时停 */ 
	
int first=1;        /* 判断是不是第一次 */
int end=0; 
int kick=0;         /* 是否有“踢墙” */ 
int keyy=1;       	/* 憨批 */ 

int play; 
int pause;


void CharEventProcess(char ch);
void KeyboardEventProcess(int key, int event);
void MouseEventProcess(int x, int y, int button, int event);

typedef struct{        
      int x;         
      int y;        
      int type;        /* 形态参数 */ 
      int Dir;         /* 方向参数 */ 
      char* color;        
      int store;       /* 是否暂存 */ 
}BLOCK_TYPE;        
       
BLOCK_TYPE curblock={0};        /* 当前方块 */ 
BLOCK_TYPE nextblock={0};       /* 下一个方块 */ 
BLOCK_TYPE tempblock={nextstartx,nextstarty-4,-1,0,0,0};   	/* 暂存方块 */ 
BLOCK_TYPE imagblock={0};    	/* 虚像方块 */ 
       
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
   int a;        	/* 是否被填充 */ 
   char* color;        
}cc;        

/* map reflect是两个图层 */       
cc map[height+5][width+4]={0};        /* 主游戏池 */ 
cc mapcopy[height+5][width+4]={0};    /* 用来存储游戏池状态 */ 
cc reflect[height+5][width+4]={0};    /* 叠加的用来显示虚像的游戏池 */ 
   
void TEP(int timerID);			/* 定时器信息回调函数 */        
void KEP(int key,int event);	/* 键盘信息回调函数 */        
void CEP(char c);				/* 字符信息回调函数 */
//void MEP(int x, int y, int button, int event);   

int count(void);        		
void erasefakeblock(BLOCK_TYPE a);  
void MapCopy(void);  
void MapReflect(void);  
void MapFakeCopy(void);   
int spin(BLOCK_TYPE a);  
void inputscore(long score, long linescore);      

/* 计数函数——用来判断碰撞 */  
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

/* 计数函数——用来判断reflect图层里是否碰撞 */ 
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

/* 分数显示函数 */         
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
       
/* 游戏池绘制函数 */ 
void frame(char* s){        
   int i;        
   SetPenColor("nb");//背景         
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
    /*drawLabel(5, 4,  "←左移");
    drawLabel(5, 3.5, "→右移");
    drawLabel(5, 3,  "↓加速");
    drawLabel(5, 2.5, "z：逆时针旋转");
    drawLabel(5, 2, "x：顺时针旋转");
	drawLabel(5, 1.5, "c：暂存方块");
	drawLabel(5, 1, "回车键：开始游戏  \t\t空格键：直接落地  \t\t退格键：返回菜单");*/
    scoreoutput();      
}        

/* 方块绘制函数 */       
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

/* 底部方块虚像绘制函数 */ 
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
       
/* 下一个方块显示函数 */ 
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

/* 擦除下一个方块的显示 */ 
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

/* 暂存方块显示函数 */    
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

/* 擦除暂存方块的显示 */
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

/* 当前方块加入主游戏池 */ 
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

/* 当前方块虚像加入虚拟游戏池 */ 
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

/* 虚像判断函数 */ 
void fake(void){  
	int num1,num2;		/* num1反映操作前场上被填充方块个数，num2反映操作后 */ 
	int flag=1;    		/* 是否需要判断碰撞，1则判断，判断完毕该方块变为0 */ 
	int i,j;        
	   
	MapCopy(); 			/* 复制map图层 */ 
	MapReflect();  		/* 显示到reflect图层里 */ 
	//erasefakeblock(imagblock);  
	erasefakeblock(curblock);  
	imagblock=curblock;    /* 虚像方块取代当前方块 */ 
	for(j=1;j<imagblock.y;j++)
	{        
        if(reflect[imagblock.y-j+1][imagblock.x+1].a==1 || reflect[imagblock.y-j+1][imagblock.x+2].a==1 || reflect[imagblock.y-j+1][imagblock.x+3].a==1 || reflect[imagblock.y-j+1][imagblock.x+4].a==1 || reflect[imagblock.y-j+1][imagblock.x+5].a==1)        
         {        
             j--;        
             break;        
         }        
    }        			/* 这个循环用来判断方块下落的高度，可以提高判断最终下落位置的速度 */ 
        j--;        
        imagblock.y-=j;        
        addfakeblock(imagblock);        
        
		while(flag){ 			/* 判断是否碰撞 */       
           num1=fakecount();        
           MapFakeCopy();       /* 存档 */ 
           erasefakeblock(imagblock);        
           imagblock.y--;        
           addfakeblock(imagblock);        
           num2=fakecount();        
           if(num1!=num2){        
               imagblock.y++;        
               MapReflect();        /* 有碰撞，则回档 */ 
               addfakeblock(imagblock);        
               flag=0;        
           }        
     }        
}  

/* 输出游戏池 */    
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

/* 把方块从游戏池里移除 */           
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

/* 擦除虚像方块 */ 
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

/* 擦除地图（清屏） */           
void erasemap(void){        
   int i,j;        
   for(i=1;i<=24;i++){        
       for(j=1;j<=14;j++){        
           drawblock(j,i,"nb");        
       }        
   }        
           
   frame("BLACK");        
}        
       
int rounds=0;    		/* 轮 */    
int typeran[7]={0};       /* 随机数 */ 
int cir=1;          

/* 设置随机方块组 */ 
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

/* 游戏入口 */           
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
       
   SetPenColor("Dark Gray");	//背景         
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

/* 地图恢复（将存档的地图投射到map） */           
void MapRestore(void){        
   int i,j;        
   for(i=0;i<29;i++){        
       for(j=0;j<18;j++){        
           map[i][j].a=mapcopy[i][j].a;        
           map[i][j].color=mapcopy[i][j].color;        
       }        
   }        
}        

/* map图层复制（存档） */ 
void MapCopy(void){        
   int i,j;        
   for(i=0;i<29;i++){        
       for(j=0;j<18;j++){        
           mapcopy[i][j].a=map[i][j].a;        
           mapcopy[i][j].color=map[i][j].color;        
       }        
   }        
}        

/* 将存档地图投射到reflect图层 */ 
void MapReflect(void){        
	int i,j;        
	for(i=0;i<29;i++){        
	   for(j=0;j<18;j++){        
	       reflect[i][j].a=mapcopy[i][j].a;        
	       reflect[i][j].color=mapcopy[i][j].color;        
	   }        
	}        
}        

/* reflect图层复制（存档） */ 
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

/* 生成下一个方块 */   
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

/* 键盘信息回调函数 */ 
void KEP(int key,int event)        
{        
	int i,j;        
	int num1,num2;        
	int flag=1;        
	       
	kick=0;        
	       
	switch(event){        
    case KEY_DOWN:        
        switch(key){        
            case VK_ESCAPE:					/* esc键——结束游戏 */ 
					end = 0;					
					startTimer(timer2,800);
					first = 1;
			break;
			
			case VK_BACK:					/* 退格键——返回上一界面 */ 
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
				registerMouseEvent(MouseEventProcess);      	// 鼠标
				registerCharEvent(CharEventProcess); 			// 字符
				registerKeyboardEvent(KeyboardEventProcess);	// 键盘
			break;		

			case VK_RETURN:      			/* 回车键——开始游戏 */ 
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
			
			case VK_DOWN:        			/* 向下——加速下落 */ 
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
            case VK_SPACE:        		/* 空格——直接落地 */ 
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
            case VK_LEFT:        	/* 向左——左移 */ 
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
            case VK_RIGHT:        /* 向右——右移 */ 
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

/* 定时器信息回调函数 */ 
void TEP(int timerID)        
{        
	int num1,num2;        
	int i,j;        
	char* Color;        
	       
	kick=0;        
	switch(timerID){        
	    case timer1:        	/* 下落计时器 */ 
	       if(theworld){        /* 如果时停 */ 
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
	           
	    case timer2:          /* 结束动画 */ 
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
	           
	   case timer3:        	/* 开场动画 */ 
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
	case 'c':      					/* C键——暂存 */ 
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

	case 'z':    				/* Z键——逆时针旋转 */  
	num1=count();          
	eraseblock(curblock);          
	MapCopy();          
	switch(curblock.type){          
        case 1:case 2:case 4:case 5:case 6:     /* JLSTZ形 */     
                switch(curblock.Dir){ 			/* 方向判定 */         
                    case 0:          			/* 原方向 */ 
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
                    case 1:          			/* 顺时针转90度的状态 */ 
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
                    case 2:          			/* 顺时针转180度的状态 */ 
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
                    case 3:          			/* 顺时针转270度的状态 */ 
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
        case 0:          				/* I形 */ 
            switch(curblock.Dir){       /* 方向判定 */   
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
        case 3:          			/* O形，不需要判断方向 */ 
            addblock(curblock);      
            break;          
        default:break;          
    }          
    break;          
  	
	case 'x':    					/* X键——顺时针旋转 */  
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

/* 分数读入用户信息 */ 
void inputscore(long score, long linescore){
	
	FILE *fp;
	
	if((fp=fopen("rank.txt","a"))==NULL)
	{
		printf("File open error!\n");
		exit(0);
	}
	
	// 读入
	//scanf("%d",score);
	sumscore=score+linescore;
	fprintf(fp,"%d",sumscore);
	fputc('\n',fp);
	
	if(fclose(fp)){
		printf("Can not close the file!\n");
		exit(0);
	}
}


