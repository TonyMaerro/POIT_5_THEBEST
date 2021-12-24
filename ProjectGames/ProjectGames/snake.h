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
const int width = 20; //ширина поля
const int height = 20; //высота поля
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100]; //хвосты
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
	system("cls"); //отчистка экрана
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
	system("cls"); //очищает терминал при вызове функции draw

	/*setColor(1, 6);*/

	for (int i = 0; i < width + 1; i++) //верхняя граница
		cout << "#";
	cout << endl;


	for (int i = 0; i < height; i++) //боковые границы
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

	for (int i = 0; i < width + 1; i++) //нижняя граница
		cout << "#";
	cout << endl;
	cout << "Score: " << score << endl;

	cout << "Для выхода нажите 'x' " << endl;

	Sleep(100);

}

void input()
{
	if (_kbhit()) /*отслеживает нажатия пользователя,
				  не закрывая терминал; возвращает true,
				  если пользователь нажал кнопку на клавиатуре*/
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
	system("cls"); //очистка экрана 

	showLogo(); //вывод лого игры

	const int num_menu_items = 4;

	//choosen item
	int activeMenuItem = 0;

	//хранение нажатой клавиши
	int ch = 0;

	//для выхода из цикла меню игры
	bool exit = false;

	//цикл работы с меню
	while (!exit)
	{
		//вывод пунктов меню
		showMenu();

		//переход курсора к выбраннному пункту меню
		gotoxy(0, activeMenuItem);

		//получение кода нажатой клавиши
		//при нажатии стрелок сначала идёт 224 и потом код клавиши стрелки
		ch = _getch();
		if (ch == 224) //два кода в буфер присылается, одно из них - 224
		{
			ch = _getch();
		}

		//обработка нажатой клавиши
		switch (ch)
		{
		case 27:exit = true; break; //esc

		case 72:activeMenuItem--; break; //стрелка вверх

		case 80: activeMenuItem++; break; //стрелка вниз

		case 13: //клавиша enter

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
				cout << "Используйте клавиши 'w', 's', 'd', 'a' для перемещения," << endl;
				cout << "Для выxода из игры используйте клавишу 'Esc';" << endl << endl;
				cout << "Цель игры - собрать как можно больше *, внизу отоброжается ваш текущий счёт," << endl;
				cout << "В случае, если вы дотронитесь до хвоста змейки - вы проиграете!\n\n";
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

		//ограничения перехода по пунктам меню
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