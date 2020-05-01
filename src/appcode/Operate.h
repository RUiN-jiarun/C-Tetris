#ifndef ____Operate_h______
#define ____Operate_h______


typedef struct
{        
    int x;         
    int y;        
    int type;        
    int Dir;        
    char* color;        
    int store;    
}BLOCK_TYPE;   


int count(void);
int fakecount(void);
void scoreoutput(void);
void frame(char* s);
void drawblock(int x,int y,char* color);
void drawfakeblock(int x,int y,char* color);
void printnext(BLOCK_TYPE a);
void erasenext(BLOCK_TYPE a);
void printtemp(BLOCK_TYPE a);
void erasetemp(BLOCK_TYPE a);
void addblock(BLOCK_TYPE a);
void addfakeblock(BLOCK_TYPE a);
void fake(void);
void printmap(void);
void eraseblock(BLOCK_TYPE a);
void erasefakeblock(BLOCK_TYPE a);
void erasemap(void);

void createblockgroup(void);
void Game();
void MapRestore(void);
void MapCopy(void);
void MapReflect(void);
void MapFakeCopy(void);
int spin(BLOCK_TYPE a);
void next(void);
void KEP(int key,int event);
void TEP(int timerID);
void CEP(char c);
void inputscore(long score, long linescore);    

#endif
