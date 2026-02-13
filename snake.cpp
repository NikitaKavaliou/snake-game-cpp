#include <iostream>
#include <vector>
#include <cstdlib>
#include <unistd.h>   // for usleep()
using namespace std;

const int width = 20;
const int height = 10;

int x, y;
int fruitX, fruitY;
int score;
vector<int> tailX;
vector<int> tailY;
int dir = 2; // start moving right

void clearScreen() {
    cout << "\033[2J\033[1;1H";
}

void setup() {
    x = width / 2;
    y = height / 2;
    fruitX = rand() % width;
    fruitY = rand() % height;
    score = 0;
}

void draw() {
    clearScreen();

    for (int i = 0; i < width + 2; i++) cout << "#";
    cout << "\n";

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {

            if (j == 0) cout << "#";

            if (i == y && j == x)
                cout << "O";
            else if (i == fruitY && j == fruitX)
                cout << "F";
            else {
                bool printed = false;
                for (int k = 0; k < tailX.size(); k++) {
                    if (tailX[k] == j && tailY[k] == i) {
                        cout << "o";
                        printed = true;
                        break;
                    }
                }
                if (!printed) cout << " ";
            }

            if (j == width - 1) cout << "#";
        }
        cout << "\n";
    }

    for (int i = 0; i < width + 2; i++) cout << "#";
    cout << "\n";

    cout << "Score: " << score << "\n";
    cout << "Enter direction (w/a/s/d) and press ENTER: ";
}

void logic() {
    if (!tailX.empty()) {
        for (int i = tailX.size() - 1; i > 0; i--) {
            tailX[i] = tailX[i - 1];
            tailY[i] = tailY[i - 1];
        }
        tailX[0] = x;
        tailY[0] = y;
    }

    if (dir == 1) x--;
    if (dir == 2) x++;
    if (dir == 3) y--;
    if (dir == 4) y++;

    if (x < 0 || x >= width || y < 0 || y >= height) {
        cout << "GAME OVER!\n";
        exit(0);
    }

    for (int i = 0; i < tailX.size(); i++) {
        if (tailX[i] == x && tailY[i] == y) {
            cout << "GAME OVER!\n";
            exit(0);
        }
    }

    if (x == fruitX && y == fruitY) {
        score += 10;
        fruitX = rand() % width;
        fruitY = rand() % height;
        tailX.push_back(x);
        tailY.push_back(y);
    }
}

int main() {
    setup();

    while (true) {
        draw();

        char c;
        cin >> c;

        if (c == 'a') dir = 1;
        if (c == 'd') dir = 2;
        if (c == 'w') dir = 3;
        if (c == 's') dir = 4;

        logic();
    }

    return 0;
}
