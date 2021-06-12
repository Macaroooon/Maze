#include <iostream>
#include <Windows.h>
#include <string>
#include <process.h>
#include <Windows.h>
using namespace std;


/****************************************************************************************/
/* 
迷宫问题：
设定初始面向 East ( 如果是右手抹墙则是 West）
1如果当前格为第一排，则说明当前格为终点，结束。
2根据当前格的数据，找到下一步需要面向的方向，如果当前方向上有墙，则顺时针（右手抹墙则逆时针）转身，重复这一步骤直到面向的方向上可以行走
3沿当前方向走一步
4逆时针（右手抹墙则顺时针）转身一次，使当前面对方向为第3步之后的左手（或右手）方向， 然后回到步骤1
*/
/****************************************************************************************/

//墙体和路常量
#define WOLD  "■"
#define ROLD  "  "

//迷宫大小常量
const int X = 8;
const int Y = 8;

//计步器
int count = 0;

//方向枚举
enum direction {
	N = 0,
	S = 1,
	W = 2,
	E = 3
};

//地图类
class MazeMap
{
public:
	MazeMap() {}
	void coutMap(string map[X][Y])
	{ //构造地图
		for (int i = 0; i < X; i++)
		{
			for (int j = 0; j < Y; j++) 
			{
				cout << map[i][j];
			}
			cout << endl;
		}
	}
};

//人类
class Human {
public:
	Human() :x(6), y(6), man("☆"), direction(W) {} //默认人初始化为第一个位置
	Human(string _man) :x(6), y(6), man(_man), direction(W) {} //可以设置人的标识符

	//横纵坐标
	int x;
	int y;

	//人物标识
	string man;

	//方向
	int direction;

	// 移动方法
	void humanMove(string map[X][Y], Human* man)
	{
		MazeMap* mazeMap = new MazeMap;
		map[man->x][man->y] = man->man;
		mazeMap->coutMap(map);

		cout << "READY?(Q:y/n)" << endl;
		char flag = 'n';
		cin >> flag;

		//单向寻路原则:右手抹墙，初始朝向为W
		if (flag == 'y')
		{
			do
			{
				turnBack(map, man);
				move(map, man);
				Sleep(1000);
				system("cls");
				mazeMap->coutMap(map);
			} while (finsh(man));
			cout << "YOU WIN!!!" << endl;
		}
		else 
		{
			cout << "YOU ARE A LOSER!!!" << endl;
		}

		delete mazeMap;
		mazeMap = NULL;

	}



	//确定方向 如果方向上有墙就逆时针转一下
void turnBack(string map[X][Y], Human* man)
{
	static int cache = 0;
	if (man->direction == N) 
	{
		if (map[man->x - 1][man->y] == WOLD) 
		{
				man->direction = W;
				cache++;
				turnBack(map, man);

		}

		cache = 0;
		return;

		}
		if (man->direction == S)
		{
			if (map[man->x + 1][man->y] == WOLD)
			{
				man->direction = E;
				cache++;
				turnBack(map, man);
			}
			cache = 0;
			return;
		}
		if (man->direction == W)
		{
			if (map[man->x][man->y - 1] == WOLD)
			{
				man->direction = S;
				cache++;
				turnBack(map, man);
			}

			cache = 0;
			return;
		}

		if (man->direction == E) 
		{
			if (map[man->x][man->y + 1] == WOLD) 
			{
				man->direction = N;
				cache++;
				turnBack(map, man);
			}

			cache = 0;
			return;
		}

		if (cache == 4) 
		{
			cache = 0;
			return;
		}
	}

	//移动一格  后顺时针调转方向
void move(string map[X][Y], Human* man) 
{
	if (man->direction == N)
	{
		man->direction = E;
		map[man->x - 1][man->y] = man->man;
		map[man->x][man->y] = ROLD;
		man->x -= 1;
	}
	else if (man->direction == S) 
	{
			man->direction = W;
			map[man->x + 1][man->y] = man->man;
			map[man->x][man->y] = ROLD;
			man->x += 1;

	}
	else if (man->direction == W)
	{
			man->direction = N;
			map[man->x][man->y - 1] = man->man;
			map[man->x][man->y] = ROLD;
			man->y -= 1;

	}
	else if (man->direction == E) 
	{
			man->direction = S;
			map[man->x][man->y + 1] = man->man;
			map[man->x][man->y] = ROLD;
			man->y += 1;

	}
		return;

	}

	//判断是否完成
	bool finsh(Human* man)
	{

		if (man->x == 0)
		return false;
		return true;

	}

};

int main(void) {

	string map[X][Y] = { {WOLD,ROLD,WOLD,WOLD,WOLD,WOLD,WOLD,WOLD},
	{WOLD,ROLD,ROLD,ROLD,ROLD,ROLD,WOLD,WOLD},
	{WOLD,WOLD,WOLD,WOLD,WOLD,ROLD,ROLD,WOLD},
	{WOLD,ROLD,ROLD,ROLD,ROLD,ROLD,WOLD,WOLD},
	{WOLD,WOLD,ROLD,WOLD,ROLD,ROLD,WOLD,WOLD},
	{WOLD,WOLD,ROLD,ROLD,ROLD,WOLD,WOLD,WOLD},
	{WOLD,WOLD,WOLD,WOLD,ROLD,ROLD,ROLD,WOLD},
	{WOLD,WOLD,WOLD,WOLD,WOLD,WOLD,WOLD,WOLD} };

	Human* man = new Human("⊙");
	man->humanMove(map, man);


	delete man;
	man = NULL;
	return 0;

}
