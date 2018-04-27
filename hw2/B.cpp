#include <iostream>
#include <string>
using namespace std;

long inversions=0;

void merge(string* str, long first, long mid, long last);

void Inversions(string* str, long first, long last)
{
	if (first>=last)
		return;
	long mid=(first+last)/2;
	Inversions(str, first, mid);
	Inversions(str, mid+1, last);
	merge(str, first, mid, last);
}

void merge(string* str, long first, long mid, long last)
{ 
	string* temp=new string[last-first+1];
	int p=first, q=mid+1, p_temp=0;
	while(p<=mid && q<=last)
	{
		if (str[p].compare(str[q])<=0)
		{
			temp[p_temp]=str[p];
			p++; p_temp++;
		}
		else
		{
			temp[p_temp]=str[q];
			q++; p_temp++;
			inversions+=mid-p+1;
		}
	}
	if (p<=mid)
		for (;p<=mid;p++)
			temp[p_temp++]=str[p];
	else if (q<=last)
	 	for (;q<=last;q++)
			temp[p_temp++]=str[q];
	int k=0;
	for (int i=first;i<=last;i++)
		str[i]=temp[k++];
	delete[] temp;
}

int main()
{
	long num;
	
	while (cin>>num)
	{
		string* str=new string[num]; 
		inversions=0;
		for (int i=0;i<num;i++)
			cin>>str[i]; 
		Inversions(str, 0, num-1);
		cout<<"wo yi yue du guan yu chao xi de shuo ming"<<endl;
		cout<<inversions<<endl;
		delete[] str;
	}
	return 0;
}

