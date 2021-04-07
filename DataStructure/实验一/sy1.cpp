#include <iostream>
#include <fstream>
using namespace std;
#define MAXSIZE 100
typedef int status;
typedef int ElemType;
typedef struct
{
	ElemType *elem; //储存空间的基地址
	int length;		//顺序表长度
} SqList;
status InitList(SqList &L) //初始化顺序表（构造空的顺序表）
{
	L.elem = new ElemType[MAXSIZE];
	if (!L.elem)
		return false;
	L.length = 0;
	return true;
}
status InPutList(SqList &L, int len)
{
	int i = 0;
	if (len > MAXSIZE)
	{
		cout << "创建失败" << endl;
		return false;
	}
	for (i = 0; i < len; i++)
	{
		cin >> L.elem[i];
		L.length = i + 1;
	}
	return true;
}
status ListInsert(SqList &L, int i, ElemType e) //顺序表的插入操作 在顺序表L的第i个位置插入新元素e
{
	int j;
	if (i < 1 || i > L.length - 1 || L.length == MAXSIZE)
		return false;
	for (j = L.length - 1; j >= i - 1; j--)
		L.elem[j + 1] = L.elem[j];
	L.elem[i] = e;
	++L.length;
	return true;
}
status GetElem(SqList L, int i, ElemType e) //顺序表的取值操作  将第i个元素的值赋给e
{
	if (i < 1 || i > L.length)
		return false;
	e = L.elem[i - 1];
	return true;
}
status LocateElem(SqList L, ElemType e) //顺序表的查找操作 找到与e相等的元素则返回该元素的序号i+1
{
	int i;
	for (i = 0; i < L.length; i++)
		if (L.elem[i] == e)
			return (i + 1);
	return 0;
}
status ListDelete(SqList &L, int i) //顺序表的删除操作 删除第i个元素
{
	int j;
	if (i < 1 || i > L.length - 1)
		return false;
	for (j = i; j <= L.length; j++)
		L.elem[j - 1] = L.elem[j];
	--L.length;
	return true;
}
status OutPutList(SqList L)
{
	int i = 0;
	while (i < L.length)
	{
		cout << " " << L.elem[i];
		i++;
	}
	/*for (i = 0; i < L.length; i++)
		cout << L.elem[i];
		return true;*/
}
int main()
{
	SqList L;
	cout << "1. 建立\n";
	cout << "2. 输入\n";
	cout << "3. 插入\n";
	cout << "4. 取值\n";
	cout << "5. 查找\n";
	cout << "6. 删除\n";
	cout << "7. 输出\n";
	cout << "0. 退出\n\n";
	int choose = -1;
	while (choose != 0)
	{
		cout << "请选择：";
		cin >> choose;
		switch (choose)
		{
		case 1:
			if (InitList(L))
				cout << "顺序表初始化成功！" << endl;
			break;
		case 2:
			int len;
			cout << "请输入顺序表长度:";
			cin >> len;
			if (InPutList(L, len))
				cout << "输入成功" << endl;
			break;
		case 3:
			int i, x;
			cout << "请输入插入位置和插入值：" << endl;
			cin >> i;
			cin >> x;
			if (ListInsert(L, i, x))
				cout << "插入成功！" << endl;
			break;
		case 4:
			int m;
			cout << "请输入取值的元素位置：";
			cin >> m;
			if (GetElem(L, i, m))
				cout << m << endl;
			break;
		case 5:
			int e;
			cout << "请输入要查找的值：";
			cin >> e;
			if (LocateElem(L, e))
				cout << LocateElem(L, e) << endl;
			else
				cout << "没有找到" << endl;
			break;
		case 6:
			int j;
			cout << "请输入删除位置：";
			cin >> j;
			if (ListDelete(L, j))
				cout << "删除成功！" << endl;
			break;
		case 7:
			cout << "输出顺序表为：";
			OutPutList(L);
			cout << endl;
			break;
		}
	}
	system("pause");
	return 0;
}
