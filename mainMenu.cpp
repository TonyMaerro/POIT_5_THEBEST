#include <iostream>
#include <windows.h>
using namespace std;
void main() {
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	setlocale(LC_ALL, "ru");
	do
	{
		cout << "Выберите игру" << endl;
		cout << "1 - Змейка 12D" << endl;
		cout << "2 - Стрелялка 2D" << endl;
		cout << "3 - Угадать букву челлендж" << endl;
		cout << "4 - Выход" << endl;
		cin >> choice;
		switch (choice)
		{
		case 1:
		{
			//Функция
			break;
		}
		case 2:
		{
			//Функция
			break;
		}
		case 3:  
		{
			//Функция
			break;
		}
		case 4:
		{
			break;
		}
	} while (choice != 4);
}
	system("pause");
}
