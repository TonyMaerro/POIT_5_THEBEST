#include <iostream>
using namespace std;
void main() {
	setlocale(LC_ALL, "ru");
	srand(time(NULL));
	int number = rand() % 2000 + 1,
		countOfHelp = 6,
		enterNumber,
		countTry = 3,
		help,
		n;
	bool active = false;
	cout << "������������, � ������� ����� �� 1 �� 2000, ���������� �������� ���!\n";
	while (true) {
		cout << "\n�������� ����� ����:\n1) �������� �����!(� ��� " << countTry << " �������)\n2) ���������(" << countOfHelp << ")\n3) �������!\n"; cin >> n;
		switch (n) {
		case 1:
			break;
		case 2:
			break;
		case 3:
			break;
		default:

			break;
		}
		if (countTry == 0) {
			active = true;
			cout << "Game Over! ����� ���� " << number << endl;
		}
		if (active) {
			break;
		}
	}
	system("pause");
}