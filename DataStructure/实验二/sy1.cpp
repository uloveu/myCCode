#include <iostream>
#include <fstream>
using namespace std;

typedef int SElemType;
typedef bool Status;
typedef struct StackNode
{//链栈的存储结构
    SElemType data;
    StackNode *next;
}StackNode,*LinkStack;//结点和栈顶指针

//创建栈，栈顶指针置空
Status InitStack(LinkStack &S)
{
    S=NULL;
    return true;
}

//入栈操作(将值为e的元素入栈)
Status Push(LinkStack &S,SElemType e)
{
    LinkStack p;
    p = new StackNode;
    p->data = e;
    p->next = S;
    S = p;
    return true;
}

//出栈（栈顶元素出栈并将值赋给e）
Status Pop(LinkStack &S,SElemType &e)
{   
    LinkStack p;
    p = new StackNode;
    if(S==NULL) return false;
    e = S->data;
    p = S;
    S=S->next;
    delete p;
    return true;
}

//取栈顶元素
 SElemType GetTop(LinkStack S)
 {
     if(S != NULL) 
         return S->data;
 }

int main(void)
{
	LinkStack L;
	cout << "1. 创建\n";
	cout << "2. 入栈\n";
	cout << "3. 出栈\n";
	cout << "4. 栈顶元素\n";
    cout << "0.  退出\n";
	int choose = -1;
    int x;
    while(choose!=0)
    {
        cout<<"请选择"<<endl;
        cin>>choose;
        switch(choose)
        {
            case 1:
                if(InitStack(L))
                    cout<<"栈创建成功"<<endl;
                break;
            case 2:
                int e;
                cout<<"请输入要插入的值"<<endl;
                cin>>e;
                if(Push(L,e))
                    cout<<"入栈成功";
                break;
            case 3:
                if(Pop(L,x))
                    cout<<"出栈元素为"<< x <<endl;
                    break;
             case 4:
                 cout<<"栈顶元素为"<<GetTop(L)<<endl;
                 break;
        }
    }
    return 0;
}