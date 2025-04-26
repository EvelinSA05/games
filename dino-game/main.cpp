#include <iostream>
#include <conio.h>
#include <windows.h>
#include <ctime>

#define dinoPos 2
#define hurdlePos 74

using namespace std;

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

int dinoY = 0;
int speed = 40;
int gameover = 0;

void gotoxy(int x, int y) {
    CursorPosition.X = x;
    CursorPosition.Y = y;
    SetConsoleCursorPosition(console, CursorPosition);
}

void setcursor(bool visible, DWORD size){
    if (size == 0) size = 20;
    CONSOLE_CURSOR_INFO lpCursor;
    lpCursor.bVisible = visible;
    lpCursor.dwSize = size;
    SetConsoleCursorInfo(console, &lpCursor);
}

void init() {
    system("cls");
    gameover = 0;
    gotoxy(3, 2); cout << "SCORE : ";
    for (int i = 0; i < 79; i++) {
        gotoxy(1 + i, 1); cout << "-";
        gotoxy(1 + i, 25); cout << "-";
    }
}

void moveDino(int jump = 0) {
    static int foot = 0;

    if (jump == 0)
        dinoY = 0;
    else if (jump == 2)
        dinoY--;
    else
        dinoY++;

    // Clear previous position
    for (int i = 0; i < 10; i++) {
        gotoxy(dinoPos, 15 + i - dinoY);
        cout << "                   ";
    }

    // Draw Dino
    gotoxy(dinoPos, 15 - dinoY); cout << "   ####   ";
    gotoxy(dinoPos, 16 - dinoY); cout << "  #    #  ";
    gotoxy(dinoPos, 17 - dinoY); cout << " # O  O # ";
    gotoxy(dinoPos, 18 - dinoY); cout << " #  --  # ";
    gotoxy(dinoPos, 19 - dinoY); cout << " # ---- # ";
    gotoxy(dinoPos, 20 - dinoY); cout << "  ######  ";
    gotoxy(dinoPos, 21 - dinoY); cout << "   #  #   ";
    gotoxy(dinoPos, 22 - dinoY); cout << "  ##  ##  ";

    if (jump == 1 || jump == 2) {
        gotoxy(dinoPos, 23 - dinoY); cout << "  #    #  ";
        gotoxy(dinoPos, 24 - dinoY); cout << " #      # ";
    } else if (foot == 0) {
        gotoxy(dinoPos, 23 - dinoY); cout << "  # ##    ";
        gotoxy(dinoPos, 24 - dinoY); cout << "    #     ";
        foot = !foot;
    } else {
        gotoxy(dinoPos, 23 - dinoY); cout << "    ## #  ";
        gotoxy(dinoPos, 24 - dinoY); cout << "     #    ";
        foot = !foot;
    }

    gotoxy(2, 25 - dinoY);
    if (jump == 0)
        cout << "===============";
    else
        cout << "               ";

    Sleep(speed);
}

void drawHurdle() {
    static int plantX = 0;
    static int score = 0;

    // Clear previous hurdle
    for (int i = 20; i <= 24; i++) {
        gotoxy(hurdlePos - plantX, i);
        cout << "     ";
    }

    // Collision check
    if (plantX == 56 && dinoY < 4) {
        score = 0;
        speed = 40;
        gotoxy(36, 8); cout << "Game Over";
        getch();
        gameover = 1;
    }

    // Draw hurdle
    gotoxy(hurdlePos - plantX, 20); cout << " || ";
    gotoxy(hurdlePos - plantX, 21); cout << " || ";
    gotoxy(hurdlePos - plantX, 22); cout << " || ";
    gotoxy(hurdlePos - plantX, 23); cout << " || ";
    gotoxy(hurdlePos - plantX, 24); cout << " || ";

    plantX++;

    if (plantX == 73) {
        plantX = 0;
        score++;
        gotoxy(11, 2); cout << "     ";
        gotoxy(11, 2); cout << score;
        if (speed > 20)
            speed--;
    }
}

void play() {
    system("cls");
    char ch;
    int i;
    init();
    while (true) {
        while (!kbhit()) {
            if (gameover == 1)
                return;
            moveDino();
            drawHurdle();
        }
        ch = getch();
        if (ch == 32) {
            i = 0;
            while (i < 12) {
                moveDino(1);
                drawHurdle();
                i++;
            }
            while (i > 0) {
                moveDino(2);
                drawHurdle();
                i--;
            }
        } else if (ch == 'p' || ch == 'P') {
            gotoxy(30, 10); cout << "** Dijeda - Tekan tombol apa saja untuk melanjutkan **";
            getch();
            gotoxy(30, 10); cout << "                                      ";
        } else if (ch == 27) {
            break;
        }
    }
}

void instructions() {
    system("cls");
    cout << "Instructions";
    cout << "\n----------------";
    cout << "\n1. Hindari rintangan dengan melompat";
    cout << "\n2. Tekan 'Spacebar' untuk melompat";
    cout << "\n3. Tekan 'P' untuk menghentikan permainan";
    cout << "\n4. Tekan 'Escape' untuk keluar dari permainan";
    cout << "\n\nTekan tombol apa saja untuk kembali ke menu";
    getch();
}

int main() {
    setcursor(0, 0);
    do {
        system("cls");
        gotoxy(10, 5); cout << " -------------------------- ";
        gotoxy(10, 6); cout << " |        DINO RUN        | ";
        gotoxy(10, 7); cout << " -------------------------- ";
        gotoxy(10, 9); cout << "1. Mulai Game";
        gotoxy(10, 10); cout << "2. Instruksi";
        gotoxy(10, 11); cout << "3. Keluar";
        gotoxy(10, 13); cout << "Pilih: ";
        char op = getche();

        if (op == '1') play();
        else if (op == '2') instructions();
        else if (op == '3') exit(0);

    } while (1);

    return 0;
}
