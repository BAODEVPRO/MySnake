#include <iostream>
#include <conio.h>
#include <windows.h>
#include <ctime>
#include <cstdlib>

using namespace std;

const int ROWS = 20;
const int COLS = 40;

enum HUONG { TRAI, LEN, PHAI, XUONG };

struct VI_TRI
{
    int x, y;
};

class ConRan
{
private:
    VI_TRI mang[ROWS * COLS];
    int Huong;
    int ChieuDai;

public:
    ConRan()
    {
        mang[0].x = 10;
        mang[0].y = 10;
        ChieuDai = 1;
        Huong = PHAI;
    }
    void VeRan();
    void ThemPhan();
    void DoiHuongToi(int);
    int CapNhat();
    int LayToaDoX();
    int LayToaDoY();
    int LayChieuDai();
};

void ConRan::VeRan()
{
    system("cls");
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            bool coThan = false;
            for (int k = 0; k < ChieuDai; k++)
            {
                if (mang[k].x == j && mang[k].y == i)
                {
                    cout << "O";
                    coThan = true;
                    break;
                }
            }
            if (!coThan)
                cout << " ";
        }
        cout << endl;
    }
}

void ConRan::ThemPhan()
{
    if (ChieuDai < ROWS* COLS)
        ChieuDai++;
}

void ConRan::DoiHuongToi(int huongmoi)
{
    if ((Huong == TRAI || Huong == PHAI) && (huongmoi == LEN || huongmoi == XUONG))
        Huong = huongmoi;
    else if ((Huong == LEN || Huong == XUONG) && (huongmoi == TRAI || huongmoi == PHAI))
        Huong = huongmoi;
}

int ConRan::CapNhat()
{
    for (int i = ChieuDai - 1; i > 0; i--)
    {
        mang[i] = mang[i - 1];
    }

    if (Huong == TRAI)
    {
        mang[0].x -= 1;
        if (mang[0].x < 0)
            mang[0].x = COLS - 1;
    }
    else if (Huong == PHAI)
    {
        mang[0].x += 1;
        if (mang[0].x >= COLS)
            mang[0].x = 0;
    }
    else if (Huong == LEN)
    {
        mang[0].y -= 1;
        if (mang[0].y < 0)
            mang[0].y = ROWS - 1;
    }
    else if (Huong == XUONG)
    {
        mang[0].y += 1;
        if (mang[0].y >= ROWS)
            mang[0].y = 0;
    }

    for (int i = 1; i < ChieuDai; i++)
    {
        if (mang[0].x == mang[i].x && mang[0].y == mang[i].y)
            return 0; // Con rắn đụng vào thân, kết thúc trò chơi
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
    viTriThucAn.x = rand() % COLS;
    viTriThucAn.y = rand() % ROWS;
}

bool ThucAn::CapNhat(int x, int y)
{
    if (viTriThucAn.x == x && viTriThucAn.y == y)
    {
        return true; // Con rắn ăn được thức ăn
    }
    return false;
}

void ThucAn::Ve()
{
    COORD pos = { viTriThucAn.x, viTriThucAn.y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
    cout << "X";
}

int main()
{
    ConRan than;
    ThucAn qua;
    bool choi = true;

    qua.TaoViTri();

    while (choi)
    {
        than.VeRan();
        qua.Ve();

        if (_kbhit())
        {
            char key = _getch();
            switch (key)
            {
            case 'a':
                than.DoiHuongToi(TRAI);
                break;
            case 'w':
                than.DoiHuongToi(LEN);
                break;
            case 'd':
                than.DoiHuongToi(PHAI);
                break;
            case 's':
                than.DoiHuongToi(XUONG);
                break;
            case 'q':
                choi = false;
                break;
            }
        }

        if (!than.CapNhat())
        {
            choi = false;
        }

        if (qua.CapNhat(than.LayToaDoX(), than.LayToaDoY()))
        {
            qua.TaoViTri();
            than.ThemPhan();
        }

        if (than.LayChieuDai() == ROWS * COLS)
        {
            cout << "Ban da chien thang!" << endl;
            choi = false;
        }
        Sleep(100);
    }

    return 0;
}
