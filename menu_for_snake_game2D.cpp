
#include <iostream>
#include <conio.h>
#include <windows.h>
#include <stdio.h>
#include <cstdlib>
#include <time.h>
#include <conio.h>
using namespace std;


void gotoxy(int x, int y)  //функции для физуального стиля меню
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
void showMenu() {
	/*setColor(1, 6);*/
	system("cls"); //отчистка экрана
	cout << "New game" << endl;
	cout << "Instruction"<< endl;
	cout << "Author"<< endl;
	cout << "Exit"<< endl;
}

int main()
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
				
					/*ТУТ БУДЕТ РАСПОЛОЖЕНА ИГРА ЗМЕЙКА!*/


				
			}


			else if (activeMenuItem == 1)
			{
				system("cls");
				cout << "Instruction:" << endl;
				cout << "Используйте клавиши 'w', 's', 'd', 'a' для перемещения," << endl;
				cout << "Для выxода из игры используйте клавишу 'Esc';" << endl << endl;
				cout <<"Цель игры - собрать как можно больше *, внизу отоброжается ваш текущий счёт," << endl;
				cout <<"В случае, если вы дотронитесь до хвоста змейки - вы проиграете!\n\n";
				system("pause");
			}

			else if (activeMenuItem == 2)
			{
				system("cls");
				cout << "POIT_5" << endl << endl;
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


	return 0;
}
