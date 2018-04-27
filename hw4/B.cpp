#include <stdio.h>
#include <cmath>
#include <algorithm>
#include <iostream>

#define INF 9999

using namespace std;

struct Node{
	int x;
	int y; 
}; 

double distance(Node* array, int a, int b){
	int x1=(array+a)->x;
	int y1=(array+a)->y;
	int x2=(array+b)->x;
	int y2=(array+b)->y;
	return sqrt((double)((double)x1-(double)x2)*((double)x1-(double)x2)+((double)y1-(double)y2)*((double)y1-(double)y2));
}

double min(double a, double b){
	return a>b?b:a;
}

bool cmp(struct Node a, struct Node b){
	if (a.x<b.x) return 1;
	else if (a.x>b.x) return 0;
	else if (a.y<=b.y) return 1;
	else return 0;
}

bool cmp_y(struct Node a, struct Node b){
	if (a.y<=b.y) return 1;
	else return 0;
}

double closestPair(Node* node, Node* temp, int left, int right){
	if (left==right)
		return INF;
	if (left+1==right)
		return distance(node, left, right);
	int mid=(left+right)/2;
	double d_left=closestPair(node, temp, left, mid);
	double d_right=closestPair(node, temp, mid, right);
	double d_min=min(d_left, d_right);
	 
	int k=0;
	for (int i=left;i<=right;i++){
		if(abs(node[i].x-node[mid].x)<d_min)
			temp[k++]=node[i];
	}
	
	sort(&temp[0], &temp[k], cmp_y);
	for (int i=0;i<k;i++){
		for (int j=i+1;j<k;j++){
			if (temp[j].y-temp[i].y>d_min) break;
			d_min=min(d_min, distance(temp, i, j));
		}
	}
	return d_min;
}

int main()
{
    int num;
    while(scanf("%d",&num) != EOF)
    {
    	Node* node = new Node[num];
    	Node* temp = new Node[num];
    	for (int i=0;i<num;i++){
    		scanf("%d,%d", &node[i].x, &node[i].y);
		} 
		sort(&node[0], &node[num], cmp);
		
		double dis =closestPair(node, temp, 0, num-1);
		cout<<"wo yi yue du guan yu chao xi de shuo ming"<<endl;
		printf("%.6lf", dis);
		delete[] node;
		delete[] temp;
	}
    return 0;
}
