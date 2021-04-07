#include <iostream>
using namespace std;

// 二叉树链式储存结构
typedef struct BiTNode
{
    char data;
    struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree;

// 链栈的储存结构
typedef struct StackNode
{
    BiTNode data;
    struct StackNode *next;
} StackNode, *LinkStack;

// 先序遍历建立二叉链表
void CreateBiTree(BiTree &T)
{
    char ch;
    cin >> ch;
    if (ch == '#')
        T = NULL;
    else
    {
        T = new BiTNode;
        T->data = ch;
        CreateBiTree(T->lchild);
        CreateBiTree(T->rchild);
    }
}

// 链栈初始化
void InitStack(LinkStack &L)
{
    L = NULL;
}

// 判断链栈是否为空
bool StackEmpty(LinkStack &L)
{
    if (!L)
        return true;
    return false;
}

void Push(LinkStack &S, BiTree e)
{
    //在栈顶插入元素*e
    StackNode *p = new StackNode;
    p->data = *e;
    p->next = S;
    S = p;
}

//出栈（栈顶元素出栈并将值赋给e）
void Pop(LinkStack &S, BiTree e)
{
    if (S != NULL)
    {
        *e = S->data;
        StackNode *p = S;
        S = S->next;
        delete p;
    }
}

// 中序遍历的递归算法
void InOrderTraverse(BiTree &T)
{
    if (T)
    {
        InOrderTraverse(T->lchild);
        cout << T->data;
        InOrderTraverse(T->rchild);
    }
}

// 后序遍历的递归算法
void PostOrderTraverse(BiTree &T)
{
    if (T)
    {
        PostOrderTraverse(T->lchild);
        PostOrderTraverse(T->rchild);
        cout << T->data;
    }
}

// 中序遍历的非递归算法
void StackInOrderTraverse(BiTree &T)
{
    LinkStack L;
    BiTree p;
    BiTree q = new BiTNode;
    InitStack(L);
    p = T;
    // 当二叉链表为空或链栈为空时停止循环
    while (p || !StackEmpty(L))
    {
        if (p)
        {
            Push(L, p);
            p = p->lchild;
        }
        else
        {
            Pop(L, q);
            cout << q->data;
            p = q->rchild;
        }
    }
}

// // 后序遍历的非递归算法
// void StackPostOrderTraverse(BiTree &T)
// {
//     LinkStack L;
//     BiTree p;
//     BiTree q = new BiTNode;
//     InitStack(L);
//     p = T;
//     while (p || !StackEmpty(L))
//     {
//         if (p)
//         {
//             Push(L, p);
//             p->tag = 0;
//             p = p->lchild;
//         }
//         else
//         {
//             Pop(L, p);
//             if (p->tag == 0)
//             {
//                 p->tag = 1;
//                 Push(L, p);
//                 p = p->rchild;
//             }
//             else
//             {
//                 cout << p->data;
//             }
//         }
//     }
// }

int main(void)
{
    BiTree T;
    cout << "请先序顺序创建二叉树" << endl;
    CreateBiTree(T);
    cout << "中序递归遍历结果：" << endl;
    InOrderTraverse(T);
    cout << endl;
    cout << "中序非递归遍历结果：" << endl;
    StackInOrderTraverse(T);
    cout << endl;
    cout << "后序递归遍历结果：" << endl;
    PostOrderTraverse(T);
    cout << endl;
    // cout << "后序非递归遍历结果：" << endl;
    // StackPostOrderTraverse(T);
    return 0;
}