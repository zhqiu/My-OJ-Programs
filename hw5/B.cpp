#include <iostream>
#include <string>  
#include <sstream>
#include <vector>
using namespace std;

#define N 5000

struct vertex{
	int id;
	int color;       
	int discovertime;
	int back; 
	struct vertex* next;
};

struct edge{
	int p1;
	int p2;
	bool visited;  // True means has visited
};

vector<edge> edges; 

int min(int a, int b){
	return (a<b)?a:b;
}

bool ifVisited(int p1, int p2){
	for (int i=0;i<edges.size();i++){
		if(p1==edges[i].p1&&p2==edges[i].p2)
			return edges[i].visited;
	}
}

void markVisted(int p1, int p2){
	for (int i=0;i<edges.size();i++){
		if(p1==edges[i].p1&&p2==edges[i].p2)
			edges[i].visited=true;
	}
}

int bicompDFS(vertex* point, int id, int time){
	int back;
	point[id].color=1;        // gray
	time++; point[id].discovertime=time;
	point[id].back=point[id].discovertime; 
	back=point[id].back;
	vertex* p=point[id].next;
	while(p!=NULL && !ifVisited(id, p->id)){ 
		if(point[p->id].color==0) // it's a tree edge
		{
			int wBack=bicompDFS(point, p->id, time);
			if(wBack>=point[id].discovertime){
				cout<<"articulation point: "<<id<<endl; 
				cout<<"id: "<<id<<" "<<"p->id: "<<p->id<<endl; 
			}
			back=min(back, wBack); 
		}
		else if(point[p->id].color==1)  // it's a back edge
		{
			back=min(back, point[p->id].discovertime);
		}
		markVisted(id, p->id);
		p=p->next;
	}
	point[id].color=2;         //black 
	return back;
}

void dfsSweep(vertex* point, int num){
	int time=0;
	for (int i=0;i<num;i++){  // init the color
		point[i].color=0;     // white
	}
	for (int i=0;i<num;i++){
		if (point[i].color == 0){
			bicompDFS(point, i, time);
		}
	}
}

int main()
{
	string temp;
	int mark=0; 
	struct vertex* Point = new vertex[N];
	
	int num_of_vertex=0;
	
	int a[2]={-1,-1};
	
	string s;
	while(getline(cin, s))
	{
		stringstream ss;
		ss << s;
		int index=0;
		int n;
		while(ss>>n){ 
			a[index]=n;
			index++;
		}  	  
		
		if (a[1]==-1 && mark==0){
			//init graph
			for (int i=0;i<N;i++){
				Point[i].color=0;
				Point[i].id=i;
				Point[i].next=NULL;
			}
			//recode nums of vertex
			num_of_vertex = a[0];
			mark=1;
		}
		else if (a[0]!=-1 && a[1]!=-1){
			//put the edge into graph(add two nodes)
			struct vertex* newVertex1 = new vertex;
			newVertex1->id = a[1];
			newVertex1->next = Point[a[0]].next;
			newVertex1->color = 0;
			Point[a[0]].next = newVertex1;
			
			struct vertex* newVertex2 = new vertex;
			newVertex2->id = a[0];
			newVertex2->next = Point[a[1]].next;
			newVertex2->color = 0;
			Point[a[1]].next = newVertex2;
			
			//put the edge into Edge(vector)
			edge newEdge1;
			newEdge1.p1=a[0];
			newEdge1.p2=a[1];
			newEdge1.visited=false;
			edges.push_back(newEdge1);
			
			edge newEdge2;
			newEdge2.p1=a[1];
			newEdge2.p2=a[0];
			newEdge2.visited=false;
			edges.push_back(newEdge2);
		}
		else if (a[1]==-1 && mark==1){
			//start to calculate!!
			//output result!!
			dfsSweep(Point, num_of_vertex);
			// output info of the graph
			cout<<"num of vertex: "<<num_of_vertex<<endl;
			for(int i=0;i<num_of_vertex;i++){
				cout<<"vertex: "<<i<<" -- ";
				struct vertex* p = Point[i].next;
				while(p!=NULL){
					cout<<p->id<<" ";
					p=p->next;
				}
				cout<<endl;
			}
			cout<<"edges: "<<endl;
			for(int i=0;i<edges.size();i++){
				cout<<edges[i].p1<<" "<<edges[i].p2<<endl; 
			}
			cout<<"over"<<endl;
			//clean the graph
			for (int i=0;i<N;i++){
				Point[i].color=0;
				Point[i].id=i;
				struct vertex* d = Point[i].next;
				while(d!=NULL){
					Point[i].next=d->next;
					delete d;
					d=Point[i].next;
				}
			}
			//record nums of vertex
			num_of_vertex = a[0];
		}
	}
	//start to calculate!!£¨for the last input£© 
	//output result!! 
	return 0;
}
