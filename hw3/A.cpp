#include <stdio.h>
 
struct MaxHeap{
	int* MaxHeap;
	int size;
};

struct MinHeap{
	int* MinHeap;
	int size;
}; 

void MaxHeapify(struct MaxHeap& a, int i)  
{
	int temp=a.MaxHeap[i];
	int j=2*i+1;
	
	while(j<=a.size)
	{
		if (j<a.size && a.MaxHeap[j+1]>a.MaxHeap[j]) j++;
		if (temp>a.MaxHeap[j]) break;
		else{
			a.MaxHeap[i]=a.MaxHeap[j];
			i=j;
			j=2*j+1;
		}
	}
	a.MaxHeap[i]=temp; 
}  

void MaxHeapInsert(struct MaxHeap& a, int key)
{
	a.size++;
	a.MaxHeap[a.size]=key;
	int i=a.size;
	while(i>0 && a.MaxHeap[(i-1)/2]<a.MaxHeap[i]){
		int temp=a.MaxHeap[(i-1)/2];
		a.MaxHeap[(i-1)/2]=a.MaxHeap[i];
		a.MaxHeap[i]=temp;
		i=(i-1)/2;
	}
} 
 
void MinHeapify(struct MinHeap& a, int i)  
{
	int temp=a.MinHeap[i];
	int j=2*i+1;
	
	while(j<=a.size)
	{
		if (j<a.size && a.MinHeap[j+1]<a.MinHeap[j]) j++;
		if (temp<a.MinHeap[j]) break;
		else{
			a.MinHeap[i]=a.MinHeap[j];
			i=j;
			j=2*j+1;
		}
	}
	a.MinHeap[i]=temp; 
} 
 
void MinHeapInsert(struct MinHeap& a, int key)
{
	a.size++;
	a.MinHeap[a.size]=key;
	int i=a.size;
	while(i>0 && a.MinHeap[(i-1)/2]>a.MinHeap[i]){
		int temp=a.MinHeap[(i-1)/2];
		a.MinHeap[(i-1)/2]=a.MinHeap[i];
		a.MinHeap[i]=temp;
		i=(i-1)/2;
	}
} 

int main(){
	
	int len=500000;  
	
	struct MaxHeap maxH;
	maxH.MaxHeap = new int[len];
	maxH.size=-1;
	
	struct MinHeap minH;
	minH.MinHeap = new int[len];
	minH.size=-1;  
	 
    int num;
    while(scanf("%d", &num) != EOF){ 
    
    	int max_maxH=maxH.MaxHeap[0];
    	int min_minH=minH.MinHeap[0];
    	if (maxH.size==-1 || (num<max_maxH && maxH.size<=minH.size)){
    		MaxHeapInsert(maxH, num); 
		}
    	else if(minH.size==-1 || (num>min_minH && minH.size<=maxH.size) ){
    		MinHeapInsert(minH, num); 
		} 
		else if(num<maxH.MaxHeap[0] && maxH.size>minH.size){
			MinHeapInsert(minH, max_maxH);
			maxH.MaxHeap[0]=num;
    		MaxHeapify(maxH, 0);
		} 
		else if(num>min_minH && minH.size>maxH.size){
			MaxHeapInsert(maxH, min_minH);
			minH.MinHeap[0]=num;
    		MinHeapify(minH, 0);
		}
		else if(minH.size>maxH.size){
			MaxHeapInsert(maxH, num); 
		}	
		else{
			MinHeapInsert(minH, num); 
		}
		
		if(maxH.size>=minH.size)
    		printf("%d ", maxH.MaxHeap[0]);
    	else if(maxH.size<minH.size)
    		printf("%d ", minH.MinHeap[0]);
	}
    return 0;
}
