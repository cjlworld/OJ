#include<set>
#include<map>
#include<queue>
#include<stack>
#include<ctime>
#include<cmath>
#include<bitset>
#include<vector>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>

using namespace std;
typedef long long LL;
typedef unsigned long long ULL;

stack<int> s[5];

int A() 
{	
	int res=0;
	for(int i=1;i<=3;i++) res+=s[i].size();
	return res;
}

bool dfs(int u,int depth) 
{
	if(u-1+A()>depth) return false;
	else if(u-1==depth) return true;
	
	int x;
	for(int i=1;i<=4;i++) {
		if(s[i].empty()) continue;
		x=s[i].top();
		for(int j=1;j<=4;j++) {
			if(i==j) continue;
			if(s[j].empty()||s[j].top()>x) {
				s[j].push(x),s[i].pop();
				if(dfs(u+1,depth)) return true;
				s[i].push(x),s[j].pop();
			}
		}
	}
	return false;
}

int main()
{
	freopen("1.in","r",stdin);
	
	int n;
	int i;
	for(n=1;n<=12;n++) {
		for(i=1;i<=4;i++) 	
			while(s[i].size()) s[i].pop();
		for(i=n;i>=1;i--) s[1].push(i);
		
		int depth=0;
		while(!dfs(1,depth)) depth++;
		printf("%d\n",depth);
	}
	return 0;
}

