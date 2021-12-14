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
	cout << "Здравствуйте, я загадал число от 1 до 2000, попробуйте отгадать его!\n";
	while (true) {
		cout << "\nВыберите пункт меню:\n1) Написать число!(У вас " << countTry << " попыток)\n2) Подсказки(" << countOfHelp << ")\n3) Сдаться!\n"; cin >> n;
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
			cout << "Game Over! Число было " << number << endl;
		}
		if (active) {
			break;
		}
	}
	system("pause");
}