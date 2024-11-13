// snake_game.cpp
#include <iostream>
#include <conio.h> // For _kbhit() and _getch()
#include <windows.h> // For Sleep()
#include <ctime> // For srand() and rand()
#include <vector>

using namespace std;

class Point {
public:
    int x, y;
    Point(int x = 0, int y = 0) : x(x), y(y) {}
};

class SnakeGame {
private:
    bool gameOver;
    const int width = 20;
    const int height = 20;
    Point head;
    Point food;
    vector<Point> tail;
    int score;
    enum Direction { STOP = 0, LEFT, RIGHT, UP, DOWN };
    Direction dir;

    void GenerateFood() {
        food.x = rand() % width;
        food.y = rand() % height;
    }

    void Draw() {
        system("cls"); // Clear the screen

        for (int i = 0; i < width + 2; i++) cout << "#";
        cout << endl;

        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                if (j == 0) cout << "#";
                if (i == head.y && j == head.x) cout << "O";
                else if (i == food.y && j == food.x) cout << "F";
                else {
                    bool print = false;
                    for (auto segment : tail) {
                        if (segment.x == j && segment.y == i) {
                            cout << "o";
                            print = true;
                        }
                    }
                    if (!print) cout << " ";
                }
                if (j == width - 1) cout << "#";
            }
            cout << endl;
        }

        for (int i = 0; i < width + 2; i++) cout << "#";
        cout << endl;

        cout << "Score: " << score << endl;
    }

    void Input() {
        if (_kbhit()) {
            switch (_getch()) {
            case 'a': dir = LEFT; break;
            case 'd': dir = RIGHT; break;
            case 'w': dir = UP; break;
            case 's': dir = DOWN; break;
            case 'x': gameOver = true; break;
            }
        }
    }

    void Update() {
        Point prev = head;
        Point prev2;

        if (!tail.empty()) {
            prev2 = tail[0];
            tail[0] = prev;
        }

        for (int i = 1; i < tail.size(); i++) {
            prev = tail[i];
            tail[i] = prev2;
            prev2 = prev;
        }

        switch (dir) {
        case LEFT: head.x--; break;
        case RIGHT: head.x++; break;
        case UP: head.y--; break;
        case DOWN: head.y++; break;
        default: break;
        }

        // Wall collision detection
        if (head.x >= width) head.x = 0; else if (head.x < 0) head.x = width - 1;
        if (head.y >= height) head.y = 0; else if (head.y < 0) head.y = height - 1;

        // Self-collision detection
        for (auto segment : tail)
            if (segment.x == head.x && segment.y == head.y)
                gameOver = true;

        // Eating food
        if (head.x == food.x && head.y == food.y) {
            score += 10;
            GenerateFood();
            tail.push_back(Point());
        }
    }

public:
    SnakeGame() : gameOver(false), score(0), dir(STOP) {
        head.x = width / 2;
        head.y = height / 2;
        srand(static_cast<unsigned>(time(0)));
        GenerateFood();
    }

    void Run() {
        while (!gameOver) {
            Draw();
            Input();
            Update();
            Sleep(100); // Control game speed
        }
    }
};

int main() {
    SnakeGame game;
    game.Run();
    return 0;
}
