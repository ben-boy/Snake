#include <iostream>
#include <conio.h>
#include <Windows.h>

using namespace std;

bool gameOver;
const int width = 20;
const int height = 20;
int x, y, fruitX, fruitY, score;
enum eDirection { STOP = 0, UP, DOWN, LEFT, RIGHT };
eDirection dir;

int tailX[100], tailY[100];
int tailLen = 2;

int gameSleepTime = 10; //time between game updates - in ms (this is probably terrible)

bool debug = false;


void Setup() {
	gameOver = false;
	dir = STOP;
	x = width / 2;
	y = height / 2;
	score = 0;
	fruitX = rand() % width;
	fruitY = rand() % height;
}

void Draw() {
	system("cls");
	for (int i = 0; i < width; i++) {
		cout << "#";
	}
	cout << endl;

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (j == 0 || j == width-1) {
				cout << "#";
			}
			else if (i == fruitY && j == fruitX) {
				cout << "f";
			}
			else if (i == y && j == x) {
				cout << "O";
			}
			else {
				bool print = false;
				for (int k = 0; k < tailLen; k++) {
					if (tailX[k] == j && tailY[k] == i) {
						print = true;
						cout << "o";
					}
				}
				if(!print)
					cout << " ";
			}
		}
		cout << endl;
	}

	for (int i = 0; i < width; i++) {
		cout << "#";
	}
	cout << endl;
	cout << "SCORE=" << score;
	cout << endl;
	if (debug == true) {
		cout << "X=" << x;
		cout << " Y=" << y;
		cout << endl;
		cout << "TAIL LENGTH=" << tailLen;
	}
}

void Input() {
	if (_kbhit()) {
		switch (_getch()) {
		case 'w':
			dir = UP;
			break;
		case 's':
			dir = DOWN;
			break;
		case 'a':
			dir = LEFT;
			break;
		case 'd':
			dir = RIGHT;
			break;
		case 'x':
			gameOver = true;
			break;
		}
	}
}

void Logic() {
	int prevX = tailX[0];
	int prevY = tailY[0];
	int prev2x, prev2y;
	tailX[0] = x;
	tailY[0] = y;
	for (int i = 1; i < tailLen; i++) {
		prev2x = tailX[i];
		prev2y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevY = prev2y;
		prevX = prev2x;
	}
	
	switch (dir) {
	case LEFT:
		x--;
		break;
	case RIGHT:
		x++;
		break;
	case UP:
		y--;
		break;
	case DOWN:
		y++;
		break;
	}
	if (x == 0 || x == width) {
		gameOver = true;
	}
	if (y == -2 || y == height) {
		gameOver = true;
	}
	if (x == fruitX && y == fruitY) {
		fruitX = rand() % width;
		fruitY = rand() % height;
		score++;
		tailLen++;
	}
}

int main() {
	Setup();
	while (true) { //this is bad practise but i don't care
		while (!gameOver) {
			Draw();
			Input();
			Logic();
			Sleep(gameSleepTime);
		}
		system("cls");
		cout << "GAME OVER";
		cout << endl;
		cout << "final score = " << score;
		cout << endl;
		cout << "PRESS ANY KEY TO EXIT";
		if (_kbhit()) {
			break;
		}
 	}
	return 0;
}
