#include<stdio.h>
int max(int a[], int length)
{
	int maxsum = 0;
	int tsum;
	int i, j;
	for (i = 0; i < length; i++)
	{
		tsum = 0;
		for (j = i; j < length; j++)
		{
			tsum += a[j];
			if (tsum > maxsum)
				maxsum = tsum;
		}
	}
	return maxsum;
}
int main()
{
	int length; int flag = 0;
	scanf("%d",&length);
	int a[20];
	for (int i = 0; i < length; i++)
	{
		scanf("%d", &a[i]);
		if (a[i] < 0)flag++;
	}
	if (flag == length)
		printf("0");
	else
	{
		printf("%d", max(a, length));
	}
}