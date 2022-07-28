#include<set>
#include<map>
#include<cmath>
#include<ctime>
#include<stack>
#include<queue>
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

const int N=50;

int n,m;
int a[N];

void dfs(int step)
{
	if(step==m+1) {
		for(int i=1;i<=m;i++) 
			printf("%d ",a[i]);
		printf("\n");
		return;
	}
	if(n-a[step]<m-step+1) return;
	for(int i=a[step-1]+1;i<=n;i++) {
		a[step]=i;
		dfs(step+1);
		a[step]=0;
	}
	return;
}

int main()
{	
	cin>>n>>m;
	dfs(1);
	return 0;
}

