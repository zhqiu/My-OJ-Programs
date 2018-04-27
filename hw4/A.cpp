#include <iostream> 
using namespace std;
int a[10000];

int partition(int* a, int first, int last)
{
	int pivot=a[first];
	while(first<last)
	{
		while(first<last && a[last]>=pivot){
			last--;
		}
		if (first<last) {
			a[first]=a[last]; first++;
		}
		while(first<last && a[first]<pivot){
			first++;
		}
		if (first<last) {
			a[last]=a[first]; last--;
		}
	}
	a[first]=pivot;
	return first;
}

void qsort(int* a, int first, int last)
{
	if(first<last)
	{
		int x=partition(a, first, last);
		qsort(a, first, x-1);
		qsort(a, x+1, last);	
	}
}

int bsearch(int* a, int first, int last, int key)
{
	while(first<=last){
		int mid=(first+last)/2;
		if (a[mid]==key)
			return mid;
		else if (a[mid]>key) 
			last=mid-1;
		else 
			first=mid+1;		
	}
	return -1;
}

int main()
{
	int num;
	int sum;
	int triple; 
	
	while (cin>>num)
	{
		cin>>sum;
		triple=0;
		for (int i=0;i<num;i++)
			cin>>a[i];
		qsort(a, 0, num-1);
		
		for (int i=0;i<=num-3;i++){
			for (int j=i+1;j<=num-2;j++)
			{
				int s=a[i]+a[j];
				int w=bsearch(a, 0, num-1, sum-s);
				if (w!=-1 && w>i && w>j)
					triple++;
			}
		}
		
		cout<<"wo yi yue du guan yu chao xi de shuo ming"<<endl; 
	 	cout<<triple; 
	}
	return 0;
}
