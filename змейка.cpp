#include <iostream>
#include <conio.h>
#include <cstdlib>
#include <ctime>
#include <vector>
#include<Windows.h>
#include<stralign.h>
#include<list>
#include <utility>

using namespace std;

const int WIDTH = 20;
const int HEIGHT = 20;
const char SNAKE_BODY = '&';
const char FOOD = '@';

enum Direction { UP, DOWN, LEFT, RIGHT };

class Snake {
private:
    vector<pair<int, int>> body;
    Direction dir;

public:
    Snake() {
        body.push_back(make_pair(WIDTH / 2, HEIGHT / 2));
        dir = RIGHT;
    }

    void moving() {
        pair<int, int> nextPos = body[0];

        switch (dir) {
        case UP:
            nextPos.second--;
            break;
        case DOWN:
            nextPos.second++;
            break;
        case LEFT:
            nextPos.first--;
            break;
        case RIGHT:
            nextPos.first++;
            break;
        }

        body.insert(body.begin(), nextPos);
        body.pop_back();
    }

    bool checkCollision() {
        pair<int, int> head = body[0];

        if (head.first < 0 || head.first >= WIDTH || head.second < 0 || head.second >= HEIGHT)
            return true;

        for (size_t i = 1; i < body.size(); ++i) {
            if (head == body[i])
                return true;
        }

        return false;
    }

    void setDirection(Direction newDir) {
        if (dir == UP && newDir == DOWN || dir == DOWN && newDir == UP ||
            dir == LEFT && newDir == RIGHT || dir == RIGHT && newDir == LEFT)
            return;

        dir = newDir;
    }

    void eatFood() {
        body.push_back(body.back());
    }

    vector<pair<int, int>> getBody() {
        return body;
    }
};

class Game {
private:
    Snake snake;
    pair<int, int> food;
    int score;
    string name;
    bool gameOver;

public:
    Game() {
        srand(time(nullptr));
        score = 0;
        spawnFood();
    }

    void setname(string name) {
        this->name = name;
    }

    void spawnFood() {
        food = make_pair(rand() % WIDTH, rand() % HEIGHT);
    }

    void board() {
        system("cls");

        vector<pair<int, int>> snakeBody = snake.getBody();

        for (int y = 0; y < HEIGHT; ++y) {
            for (int x = 0; x < WIDTH; ++x) {
                if (x == food.first && y == food.second)
                    cout << FOOD;
                else {
                    bool isSnakeBody = false;
                    for (const auto& part : snakeBody) {
                        if (x == part.first && y == part.second) {
                            cout << SNAKE_BODY;
                            isSnakeBody = true;
                            break;
                        }
                    }
                    if (!isSnakeBody)
                        cout << ' ';
                }
            }
            cout << endl;
        }

        cout << "Конфеток: " << score << endl;
    }

    void update() {
        snake.moving();

        if (snake.checkCollision()) {
            gameOver = true;

        }

        if (snake.getBody()[0] == food) {
            snake.eatFood();
            spawnFood();
            score++;
        }
    }

    void klavisha() {
        if (_kbhit()) {
            switch (_getch()) {
            case 'w':
                snake.setDirection(UP);
                break;
            case 's':
                snake.setDirection(DOWN);
                break;
            case 'a':
                snake.setDirection(LEFT);
                break;
            case 'd':
                snake.setDirection(RIGHT);
                break;
            case 'q':
                gameOver = true;
            }
        }
    }

    void run() {
        while (true) {
            board();
            klavisha();
            update();
            if (gameOver) { 
                cout << "Проиграли! Конфеток съедено: " << score << endl;
                system("cls");
                break; 
            }
            Sleep(100);
        }
    }

};

int main() {
    setlocale(LC_ALL, "RUS");
    string userName;
    int action;
    bool isRun = false;
    char key;

    Game game;

    cout << "Введите имя:" << endl;
    cin >> userName;
    system("cls");
    game.setname(userName);
    while (!isRun) {
        cout << "1. Начать игру\n" << "2. Выйти из игры" << endl;
        cin >> action;

        switch (action)
        {
        case 1:
            game.run();
            break;
        case 2:
            isRun = true;
            break;
        default:
            break;
        }
    }
    return 0;
}