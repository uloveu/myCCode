#include<stdio.h>
#define  N   10

int main(void)
{
    int i,a[N+1];
    void selectionsort(int R[],int n);

    for(i=1;i<=N;i++)
        scanf("%d",&a[i]);
    selectionsort(a,N);
    for(i=1;i<=N;i++)
        printf("%d  ",a[i]);
}

// 选择排序
void selectionsort(int R[],int n)
{ int i,j,k;
for(i=1;i<=n-1;i++)
   {k=i;
    for(j=i+1;j<=n;j++)
      {if(R[j]>R[k])
        k=j;
       }
    if(i!=k)
     {R[0]=R[k];
      R[k]=R[i];
      R[i]=R[0];
     }
   }
}

// 插入排序
 void InsertSort(int a[],int n)
{
	int j;
	for (int i = 2; i <= n-1; i++)
	{
		if (a[i] < a[i - 1])
		{
			a[0] = a[i];
			a[i] = a[i - 1];
			for (j = i - 2; a[0] < a[j]; j--)
			{
				a[j + 1] = a[j];
			}
			a[j + 1] = a[0];
		}
	}
}

// 希尔排序
