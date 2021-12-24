#pragma once
#include <iostream>
#include <conio.h> 
#include <windows.h>
#include <stdio.h>
#include <cstdlib>
#include <time.h>
#include <conio.h>

using namespace std;

HANDLE hConsole;


bool gameOver;
const int width = 20; //������ ����
const int height = 20; //������ ����
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100]; //������
int nTail;
enum Edirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
Edirection dir;

//void setColor(int background, int text)
//{
//	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
//	SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
//}



void gotoxy(int x, int y)
{
	COORD p = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), p);
}

void showLogo()
{
	gotoxy(50, 15);
	cout << "S N A K E" << endl;
	Sleep(1200);
}

void showLose()
{
	gotoxy(50, 15);
	cout << "You lose!" << endl;
	Sleep(1000);
}

void showMenu() {
	/*setColor(1, 6);*/
	system("cls"); //�������� ������
	cout << "New game" << endl;
	cout << "Instruction" << endl;
	cout << "Author" << endl;
	cout << "Exit" << endl;
}


void setup()
{
	gameOver = false;
	dir = STOP;
	x = width / 2 - 1;
	y = height / 2 - 1;
	fruitX = rand() % width;
	fruitY = rand() % height;
	score = 0;
	nTail = 0;
}

void draw()
{
	system("cls"); //������� �������� ��� ������ ������� draw

	/*setColor(1, 6);*/

	for (int i = 0; i < width + 1; i++) //������� �������
		cout << "#";
	cout << endl;


	for (int i = 0; i < height; i++) //������� �������
	{
		for (int j = 0; j < width; j++)
		{
			if (j == 0 || j == width - 1)
				cout << "#";

			if (i == y && j == x)
			{
				cout << "0";
			}

			else if (i == fruitY && j == fruitX)
			{
				cout << "*";
			}

			else
			{
				bool print = false;
				for (int k = 0; k < nTail; k++)
				{
					if (tailX[k] == j && tailY[k] == i)
					{
						print = true;
						cout << "o";
					}
				}
				if (!print)
				{
					cout << " ";
				}

			}

		}
		cout << endl;

	}

	for (int i = 0; i < width + 1; i++) //������ �������
		cout << "#";
	cout << endl;
	cout << "Score: " << score << endl;

	cout << "��� ������ ������ 'x' " << endl;

	Sleep(100);

}

void input()
{
	if (_kbhit()) /*����������� ������� ������������,
				  �� �������� ��������; ���������� true,
				  ���� ������������ ����� ������ �� ����������*/
	{
		switch (_getch())
		{
		case 'a':
			dir = LEFT;
			break;

		case 'd':
			dir = RIGHT;
			break;

		case 'w':
			dir = UP;
			break;

		case 's':
			dir = DOWN;
			break;

		case 'x':
			gameOver = true;
			break;
		}
	}
}

void logic()
{
	int prevX = tailX[0];
	int prevY = tailY[0];
	int prev2x, prev2y;
	tailX[0] = x;
	tailY[0] = y;

	for (int i = 1; i < nTail; i++)
	{
		prev2x = tailX[i];
		prev2y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2x;
		prevY = prev2y;
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
	}

	/*if (x>width || x<0 || y>height || y<0)
	{
		gameOver = true;
	}*/

	if (x >= width - 1)
	{
		x = 0;
	}

	else if (x < 0)
	{
		x = width - 2;
	}

	if (y >= height)
	{
		y = 0;
	}

	else if (y < 0)
	{
		y = height - 1;
	}

	for (int i = 0; i < nTail; i++)
	{
		if (tailX[i] == x && tailY[i] == y)
		{
			gameOver = true;
			showLose();

		}
	}

	if (x == fruitX && y == fruitY)
	{
		score += 10;
		fruitX = rand() % width;
		fruitY = rand() % height;
		nTail++;
	}

}

void SnakeMain()
{
	setlocale(LC_ALL, "Rus");
	srand(time(NULL));
	system("color F3"); //backgroud**text**
	system("cls"); //������� ������ 

	showLogo(); //����� ���� ����

	const int num_menu_items = 4;

	//choosen item
	int activeMenuItem = 0;

	//�������� ������� �������
	int ch = 0;

	//��� ������ �� ����� ���� ����
	bool exit = false;

	//���� ������ � ����
	while (!exit)
	{
		//����� ������� ����
		showMenu();

		//������� ������� � ����������� ������ ����
		gotoxy(0, activeMenuItem);

		//��������� ���� ������� �������
		//��� ������� ������� ������� ��� 224 � ����� ��� ������� �������
		ch = _getch();
		if (ch == 224) //��� ���� � ����� �����������, ���� �� ��� - 224
		{
			ch = _getch();
		}

		//��������� ������� �������
		switch (ch)
		{
		case 27:exit = true; break; //esc

		case 72:activeMenuItem--; break; //������� �����

		case 80: activeMenuItem++; break; //������� ����

		case 13: //������� enter

			if (activeMenuItem == 0)
			{
				setup();

				while (!gameOver)
				{
					draw();
					input();
					logic();


				}
			}


			else if (activeMenuItem == 1)
			{
				system("cls");
				cout << "Instruction:" << endl;
				cout << "����������� ������� 'w', 's', 'd', 'a' ��� �����������," << endl;
				cout << "��� ��x��� �� ���� ����������� ������� 'Esc';" << endl << endl;
				cout << "���� ���� - ������� ��� ����� ������ *, ����� ������������ ��� ������� ����," << endl;
				cout << "� ������, ���� �� ����������� �� ������ ������ - �� ����������!\n\n";
				system("pause");
			}

			else if (activeMenuItem == 2)
			{
				system("cls");
				cout << "KRAVCHENKO ALEKSEY" << endl << endl;
				system("pause");
			}

			else if (activeMenuItem == 3)
			{
				exit = true;

			}

			break;
		}

		//����������� �������� �� ������� ����
		if (activeMenuItem < 0)
		{
			activeMenuItem = 0;
		}

		if (activeMenuItem > num_menu_items - 1)
		{
			activeMenuItem = num_menu_items - 1;
		}
	}
	system("color 0F");
}