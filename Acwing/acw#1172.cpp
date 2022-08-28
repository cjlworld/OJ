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

const int N=2e5+5;

int one[N],idx;
int ver[N],Next[N];
void AddEdge(int a,int b)
{
	Next[idx]=one[a]; ver[idx]=b; one[a]=idx++;
}

int n,m,rt;
int eu[N],tot;
int fr[N],ed[N];

void dfs(int x,int fa)
{
	eu[++tot]=x; fr[x]=tot;
	for(int i=one[x],y;~i;i=Next[i]) {
		y=ver[i];
		if(y==fa) continue;
		dfs(y,x);
	}
	eu[++tot]=x; ed[x]=tot;
}

int main()
{
//	freopen("1.in","r",stdin);
	
	scanf("%d",&n);
	memset(one,-1,sizeof one);
	for(int i=1,x,y;i<=n;i++) {
		scanf("%d%d",&x,&y);
		if(y==-1) rt=x;
		else AddEdge(x,y),AddEdge(y,x);
	}
	
	dfs(rt,-1);
	scanf("%d",&m);
	while(m--) {
		int x,y;
		scanf("%d%d",&x,&y);
		if(fr[x]<fr[y] && ed[x]>ed[y]) puts("1");
		else if(fr[y]<fr[x] && ed[x]<ed[y]) puts("2");
		else puts("0");
	}
	
	return 0;
}

