#include<iostream>
#include<conio.h>
#include<windows.h>
#include<ctime>

#define SCREEN_WIDTH 90
#define SCREEN_HEIGHT 26
#define WIN_WIDTH 70

using namespace std;

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

int enemyY[3];
int enemyX[3];
int enemyFlag[3];
char car[4][4] = {
    ' ', '_', '_', ' ',
    '|', '_', '_', '|',
    ' ', 'O', 'O', ' ',
    ' ', ' ', ' ', ' '
};

int carPos = WIN_WIDTH / 2;
int score = 0;

void gotoxy(int x, int y) {
    CursorPosition.X = x;
    CursorPosition.Y = y;
    SetConsoleCursorPosition(console, CursorPosition);
}

void setcursor(bool visible, DWORD size) {
    if (size == 0)
        size = 20;
    CONSOLE_CURSOR_INFO lpCursor;
    lpCursor.bVisible = visible;
    lpCursor.dwSize = size;
    SetConsoleCursorInfo(console, &lpCursor);
}

void drawBorder() {
    for (int i = 0; i < SCREEN_HEIGHT; i++) {
        gotoxy(0, i); cout << "|";
        gotoxy(WIN_WIDTH, i); cout << "|";
    }
    for (int i = 0; i < SCREEN_HEIGHT; i++) {
        gotoxy(SCREEN_WIDTH, i); cout << "|";
    }
}

void genEnemy(int ind) {
    enemyX[ind] = 18 + rand() % (WIN_WIDTH - 24);
}

void drawEnemy(int ind) {
    if (enemyFlag[ind] == true) {
        gotoxy(enemyX[ind], enemyY[ind]);     cout << "****";
        gotoxy(enemyX[ind], enemyY[ind] + 1); cout << " ** ";
        gotoxy(enemyX[ind], enemyY[ind] + 2); cout << "****";
        gotoxy(enemyX[ind], enemyY[ind] + 3); cout << " ** ";
    }
}

void eraseEnemy(int ind) {
    if (enemyFlag[ind] == true) {
        for (int i = 0; i < 4; i++) {
            gotoxy(enemyX[ind], enemyY[ind] + i); cout << "    ";
        }
    }
}

void resetEnemy(int ind) {
    eraseEnemy(ind);
    enemyY[ind] = 1;
    genEnemy(ind);
}

void drawCar() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            gotoxy(j + carPos, i + 22); cout << car[i][j];
        }
    }
}

void eraseCar() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            gotoxy(j + carPos, i + 22); cout << " ";
        }
    }
}

int collision() {
    for (int i = 0; i < 3; i++) {
        if (enemyFlag[i] == true && enemyY[i] + 4 >= 22) {
            if ((enemyX[i] >= carPos && enemyX[i] < carPos + 4) ||
                (enemyX[i] + 3 >= carPos && enemyX[i] + 3 < carPos + 4)) {
                return 1;
            }
        }
    }
    return 0;
}

void gameover() {
    system("cls");
    cout << endl;
    cout << "\t\t--------------------------" << endl;
    cout << "\t\t-------- Game Over -------" << endl;
    cout << "\t\t--------------------------" << endl << endl;
    cout << "\t\tTekan tombol apa saja untuk kembali ke menu.";
    getch();
}

void updateScore() {
    gotoxy(WIN_WIDTH + 7, 5); cout << "Skor: " << score;
}

void instructions() {
    system("cls");
    cout << "Instruksi";
    cout << "\n----------------";
    cout << "\n Hindari dengan bergerak ke kiri atau kanan. ";
    cout << "\n\n Tekan 'a' untuk pindah ke kiri";
    cout << "\n Tekan 'd' untuk pindah ke kanan";
    cout << "\n Tekan 'escape' untuk keluar";
    cout << "\n\nTekan tombol apa saja untuk kembali ke menu";
    getch();
}

void play() {
    carPos = WIN_WIDTH / 2;
    score = 0;
    enemyFlag[0] = 1;
    enemyFlag[1] = 0;
    enemyY[0] = enemyY[1] = 1;

    int speed = 50;
    system("cls");
    drawBorder();
    updateScore();
    genEnemy(0);
    genEnemy(1);

    gotoxy(WIN_WIDTH + 7, 2); cout << "Car Game";
    gotoxy(WIN_WIDTH + 6, 4); cout << "----------";
    gotoxy(WIN_WIDTH + 6, 6); cout << "----------";
    gotoxy(WIN_WIDTH + 7, 12); cout << "Kontrol ";
    gotoxy(WIN_WIDTH + 7, 13); cout << "-------- ";
    gotoxy(WIN_WIDTH + 2, 14); cout << " A Tombol - Kiri";
    gotoxy(WIN_WIDTH + 2, 15); cout << " D Tombol - Kanan";

    gotoxy(18, 5); cout << "Tekan tombol apa saja untuk memulai";
    getch();
    gotoxy(18, 5); cout << "                      ";

    while (1) {
        if (kbhit()) {
            char ch = getch();
            if (ch == 'a' || ch == 'A') {
                if (carPos > 18)
                    carPos -= 4;
            }
            if (ch == 'd' || ch == 'D') {
                if (carPos < WIN_WIDTH - 5)
                    carPos += 4;
            }
            if (ch == 27) {
                break;
            }
        }

        drawCar();
        drawEnemy(0);
        drawEnemy(1);
        if (collision() == 1) {
            gameover();
            return;
        }

        Sleep(speed);
        eraseCar();
        eraseEnemy(0);
        eraseEnemy(1);

        if (enemyY[0] == 10 && enemyFlag[1] == 0)
            enemyFlag[1] = 1;

        if (enemyFlag[0] == 1)
            enemyY[0] += 1;
        if (enemyFlag[1] == 1)
            enemyY[1] += 1;

        if (enemyY[0] > SCREEN_HEIGHT - 4) {
            resetEnemy(0);
            score++;
            updateScore();
            if (speed > 25) speed -= 1; // Jangan terlalu cepat
        }

        if (enemyY[1] > SCREEN_HEIGHT - 4) {
            resetEnemy(1);
            score++;
            updateScore();
            if (speed > 25) speed -= 1;
        }
    }
}

int main() {
    setcursor(0, 0);
    srand((unsigned)time(NULL));

    do {
        system("cls");
        gotoxy(10, 5); cout << " -------------------------- ";
        gotoxy(10, 6); cout << " |        Car Game        | ";
        gotoxy(10, 7); cout << " -------------------------- ";
        gotoxy(10, 9); cout << "1. Mulai Game";
        gotoxy(10, 10); cout << "2. Instruksi";
        gotoxy(10, 11); cout << "3. Keluar";
        gotoxy(10, 13); cout << "Pilih : ";
        char op = getche();

        if (op == '1') play();
        else if (op == '2') instructions();
        else if (op == '3') exit(0);

    } while (1);

    return 0;
}
