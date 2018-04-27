#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<char> L;

int main()
{
	string s;
	getline(cin,s);
	stringstream ss;
	ss << s; 
	char ch;
	while(ss>>ch){
		L.push_back(ch);
	}
	int n=L.size();
	vector<vector<short> > dp(n, vector<short>(n));
	
	for(int i=n-1;i>=0;i--){
		dp[i][i]=1;
		for(int j=i+1;j<n;j++){
			if(L[i]==L[j])
				dp[i][j]=dp[i+1][j-1]+2;
			else
				dp[i][j]=max(dp[i+1][j], dp[i][j-1]);
		}
	}
	cout<<"I have read the rules about plagiarism punishment"<<endl;
	cout<<dp[0][n-1];
} 
