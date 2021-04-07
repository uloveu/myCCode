#include <iostream>
using namespace std;
int main()
{
    int i, j, m, n, k = 0;
    int realleft=1,realright=1;
    int left[100];
    int right[100];
    char ch[1000][1000] = {""};
    scanf("%d %d", &m, &n);
    for (i = 0; i < m; i++)
        for (j = 0; j < n; j++)
        {
            cin>>ch[i][j];
        }
    for (i = 0; i < m; i++)
        for (j = 0; j < n; j++)
        {
            if (ch[i][j] == '*')
            {
                left[k] = i;
                right[k] = j;
                k++;
            }
        }
    if(k==0)
        printf("NO");
    else if (k == 1)
    {
        printf("YES\n");
        printf("%d %d", left[0]+1, right[0]+1);
    }
    else if (k == 2)
    {
        if (left[0] == left[1] || right[0] == right[1])
        {
            printf("YES\n");
            printf("%d %d", left[0]+1, right[0]+1);
        }
        else
            printf("NO");
    }
    else
    {
        /*left = left[1];
        right = right[2];
        newleft = left[2];
        newright = right[1];*/
        if(ch[left[1]][right[0]]=='*')
            {
                realleft = left[1];
                realright = right[0];
                for (i = 2; i <= k; i++)
                {
                    if ((left[i] == realleft || right[i] == realright))
                    {
                        printf("YES\n");
                        printf("%d %d",realright+1,realright+1);
                    }
                    else
                    {
                        printf("NO1");
                        break;
                    }
                    
                }
            }
        else
            printf("NO");        

    }
}
