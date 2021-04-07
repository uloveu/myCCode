#include<iostream>
#include<fstream>
#include<string.h>
using namespace std;


typedef struct{   
   char ch[600];	//若是非空串，则按串长分配存储区，否则ch为NULL   
   int len;		    //串长度   
}HString; 

void get_next(HString T,int next[]); //求next值
int Index_KMP(HString S,HString T,int pos,int next[]); //KMP算法
void Virus_detection(); //


int main()
{
	Virus_detection();
	return 0;
}

int Index_KMP(HString S,HString T,int pos,int next[])
{
    int i,j;
    i=pos;
    j=1;
    while(i<strlen(S.ch)&&j<strlen(T.ch))
    {
        if(j==0||S.ch[i] == T.ch[j])  
        {
            ++i;++j;
        }
        else j=next[j];              //模式串向右移动
    }
    if(j>=strlen(T.ch))              //当j全部匹配时，跳出循环，匹配成功
        return i-strlen(T.ch);
    else
        return 0;
}

void get_next(HString T,int next[])
{
    int i =1;
    int j = 0;
    next[1]=0;
    while(i<strlen(T.ch))
    {
        if(j==0||T.ch[i]==T.ch[j])
        {
            ++i;++j;next[i]=j;
        }
        else
        {
            j=next[j];
        }     
    }
} 

void Virus_detection()
{ 
   int num,m,flag,i,j,next[600]; char Vir[600];
   HString Virus,Person,temp;
   ifstream inFile;
   ofstream outFile;
   inFile.open("D:\\C++\\code\\.vscode\\in.txt");
   outFile.open("D:\\C++\\code\\.vscode\\out.txt");
   inFile>>num;//读取待检测的任务数
   while(num--) //依次检测每对病毒DNA和人的DNA是否匹配
   {
    inFile>>Virus.ch+1;//读取病毒DNA序列
    inFile>>Person.ch+1;//读取人的DNA序列
    strcpy(Vir,Virus.ch);
	Virus.len=strlen(Virus.ch)-1;
	Person.len=strlen(Person.ch)-1;
	flag=0;//用来标识是否匹配，初始为0，匹配后为非0
	m=Virus.len;
    for(i=m+1,j=1;j<=m;j++)
        Virus.ch[i++]=Virus.ch[j];
    Virus.ch[2*m+1]='\0';
    for(i=0;i<m;i++)
    {
        for(j=1;j<=m;j++)
            temp.ch[j]=Virus.ch[i+j];
        temp.ch[m+1]='\0';
        get_next(temp,next);
        flag=Index_KMP(Person,temp,1,next);
        if(flag) break;
    }
    if(flag) 
    {
    if(outFile.is_open())  
    {  
    outFile<<Vir+1<<" "<<Person.ch+1<<" "<<"YES"<<endl;      
    cout<<"YES"<<endl;
    }  
    else  
    {  
       cout<<"不能打开文件1!"<<endl;  
    }  
    }
    else 
    {
    if(outFile.is_open())  
    {  
    outFile<<Vir+1<<" "<<Person.ch+1<<" "<<"NO"<<endl; 
    cout<<"NO"<<endl;
    }  
    else  
    {  
       cout<<"不能打开文件2!"<<endl;  
    }  
    }
   }//while
    inFile.close();
    outFile.close();
}

