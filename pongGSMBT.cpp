#include <iostream>
#include <conio.h>
#include <thread>
#include <chrono>

const int screen_width = 40;
const int screen_height = 20;

struct GameState {
    int ballX, ballY;
    int ballDirectionX, ballDirectionY;
    int paddle1Y, paddle2Y;
    int score1, score2;
};

struct Node {
    GameState state;
    Node* left;  
    Node* right; 
    Node(const GameState& s) : state(s), left(nullptr), right(nullptr) {}
};

int ballX = screen_width / 2;
int ballY = screen_height / 2;
int ballDirectionX = -1;
int ballDirectionY = -1;

int paddle1Y = screen_height / 2;
int paddle2Y = screen_height / 2;
const int paddleHeight = 4;
const int paddleWidth = 1;

int score1 = 0, score2 = 0;

Node* currentState = new Node({
    ballX, ballY,
    ballDirectionX, ballDirectionY,
    paddle1Y, paddle2Y,
    score1, score2
    });

void Draw() {
    system("cls");
    GameState& s = currentState->state;

    for (int i = 0; i < screen_width + 2; i++) std::cout << "-";
    std::cout << std::endl;

    for (int i = 0; i < screen_height; i++) {
        for (int j = 0; j < screen_width; j++) {
            if (j == 0 || j == screen_width - 1) std::cout << "|";
            else if (j == s.ballX && i == s.ballY) std::cout << "O";
            else if (j == 1 && i >= s.paddle1Y && i < s.paddle1Y + paddleHeight) std::cout << "#";
            else if (j == screen_width - 2 && i >= s.paddle2Y && i < s.paddle2Y + paddleHeight) std::cout << "#";
            else std::cout << " ";
        }
        std::cout << std::endl;
    }

    for (int i = 0; i < screen_width + 2; i++) std::cout << "-";
    std::cout << std::endl;
    std::cout << "Score 1: " << s.score1 << " Score 2: " << s.score2 << std::endl;
}

void Input() {
    if (_kbhit()) {
        char current = _getch();
        if (current == 'w' && currentState->state.paddle1Y > 0) currentState->state.paddle1Y--;
        if (current == 's' && currentState->state.paddle1Y < screen_height - paddleHeight) currentState->state.paddle1Y++;
        if (current == 'i' && currentState->state.paddle2Y > 0) currentState->state.paddle2Y--;
        if (current == 'k' && currentState->state.paddle2Y < screen_height - paddleHeight) currentState->state.paddle2Y++;
    }
}

void Logic() {
    GameState& s = currentState->state;
    s.ballX += s.ballDirectionX;
    s.ballY += s.ballDirectionY;

    if (s.ballY <= 0 || s.ballY >= screen_height - 1) s.ballDirectionY *= -1;
    if (s.ballX == 1 && s.ballY >= s.paddle1Y && s.ballY < s.paddle1Y + paddleHeight ||
        s.ballX == screen_width - 2 && s.ballY >= s.paddle2Y && s.ballY < s.paddle2Y + paddleHeight) s.ballDirectionX *= -1;

    if (s.ballX == 0) {
        s.score2++;
        s.ballX = screen_width / 2;
        s.ballY = screen_height / 2;
        s.ballDirectionX = 1;
    }

    if (s.ballX == screen_width - 1) {
        s.score1++;
        s.ballX = screen_width / 2;
        s.ballY = screen_height / 2;
        s.ballDirectionX = -1;
    }

    GameState newState = {
        s.ballX, s.ballY,
        s.ballDirectionX, s.ballDirectionY,
        s.paddle1Y, s.paddle2Y,
        s.score1, s.score2
    };

    Node* newNode = new Node(newState);
    if (s.ballDirectionX == -1) {
        currentState->left = newNode;
    }
    else {
        currentState->right = newNode;
    }

    currentState = newNode;
}

int main() {
    while (true) {
        Draw();
        Input();
        Logic();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    return 0;
}
