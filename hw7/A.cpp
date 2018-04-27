#include <iostream>  
#include <stdio.h> 
#include <vector>
#include <algorithm>
#include <cstring>
#include <assert.h>

#define N 20000
using namespace std; 

struct Edge
{
	short p1;
	short p2;
	short weight;
};

vector<Edge> G[N]; 
vector<Edge> Gt[N];
short color[N];
short topo[N]; 
int longpath[N];
int topoNum=0;

void dfsTopo(int v)
{
	color[v]=1;
	for(int i=0;i<G[v].size();i++){
		int w=G[v][i].p2;
		if (color[w]==0)
			dfsTopo(w);
	}
	topo[v]=topoNum++;
	color[v]=2;
	return;
}

void dfsTopoSweep(int vertex)
{
	for(int i=0;i<vertex;i++)
	{
		if (color[i]==0)
			dfsTopo(i);
	}
	return;
}

void GT(int vertex)
{
	for(int i=0;i<vertex;i++){
		for(int j=0;j<G[i].size();j++){
			Edge e;
			e.p1=G[i][j].p2; e.p2=G[i][j].p1;
			e.weight=G[i][j].weight; 
			Gt[e.p1].push_back(e);
		}
		vector<Edge>().swap(G[i]);
	}
}

int getVertex(int vertex, int topoNum){
	for(int i=0;i<vertex;i++)
		if (topo[i]==topoNum)
			return i;
	assert(0);
}

void init()
{
	memset(color, 0, N*sizeof(int));
	memset(topo, 0, N*sizeof(int));
	memset(longpath, 0, N*sizeof(int));  
} 

int main()
{
	init();
	int vertex;
	cin>>vertex;
	assert(vertex<20000);
	int va, vb, weight;   
	while(scanf("%d %d %d",&va, &vb, &weight)!=EOF)
	{     
		Edge E;
		E.p1=va; E.p2=vb; E.weight=weight;
		G[va].push_back(E);
	}
	cout<<"I have read the rules about plagiarism punishment"<<endl; 
	dfsTopoSweep(vertex); 
	GT(vertex);  
	for(int i=vertex-1;i>=0;i--){
		int v=getVertex(vertex, i);
		int longest=0;
		for(int j=0;j<Gt[v].size();j++){
			int w=Gt[v][j].p2;
			if (longest<longpath[w]+Gt[v][j].weight)
				longest=longpath[w]+Gt[v][j].weight;
		}
		longpath[v]=longest;
	}
	for(int i=1;i<vertex;i++)
		cout<<longpath[i]<<" ";
}
