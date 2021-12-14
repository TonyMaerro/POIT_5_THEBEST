#include <iostream>
#include <conio.h>
#include <iomanip>
#include <windows.h>

using namespace std;
enum DirectionUs { STOP = 0, UP, DOWN };
DirectionUs dirUs1;
DirectionUs dirUs2;
bool gameover;
int width = 15;
const int height = 25;
const int Us1_X = 2;
int Us2_X = width - 3;
int user1 = height / 2,
user2 = height / 2,
cartridgeX_Us1,
cartridgeY_Us1,
cartridgeX_Us2,
cartridgeY_Us2,
scoreOfUs1 = 0,
scoreOfUs2 = 0,
cPullsUs1 = 0,
cPullsUs2 = 0,
bonusX = width / 2,
bonusY = rand() % height + 1,
cBonusPull_USER1 = 0,
cBonusPull_USER2 = 0,
liveUSER1 = 30,
liveUSER2 = 30,
boxX = width / 2,
boxY = rand() % height + 1,
blockX = width / 2,
blockY = 1,
nBlock = rand() % 4 + 1,
blocksY[4];

bool us1ShotedBonus = false,
us2ShotedBonus = false,
us1ShotedGift = false,
us2ShotedGift = false,
ShotedUs2 = false,
ShotedUs1 = false,
gameMode = false,
AI_came = false,
followingUser = false,
followingBox = false,
followingBonus = false;

bool* typeGame();

int move(DirectionUs dir, int y) {
	switch (dir) {
	case UP:
		y--;
		break;
	case DOWN:
		y++;
		break;
	case STOP:
		y = y;
		break;
	}
	return y;
}

bool bonus(int pullX, int pullY, int bonusX, int bonusY) {
	bool shot = false;
	if (pullX == bonusX && pullY == bonusY) {
		shot = true;
	}
	else if (pullX - 1 == bonusX && pullY == bonusY) {
		shot = true;
	}
	else if (pullX - 3 == bonusX && pullY == bonusY) {
		shot = true;
	}
	else if (pullX - 2 == bonusX && pullY == bonusY) {
		shot = true;
	}
	else if (pullX - 5 == bonusX && pullY == bonusY) {
		shot = true;
	}
	return shot;
}

int ultimate(int score) {
	int pull;
	if (score >= 50 && score < 100)
		pull = 2;
	else if (score >= 100) {
		pull = 3;
	}
	else
		pull = 1;
	return pull;
}
bool wall(int pullX, int pullY, int wallX, int wallY[], int nWall) {
	bool userShotedWall = false;
	for (int i = 0; i < nWall; i++) {
		if (pullX == wallX && pullY == wallY[i]) {
			userShotedWall = true;
			break;
		}
		else if (pullX - 1 == wallX && pullY == wallY[i]) {
			userShotedWall = true;
			break;
		}
		else if (pullX + 1 == wallX && pullY == wallY[i]) {
			userShotedWall = true;
			break;
		}

	}
	return userShotedWall;
}
void startMenu() {
	int n;
	cout << "Добро пожаловать в игру!" << endl;
	cout << "Выберите пункт: \n1) Начало\n2) Выход из игры\n3) Инструкция\n";
	cin >> n;
	switch (n) {
	case 1:
		break;
	case 2:
		gameover = true;
		break;
	case 3:
		cout << "Для первого игрока:\n W - движение вверх\n S - движение вниз\n D - остановиться\n A - стрелять \n\nДля второго игрока:\n 8 - движение вверх\n 5 - движение вниз\n 4 - остановиться\n 6 - стрелять \n\n X - выход из игры!\n";
		cout << "Нажмите любую клавишу для входа в игру";
		if (_kbhit)
			if (_getch())
				break;
	}
	if (!gameover)
		gameMode = *typeGame();
}
void setup() {
	gameover = false;
}
void draw() {
	system("cls");
	for (int i = 0; i < width; i++)
		cout << "8";
	cout << endl;
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (j == 0 || j == width - 1)
				cout << "8";
			else if (Us1_X == j && user1 == i && ShotedUs1) {
				cout << "\x1b[46mР\x1b[0m";
			}
			else if (Us1_X == j && user1 == i) {
				cout << "\x1b[36mР\x1b[0m";
			}
			else if (boxX == j && boxY == i) {
				cout << "\x1b[32m&\x1b[0m";
			}
			else if (bonusX == j && bonusY == i) {
				cout << "\x1b[33m%\x1b[0m";
			}
			else if (cartridgeX_Us2 == j && cartridgeY_Us2 == i) {
				cout << "\x1b[31m*\x1b[0m";
			}
			else if (cartridgeX_Us2 == j && cartridgeY_Us2 - 1 == i && cBonusPull_USER2 > 0) {
				cout << "\x1b[31m*\x1b[0m";
			}
			else if (cartridgeX_Us2 == j && cartridgeY_Us2 + 1 == i && cBonusPull_USER2 > 0) {
				cout << "\x1b[31m*\x1b[0m";
			}
			else if (cartridgeX_Us1 == j && cartridgeY_Us1 - 1 == i && cBonusPull_USER1 > 0) {
				cout << "\x1b[31m*\x1b[0m";
			}
			else if (cartridgeX_Us1 == j && cartridgeY_Us1 + 1 == i && cBonusPull_USER1 > 0) {
				cout << "\x1b[31m*\x1b[0m";
			}
			else if (cartridgeX_Us1 == j && cartridgeY_Us1 == i) {
				cout << "\x1b[31m*\x1b[0m";
			}
			else if (Us2_X == j && user2 == i && ShotedUs2) {
				cout << "\x1b[45mЯ\x1b[0m";
			}
			else if (Us2_X == j && user2 == i) {
				cout << "\x1b[35mЯ\x1b[0m";
			}
			else {
				bool printSpace = false;
				for (int m = 0; m < nBlock; m++) {
					if (blockX == j && blocksY[m] == i) {
						cout << "|";
						printSpace = false;
						break;
					}
					else
						printSpace = true;
				}
				if (printSpace) {
					cout << " ";
					printSpace = false;
				}
			}
		}
		cout << endl;
	}
	for (int i = 0; i < width; i++)
		cout << "8";
	cout << endl;
	cout << "Score of User 1: \x1b[32m" << scoreOfUs1 << "\x1b[0m\t\t\tScore Of User 2: \x1b[32m " << scoreOfUs2 << "\x1b[0m" << endl << "Level of User 1: \x1b[32m " << ultimate(scoreOfUs1) << "\x1b[0m\t\t\tLevel of User 2: \x1b[32m " << ultimate(scoreOfUs2) << "\x1b[0m" << endl
		<< "Count of Live of User 1:\x1b[32m " << liveUSER1 << "\x1b[0m" << "\t\tCount of Live of User 2: \x1b[32m" << liveUSER2 << "\x1b[0m" << endl;;
	for (int i = 0; i < 400; i++)
		cout << " ";
}
bool Us1Pull = false,
Us2Pull = false;

void input() {
	if (_kbhit()) {
		switch (_getch()) {
		case 's':
			dirUs1 = DOWN;
			break;
		case 'w':
			dirUs1 = UP;
			break;
		case 'd':
			dirUs1 = STOP;
			break;
		case 'a':
			if (Us1Pull) {
				break;
			}
			else {
				cBonusPull_USER1--;
				Us1Pull = true;
				cartridgeX_Us1 = Us1_X + 1;
				cartridgeY_Us1 = user1;
				break;
			}
			//////////////////////////////////////
		case '5':
			if (!gameMode) {
				dirUs2 = DOWN;
				break;
			}
		case '8':
			if (!gameMode) {
				dirUs2 = UP;
				break;
			}
		case '4':
			if (!gameMode) {
				dirUs2 = STOP;
				break;
			}
		case '6':
			if (!gameMode) {
				if (Us2Pull) {
					break;
				}
				else {
					cBonusPull_USER2--;
					Us2Pull = true;
					cartridgeX_Us2 = Us2_X - 1;
					cartridgeY_Us2 = user2;
					break;
				}
			}
		case 'x':
			gameover = true;
			break;
		}
	}
}
int scorePull = 0;
void logicForAI() {
	int randDir = rand() % 4 + 1;
	if (gameMode) {
		if (user1 == user2) {
			if (!Us2Pull) {
				cBonusPull_USER2--;
				scorePull++;
				Us2Pull = true;
				cartridgeX_Us2 = Us2_X - 1;
				cartridgeY_Us2 = user2;
			}
		}
		else if (abs(user1 - user2) == 1 || abs(user1 - user2) == 2 || abs(user1 - user2) == 3 && dirUs1 + dirUs2 == 0) {
			if (!Us2Pull) {
				cBonusPull_USER2--;
				scorePull++;
				Us2Pull = true;
				cartridgeX_Us2 = Us2_X - 1;
				cartridgeY_Us2 = user2;
			}
		}
		else if (user2 == bonusY || user2 == boxY) {
			if (!Us2Pull) {
				cBonusPull_USER2--;
				Us2Pull = true;
				cartridgeX_Us2 = Us2_X - 1;
				scorePull++;
				cartridgeY_Us2 = user2;
			}
		}

		if (scorePull >= 4) {
			randDir = rand() % 4 + 1;
			scorePull = 0;
		}

		if (randDir == 1 || randDir == 4 && !AI_came) {
			scorePull = 0;
			AI_came = true;
			followingBox = true;
		}
		else if (randDir == 2 && !AI_came) {
			scorePull = 0;
			AI_came = true;
			followingUser = true;
		}
		else if (randDir == 3 && !AI_came) {
			scorePull = 0;
			AI_came = true;
			followingBonus = true;
		}
		if (followingUser) {
			if (user1 - user2 > rand() % 10) {
				dirUs2 = DOWN;
			}
			else if (user1 - user2 < -(rand() % 10)) {
				dirUs2 = UP;
			}
			else if (user1 - user2 == 0) dirUs2 = STOP;
		}
		else if (followingBox) {
			if (boxY > user2) {
				dirUs2 = DOWN;
			}
			else if (boxY < user2) {
				dirUs2 = UP;
			}
			else dirUs2 = STOP;
		}
		else if (followingBonus) {
			if (bonusY > user2) {
				dirUs2 = DOWN;
			}
			else if (bonusY < user2) {
				dirUs2 = UP;
			}
			else dirUs2 = STOP;
		}
	}
}
void logic() {
	blockX = width / 2;
	bonusX = width / 2;
	boxX = width / 2;
	if (blocksY[nBlock - 1] >= height || blocksY[nBlock - 1] < -2) {
		srand(time(NULL));
		nBlock = rand() % 3 + 2;
		blockY = 1;
		blocksY[nBlock - 1] = blockY - nBlock + 1;
	}
	else {
		blocksY[0] = blockY++;
		for (int i = 1; i < nBlock; i++) {
			blocksY[i] = blocksY[i - 1] - 1;
			if (i + 1 == nBlock && blocksY[nBlock - 1] == height) {
				blocksY[nBlock - 1] = -2323;
			}
		}
	}

	ShotedUs1 = false;
	ShotedUs2 = false;

	user1 = move(dirUs1, user1);
	user2 = move(dirUs2, user2);

	if (Us2Pull) {
		cartridgeX_Us2--;
		if (cartridgeX_Us2 <= 0) {
			Us2Pull = false;
		}
	}
	if (Us1Pull) {
		cartridgeX_Us1++;
		if (cartridgeX_Us1 >= width - 1) {
			Us1Pull = false;
		}
	}
	if (cartridgeX_Us1 == cartridgeX_Us2 && cartridgeY_Us1 == cartridgeY_Us2) {
		cartridgeX_Us1 = width;
		cartridgeX_Us2 = 0;
		Us1Pull == false;
		Us2Pull = false;
	}
	else if (cartridgeX_Us1 + 1 == cartridgeX_Us2 && cartridgeY_Us1 == cartridgeY_Us2) {
		cartridgeX_Us1 = width;
		cartridgeX_Us2 = 0;
		Us1Pull == false;
		Us2Pull = false;
	}
	if (user1 >= height - 1) {
		dirUs1 = STOP;
		user1 = height - 1;
	}
	else if (user1 < 1) {
		dirUs1 = STOP;
		user1 = 0;
	}
	if (user2 >= height - 1) {
		dirUs2 = STOP;
		user2 = height - 1;
	}
	else if (user2 < 1) {
		dirUs2 = STOP;
		user2 = 0;
	}
	if (cartridgeX_Us1 == Us2_X && cartridgeY_Us1 == user2) {
		cartridgeX_Us1 = 1000;
		Us1Pull = false;
		scoreOfUs1 += 10;
		ShotedUs2 = true;
		liveUSER2--;
	}
	else if (cartridgeX_Us1 == Us2_X && cartridgeY_Us1 + 1 == user2 && cBonusPull_USER1 > 0) {
		cartridgeX_Us1 = 1000;
		Us1Pull = false;
		ShotedUs2 = true;
		scoreOfUs1 += 10;
		liveUSER2--;
	}
	else if (cartridgeX_Us1 == Us2_X && cartridgeY_Us1 - 1 == user2 && cBonusPull_USER1 > 0) {
		cartridgeX_Us1 = 1000;
		Us1Pull = false;
		ShotedUs2 = true;
		scoreOfUs1 += 10;
		liveUSER2--;
	}
	if (cartridgeX_Us2 == Us1_X && cartridgeY_Us2 == user1) {
		cartridgeX_Us2 = 1000;
		Us2Pull = false;
		ShotedUs1 = true;
		followingUser = false;
		AI_came = false;
		liveUSER1--;
		scoreOfUs2 += 10;
	}
	else if (cartridgeX_Us2 == Us1_X && cartridgeY_Us2 - 1 == user1 && cBonusPull_USER2 > 0) {
		cartridgeX_Us2 = 1000;
		Us2Pull = false;
		ShotedUs1 = true;
		followingUser = false;
		AI_came = false;
		liveUSER1--;
		scoreOfUs2 += 10;
	}
	else if (cartridgeX_Us2 == Us1_X && cartridgeY_Us2 + 1 == user1 && cBonusPull_USER2 > 0) {
		cartridgeX_Us2 = 1000;
		ShotedUs1 = true;
		followingUser = false;
		AI_came = false;
		Us2Pull = false;
		liveUSER1--;
		scoreOfUs2 += 10;
	}

	if (wall(cartridgeX_Us1, cartridgeY_Us1, blockX, blocksY, nBlock)) {
		Us1Pull = false;
		cartridgeX_Us1 = 1000;
	}
	if (wall(cartridgeX_Us2, cartridgeY_Us2, blockX, blocksY, nBlock)) {
		Us2Pull = false;
		cartridgeX_Us2 = 1000;
	}

	us1ShotedBonus = bonus(cartridgeX_Us1, cartridgeY_Us1, bonusX, bonusY);
	us2ShotedBonus = bonus(cartridgeX_Us2, cartridgeY_Us2, bonusX, bonusY);

	if (us1ShotedBonus) {
		cBonusPull_USER1 = 5;
		bonusY = rand() % height;
	}
	if (us2ShotedBonus) {
		cBonusPull_USER2 = 5;
		AI_came = false;
		followingBonus = false;
		bonusY = rand() % height;
	}
	switch (ultimate(scoreOfUs1)) {
	case 1:
		break;
	case 2:
		cartridgeX_Us1++;
		break;
	case 3:
		cartridgeX_Us1 += 3;
		if (scoreOfUs1 >= 100 && scoreOfUs2 >= 100) {
			width = 27;
			Us2_X = width - 3;
		}
		break;
	case 4:
		cartridgeX_Us1 += 5;
		if (scoreOfUs1 >= 100 && scoreOfUs2 >= 100) {
			width = 27;
			Us2_X = width - 3;
		}
		break;
	}
	switch (ultimate(scoreOfUs2)) {
	case 1:
		break;
	case 2:
		cartridgeX_Us2--;
		break;
	case 3:
		cartridgeX_Us2 -= 3;
		if (scoreOfUs1 >= 100 && scoreOfUs2 >= 100) {
			width = 27;
			Us2_X = width - 3;
		}
		break;
	case 4:
		cartridgeX_Us2 -= 5;
		if (scoreOfUs1 >= 100 && scoreOfUs2 >= 100) {
			width = 27;
			Us2_X = width - 3;
		}
		break;
	}
	if (scoreOfUs1 == 1000 || scoreOfUs2 == 1000) {
		gameover = true;
	}
	us1ShotedGift = bonus(cartridgeX_Us1, cartridgeY_Us1, boxX, boxY);
	us2ShotedGift = bonus(cartridgeX_Us2, cartridgeY_Us2, boxX, boxY);
	if (us1ShotedGift) {
		scoreOfUs1 += 5;
		boxY = rand() % height;
		us1ShotedBonus = false;
	}
	else if (us2ShotedGift) {
		scoreOfUs2 += 5;
		boxY = rand() % height;
		AI_came = false;
		followingBox = false;
		us2ShotedBonus = false;
	}
	if (liveUSER1 == -1 || liveUSER2 == -1)
		gameover = true;
}

void winner() {
	system("cls");
	int height = 5,
		width = 60,
		lenFill;
	char User1Win[] = "User 1 is winner",
		draw[] = "User 1 and User 2 is winners",
		space = ' ';
	lenFill = (width - 2 - strlen(User1Win)) / 2;
	for (int i = 0; i < width; i++)
		cout << "0";
	cout << endl;
	for (int i = 0; i < width; i++) {
		if (i == 0 || i + 1 == width) {
			cout << "0";
		}
		else cout << " ";
	}


	if (liveUSER1 == -1)
		scoreOfUs2 += 500;
	if (liveUSER2 == -1)
		scoreOfUs1 += 500;

	if (scoreOfUs1 > scoreOfUs2) {
		cout << endl;
		cout << "0";
		for (int i = 0; i < lenFill; i++)
			cout << " ";
		cout << "User 1 is winner" << setw(lenFill + 1) << setfill(space) << "0" << endl;
	}
	else if (scoreOfUs1 < scoreOfUs2) {
		cout << endl;
		cout << "0";
		for (int i = 0; i < lenFill; i++)
			cout << " ";
		cout << "User 2 is winner" << setw(lenFill + 1) << setfill(space) << "0" << endl;
	}
	else if (scoreOfUs1 == 0 && scoreOfUs2 == 0) {
		cout << endl;
		lenFill = (width - 2 - strlen("Good Bye!")) / 2;
		cout << "0";
		for (int i = 0; i < lenFill; i++)
			cout << " ";
		cout << "Good Bye! ";
		for (int i = 0; i < lenFill; i++)
			cout << " ";
		cout << "0" << endl;
	}
	else if (scoreOfUs1 == scoreOfUs2) {
		cout << endl;

		lenFill = (width - 2 - strlen("User 1 and User 2 is winners")) / 2;
		cout << "0";
		for (int i = 0; i < lenFill; i++)
			cout << " ";
		cout << "User 1 and User 2 is winners";
		for (int i = 0; i < lenFill; i++)
			cout << " ";
		cout << "0" << endl;
	}
	for (int i = 0; i < width; i++) {
		if (i == 0 || i + 1 == width) {
			cout << "0";
		}
		else cout << " ";
	}
	cout << endl;
	for (int i = 0; i < width; i++)
		cout << "0";
	cout << endl << endl;
}
bool* typeGame() {
	system("cls");
	int type;
	bool typeG = false;;
	cout << "Выберите тип игры: \n1) Против ИИ\n2) На двоих\n";
	cin >> type;
	while (type != 1 && type != 2) {
		cout << "Ошибка. Выберите тип игры(1 или 2): \n1) Против ИИ\n2) На двоих\n";
		cin >> type;
	}
	if (type == 1) {
		typeG = true;
	}
	return &typeG;
}
void main() {
	srand(time(NULL));
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setup();
	startMenu();
	while (!gameover) {
		draw();
		input();
		logicForAI();
		logic();
	}
	if (gameover)
		winner();
	system("pause");
}