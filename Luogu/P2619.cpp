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
#include<complex>
#include<iostream>
#include<algorithm>

using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
typedef pair<int,int> PII;

const int N=2e5+5;

struct Edge
{
	int a,b,c;
	int col;
	inline bool operator<(const Edge& t) const
	{
		if(c!=t.c) return c<t.c;
		else return col<t.col;
	}
}e[N];

int n,m,need;

int par[N];
int Find(int x)
{
	if(par[x]!=x) return par[x]=Find(par[x]);
	else return x;
}

PII Kruscal()
{
	PII res(0,0);
	sort(e+1,e+m+1);
	for(int i=1;i<=n;i++) par[i]=i;
	for(int i=1;i<=m;i++) {
		int x=Find(e[i].a),y=Find(e[i].b);
		if(x==y) continue;
		par[x]=y;
		res.first+=e[i].c;
		res.second+=!e[i].col;
	}
	return res;
}

PII check(int t)
{
	int i;
	for(i=1;i<=m;i++) 
		if(e[i].col==0)
			e[i].c-=t;
	
	PII tmp=Kruscal();
	for(i=1;i<=m;i++) 
		if(e[i].col==0) 
			e[i].c+=t;
	return tmp;
}

int main()
{
//	freopen("1.in","r",stdin);
	int i;
	
	scanf("%d%d%d",&n,&m,&need);
	for(i=1;i<=m;i++) {
		scanf("%d%d%d%d",&e[i].a,&e[i].b,&e[i].c,&e[i].col);
		e[i].a++;
		e[i].b++;
	} 
	
	int L=-200,R=200,mid;
	while(L+1<R) {
		mid=(L+R)>>1;
		if(check(mid).second>=need) R=mid;
		else L=mid;
	}
	// 由于我们先选的是 white 
	// 所以即使没有选出恰好 need 条白边，ans 也保留在 R 中。 
	
	printf("%d\n",check(R).first+need*R);
	return 0;
}

