#include <iostream> 
#include <assert.h>
#include <queue>
#include <string.h>

#define N 10000

using namespace std;

struct node{
	int id;
	struct node* next;
};

struct vertex{
	int id;
	int color;
	int part;
	struct node* next;
};

void dfs(struct vertex* point, int start, int part){
	point[start].part = part;
	point[start].color = 1;
	int nextpart;
	if (part == 1) nextpart = 0;
	else nextpart = 1;
	struct node* p = point[start].next;
	while (p != NULL)
	{
		if (point[p->id].color == 0)
		{
			dfs(point, p->id, nextpart);
		}
		p = p->next;
	}
	point[start].color = 2;
} 

void bfs(struct vertex* point, int start, int max)
{
	queue<int> q;
	q.push(start);
	int part=0;
	int i=0;
	while(i<=max){
		int proc;
		int size=q.size(); 
		while(size>0){
			proc=q.front();
			q.pop();
			point[proc].color=2;
			point[proc].part=part;
			i++;
			node* p =point[proc].next;
			while(p!=NULL){
				if (point[p->id].color==0)
					q.push(p->id);
				p=p->next;
			}
			size--;
		}
		if(part==1) part=0;
		else part=1;
	}
}

int str2int(char* p){ 
	char* s = p;
	int res = 0;
	while (*s<'0' || *s>'9')
		s++;
	while ((*s <= '9') && (*s >= '0')){
		res = res * 10 + (*s - '0');
		s++;
	}
	return res;
}

int main()
{
	cout << "wo yi yue du guan yu chao xi de shuo ming" << endl;
	vertex Point[N];
	for (int i = 0; i<N; i++){
		Point[i].id = i;
		Point[i].color = 0;
		Point[i].part = -1;
		Point[i].next = NULL;
	}

	int max = -1;
	int v_now = -1; 
	char* temp = new char[1000];
	char* delim=" ";
	while (cin.getline(temp, 1000))
	{   
		v_now++; 

		char* p = strtok(temp, delim);

		int order = 1;
		int proc = -1;
		while (p != NULL)
		{  
			if (order == 1)
			{ 
				int number = str2int(p); 
				proc = number;
				if (max<number) max = number;
			}
			else
			{
				struct node* newNode = new node; 
				int number = str2int(p);
				if (max<number) max = number;
				newNode->id = number;
				newNode->next = Point[proc].next;
				Point[proc].next = newNode;
			}
			p=strtok(NULL, delim);
		} 
		if (v_now == max)
		{    
			dfs(Point, 0, 0);
//			bfs(Point, 0, max);

			for (int i = 0; i<=max; i++)
				if (Point[i].part == 0)
					cout << i << endl;

			for (int i = 0; i <N; i++)
			{
				Point[i].id = i;
				Point[i].color = 0;
				Point[i].part = -1;
				struct node* d = Point[i].next;
				while (d != NULL){
					Point[i].next = d->next;
					delete d;
					d = Point[i].next;
				}
				Point[i].next=NULL;
			}
			max = -1;
			v_now = -1; 
			
		} 
	}
	return 0;
}
