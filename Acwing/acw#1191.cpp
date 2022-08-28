#include<set>
#include<map>
#include<queue>
#include<stack>
#include<cmath>
#include<ctime>
#include<bitset>
#include<vector>
#include<cstdio>
#include<complex>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>

using namespace std;
typedef long long LL;
typedef long double LD;
typedef unsigned long long ULL;

const int N=1e4+5;

int n;
vector<int> v[N];

int dep[N]; // »Î∂» 

void topsort()
{
	queue<int> q;
	
	for(int i=1;i<=n;i++) 
		for(int j=0;j<(int)v[i].size();j++) 
			dep[v[i][j]]++;
	
	for(int i=1;i<=n;i++) 
		if(dep[i]==0) q.push(i);
	
	while(q.size()) {
		int x=q.front(); q.pop();
		printf("%d ",x);
		for(int i=0,y;i<(int)v[x].size();i++) {
			y=v[x][i];
			if(!(--dep[y])) q.push(y);
		}
	}
}

int main()
{
//	freopen("1.in","r",stdin);
	
	scanf("%d",&n);
	for(int i=1,x;i<=n;i++) 
		for(scanf("%d",&x);x;scanf("%d",&x)) 
			v[i].push_back(x);
	topsort();
	
	return 0;
}

