#include<iostream>
using namespace std;

//划分函数
int partition(int *a,int low,int high)
{
	int key = a[low];
	while(low<high)
	{
		while(low<high&&key<a[high]) high--;
		if(low<high)
		{
			a[low] = a[high];
			low++;
		}
		while(low<high&&key>a[low]) low++;
		if(low<high)
		{
			a[high] = a[low];
			high++;
		}
	}
	a[low] = key;
	return low;
}

//快速排序
void quickSort(int *a,int low,int high)
{
	if(low<high)
	{
	//规定划分点
		int pi = partition(a,low,high);
		quickSort(a,low,pi-1);
		quickSort(a,pi+1,high);
	}
}

int main()
{
	int a[] = {7,9,3,8,5,0,6};
	
	int n = sizeof(a)/sizeof(a[0]);
	quickSort(a,0,n-1);
	
	for(int i =0;i<n;i++)
	{
		cout<<a[0]<<'\t';
	}
	cout<<endl;
	
	return 0;
}
