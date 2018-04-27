#include <iostream> 
using namespace std; 

void Sort(int*, int, int); 

int main()
{ 
    int k,n; 
    while(cin >> k >> n)
	{
		int* a=new int[n];
		for (int i=0;i<n;i++)
			cin>>a[i];
		Sort(a, 0, n-1);
		for (int i=(n+1)/2-k-1;i<(n+1)/2+k-1;i++)
			cout<<a[i]<<" ";
		cout<<a[(n+1)/2+k-1];
		delete[] a;	
	}  
    return 0;
}

void Sort(int* a, int start, int end)  
{  
    if (start < end)  
    {        
        int i = start, j = end, x = a[start];  
        while (i < j)  
        {  
            while(i < j && a[j]>= x)   
                j--;   
            if(i < j)  
                a[i++] = a[j];  
            while(i < j && a[i]< x) 
                i++;   
            if(i < j)  
                a[j--] = a[i];  
        }  
        a[i] = x;  
        Sort(a, start, i - 1);   
        Sort(a, i + 1, end);  
    }  
} 
