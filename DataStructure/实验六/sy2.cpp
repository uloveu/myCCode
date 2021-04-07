#include<iostream>
using namespace std;
#define ENDFLAG '#'
//char a[10]={'5','6','7','2','1','9','8','10','3','4','#'};//全局变量

//结点数据的结构
typedef struct ElemType{	
	char key;
}ElemType;

typedef struct BSTNode{
	ElemType data;	//结点数据域
	BSTNode *lchild,*rchild;	//左右孩子指针
}BSTNode,*BSTree;

//算法7.4　二叉排序树的递归查找
BSTree SearchBST(BSTree T,char key) {
    if(!T)
    {
        return NULL;
    }
    else
    {
        if(T->data.key == key) return T;
        else if(T->data.key>key) return SearchBST(T->lchild,key);
        else return SearchBST(T->rchild,key);
    }   
} // SearchBST

//二叉排序树的插入
void InsertBST(BSTree &T,ElemType e ) {
  //当二叉排序树T中不存在关键字等于e.key的数据元素时，则插入该元素
    if(!T){
        BSTNode *S;
        S = new BSTNode;
        S->data = e;
        S->lchild=S->rchild=NULL;
        T=S;
    }
    else if(e.key<T->data.key) InsertBST(T->lchild,e);
    else InsertBST(T->rchild,e);
}// InsertBST

//二叉排序树的创建
void CreateBST(BSTree &T ) {
  //依次读入一个关键字为key的结点，将此结点插入二叉排序树T中
  T=NULL;
  ElemType e;
  cin>>e.key;        //???
  while(e.key!=ENDFLAG){   	//ENDFLAG为自定义常 量，作为输入结束标志
    InsertBST(T, e);          	//将此结点插入二叉排序树T中
    cin>>e.key;			//???
  }//while            
}//CreatBST

//二叉排序树的删除
void DeleteBST(BSTree &T,char key) {
  //从二叉排序树T中删除关键字等于key的结点
  BSTree p=T;   BSTree f=NULL;                     			//初始化
  BSTree q;
  BSTree s;
  /*------------下面的while循环从根开始查找关键字等于key的结点*p-------------*/
  while(p)
  {
      if(p->data.key==key) break;
      f=p;
      if(p->data.key>key) p=p->lchild;
      else p=p->rchild;
  }
  if(!p) return;
  
  q=p;
  if((p->lchild)&&(p->rchild))
  {
      s=p->lchild;
      while (s->rchild)
      {
          q=s;
          s=s->rchild;
      }
      p->data=s->data;
      if(q!=p) q->rchild=s->lchild;
      else q->lchild=s->lchild;
      delete s;
      return;
  }
  else if(!p->rchild){
      p=p->lchild;
  }
  else if(!p->lchild){
      p=p->rchild;
  }
  
  if(!f) T=p;
  else if(q==f->lchild) f->lchild=p;
  else f->rchild=p;
  delete q;
}//DeleteBST


//中序遍历
void InOrderTraverse(BSTree &T)
{
	if(T)
	{
	InOrderTraverse(T->lchild);
	cout<<T->data.key;
	InOrderTraverse(T->rchild);
	}
}

int main(void)
{
	BSTree T;
	cout<<"请输入若干字符，用回车区分，以#结束输入"<<endl;
	CreateBST(T);
	cout<<"当前有序二叉树中序遍历结果为"<<endl;
	InOrderTraverse(T);
    cout<<endl;
	char key;//待查找或待删除内容
	cout<<"请输入待查找字符"<<endl;
	cin>>key;
	BSTree result=SearchBST(T,key);
	if(result)
	{cout<<"找到字符"<<key<<endl;}
	else
	{cout<<"未找到"<<key<<endl;}
	cout<<"请输入待删除的字符"<<endl;
	cin>>key;
	DeleteBST(T,key);
	cout<<"当前有序二叉树中序遍历结果为"<<endl;
	InOrderTraverse(T);
    cout<<endl;
	system("pause");   //系统暂停
    return 0;
}
