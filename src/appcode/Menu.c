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

// 状态量——全局
extern int	STATE;


// 全局变量
static double winwidth, winheight;   // 窗口尺寸
static int    start = 0; // 开始按钮是否按下判定参量 
static int    help = 0; // 帮助按钮是否按下判定参量 
static int    login = 0; // 录入按钮是否按下判定参量 
static int	  highscore = 0; // 排行榜按钮是否按下判定参量 

extern int    play = 0;
extern int    pause = 0; 

// 用户信息 
typedef struct inf{
	char name[20];
	int score;
	char score_string[20];
}info;

info rank[4];

// 清屏函数
void DisplayClear(void); 
// 计时器启动函数
void startTimer(int id,int timeinterval);
// 用户的显示函数
void display(void); 
// 菜单主程序 
void Menu();
// 主标题模块
void Title();
// 文本编辑模块 
void Text();
// 用户信息读入模块 
void inputrank(char* s);
// 排行榜显示模块 
void Rank();
 

// 用户的字符事件响应函数
extern void CharEventProcess(char ch)
{
	uiGetChar(ch); // GUI字符输入
	display(); //刷新显示
}

// 用户的键盘事件响应函数
extern void KeyboardEventProcess(int key, int event)
{
	uiGetKeyboard(key,event); // GUI获取键盘
	display(); // 刷新显示
}

// 用户的鼠标事件响应函数
extern void MouseEventProcess(int x, int y, int button, int event)
{
	uiGetMouse(x,y,button,event); //GUI获取鼠标
	display(); // 刷新显示
}


// 用户主程序入口
void Main() 
{
	// 初始化窗口和图形系统
	SetWindowTitle("Tetris");
	
    InitGraphics();
    
    DefineColor("PURPLE",0.25,0.875,0.8);                
	DefineColor("myBLUE",0.01,0.2,0.8);        
    DefineColor("myRED",0.89,0.09,0.05);        
    DefineColor("nb",0.79,0.92,0.85);        
    DefineColor("darknb",0.69,0.80,0.73); 
	
	// 获得窗口尺寸
    winwidth = GetWindowWidth();
    winheight = GetWindowHeight();
    
    // 确定笔刷大小 
	SetPointSize(20);

	// 注册时间响应函数
	registerMouseEvent(MouseEventProcess);      	// 鼠标
	registerCharEvent(CharEventProcess); 			// 字符
	registerKeyboardEvent(KeyboardEventProcess);	// 键盘
	
	
}


// 菜单主程序 
void Menu()
{
	double fH = GetFontHeight();
	double h = fH*2;  
	double x = winwidth/8;  
	double y = winheight/2-h; 
	double w = winwidth/5; 

 
	Title(); 
	SetPointSize(20);
	if ( button(GenUIID(0), x, y, w, h, start ? "返回" : "开始游戏") )
		start = ! start;
	
	if( button(GenUIID(0), x, y-2*h, w, h, "退出") )
		exit(-1);

	if( start ) {
		if( button(GenUIID(0), x + w*1.2, y, w, h, "玩家录入") )
			login = ! login;
		if( button(GenUIID(0), x + w*1.2, y - 1*h*2, w, h, "帮助") )
			help = ! help; 

		if( button(GenUIID(0), x + w*1.2, y - 2*h*2, w, h, "排行榜") )	 
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
		drawBox(2.5, 4, 4, 1, 1, "帮   助", "P", "myBlue");
		SetPointSize(20);
		drawLabel(x + w*0.5,  y, "←左移\t\t  →右移\t\t  ↓加速下落");
		drawLabel(x + w*0.5,  y - h, "z：逆时针旋转  \t\tx：顺时针旋转  \t\tc：暂存方块");
		drawLabel(x + w*0.5,  y - 2 * h, "回车键：开始游戏  \t\t空格键：直接落地  \t\t退格键：返回菜单 \t\tEsc键：结束游戏");
		if( button(GenUIID(0), x + w*2.4, y - 2*h*2, w, h, "返回") ) 
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
	// 清屏
	DisplayClear();
			
	// 主菜单
	Menu();
	
}

// 主标题模块
void Title()
{
	SetPenColor("nb"); 
	SetPointSize(100);
	SetFont("Bradley Hand ITC"); 
	drawBox(2, 4, 5, 1.8, 1, "T E T R I S", "P", "myBlue");
} 
 
// 文本编辑模块 
void Text()
{
	static char name[80] = "player";

	static char results[200] = "";


	double fH = GetFontHeight();
	double h = fH*2; 			// 控件高度
	double w = winwidth/4;		// 控件宽度
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
	drawLabel(x-fH/2-TextStringWidth("名称"), (y-=h*1.2)+fH*0.7, "名称");
	if( textbox(GenUIID(0), x, y, w, h, name, sizeof(name)) )
	{	
		sprintf(results,"玩家名称: %s", name);

	}
	
	//SaveGraphicsState();
	if( button(GenUIID(0), x1 + w1*2.4, y - 2.5*h, w1, h, "返回") ) 
		login = 0; 
	
	if( button(GenUIID(0), x1 + w1*2.4, y - 1*h, w1, h, "继续")) 	// 在这里链接游戏界面 
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


// 用户信息读入模块 
void inputrank(char* s){
	
	FILE *fp;
	
	if((fp=fopen("rank.txt","a"))==NULL)
	{
		printf("File open error!\n");
		exit(0);
	}
	
	// 读入
	scanf("%s",s);
	fputs(s,fp);
	fputc(10,fp);
	
	if(fclose(fp)){
		printf("Can not close the file!\n");
		exit(0);
	}
}

// 排行榜显示模块 
void Rank()
{
	readrank();
	DrawChart(); 
	drawButtons(); 
}

// 表格绘制模块 
void DrawChart(){
	SetPenColor("nb");
	MovePen(4.5,5.45);
	SetPointSize(55);
	SetFont("宋体");
	drawBox(2.75, 5.00 , 4 , 0.85 , 1 , "排行榜 ", 'P', "myBlue");//排行榜标题
	
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

// 排行榜界面返回按钮
void drawButtons()
{
	// 获得窗口尺寸
    winwidth = GetWindowWidth();
    winheight = GetWindowHeight();
    SetPointSize(20);
    SetStyle(0);
	if( button(GenUIID(0), 4.05, 1.1, 1.35, 0.4, "返回") )
	{
		DisplayClear();
		highscore = 0;

		Menu();
	}
}

// 用户数据读取模块 
void readrank(){
	FILE *fp;
	int i=0, j=0, k=0;
	info tmp;
	fp=fopen("rank.txt","r");
	while(!feof(fp)){
		fscanf(fp,"%s %d",rank[i].name, &rank[i].score);
		itoa(rank[i].score,rank[i].score_string,10);   		//10代表十进制 
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

