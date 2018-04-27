#include <iostream>
#include <string>
using namespace std;

struct Data
{
	string raw_str;
	string proc_str;
};

void Process(Data* data, int num)
{
	for (int i=0;i<num;i++)
	{
		data[i].proc_str=data[i].raw_str;
		int len=data[i].proc_str.length(); 
		for (int j=0;j<len;j++)
		{
			int min=j; 
			for (int k=j+1;k<len;k++)
				if (data[i].proc_str[k]<data[i].proc_str[min])
					min=k;
			char temp=data[i].proc_str[j];
			data[i].proc_str[j]=data[i].proc_str[min];
			data[i].proc_str[min]=temp; 
		} 
	}
}

int Partition(Data* data, int start, int end)
{
	string x=data[end].proc_str;
	int i=start-1;
	for (int j=start;j<=end-1;j++)
		if (data[j].proc_str.compare(x)<0)
		{
			i++;
			Data temp=data[j];
			data[j]=data[i];
			data[i]=temp;
		}
	Data temp=data[end];
	data[end]=data[i+1];
	data[i+1]=temp;
	return i+1; 
		
} 

void qSort(Data* data, int start, int end)
{
	if (start<end)
	{
		int i=Partition(data, start, end);	
		qSort(data, start, i-1);
		qSort(data, i+1, end);
	}
}

int main()
{
	int num;
	
	while (cin>>num)
	{
		Data* data=new Data[num];
		for (int i=0;i<num;i++)
			cin>>data[i].raw_str;
		
		Process(data, num);  
		qSort(data, 0, num-1); 
	
		cout<<"wo yi yue du guan yu chao xi de shuo ming"<<endl; 
		int num_anagram=0;
		for (int i=0;i<num-1;i++)
		{
			if (data[i].proc_str.compare(data[i+1].proc_str)==0)
			{
				num_anagram++;
				while (i+1<num && data[i].proc_str.compare(data[i+1].proc_str)==0)
					i++;
			}  
		}
			
		cout<<num_anagram<<endl;
		
		string* data_out=new string[num_anagram];
		int p_data_out=0;
	
		for (int i=0;i<num-1;i++)
		{
			int min=-1;
			if (data[i].proc_str.compare(data[i+1].proc_str)==0)
			{
				min=i;
				while (i+1<num && data[i].proc_str.compare(data[i+1].proc_str)==0)
				{
					if (data[i+1].raw_str.compare(data[min].raw_str)<0)
						min=i+1;
					i++;
				}
				data_out[p_data_out++]=data[min].raw_str;
			}  	
		} 
		for (int i=0;i<num_anagram;i++)
		{
			int min=i;
			int j;
			for (j=i+1;j<num_anagram;j++)
				if (data_out[j].compare(data_out[min])<0)
					min=j;
			string temp=data_out[i];
			data_out[i]=data_out[min];
			data_out[min]=temp;
		}
		for (int i=0;i<num_anagram;i++)
			cout<<data_out[i]<<endl;
		delete[] data;
	}
	return 0;
}
