#include <iostream>
#include <conio.h>
#include <windows.h>
#include <ctime>
#include <cstdlib>
#include <graphics.h>
using namespace std;

enum HUONG { TRAI, LEN, PHAI, XUONG };

struct VI_TRI
{
    int x, y;
};

class ConRan
{
private:
    VI_TRI mang[31];
    int Huong;
    int ChieuDai;

public:
    ConRan()
    {
        mang[0].x = 30;
        mang[0].y = 30;
        ChieuDai = 1;
        Huong = PHAI;
    }
    void VeRan();
    void ThemPhan();  // Hàm giúp tăng chiều dài con rắn không vượt quá 30
    void DoiHuongToi(int);
    int CapNhat();
    int LayToaDoX();
    int LayToaDoY();
    int LayChieuDai();
};

void ConRan::VeRan()         // Vẽ Rắn
{
    for (int i = 0; i < ChieuDai; i++)
    {
        setcolor(BLUE);
        rectangle(mang[i].x, mang[i].y, mang[i].x + 30, mang[i].y + 30);
        if (i == 0)                                      // Làm màu cho Phần Đầu
            setfillstyle(SOLID_FILL, WHITE);
        else                                          // Làm màu cho Phần Đuôi
            setfillstyle(SOLID_FILL, BROWN);
        floodfill(mang[i].x + 15, mang[i].y + 15, BLUE);
    }
}


void ConRan::ThemPhan()
{
    if (ChieuDai < 30)
        ChieuDai++;
}

void ConRan::DoiHuongToi(int huongmoi)
{
    if ((Huong == TRAI || Huong == PHAI) && (huongmoi == LEN || huongmoi == XUONG))
        Huong = huongmoi;
    else if ((Huong == LEN || Huong == XUONG) && (huongmoi == TRAI || huongmoi == PHAI))
        Huong = huongmoi;
}

int ConRan::CapNhat()                                                     // Các chức năng cơ bản
{                                                                         // Thuật toán di chuyển Rắn
    for (int i = 1; i < ChieuDai; ++i)                                      // Cung cấp tất cả các phần trước
    {
        if (mang[0].x == mang[i].x && mang[0].y == mang[i].y)
        {
            return 0;
        }
    }
    for (int i = ChieuDai; i >= 0; --i)
    {
        if (i == 0)
        {
            mang[1].x = mang[0].x;
            mang[1].y = mang[0].y;
        }
        else
        {
            mang[i].x = mang[i - 1].x;
            mang[i].y = mang[i - 1].y;
        }
    }
    if (Huong == TRAI)
    {
        mang[0].x -= 30;
        if (mang[0].x == 0)
        {
            mang[0].x = 450;
        }
    }
    else if (Huong == PHAI)
    {
        mang[0].x += 30;
        if (mang[0].x == 480)
        {
            mang[0].x = 30;
        }
    }
    else if (Huong == LEN)
    {
        mang[0].y -= 30;
        if (mang[0].y == 0)
        {
            mang[0].y = 450;
        }
    }
    else if (Huong == XUONG)
    {
        mang[0].y += 30;
        if (mang[0].y == 480)
        {
            mang[0].y = 30;
        }
    }
    return 1;
}

int ConRan::LayToaDoX()
{
    return mang[0].x;
}

int ConRan::LayToaDoY()
{
    return mang[0].y;
}

int ConRan::LayChieuDai()
{
    return ChieuDai;
}

class ThucAn
{
private:
    VI_TRI viTriThucAn;
public:
    void TaoViTri();
    bool CapNhat(int, int);
    void Ve();
};

void ThucAn::TaoViTri()
{
    srand(time(0));
    viTriThucAn.x = 30 * (rand() % 15 + 1);
    srand(time(0));
    viTriThucAn.y = 30 * (rand() % 15 + 1);
}

bool ThucAn::CapNhat(int x, int y)
{
    if (viTriThucAn.x == x && viTriThucAn.y == y)
    {
        return true; // Con rắn ăn được thức ăn
    }
    return false;
}

void ThucAn::Ve()                       // Vẽ THỨC ĂN
{
    setcolor(RED);
    rectangle(viTriThucAn.x, viTriThucAn.y, viTriThucAn.x + 30, viTriThucAn.y + 30);
    setfillstyle(INTERLEAVE_FILL, RED);
    floodfill(viTriThucAn.x + 15, viTriThucAn.y + 15, RED);
}


int main()
{
    initwindow(800, 510, "SNAKE GAME");
    ConRan than;
    ThucAn qua;
    int ChieuDai, dem = 0;
    bool choi = true;
    char chuoiChieuDai[3];
    qua.TaoViTri();
    int page = 0;
     while (1)
    {
        setactivepage(page);
        setvisualpage(1 - page);
        cleardevice();
        setcolor(BLUE);

        setfillstyle(SOLID_FILL, BLUE);


        if (GetAsyncKeyState(VK_LEFT))
        {
            than.DoiHuongToi(TRAI);
        }
        if (GetAsyncKeyState(VK_UP))
        {
            than.DoiHuongToi(LEN);
        }
        if (GetAsyncKeyState(VK_RIGHT))
        {
            than.DoiHuongToi(PHAI);
        }
        if (GetAsyncKeyState(VK_DOWN))
        {
            than.DoiHuongToi(XUONG);
        }
        if (GetAsyncKeyState(VK_ESCAPE))
            break;

        if (choi == true && !than.CapNhat())
        {
            choi = false;
        }
        than.VeRan();


        if (qua.CapNhat(than.LayToaDoX(), than.LayToaDoY()))
        {
            qua.TaoViTri();
            than.ThemPhan();
        }

        // Khung
       setcolor(GREEN);
rectangle(0, 0, 30, 510);
rectangle(30, 0, 480, 30);
rectangle(480, 0, 510, 510);
rectangle(30, 480, 480, 510);
rectangle(510, 0, 800, 20);
rectangle(510, 250, 800, 270);
rectangle(780, 20, 800, 250);
rectangle(510, 490, 800, 510);
rectangle(780, 270, 800, 490);
setfillstyle(SOLID_FILL, GREEN);
floodfill(15, 250, GREEN);
floodfill(250, 15, GREEN);
floodfill(495, 250, GREEN);
floodfill(250, 495, GREEN);
floodfill(550, 260, GREEN);
floodfill(550, 10, GREEN);
floodfill(790, 150, GREEN);
floodfill(550, 500, GREEN);
floodfill(790, 300, GREEN);

        // ĐIỂM
        settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 3);
        setcolor(YELLOW);
        outtextxy(515, 70,"DIEM:");
        ChieuDai = than.LayChieuDai();
        chuoiChieuDai[0] = char(48 + ChieuDai / 10);
        chuoiChieuDai[1] = char(48 + ChieuDai % 10);
        chuoiChieuDai[2] = '\0';
        outtextxy(580, 70, chuoiChieuDai);
        settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 1);
				 setcolor(RED);
				 outtextxy(515, 110,"NGUYEN GIA BAO-23520121");
				 outtextxy(515, 130,"LE KY DUYEN-23520690");
				 outtextxy(515, 150,"LE NGUYEN MINH KHANG-");
				 outtextxy(515, 170,"23520400");

        // TÌNH TRẠNG
        settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 2);
                 setcolor(BLUE);
                 outtextxy(520, 300, "STATUS :-");
                 if (than.LayChieuDai() == 30)
                 {
                      outtextxy(520, 350, "YOU WON !");
                	choi=false;
                 }
                 else if(choi)
                 {
                      outtextxy(520, 350, "PLAYING");
                 }
                 else
                 {
                      outtextxy(520, 350,"GAME OVER");
                 }
                 settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 2);
                 outtextxy(520,400,"NHAN 'ESC' DE THOAT");
        qua.Ve();
        page = 1 - page;
        delay(100);
    }
    getch();
    closegraph();
}
