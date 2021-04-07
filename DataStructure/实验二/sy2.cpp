#include <iostream>
#include <fstream>
using namespace std;

typedef int QElemType;
typedef int SElemType;

#define MAXQSIZE 100
typedef struct
{
    QElemType *base;
    int front;
    int rear;
}SqQueue;

bool InitQueue(SqQueue &Q)
{//循环队列初始化(构造空队列)
    Q.base = new QElemType[MAXQSIZE];
    if(!Q.base) return false;
    Q.front = Q.rear=0;
    return true;
}

bool EnQueue(SqQueue &Q,QElemType e)
{//入队操作
    if((Q.rear+1)%MAXQSIZE==Q.front) //判断队满
        return false;
    Q.base[Q.rear]=e;
    Q.rear=(Q.rear+1)%MAXQSIZE; //队尾指针加一
    return true;
}

int DeQueue(SqQueue &Q,QElemType &e)
{//出队操作
    if(Q.rear==Q.front) //判断队空
        return false;
    e = Q.base[Q.front];
    Q.front = (Q.front+1)%MAXQSIZE;
    return e;
}

SElemType GetHead(SqQueue Q)
{
    if(Q.front!=Q.rear)
        return Q.base[Q.front];
}

int main(void)
{
    SqQueue L;
	cout << "1. 创建队列\n";
	cout << "2. 入栈=队\n";
	cout << "3. 出队\n";
	cout << "4. 队头元素\n";
    cout << "0.  退出\n";
	int choose = -1;
    int x=0;
    while(choose)
    {
         cout<<"请选择"<<endl;
        cin>>choose;
        switch(choose)
        {
            case 1:
                if(InitQueue(L))
                    cout<<"队列创建成功"<<endl;
                break;
            case 2:
                int e;
                cout<<"请输入要入队的值"<<endl;
                cin>>e;
                if(EnQueue(L,e))
                    cout<<"入队成功"<<endl;
                break;
            case 3:
                if(DeQueue(L,x))
                    cout<<"出队元素为"<< x <<endl;
                    break;
            case 4:
                cout<<"队头元素为"<<GetHead(L)<<endl;

    }
}
}

