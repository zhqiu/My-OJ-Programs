#include <iostream> 
#include <sstream>
#include <string>
#include <vector> 
#include <algorithm>
#include <assert.h>
using namespace std;

#define N 50000

struct Edge{
	int p1;
	int p2; 
}; 

struct compV{
	int id;
	int leader;
	vector<int> point;   //contains, index of src G
	vector<int> impactP; //impacts, index of compact G 
	int num;	
	int impact_all; 
};

struct compE{
	int v1; // index of V_of_compG
	int v2;
};

vector<compV> V_of_compG;
vector<Edge> G[N];
vector<Edge> Gt[N];
vector<compE> compG[N];
vector<int> finishStack;
int scc[N];
int color_1[N];
int color_2[N];
int num_of_edges_in_compG=0;

void dfsImpact(int* color, int u)
{ 
	color[u]=1;   
	V_of_compG[u].impactP.push_back(u);
	assert(compG[u].size()<N && compG[u].size()>=0); 
	for(int i=0;i<compG[u].size();i++){
		int v=compG[u][i].v2;
		if (color[v]==1) assert(0);
		if(color[v]==0)
			dfsImpact(color, v);

		for(int j=0;j<V_of_compG[v].impactP.size();j++){
			int p=V_of_compG[v].impactP[j];
			bool flag=true; 
			for(int k=0;k<V_of_compG[u].impactP.size();k++){ 
				if(V_of_compG[u].impactP[k]==p) {flag=false;   break;} 
			} 
			if(flag){
				 V_of_compG[u].impactP.push_back(p);
			}
		}
 
	} 
	color[u]=2;
}

void getCompactG(int num_of_vertex)
{
	for(int i=0;i<num_of_vertex;i++){
		for (int j=0;j<G[i].size();j++){
			if(scc[i]!=scc[G[i][j].p2])
			{ 
				int v1,v2;
				for(int k=0;k<V_of_compG.size();k++){ 
					if (V_of_compG[k].leader==scc[i]) v1=k;  
					if (V_of_compG[k].leader==scc[G[i][j].p2]) v2=k; 
				} 
				compE cE;
				cE.v1=v1; cE.v2=v2;
				int flag=true;
				for(int i=0;i<compG[v1].size();i++)
					if(compG[v1][i].v2==v2) flag=false; 
				if(flag){
					compG[v1].push_back(cE);
					num_of_edges_in_compG++;
				}
			}
		}
	}
}

void dfs(int u)
{
	color_1[u]=1;
	for(int i=0;i<G[u].size();i++){
		if (color_1[G[u][i].p2]==0)
			dfs(G[u][i].p2);
	}
	color_1[u]=2;
	finishStack.push_back(u); 
}

void dfsSweep(int num_of_vertex)
{
	for(int i=0;i<num_of_vertex;i++){
		if(color_1[i]==0)
			dfs(i);
	}
}

void computeGt(int num_of_vertex)
{
	for(int i=0;i<num_of_vertex;i++){
		for (int j=0;j<G[i].size();j++){
			Edge E;
			E.p1=G[i][j].p2; E.p2=G[i][j].p1;
			Gt[E.p1].push_back(E);
		}
	}
}

void dfsT(int u, int leader)
{
	color_2[u]=1;
	for(int i=0;i<Gt[u].size();i++){
		if (color_2[Gt[u][i].p2]==0)
			dfsT(Gt[u][i].p2, leader);
	}
	color_2[u]=2;
	scc[u]=leader;
}

void dfsTsweep()
{
	while(finishStack.size()>0)
	{
		int v=finishStack.back();
		finishStack.pop_back();
		if (color_2[v]==0)
			dfsT(v, v);
	}
}

void strongComponents(int num_of_vertex)
{
	// phase 1
	dfsSweep(num_of_vertex);
	// phase 2
	computeGt(num_of_vertex);
	dfsTsweep();
}

int main()
{
	int num_of_vertex=-1;
	string s;
	int v_now=0;
	for(int i=0;i<N;i++){
		scc[i]=-1;
		color_1[i]=0;
		color_2[i]=0;
	}
	
	int time=0;
	
	while(time<6){
		time++;
		getline(cin,s);
		stringstream ss;
		ss << s; 
		int n;
		while(ss>>n){
			if (num_of_vertex<n)
				num_of_vertex=n;
			Edge E;
			E.p1=v_now; E.p2=n;
			G[v_now].push_back(E);
		}
		v_now++;  
	}
	num_of_vertex++;
	assert(num_of_vertex==v_now);
	cout<<"I have read the rules about plagiarism punishment"<<endl;
	cout<<num_of_vertex<<endl;
	for (int i=0;i<num_of_vertex;i++){
		cout<<i<<": ";
		for (int j=0;j<G[i].size();j++)
			cout<<G[i][j].p2<<" ";
		cout<<endl;
	}
//	cout<<"G.T:"<<endl;
//	computeGt(num_of_vertex);
//	for (int i=0;i<num_of_vertex;i++){
//		cout<<i<<": ";
//		for (int j=0;j<Gt[i].size();j++)
//			cout<<Gt[i][j].p2<<" ";
//		cout<<endl;
//	}
//	cout<<"after first dfs, the stack:"<<endl;
//	dfsSweep(num_of_vertex);
//	for(int i=0;i<finishStack.size();i++)
//		cout<<finishStack[i]<<" ";
		
	cout<<"scc:"<<endl;
	strongComponents(num_of_vertex);
	for(int i=0;i<num_of_vertex;i++){
		cout<<i<<" belong to "<<scc[i]<<endl;
	}
	
	cout<<"name scc:"<<endl;
	int num_of_scc=0;
	vector<int> record;
	 
	for (int i=0;i<num_of_vertex;i++){
		// look in record
		bool isfind=false;
		for(int j=0;j<record.size();j++)
			if(record[j]==scc[i]) isfind=true; 
		if(isfind){
			cout<<"find: "<<i<<endl; 
			for(int k=0;k<V_of_compG.size();k++)
				if(scc[i]==V_of_compG[k].leader){
					V_of_compG[k].point.push_back(i);
					V_of_compG[k].num++;
				}
		}
		else{
			cout<<"not find: "<<i<<endl;
			compV cV;
			cV.id=num_of_scc; cV.num=1; cV.leader=scc[i];
			cV.point.push_back(i);
			V_of_compG.push_back(cV);
			num_of_scc++;
			record.push_back(scc[i]);
		}
	}
	for (int i=0;i<num_of_scc;i++){
		cout<<V_of_compG[i].id<<": ";
		cout<<"leader: "<<V_of_compG[i].leader<<" "; 
		for(int j=0;j<V_of_compG[i].point.size();j++)
			cout<<V_of_compG[i].point[j]<<" ";
		cout<<"num: "<<V_of_compG[i].num<<endl; 
	}
	
	cout<<"get compactG:"<<endl;
	getCompactG(num_of_vertex);
	cout<<V_of_compG.size()<<endl;
	for(int i=0;i<num_of_edges_in_compG;i++){
		for(int j=0;j<compG[i].size();j++)
			cout<<compG[i][j].v1<<"->"<<compG[i][j].v2<<endl;
	}
	
	cout<<"calculate impact:"<<endl; 
	int color[num_of_scc];
	for(int i=0;i<num_of_scc;i++)
		color[i]=0;
	for(int i=0;i<num_of_scc;i++){
		if (color[i]==0)
			dfsImpact(color, i); 
	}
	for(int i=0;i<V_of_compG.size();i++){
		cout<<i<<": ";
		for(int j=0;j<V_of_compG[i].impactP.size();j++)
			cout<<V_of_compG[i].impactP[j]<<" ";
		cout<<endl;
	} 
	// calculate impact_all of one vertex
	for(int i=0;i<V_of_compG.size();i++){
		cout<<i<<": ";
		V_of_compG[i].impact_all=-1;
		for(int j=0;j<V_of_compG[i].impactP.size();j++)
			V_of_compG[i].impact_all+=V_of_compG[V_of_compG[i].impactP[j]].num;
		cout<<V_of_compG[i].impact_all<<endl;
	} 
	// output final result
	int i_max=0;
	for(int i=1;i<V_of_compG.size();i++){  
		if(V_of_compG[i].impact_all>V_of_compG[i_max].impact_all)
			i_max=i;
	} 
	cout<<V_of_compG[i_max].impact_all<<endl;
	sort(V_of_compG[i_max].point.begin(), V_of_compG[i_max].point.end());
	for(int i=0;i<V_of_compG[i_max].point.size();i++)
		cout<<V_of_compG[i_max].point[i]<<" ";
	return 0;
}
