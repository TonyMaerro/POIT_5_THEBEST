#include <iostream>
#include <windows.h>
using namespace std;
void main() {
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	setlocale(LC_ALL, "ru");
	do
	{
		cout << "�������� ����" << endl;
		cout << "1 - ������ 12D" << endl;
		cout << "2 - ��������� 2D" << endl;
		cout << "3 - ������� ����� ��������" << endl;
		cout << "4 - �����" << endl;
		cin >> choice;
		switch (choice)
		{
		case 1:
		{
			//�������
			break;
		}
		case 2:
		{
			//�������
			break;
		}
		case 3:  
		{
			//�������
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
