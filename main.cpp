#include <iostream>
#include <conio.h>
#include <windows.h>
d
using namespace std;

int CHIEURONG = 30;
int CHIEUCAO = 20;

class ConRan
{
private:
    bool ketThuc;
    int x, y, diem;
    int duoiX[100], duoiY[100];
    int soDuoi;
    int quaX,quaY;
    bool daanqua;
    enum Huong { STOP = 0, TRAI, PHAI, LEN, XUONG };
    Huong huong;

public:
    ConRan();
    void CaiDat();
    void Ve();
    void Nhap();
    void XuLy();
    bool Gameover();
};

ConRan::ConRan()
{
    ketThuc = false;
    huong = STOP;
    x = CHIEURONG / 2;
    y = CHIEUCAO / 2;
    diem = 0;
    soDuoi = 0;
    daanqua=true;
}

void ConRan::CaiDat()
{
    ketThuc = false;
    huong = STOP;
    x = CHIEURONG / 2;
    y = CHIEUCAO / 2;
    diem = 0;
    soDuoi = 0;
    daanqua=true;
}

void ConRan::Ve()
{
    system("cls");
    for (int i = 0; i < CHIEURONG + 2; i++)
        cout << "#";
    cout << endl;

    for (int i = 0; i < CHIEUCAO; i++)
    {
        for (int j = 0; j < CHIEURONG; j++)
        {
            if (j == 0)
                cout << "#";
            if (i == y && j == x)
                cout << "0";
            else if(i==quaY && j==quaX)
                cout<<"F";
            else
            {
                bool inDuoi = false;
                for (int k = 0; k < soDuoi; k++)
                {
                    if (duoiX[k] == j && duoiY[k] == i)
                    {
                        cout << "O";
                        inDuoi = true;
                    }
                }
                if (!inDuoi)
                    cout << " ";
            }

            if (j == CHIEURONG - 1)
                cout << "#";
        }
        cout << endl;
    }

    for (int i = 0; i < CHIEURONG + 2; i++)
        cout << "#";
    cout << endl;
    cout << "Diem: " << diem << endl;
}

void ConRan::Nhap()
{
    if (_kbhit())
    {
        switch (_getch())
        {
        case 'a':
            if (huong != PHAI)
                huong = TRAI;
            break;
        case 'd':
            if (huong != TRAI)
                huong = PHAI;
            break;
        case 'w':
            if (huong != XUONG)
                huong = LEN;
            break;
        case 's':
            if (huong != LEN)
                huong = XUONG;
            break;
        case 'x':
            ketThuc = true;
            break;
        }
    }
}

void ConRan::XuLy()
{
    int truocX = duoiX[0];
    int truocY = duoiY[0];
    int truoc2X, truoc2Y;
    duoiX[0] = x;
    duoiY[0] = y;
    for (int i = 1; i < soDuoi; i++)
    {
        truoc2X = duoiX[i];
        truoc2Y = duoiY[i];
        duoiX[i] = truocX;
        duoiY[i] = truocY;
        truocX = truoc2X;
        truocY = truoc2Y;
    }
    switch (huong)
    {
    case TRAI:
        x--;
        break;
    case PHAI:
        x++;
        break;
    case LEN:
        y--;
        break;
    case XUONG:
        y++;
        break;
    default:
        break;
    }
    if (x >= CHIEURONG || x < 0 || y >= CHIEUCAO || y < 0)
        ketThuc = true;

    for (int i = 0; i < soDuoi; i++)
        if (duoiX[i] == x && duoiY[i] == y)
            ketThuc = true;

    if (x == quaX && y == quaY) {
        diem += 10;
        soDuoi++;
        daanqua = true;
    }


    if (daanqua) {
        quaX = rand() % CHIEURONG;
        quaY = rand() % CHIEUCAO;
        daanqua = false;
    }
}
bool ConRan::Gameover()
{
    return ketThuc;
}

int main()
{
    ConRan conRan;
    conRan.CaiDat();
    while (!conRan.Gameover())
    {
        conRan.Ve();
        conRan.Nhap();
        conRan.XuLy();
        Sleep(85);
    }
    cout << "Game Over";
    return 0;
}
