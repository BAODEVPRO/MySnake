#include <iostream>
#include <conio.h>
#include <windows.h>
#include <graphics.h>
#include <ctime>    
using namespace std;
enum DIR {LEFT , UP , RIGHT , DOWN};        
////// CO CAU VI TRI --  DUOC SU DUNG TRONG RAN CHI DO GIA TRI DAT TRUOC CUA NO
struct POS
{
       int x,y;
       POS()
       {
            x = -50;
            y = 0;
       }
};
class ConRan
{
private:
    POS arr[31];            // Mang nay chua toan bo vi tri cua ran
    int Huong;          // Lam viec voi enum
    int ChieuDai;   

public:
    ConRan()  // Thiet lap san cac yeu to ban dau cho con ran
    {
        arr[0].x = 30;        // Cung cap gia tri ban dau cho con ran
        arr[0].y = 30;        // Cung cap gia tri ban dau cho con ran
        ChieuDai = 2;           // Chieu dai =2
        Huong = RIGHT;    // Huong Phai
    }
    void VeRan();
    void appendSnake();         // Ham giup tang chieu dai con ran khong vuot qua 30
    void changeDirTo(int);
    int CapNhat();
    int getPosx();              
    int getPosy();              
    int getChieuDai();           
};
void ConRan::VeRan()         // Ve Ran
{
     for(int i=0; i<ChieuDai ; i++)
     {
          setcolor(BLUE);
          rectangle(arr[i].x , arr[i].y , arr[i].x+30 , arr[i].y+30);
          if(i==0)                                      // Lam mau cho Phan Dau
                  setfillstyle(SOLID_FILL , GREEN);
          else                                          //  Lam mau cho Phan Duoi
                  setfillstyle(SOLID_FILL , LIGHTGREEN);
          floodfill(arr[i].x+15 , arr[i].y+15 , BLUE);
     }
}

void ConRan::appendSnake()
{
     if(ChieuDai < 30)                            
        ChieuDai++;
}

void ConRan::changeDirTo(int newdir)
{
     if(newdir == LEFT || newdir == RIGHT)
     {
            if(Huong == UP || Huong == DOWN)
                         Huong = newdir;
     }
     else if(newdir == UP || newdir == DOWN)
     {
            if(Huong == LEFT || Huong == RIGHT)
                         Huong = newdir;
     }
}

int ConRan::CapNhat()                                                     // Cac chuc nang co ban
{                                                                         // Thuat toan di chuyen Ran
     for(int i=1 ; i<ChieuDai ; ++i)                                      // Cung cap tat ca cac phan truoc
     {                                                                      
             if(arr[0].x == arr[i].x && arr[0].y == arr[i].y)   
			 {
			 	return 0;
			}            
     }
     for(int i=ChieuDai ; i>=0 ; --i)
     {
             if(i==0)
             {
                     arr[1].x = arr[0].x;
                     arr[1].y = arr[0].y;
             }
             else
             {
                     arr[i].x = arr[i-1].x;
                     arr[i].y = arr[i-1].y;
             }
     }
     if(Huong == LEFT)
     {
                  arr[0].x -= 30;
                  if(arr[0].x == 0)
                  {
                              arr[0].x = 450;
                  }
     }
     else if(Huong == RIGHT)
     {
                  arr[0].x += 30;
                  if(arr[0].x == 480)
                  {
                              arr[0].x = 30;
                  }
     }
     else if(Huong == UP)
     {
                  arr[0].y -= 30;
                  if(arr[0].y == 0)
                  {
                              arr[0].y = 450;
                  }
     }
     else if(Huong == DOWN)
     {
                  arr[0].y += 30;
                  if(arr[0].y == 480)
                  {
                              arr[0].y = 30;
                  }
     }
     return 1;
}

int ConRan::getPosx()
{
    return arr[0].x;
}

int ConRan::getPosy()
{
    return arr[0].y;
}

int ConRan::getChieuDai()
{
    return ChieuDai;
}

                   

class food
{
private:
        POS foodPos;                    // Vi tri
public :
        void Ve();                    // Ve food
        void generate(int, int);        // Ham tao ra moi khi ran an
        bool CapNhat(int, int);          // Ham nay cho biet moi da bi an hay chua
};

void food::Ve()                       // Ve FOOD
{
     setcolor(RED);
     rectangle(foodPos.x, foodPos.y, foodPos.x+30, foodPos.y+30);
     setfillstyle(INTERLEAVE_FILL, RED);
     floodfill(foodPos.x+15, foodPos.y+15, RED);
}

void food::generate(int snakeHeadx, int snakeHeady)     // Tao vi tri moi cho moi
{
     srand(time(0));
     foodPos.x = 30*(rand()%15 + 1);
     srand(time(0));
     foodPos.y = 30*(rand()%15 + 1);
     if (foodPos.x == snakeHeadx && foodPos.y == snakeHeady)
          generate(snakeHeadx, snakeHeady);
}

bool food::CapNhat(int snakeHeadx, int snakeHeady)       // Cho biet trang thai cua moi
{
     if (foodPos.x == snakeHeadx && foodPos.y == snakeHeady)
          return true;
     else
          return false;
}
int main()
{
    initwindow(800,510,"SNAKE GAME");
    ConRan body;
    food fruit;
    int ChieuDai,count=0;
    bool playing=true;
    char ChieuDaiarr[3];
    fruit.generate(body.getPosx(), body.getPosy());
    int page=0;

    while(1)
    {
            setactivepage(page);
            setvisualpage(1-page);
            cleardevice();
            setcolor(BLUE);

            setfillstyle(SOLID_FILL, BLUE);


            if(GetAsyncKeyState(VK_LEFT))
            {    body.changeDirTo(LEFT);    }
            if(GetAsyncKeyState(VK_UP))
            {    body.changeDirTo(UP);      }
            if(GetAsyncKeyState(VK_RIGHT))
            {    body.changeDirTo(RIGHT);   }
            if(GetAsyncKeyState(VK_DOWN))
            {    body.changeDirTo(DOWN);    }
            if(GetAsyncKeyState(VK_ESCAPE))
                  break;

            if(playing==true && !body.CapNhat())
            {
                  playing = false;
            }
            body.VeRan();


            if(fruit.CapNhat(body.getPosx(), body.getPosy()))
            {
                 fruit.generate(body.getPosx(), body.getPosy());
                 body.appendSnake();
            }

            // Box
                 setcolor(BLUE);
                 rectangle(0,0,30,510);
                 rectangle(30,0,480,30);
                 rectangle(480,0,510,510);
                 rectangle(30,480,480,510);
                 rectangle(510,0,800,20);
                 rectangle(510,250,800,270);
                 rectangle(780,20,800,250);
                 rectangle(510,490,800,510);
                 rectangle(780,270,800,490);
                 setfillstyle(SOLID_FILL, BLUE);
                 floodfill(15,250,BLUE);
                 floodfill(250,15,BLUE);
                 floodfill(495,250,BLUE);
                 floodfill(250,495,BLUE);
                 floodfill(550,260,BLUE);
                 floodfill(550,10,BLUE);
                 floodfill(790,150,BLUE);
                 floodfill(550,500,BLUE);
                 floodfill(790,300,BLUE);

            // SCORE
                 settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 5);
                 setcolor(GREEN);
                 outtextxy(560, 70,"   DIEM  ");
                 outtextxy(520, 130, "   DAT DUOC");
                 ChieuDai = body.getChieuDai();
                 ChieuDaiarr[0]=char(48+ChieuDai/10);
                 ChieuDaiarr[1]=char(48+ChieuDai%10);
                 ChieuDaiarr[2]='\0';
                 outtextxy(620, 190, ChieuDaiarr);


            // STATUS
                 settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 4);
                 outtextxy(520, 300, "STATUS :-");
                 if (body.getChieuDai() == 30)
                 {
                      outtextxy(520, 350, "YOU WON !");
                      playing=false;
                 }
                 else if(playing)
                 {
                      outtextxy(520, 350, "PLAYING");
                 }
                 else
                 {
                      outtextxy(520, 350,"GAME OVER");
                 }
                 settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 2);
                 outtextxy(520,400,"PRESS 'ESC' to EXIT");

            fruit.Ve();
            page = 1-page;
            delay(100);
    }
    getch();
    closegraph();
}
