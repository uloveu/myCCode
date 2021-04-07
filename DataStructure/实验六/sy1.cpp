#include<iostream>
using namespace std;
#define MAXSIZE 10
#define OK 1;

typedef struct{
	int key;//关键字域
}ElemType;

typedef struct{
	ElemType *R;
	int length;
}SSTable;

int InitList_SSTable(SSTable &L)
{
	L.R=new ElemType[MAXSIZE];
	if (!L.R)
	{
		cout<<"初始化错误";
		return 0;
	}
	L.length=0;
	return OK;
}

int Insert_SSTable(SSTable &L) 
{
	cout<<"请输入关键字序列:\n";
	for(int i=1;i<=MAXSIZE;i++)
	{
		cin>>L.R[i].key;
		L.length++;
	}
	return 1;
}

int Search_Bin(SSTable ST,int key) {
    int low = 0;
    int high = ST.length;
    while(low <= high){
        int mid = (low+high)/2;
        if (ST.R[mid].key == key)
        {
            return mid;
        }
        else if(ST.R[mid].key < key){
            low = mid +1;
        }
        else
        {
            high = mid - 1;
        }
    }
    return 0;
}// Search_Bin

void Show_End(int result,int testkey)
{
	if(result==0)
		cout<<"未找到"<<testkey<<endl;
	else
		cout<<"找到"<<testkey<<"位置为"<<result<<endl;
	return;
}

int main(void)
{
	SSTable ST;
	InitList_SSTable(ST);
	Insert_SSTable(ST);
	int testkey;
	cout<<"请输入要查找的关键字：";
	cin>>testkey;
	int result;
	result=Search_Bin(ST, testkey);
	Show_End(result,testkey);
	system("pause");   //系统暂停
    return 0;
}
