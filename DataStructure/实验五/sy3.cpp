#include <iostream>
#include <fstream>
#include <queue>
#include <string>
#include <stack>
#define MAX_SIZE 1000
#define MAX_DOUBLE 1e10
using namespace std;

struct Tmesa
{
	string name; 
	double weight[2];
};
typedef struct Graph
{
	string vertex[MAX_SIZE];
	struct Tmesa adjM[MAX_SIZE][MAX_SIZE];
	int verNum;
	int edgNum;
} AMGraph;

const string cityName = "./cityname.txt";
const string filePath[2] = {"./railwayTime.txt", "./airTime.txt"};
const string vehicles[2] = {"列车", "航班"};
const string way[2] = {"小时.", "元人民币."};

AMGraph G[2];

int findIndex(int toa, string v)
{
	int i;
	for (i = 0; i < G[toa].verNum; i++)
	{
		if (v == G[toa].vertex[i])
		{
			break;
		}
	}
	if (i >= G[toa].verNum)
	{
		return -1;
	}
	else
	{
		return i;
	}
}

bool createAMG(int toa)
{

	ifstream fin(filePath[toa], ios::in);
	ifstream fcin(cityName, ios::in);
	fin >> G[toa].verNum >> G[toa].edgNum;
	for (int i = 0; i < G[toa].verNum; i++)
	{
		fcin >> G[toa].vertex[i];
	}
	fcin.close();
	for (int i = 0; i < G[toa].verNum; i++)
	{
		for (int j = 0; j < G[toa].verNum; j++)
		{
			G[toa].adjM[i][j].weight[0] = 0;
			G[toa].adjM[i][j].weight[1] = 0;
			G[toa].adjM[i][j].name = "";
		}
	}
	
	for (int k = 0; k < G[toa].edgNum; k++)
	{
		string v1, v2, name;
		double time, cost;
		fin >> v1 >> v2 >> name >> time >> cost;
		int i = findIndex(toa, v1);
		int j = findIndex(toa, v2);
		if (i == -1 || j == -1)
		{
			cout << "error!" << endl;
			return false;
		}
		G[toa].adjM[i][j].name = name;
		G[toa].adjM[i][j].weight[0] = time;
		G[toa].adjM[i][j].weight[1] = cost;
	}
	return true;
}
void printPlan(int toa, int path[], int s, int d)
{
	stack<int> p;
	int temp = d;
	while (temp != s)
	{
		p.push(path[temp]);
		temp = path[temp];
	}
	while (!p.empty())
	{
		int m = p.top();
		p.pop();
		int n = p.empty() ? d : p.top();
		cout << "从" << G[toa].vertex[m] << "出发,乘坐" << G[toa].adjM[m][n].name << vehicles[toa]
			 << ",花费" << G[toa].adjM[m][n].weight[0] << "小时" << G[toa].adjM[m][n].weight[1]
			 << "元钱,到达" << G[toa].vertex[n] << endl;
	}
}

void unweight(int toa, string source, string destination)
{
	int s = findIndex(toa, source);
	int d = findIndex(toa, destination);
	queue<int> q;
	double dist[MAX_SIZE];
	int path[MAX_SIZE];
	for (int i = 0; i < MAX_SIZE; i++)
	{
		dist[i] = -1;
		path[i] = -1;
	}
	dist[s] = 0;
	q.push(s);
	while (!q.empty())
	{
		int v = q.front();
		q.pop();
		for (int i = 0; i < G[toa].verNum; i++)
		{
			if (G[toa].adjM[v][i].weight[0] && (dist[i] == -1))
			{
				dist[i] = dist[v] + 1;
				path[i] = v;
				q.push(i);
			}
		}
	}
	if (dist[d] == -1)
	{
		cout << "没有可乘坐的" << vehicles[toa] << endl;
		return;
	}
	else
	{
		cout << "最短中转次数:" << dist[d] << endl;
		printPlan(toa, path, s, d);
	}
}
int findMinDist(int toa, double dist[], bool collected[])
{
	int minV, v;
	double minDist = MAX_DOUBLE;
	for (v = 0; v < G[toa].verNum; v++)
	{
		if (!collected[v] && dist[v] < minDist)
		{
			minDist = dist[v];
			minV = v;
		}
	}
	if (minDist < MAX_DOUBLE)
	{
		return minV;
	}
	else
	{
		return -1;
	}
}

void dijkstra(int toa, int toc, string source, string destination)
{
	int s = findIndex(toa, source);
	int d = findIndex(toa, destination);
	double dist[MAX_SIZE];
	int path[MAX_SIZE];
	bool collected[MAX_SIZE];
	int v, w;
	for (v = 0; v < G[toa].verNum; v++)
	{
		if (G[toa].adjM[s][v].weight[toc])
		{
			dist[v] = G[toa].adjM[s][v].weight[toc];
			path[v] = s;
		}
		else
		{
			dist[v] = MAX_DOUBLE;
			path[v] = -1;
		}
		collected[v] = false;
	}
	dist[s] = 0;
	collected[s] = true;
	while (true)
	{
		v = findMinDist(toa, dist, collected);
		if (v == -1)
		{
			break;
		}
		collected[v] = true;
		for (w = 0; w < G[toa].verNum; w++)
		{
			if (!collected[w] && (G[toa].adjM[v][w].weight[toc]))
			{
				if (dist[v] + G[toa].adjM[v][w].weight[toc] < dist[w])
				{
					dist[w] = dist[v] + G[toa].adjM[v][w].weight[toc];
					path[w] = v;
				}
			}
		}
	}
	if (dist[d] == MAX_DOUBLE)
	{
		cout << "没有可乘坐的" << vehicles[toa] << endl;
		return;
	}
	else
	{
		cout << "最少花费:" << dist[d] << way[toc] << endl;
		printPlan(toa, path, s, d);
	}
}
int menu(void)
{
	cout << endl
		 << endl;
	cout << "==============交通咨询系统===============" << endl;
	cout << "[1]最少中转次数" << endl;
	cout << "[2]最少时间" << endl;
	cout << "[3]最少花费" << endl;
	cout << "[0]退出" << endl;
	cout << "请选择[_]:";
	int choose;
	cin >> choose;
	return choose;
}
int main(void)
{
	int toa;
	int toc;
	string source;
	string destination;
	createAMG(1);
	createAMG(0);
	while (true)
	{
		switch (menu())
		{
		case 0:
			cout << "Good bye !!!" << endl;
			exit(0);
			break;
		case 1:
			cout << "请选择交通方式(0:火车 1:飞机):";
			cin >> toa;
			cout << "请输入出发地和目的地:";
			cin >> source >> destination;
			unweight(toa, source, destination);
			break;
		case 2:
			cout << "请选择交通方式(0:火车 1:飞机):";
			cin >> toa;
			toc = 0;
			cout << "请输入出发地和目的地:";
			cin >> source >> destination;
			dijkstra(toa, toc, source, destination);
			break;
		case 3:
			cout << "请选择交通方式(0:火车 1:飞机):";
			cin >> toa;
			toc = 1;
			cout << "请输入出发地和目的地:";
			cin >> source >> destination;
			dijkstra(toa, toc, source, destination);
			break;
		default:
			cout << "请重新输入!" << endl;
			break;
		}
	}
	return 0;
}