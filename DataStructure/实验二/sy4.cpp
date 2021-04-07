#include <iostream>
#include <fstream>
using namespace std;

typedef struct StackNode
{//链栈的存储结构
    char data;
    StackNode *next;
}StackNode,*LinkStack;//结点和栈顶指针

//创建栈，栈顶指针置空
bool InitStack(LinkStack &S)
{
    S=NULL;
    return true;
}

//入栈操作(将值为e的元素入栈)
bool Push(LinkStack &S,char e)
{
    LinkStack p;
    p = new StackNode;
    p->data = e;
    p->next = S;
    S = p;
    return true;
}

//出栈（栈顶元素出栈并将值赋给e）
bool Pop(LinkStack &S,char &e)
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

int GetTop(LinkStack S)
 {
     if(S != NULL) 
         return S->data;
 }

bool StackEmpty(LinkStack &S)
{
    if(S==NULL)
        return true;   
}

bool In(char ch)
{
    if(ch=='+' || ch=='-' || ch=='*' || ch=='/'||ch=='('||ch==')'||ch=='#')
        return true;
}

char Precede(char a,char b)
{
    if ((a == '(' && b == ')') /*|| (theta1 == '#' && theta2 == '#')*/) {
		return '=';  // 如果都是(或#则优先级别相等
	}
	else if (a == '(' || a == '#' || b == '(' || ((a
		== '+' || a == '-') && (b == '*' || b == '/'))) {
		return '<';
	}
	else {
		return '>';
	}
}

char Oprate(char a,char ch, char b)
{
    switch(ch)
    {
        case '+':
           return (a - '0') + (b - '0') + 48;
            ;
            break;
        case '-':
            return (a - '0') - (b - '0') + 48;
            break;
        case '*':
            return (a - '0') * (b - '0') + 48;
            break;
        case '/':
            return (a - '0') / (b - '0') + 48;
            break;
    }
}

char EvaluateExpression()         //以字符形式输出
{
    char ch;
    char theta;                   //运算符
    char a,b,x;
    LinkStack OPND,OPTR;
    InitStack(OPND);              //存储读取数字和操作结果
    InitStack(OPTR);              //存储运算符
    Push(OPTR,'#');               //将'#'存入栈底，可以作为循环结束的条件
    cin>>ch;
    while(ch!='#'||GetTop(OPTR)!='#') //没有将表达式读取完或者optr栈内运算符没有使用完时执行
    {
        if(!In(ch))                  //不是运算符则进OPND
            {
                Push(OPND,ch);
                cin>>ch;
            }
        else
            switch(Precede(GetTop(OPTR),ch))
            {
                case '<':
                    Push(OPTR,ch);
                    cin>>ch;
                    break;
                case '>':
                    Pop(OPTR,theta);    //从OPTR取栈顶运算符先计算
                    Pop(OPND,b);
                    Pop(OPND,a);
                    Push(OPND,Oprate(a,theta,b));//将运算结果压入栈顶
                    break;
                case '=':                     //栈顶元素为(''且ch为')'
                    Pop(OPTR,x);              //弹出栈顶'(',配对成功
                    cin>>ch;
                    break;
            }
    }
    return GetTop(OPND);
}

int main(void)
{
    cout<<EvaluateExpression();
}