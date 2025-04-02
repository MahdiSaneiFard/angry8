#include <iostream>
#include <thread>
#include <windows.h>
#include <vector>

using namespace std;

int score = 0;
int difficati;
int x_now = 14, y_now = 25;
vector<pair<int, int>> enemi_list;

void SetCursorPosition(int x, int y) {
    static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    std::cout.flush();
    COORD coord = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(hOut, coord);
}

void drawBorder() {
    for (int i = 5; i <= 26; ++i) {
        for (int j = 5; j <= 23; ++j) {
            if (i == 5 || i == 26 || j == 5 || j == 23) {
                SetCursorPosition(j, i);
                cout << '#';
            }
        }
    }
}

void enemi() {
    while (true) {
        Sleep(1500);
        int randLoc = (rand() % 16) + 6;
        enemi_list.push_back({ randLoc, 6 });
    }
}

void moveEnemi() {
    int randdr;
    while (true) {
        Sleep(700 - (difficati / 4));
        for (int i = 0; i < enemi_list.size(); i++) {
            randdr = (rand() % 2);
            SetCursorPosition(enemi_list[i].first, enemi_list[i].second);
            cout << ' ';
            enemi_list[i].second++;
            if (randdr == 0 && 22 != enemi_list[i].first && 6 != enemi_list[i].first) enemi_list[i].first++;
            else if (randdr == 1 && 22 != enemi_list[i].first && 6 != enemi_list[i].first) enemi_list[i].first--;
            else if (22 == enemi_list[i].first) enemi_list[i].first--;
            else if (6 == enemi_list[i].first) enemi_list[i].first++;
            if (enemi_list[i].second >= 26) {difficati = 6000; system("cls");  SetCursorPosition(10, 10); cout << "game over\n now you are all alown "; SetCursorPosition(0, 22); cout << "score is : " << score << endl; SetCursorPosition(0, 30); Sleep(5000); exit(0); }
            SetCursorPosition(enemi_list[i].first, enemi_list[i].second);
            if ((enemi_list[i].first == x_now && enemi_list[i].second == y_now + 1) || (enemi_list[i].first == x_now && enemi_list[i].second == y_now - 1) || (enemi_list[i].first == x_now + 1 && enemi_list[i].second == y_now) || (enemi_list[i].first == x_now - 1 && enemi_list[i].second == y_now))
            {enemi_list.erase(enemi_list.begin() + i);i--; score++; continue;}
            if (enemi_list[i].first == x_now && enemi_list[i].second == y_now) {difficati = 6000; system("cls"); SetCursorPosition(10, 10); cout << "game over \nnow you are all alown\n\t\ta wild 8 killed you"; SetCursorPosition(0, 22); SetCursorPosition(0, 22); cout <<"score is : " << score << endl; SetCursorPosition(0, 30);  Sleep(5000); exit(0); }
            cout << '8';
        }
    }
}

void work() {
    thread enemiMover(moveEnemi);
    while (true) {
        Sleep(difficati);
        if ((y_now > 6) && (GetAsyncKeyState('W') & 0x8000)) { if (difficati == 6000)continue; SetCursorPosition(x_now, y_now); cout << ' '; SetCursorPosition(x_now, --y_now); cout << '+'; }
        else if ((y_now < 25) && (GetAsyncKeyState('S') & 0x8000)) { if (difficati == 6000)continue; SetCursorPosition(x_now, y_now); cout << ' '; SetCursorPosition(x_now, ++y_now); cout << '+'; }
        else if ((x_now > 6) && (GetAsyncKeyState('A') & 0x8000)) { if (difficati == 6000)continue; SetCursorPosition(x_now, y_now); cout << ' '; SetCursorPosition(--x_now, y_now); cout << '+'; }
        else if ((x_now < 22) && (GetAsyncKeyState('D') & 0x8000)) { if (difficati == 6000)continue; SetCursorPosition(x_now, y_now); cout << ' '; SetCursorPosition(++x_now, y_now); cout << '+'; }
    }
    enemiMover.join();
}

int main() {
    system("cls");
    system("color 6");
    do {
    cout << "difficati : hard (1) , mediom (2) , esey (3)" << endl;
    cin >> difficati;
    system("cls");
    } while (difficati <= 0 || (float)difficati / 3 > 1);
    if (difficati == 3) { cout << "sike it was in reverce your game ganna run on hard mode "; Sleep(5000); system("cls"); }
    difficati = (difficati-1) * 100 + 200;
    SetCursorPosition(x_now, y_now); cout << '+';
    drawBorder();
    thread enemiSpawner(enemi);thread Worker(work);
    enemiSpawner.join();Worker.join();
    return 0;
}
