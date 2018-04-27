#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

#define N 150000

using namespace std;

vector<int> T[N];

void DP(int s, int dp[][2])
{
	dp[s][0]=1; dp[s][1]=0;
	for(int i=0;i<T[s].size();i++){
		int child=T[s][i];
		DP(child, dp);
		dp[s][0]+=min(dp[child][0], dp[child][1]);
		dp[s][1]+=dp[child][0];
	}
}

int main()
{
	string s; 
	int n=0; 
	while(getline(cin,s)){ 
		n++; 
		stringstream ss;
		ss << s; 
		int par;
		ss>>par;
		int p;
		while(ss>>p){
			T[par].push_back(p);
		}
	} 
	int dp[n][2];
	for(int i=0;i<n;i++)
		for(int j=0;j<2;j++)
			dp[i][j]=0;
	DP(0, dp); 
	cout<<"I have read the rules about plagiarism punishment"<<endl;
	cout<<min(dp[0][0], dp[0][1]);
} 
