#include <iostream> 
using namespace std; 

void Sort(int*, int);

int main()
{ 
    int n,tag; 
    while(cin >> n)
	{
		int* a=new int[n];
		for (int i=0;i<n;i++)
			cin>>a[i];
		cin>>tag;
		Sort(a, n);
		for (int i=0;i<n-1;i++)
			for (int j=i+1;j<n;j++)
				if (a[i]+a[j]==tag)
					cout<<a[i]<<" "<<a[j]<<endl;	
	}  
    return 0;
}

void Sort(int* a, int n)
{
	int min;
	for (int i=0;i<n;i++)
	{
		min=i;
		for (int j=i+1;j<n;j++)
		{
			if (a[j]<a[min])
				min=j; 	
		}
		int temp=a[i];
		a[i]=a[min];
		a[min]=temp;
	}
}
