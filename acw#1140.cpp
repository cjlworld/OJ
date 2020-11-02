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

const int N=1e5+5;

struct Edge
{
	int x,y,cost;
	bool operator<(const Edge &t) const
	{
		return cost<t.cost;
	}
}e[N];
int n,m;

int par[N];
int Find(int x)
{
	if(par[x]!=x) return par[x]=Find(par[x]);
	else return x;
}

int Kruscal()
{
	int i,x,y;
	int res=0;
	sort(e+1,e+m+1);
	for(i=1;i<=n;i++) par[i]=i;
	for(i=1;i<=m;i++) {
		x=e[i].x,y=e[i].y;
		if(Find(x)==Find(y)) continue;
		res+=e[i].cost;
		par[Find(x)]=Find(y);
	}
	return res;
}
int main()
{
//	freopen("1.in","r",stdin);
	int i,j,x;
	scanf("%d",&n);
	for(i=1;i<=n;i++) 
		for(j=1;j<=n;j++) {
			scanf("%d",&x);
			if(i!=j) {
				m++;
				e[m].x=i,e[m].y=j,e[m].cost=x;
			}
		}
	cout<<Kruscal()<<endl;
	return 0;
}

