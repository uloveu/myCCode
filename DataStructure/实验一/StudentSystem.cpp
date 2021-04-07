#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#define MAXSIZE 1000
using namespace std;


//定义学生
typedef struct{
    char num[8];//8位学号
    char name[20];//学生姓名
    char xueyuan[20];//学生学院
    char zhuanye[20];//学生专业
    char banji[20];//学生班级
    char xingbie[20];//学生班级
    int age[100];//学生年龄
}Student;
Student student;


//---单链表的存储结构---
typedef struct LNode
{
   Student data;
   struct LNode *next;//节点的指针域
}LNode,*LinkList;//LinkList为指向结构体LNode的结构体类型


typedef struct{
    int length;
}T;
T list;


LinkList L;
LNode *p,*s,*q,*head;

//初始化单链表
int InitList(LinkList &L)
{
    //构造一个空的单链表
    L = new LNode;
    L->next=NULL;
    list.length=0;
    return 1;
 }
 
 
 //单链表按照序号取值
int GetElem(LinkList L,int i,Student &e)
{
    //在带头节点的链表L中根据序号i获取元素的值，用e返回L中第i个数据元素的值
    p=L->next;
    int j=1;
    while(p&&j<i)
    {
        p=p->next;
        ++j;
    }
    if(!p||j>i)
        return 0;
    e=p->data;
    return 1;
}





//单链表的姓名查找
int LocateElem(LinkList L,Student &e)
 {
    int j=0;
    p=L->next;
    while(p && strcmp((p->data).name,e.name))//如果p不为空，且p指向的数据与发送过来的数据名字不相等。执行while循环语句
    {
        p=p->next;
        ++j;
    }
    if(!p||j>list.length)
        return 0;
    e=p->data;
    return 1;
}


//单链表的插入
int ListInsert(LinkList $L,int i,Student &e)
{
    //在带头结点的链表L中第i个位置插入值为e的新节点
    p=L;int j=0;
    while(p && (j<i-1))
    {
        p=p->next;++j;
    }
    if(!p||j>i-1) return 0;
    s = new LNode;
    s->data=e;
    s->next=p->next;
    p->next=s;
    list.length++;
    return 1;
}


//单链表的删除

int ListDelete(LinkList &L,int i)
{
    //在带头节点的链表L中删除第i个元素
    p=L;int j=0;
    while((p->next) && (j<i-1))
    {p=p->next;++j;}
    if(!(p->next)||(j>i-1)) return 0;//当i>n或i<1时，删除位置不合理
    q=p->next;//临时保存被删除的节点的地址以备释放
    p->next=q->next;//改变删除节点前驱节点的指针域
    delete q;
    list.length--;
    return 1;
}

//单链表的创建（后插法)
void CreateList_H(LinkList &L,int n)
{//逆位序输入n个元素的值，建立带表头结点的单链表L
    //L=new LNode;//先建立一个带头结点的空链表
    L->next=NULL;
    Student stu;
    LNode *r;
    r=L;
    for(int i=0;i<n;++i)
    {
        p=new LNode;
        printf("学号：");
        scanf("%s",&student.num);
        printf("姓名：");
        scanf("%s",&student.name);
        printf("学院：");
        scanf("%s",&student.xueyuan);
        printf("专业：");
        scanf("%s",&student.zhuanye);
        printf("班级：");
        scanf("%s",&student.banji);
        printf("性别：");
        scanf("%s",&student.xingbie);
        printf("年龄：");
        scanf("%d",&student.age);
        list.length++;//输入元素值赋给新结点*p的数据域
        printf("\n\n");
        p->data=student;
        p->next=NULL;
        r->next=p;
        r=p;//将新结点*p插入到头结点之后
    }
}

//主函数
int main()
{
    Student student;
    InitList(L);
    int a;
    while(1) {
        printf("------------学生信息系统------------\n");
        printf("1:输入学生信息\n");
        printf("2:显示所有学生信息\n");
        printf("3:根据学生姓名查找学生信息\n");
        printf("4:根据位置查找学生信息\n");
        printf("5:添加学生信息\n");
        printf("6:删除指定位置的学生记录；\n");
        printf("7:统计表中学生个数\n");
        printf("8:退出学生信息系统\n");
        printf("请输入您的选择：");
        scanf("%d",&a);
        printf("--------------------------------------------------------");
        printf("\n");
        switch(a)//输入学生的信息；
        {
            case 1:
        {
            CreateList_H(L,5);
            printf("输入学生信息成功，请选择接下来的操作…………");
            printf("\n\n\n\n\n\n");
            break;
        }
            
            case 2://显示全部学生的信息；
        {
           printf("学号\t\t姓名\t\t学院\t\t专业\t\t班级\t\t性别\t\t\n");
           for(int i=1;i<=list.length;i++)
             {
                GetElem(L,i,student);
                printf("%s\t\t%s\t\t\t%s\t\t\%s\t\t\%s\t\t\%s\t\t\%d\t\n",student.num,student.name,student.xueyuan,student.zhuanye,student.banji,student.xingbie,student.age);
             }
             printf("\n\n\n\n\n\n");
            break;
        }
            case 3://根据学生姓名查找学生信息
        {
            int i;
            printf("请输入您要查找学生的名字：");
            scanf("%s",&student.name);
            i=LocateElem(L,student);
            if(!i)
                printf("系统中没有此学生\n");
            printf("学号:%s\t\t姓名:%s\t\t学院:%s\t\t专业:%s\t\t班级:%s\t\t性别:%s\t\t年龄:%d\n",student.num,student.name,student.xueyuan,student.zhuanye,student.banji,student.xingbie,student.age);
            printf("\n\n\n\n\n\n");
            break;
        }
         case 4://根据位置查找学生信息
        {
            int i;
            int local;
            printf("请输入要查询的位置：");
            scanf("%d",&local);
            GetElem(L,local,student);
            printf("学号:%s\t\t姓名:%s\t\t学院:%s\t\t专业:%s\t\t班级:%s\t\t性别:%s\t\t年龄:%d\n",student.num,student.name,student.xueyuan,student.zhuanye,student.banji,student.xingbie,student.age);
            printf("\n\n\n\n\n\n");
            break;
        }
         case 5://给定一个学生信息，插入到表中指定位置；
        {
            int t,i;
            printf("学号：");
            scanf("%s",&student.num);
            printf("姓名：");
            scanf("%s",&student.name);
            printf("学院：");
            scanf("%s",&student.xueyuan);
            printf("专业：");
            scanf("%s",&student.zhuanye);
            printf("班级：");
            scanf("%s",&student.banji);
            printf("性别：");
            scanf("%s",&student.xingbie);
            printf("年龄：");
            scanf("%d",&student.age);
            printf("插入位置：");
            scanf("%d",&t);
            ListInsert(L,t,student);
            if(/* DISABLES CODE */ (1))
        {
           printf("添加成功…………");
           printf("\n") ;
           printf("学号\t\t姓名\t\t学院\t\t专业\t\t班级\t\t性别\t\n");
           for(int i=1;i<=list.length;i++)
             {
                GetElem(L,i,student);
                printf("%s\t\t%s\t\t\t%s\t\t\%s\t\t\%s\t\t\%s\t\t\%d\t\n",student.num,student.name,student.xueyuan,student.zhuanye,student.banji,student.xingbie,student.age);
             }
        }
           else
               printf("插入失败，请选择正确的插入位置…………");
            printf("\n\n\n\n\n\n");
            break;
            
        }
        case 6://删除指定位置的学生信息；
        {
            int i;
            printf("请输入要删除的位置：");
            scanf("%d",&i);
            ListDelete(L,i);
            printf("删除成功…………");
            printf("\n");
            printf("学号\t\t姓名\t\t学院\t\t专业\t\t班级\t\t性别\t\n");
            for(int i=1;i<=list.length;i++)
             {
                GetElem(L,i,student);
                printf("%s\t\t%s\t\t\t%s\t\t\%s\t\t\%s\t\t\%s\t\t\%d\t\n",student.num,student.name,student.xueyuan,student.zhuanye,student.banji,student.xingbie,student.age);
             }
            printf("\n\n\n\n\n\n");
            break;
        }
        case 7://统计系统中学生个数
        {
            printf("系统中学生个数：%d\n",list.length);
            printf("\n\n\n\n\n\n");
            break;
        }
        case 8://退出系统；
         {
            return 0;
         }
        default:
         {
            printf("输入错误，请重新输入");
            printf("\n\n\n\n\n\n");
         }
     }
  }
}

