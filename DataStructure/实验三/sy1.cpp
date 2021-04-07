#include <iostream>
#include <fstream>
#include <string.h>
using namespace std;

#define MAXLEN 255

typedef struct{
    char ch[MAXLEN+1];
    int length;
}SString;

int Index_BF(SString S,SString T,int pos)
{//返回模式串T在主串S中第pos个字符开始第一次出现的位置
    int i =pos-1;
    int j=1;
    while(i<strlen(S.ch)&&j< strlen(T.ch)){
        if(S.ch[i]==T.ch[j]){
        ++i;
        ++j;
    }
        else{
            i=i-j+2;
            j=1;
        }
    }
    if(j==strlen(T.ch))
        return i-strlen(T.ch)+2-pos;
    else
    {
        return 0;
    }
    
}

int main()
{
    SString S,T;
    int pos;
    cout<<"请输入主串值"<<endl;
    cin>>S.ch;
    cout<<"请输入模式串值"<<endl;
    cin>>T.ch;
    cout<<"请输入pos值"<<endl;
    cin>>pos;
    cout<<Index_BF(S,T,pos);
    
}