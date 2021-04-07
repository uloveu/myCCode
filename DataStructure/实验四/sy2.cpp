#include <iostream>
#include <algorithm>
#include <string.h>
using namespace std;

typedef struct
{
    int weight;
    int parent;
    int lchild, rchild;
} HTNode, *HuffmanTree;

typedef char **HuffmanCode;

// int min(HuffmanTree HT,int k)
// {
//    int i = 0;
//    int min;        //用来存放weight最小且parent为-1的元素的序号
//    int min_weight; //用来存放weight最小且parent为-1的元素的weight值
 
// //先将第一个parent为-1的元素的weight值赋给min_weight,留作以后比较用。
// //注意，这里不能按照一般的做法，先直接将HT[0].weight赋给min_weight，
// //因为如果HT[0].weight的值比较小，那么在第一次构造二叉树时就会被选走，
// //而后续的每一轮选择最小权值构造二叉树的比较还是先用HT[0].weight的值来进行判断，
// //这样又会再次将其选走，从而产生逻辑上的错误。
//    while(HT[i].parent != 0)
//    i++;
//    min_weight = HT[i].weight;
//    min = i;
 
// //选出weight最小且parent为-1的元素，并将其序号赋给min
//    for(;i<k;i++)
//   {
//      if(HT[i].weight<min_weight && HT[i].parent==0)
//       {
//         min_weight = HT[i].weight;
//         min = i;
//       }
//   }
 
//    //选出weight最小的元素后，将其parent置1，使得下一次比较时将其排除在外。
//    HT[min].parent = 1;
//    return min;
// }

// void Select(HuffmanTree HT,int k,int &min1,int &min2)
// {
//    min1 = min(HT,k);
//    min2 = min(HT,k);
// }


void Select(HuffmanTree &HT, int m, int &s1, int &s2)
{
    int k = 0;
    int array[100];
    for (int i = 1; i <= m; i++)
    {
        if (HT[i].parent == 0)
        {
            array[i] = HT[i].weight;
            k++;
        }
    }
    sort(array, array + k);
    for (int i = 1; i <= m; i++)
    {
        if (HT[i].weight == array[1])
            s1 = i;
        if (HT[i].weight == array[2])
            s2 = i;
    }
}

// 构建哈夫曼树
void CreateHuffmanTree(HuffmanTree &HT, int n)
{
    int m;
    int s1, s2;
    if (n <= 1)
        return;
    m = 2 * n - 1;
    HT = new HTNode[m + 1];
    for (int i = 1; i <= m; ++i)
    {
        HT[i].parent = 0;
        HT[i].lchild = 0;
        HT[i].rchild = 0;
    }
    for (int i = 1; i <= n; ++i)
        cin >> HT[i].weight;

    for (int i = n + 1; i <= m; ++i)
    {
        Select(HT, i - 1, s1, s2);
        HT[s1].parent = i;
        HT[s2].parent = i;
        HT[i].lchild = s1;
        HT[i].rchild = s2;
        HT[i].weight = HT[s1].weight + HT[s2].weight;
    }
}

// 根据哈夫曼树求哈夫曼编码
HuffmanCode CreatHuffmanCode(HuffmanTree &HT, HuffmanCode &HC, int n)
{
    int c, f, start;
    char *cd;
    HC = new char *[n + 1];
    cd = new char[n];
    cd[n - 1] = '\0';
    for (int i = 1; i <= n; i++)
    {
        c = i;
        start = n - 1;
        f = HT[i].parent;
        while (f!=0)
        {
            --start;
            if (HT[f].lchild == c)
                cd[start] = '0';
            else
                cd[start] = '1';
            c = f;
            f = HT[f].parent;
        }
        HC[i] = new char[n - start];
        strcpy(HC[i], &cd[start]);
    }
    delete cd;
    return HC;
}

int main()
{
    HuffmanTree HT;
    HuffmanCode HC;
    int n;
    cout << "请输入结点数量" << endl;
    cin >> n;
    cout << "请输入权重值" << endl;
    CreateHuffmanTree(HT, n);
    cout << "创建成功" << endl;
    cout << "哈弗曼编码依次为:" << endl;
    HC = CreatHuffmanCode(HT, HC, n);
    for (int i = 1; i <= n; i++)
    {
        cout<<i<<":"<<" ";
        cout << HC[i] <<endl;
    }
    return 0;
}