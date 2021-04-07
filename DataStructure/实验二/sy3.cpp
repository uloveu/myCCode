#include <iostream>
#include <fstream>
using namespace std;

typedef struct StackNode
{//链栈的存储结构
    int data;
    StackNode *next;
}StackNode,*LinkStack;//结点和栈顶指针

//创建栈，栈顶指针置空
bool InitStack(LinkStack &S)
{
    S=NULL;
}

//入栈操作(将值为e的元素入栈)
bool Push(LinkStack &S,int e)
{
    LinkStack p;
    p = new StackNode;
    p->data = e;
    p->next = S;
    S = p;
    return true;
}

//出栈（栈顶元素出栈并将值赋给e）
bool Pop(LinkStack &S,int &e)
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

bool StackEmpty(LinkStack &S)
{
    if(S==NULL)
        return true;   
}

void conversion_2(int N)
{
    int e=0;
    LinkStack S;
    InitStack(S);
    while(N)
    {
        Push(S,N%2);
        N/=2;
    }
    while(!StackEmpty(S))
    {
        Pop(S,e);
        cout<<e;
    }
}

void conversion_8(int N)
{
    int e=0;
    LinkStack S;
    InitStack(S);
    while(N)
    {
        Push(S,N%8);
        N/=8;
    }
    while(!StackEmpty(S))
    {
        Pop(S,e);
        cout<<e;
    }
}

void conversion_16(int N)
{
    int e=0;
    LinkStack S;
    InitStack(S);
    while(N)
    {
        Push(S,N%16);
        N/=16;
    }
    while(!StackEmpty(S))
    {
        Pop(S,e);
        cout<<e;
    }
}

int main(void)
{
    int choose;
    int M;
    cout<<"请输入要转换的十进制数"<<endl;
    cin>>M;
    cout<<"请输入要转换的进制数"<<endl;
    cin>>choose;
    switch(choose)
    {   case 2:
            conversion_2(M);
            break;
        case 8:
            conversion_8(M);
            break;
        case 16:
            conversion_16(M);
            break;
    }

}