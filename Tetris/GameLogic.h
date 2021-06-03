#pragma once

using namespace std;
const int M = 20; // высота игрового поля
const int N = 10; 
int countOfLines = 0;
int score = 0;
int recentLevel = 1;
int field[M][N] = { 0 }; // игровое поле
bool isMusic=true;
bool isBlack = false;
// Массив фигурок-тетрамино
int figures[7][4] =
{
	1,3,5,7, // I
	2,4,5,7, // Z
	3,5,4,6, // S
	3,5,4,7, // T
	2,3,5,7, // L
	3,5,7,6, // J
	2,3,4,5, // O
};

struct Point
{
	int x, y;
} a[4], b[4];

bool check()
{
	for (int i = 0; i < 4; i++)
		if (a[i].x < 0 || a[i].x >= N || a[i].y >= M) return 0;
		else if (field[a[i].y][a[i].x]) return 0;



	return 1;

};
bool GameOver() {
	for (int i = 0; i < N; i++) {
		if (field[2][i] == 0) continue;
		return 0;

	}
}
void SetLevel(float &delay,float &recentDelay) {
	switch (countOfLines)
	{
	case 5: {recentLevel = 2;   break; }
	case 10: {recentLevel = 3; break; }
	case 20: {recentLevel = 4;  break; }
	case 30: {recentLevel = 5; break; }
	case 50: {recentLevel = 6;  break; }
	}
	switch (recentLevel) {
	case 2: { delay = 0.5; recentDelay = 0.5; break; }
	case 3: { delay = 0.35; recentDelay = 0.35; break; }
	case 4: { delay = 0.25; recentDelay = 0.25; break; }
	case 5: { delay = 0.20; recentDelay = 0.20; break; }
	case 6: { delay = 0.15; recentDelay = 0.15; break; }
	}
}
void Rotate(bool rotate) {
	if (rotate)
	{
		Point p = a[1]; // задаем центр вращения
		for (int i = 0; i < 4; i++)
		{
			int x = a[i].y - p.y; //y-y0
			int y = a[i].x - p.x; //x-x0
			a[i].x = p.x - x;
			a[i].y = p.y + y;
		}
		// Вышли за пределы поля после поворота? Тогда возвращаем старые координаты 
		if (!check()) { for (int i = 0; i < 4; i++) a[i] = b[i]; }

	}
}
void MoveDown(float &timer,int &colorNum,float &delay,int &n) {
	if (timer > delay)
	{
		for (int i = 0; i < 4; i++) { b[i] = a[i]; a[i].y += 1; }
		if (!check())
		{
			for (int i = 0; i < 4; i++) field[b[i].y][b[i].x] = colorNum;
			colorNum = 1 + rand() % 7;
			n = rand() % 7;
			for (int i = 0; i < 4; i++)
			{

				a[i].x = 4 + figures[n][i] % 2;
				a[i].y = figures[n][i] / 2;
			}


		}
		timer = 0;

	}
}
void CheckLines() {
	int k = M - 1;
	for (int i = M - 1; i > 0; i--)
	{
		int count = 0;
		for (int j = 0; j < N; j++)
		{
			if (field[i][j]) count++;
			field[k][j] = field[i][j];
		}
		if (count < N) k--; else { countOfLines++; score += 100; }
	}
}