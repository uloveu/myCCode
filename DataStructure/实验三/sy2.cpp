#include <iostream>
#include <fstream>
#include <string.h>
using namespace std;

#define MAXLEN 255

typedef struct{
    char ch[MAXLEN+1];
    int length;
}SString;

void get_next(SString T,int next[]);

int Index_KMP(SString S,SString T,int pos,int next[])
{
    int i,j;
    i=pos-1;
    j=1;
    while(i<strlen(S.ch)&&j<strlen(T.ch))
    {
        if(j==0||S.ch[i] == T.ch[j])  
        {
            ++i;++j;
        }
        else j=next[j];              //模式串向右移动
    }
    if(j==strlen(T.ch))              //当j全部匹配时，跳出循环，匹配成功
        return i-strlen(T.ch)+2-pos;
    else
        return 0;
}

void get_next(SString T,int next[])
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

int main()
{
    int pos;
    SString S,T;
    cout<<"pos值"<<endl;
    cin>>pos;
    cout<<"please input the main string"<<endl;
    cin>>S.ch;
    cout<<"please input the other string"<<endl;
    cin>>T.ch;
    int next[(strlen(T.ch))];
    get_next(T,next);
    cout<<Index_KMP(S,T,pos,next);

}