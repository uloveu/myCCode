#include <iostream>
#include <fstream>
using namespace std;
typedef int status;
typedef int datatype;
typedef struct ListNode
{
	struct ListNode *next;
	datatype data;
} ListNode, *List;
int n;
status initList(List &L)
{ //算法2.6 初始化链表
	L = new ListNode;
	L->next = NULL;
	return 0;
}
status createList(List &L, int n)
{ //算法2.11或者//算法2.12 创建空链表
	List s, r;
	r = L;
	cout << "请输入链表：" << endl;
	for (int i = 0; i < n; i++)
	{
		s = new ListNode;
		cin >> s->data;
		s->next = NULL;
		/*	s->next=L->next;
		L->next=s;
	    s->next=r->next;*/
		//前插法
		r->next = s;
		r = s; //后插法
	}
	return 0;
}
status insertList(List &L, int i, datatype x)
{ //算法2.9
	List s, p;
	p = L;
	int j = 0;
	while (p && j < i - 1)
	{
		p = p->next;
		++j;
	}
	if (!p || j > i - 1)
		return 0;
	s = new ListNode;
	s->next = NULL;
	s->data = x;
	s->next = p->next;
	p->next = s;
	return 0;
}
status deleteList(List &L, int i)
{ //算法2.10
	List p, q;
	p = L;
	int j = 0;
	while ((p->next) && (j < i - 1))
	{
		p = p->next;
		++j;
	}
	if (!(p->next) && (j > i - 1))
		return 0;
	q = p->next;
	p->next = q->next;
	delete q;
	return 0;
}
status OutPutList(List L)
{ //单链表输出操作
	List p;
	p = L->next;
	while (p != NULL)
	{
		cout << p->data << " ";
		p = p->next;
	}
	return 0;
}
status GetElem(List L, int i, datatype &e)
{
	int j;
	List p;
	p = L->next;
	j = 1;
	while (p && j < 1)
	{
		p = p->next;
		++j;
	}
	if (!p || j > 1)
		return false;
	e = p->data;
	return true;
}
ListNode *LocateElem(List L, datatype e)
{
	List p;
	p = L->next;
	while (p && p->data != e)
	{
		p = p->next;
	}
	return p;
}
int main()
{
	List L;
	cout << "1. 建立\n";
	cout << "2. 输入\n";
	cout << "3. 取值\n";
	cout << "4. 查找\n";
	cout << "5. 插入\n";
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
			if (initList(L))
				cout << "建成一个空单链表成功！";
			break;
		case 2:
			int n;
			cout << "请输入链表长度：";
			cin >> n;
			createList(L, n);
			cout << "创建单链表完成!" << endl;
			break;
		case 3:
			int m,h;
			cout << "请输入要取值的序号" << endl;
			cin >> m;
			if (GetElem(L, m, h))
				cout << h << endl;
			break;
		case 4:
		int e;
			cout << "请输入要查找的值：";
			cin >> e;
			if (LocateElem(L, e))
				cout << LocateElem(L, e) << endl;
			else
				cout << "没有找到" << endl;
			break;

		case 5:
			int i, x;
			cout << "请输入插入位置和插入值：";
			cin >> i;
			cin >> x;
			if (insertList(L, i, x))
				cout << "插入成功！" << endl;
			break;
		case 6:
			int j;
			cout << "请输入删除位置：";
			cin >> j;
			if (deleteList(L, j))
				cout << "删除成功！" << endl;
			break;
		case 7:
			cout << "输出单链表为：";
			OutPutList(L);
			cout << endl;
			break;
		}
	}
	system("pause");
	return 0;
}
