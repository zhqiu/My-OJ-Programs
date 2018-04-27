#include <iostream>  
#include <string>
#include <sstream> 
#include <vector>
#include <queue>
#include <algorithm> 
#include <assert.h>

#define N 30000
using namespace std; 

struct Edge 
{  
    short p1;
	short p2;
	short weight;
    friend bool operator < (Edge a, Edge b)  
    {  
        return a.weight>b.weight; 
    }  
};

priority_queue<Edge> Q;
int par[N];

int find(int x){
	while(par[x]>=0)
		x=par[x];
	return x;
}

void unio(int p1, int p2){
	int r1=find(p1), r2=find(p2), temp;
	if (r1!=r2){
		temp=par[r1]+par[r2];
		if(par[r2]<par[r1]){
			par[r1]=r2; par[r2]=temp;
		}
		else{
			par[r2]=r1; par[r1]=temp;
		}
	} 
}
 
int main()
{
	for(int i=0;i<N;i++)
		par[i]=-1;
	int vertex, s, t;
	cin>>vertex>>s>>t;
	assert(vertex<N); 
	int weight, va, vb;   
	while(cin>>weight>>va>>vb)
	{      
		Edge E; 
		E.p1=va; E.p2=vb; E.weight=weight;
		Q.push(E);
	}
	cout<<"I have read the rules about plagiarism punishment"<<endl;
	int weight_now=0; 
	while(!Q.empty())  
    {     
        int weight=Q.top().weight;
        int p1=Q.top().p1; int p2=Q.top().p2; 
        Q.pop(); 
        weight_now=weight;    
        if (find(p1)!=find(p2))
        	unio(p1, p2);  
        if (find(s)==find(t))
        	break;
    } 
    cout<<weight_now; 
}

