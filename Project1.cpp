#include "pch.h"
#include <iostream>
#include<ctime>
#include<cstdlib>
using namespace std;
#include<conio.h>
#include<Windows.h>
//Basic Snake game in C++

bool gameover;
const int width = 40;
const int height = 20;
int x=0, y=0, fx=0, fy=0, score = 0;
int tailx[100], taily[100];
int ntail=0;
enum direction {
	STOP = 0, LEFT, RIGHT, UP, DOWN
};
direction dir;
void setup()
{
	gameover = false;
	dir = STOP;
	x = width / 2;
	y = height / 2;
	srand(time(0));
	fx = rand() % width;
	fy = rand() % height;
	score = 0;

}
void draw()
{
	system("cls");
	for (int i = 0; i < width + 2; i++)
	{
		cout << "#";
	}
	cout << endl;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (j == 0)
				cout << "#";
			if (i == y && j == x)
				cout << "O";
			else if (i == fy && j == fx)
				cout << "F";
			else
			{
				bool print = false;
				for (int k = 0; k < ntail; k++)
				{
					if (taily[k] == i && tailx[k] == j)
					{
						cout << "o";
						print = true;
					}
				}
				if (!print)
				{
					cout << " ";
				}
			}
			
			if (j == width - 1)
				cout << "#";
		}
		cout << endl;
	}
	for (int i = 0; i < width + 2; i++)
	{
		cout << "#";
	}
	cout << endl;

}
void input()
{
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'a':
			dir =LEFT;
			break;
		case 's':
			dir = DOWN;
			break;
		case 'w':
			dir = UP;
			break;
		case 'd':
			dir = RIGHT;
			break;
		case 'x':
			gameover = true;
		}
	}
}
void logic()
{
	int tx = tailx[0];
	int ty = taily[0];
	int px, py;
	tailx[0] = x;
	taily[0] = y;
	for (int i = 1; i < ntail; i++)
	{
		px = tailx[i];
		py = taily[i];
		tailx[i] = tx;
		taily[i] = ty;
		tx = px;
		ty = py;
	}
	switch (dir)
	{
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

	default:
		break;
	}
	//cout << x << y << fx << fy << endl;
	if (x >= width) x = 0; else if (x < 0) x = width - 1;
	if (y >= height) y = 0; else if (y < 0) y = height - 1;

	for (int i = 0; i < ntail; i++)
		if (tailx[i] == x && taily[i] == y)
			gameover = true;
	if (fx == x && fy == y)
	{
		ntail++;
		score += 10;
		fx = rand() % width;
		fy = rand() % height;
	}
	//if (x > width || x < 0 || y > height || y < 0)
		//gameover = true;
	
}
int main()
{
	setup();
	while (!gameover)
	{
		draw();
		input();
		logic();
		Sleep(100);
		cout << "Score:" << score;
	}
}