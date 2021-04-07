#include <iostream>
#include <map>
using namespace std;
bool findMostFrequentInArray(int *a, int size, int &val)
{
    if (size == 0)
    {
        return false;
    }
    map<int, int> m;
    for (int i = 0; i < size; i++)
    {
        if (++m[a[i]] >= m[val])
        {
            val = a[i];
        }
        return true;
    }

int main()
{
    int i, j, m, n, k = 0;
    int realleft = 1, realright = 1,&val1=0,&val2=0;
    int left[100];
    int right[100];
    char ch[1000][1000] = {""};
    scanf("%d %d", &m, &n);
    for (i = 0; i < m; i++)
        for (j = 0; j < n; j++)
        {
        cin >> ch[i][j];
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
    if (k == 0)
        printf("NO");
    else if (k == 1)
    {
        printf("YES\n");
        printf("%d %d", left[0] + 1, right[0] + 1);
    }
    else if (k == 2)
    {
        if (left[0] == left[1] || right[0] == right[1])
        {
        printf("YES\n");
        printf("%d %d", left[0] + 1, right[0] + 1);
        }
    else
        printf("NO");
    }
    else
    {
        findMostFrequentInArray(left, k, val1);
        findMostFrequentInArray(right, k, val2);
        if (ch[val1][val2] == '*')
        {
        printf("YES\n");
        printf("%d %d", val1, val2);
        }
        else
        {
            printf("NO");
        }
    }
}