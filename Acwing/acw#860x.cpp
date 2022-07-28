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

template<class T>
inline void relax(T& a,const T& b) { a=((a>b) ? a : b); }

const int N=2e5+5;

struct DSU
{
	int par[N],rank[N],d[N];
	PII stk[N];
	int top;
	
	void build(int n)
	{
		for(int i=1;i<=n;i++) {
			par[i]=i; rank[i]=1;
			d[i]=0;
		}	
		top=0;
	}
	PII Find(int x)
	{
		if(par[x]!=x) {
			PII res=Find(par[x]);
			res.second^=d[x];
			return res;
		}
		else return PII(x,0);
	}	
	void Join(int x,int y) // x -> y , cost = 1 
	{
		PII x_=Find(x),y_=Find(y);
		if(x_.first==y_.first) return;
		if(rank[x_.first]>rank[y_.first]) swap(x_,y_),swap(x,y);
		int root=x_.first;
		// x_.second + d[root] - y_second = 1 (mod 2) 
		d[root]=(1-x_.second+y_.second+2)%2;
		par[root]=y_.first;
		stk[++top]=PII(root,rank[par[root]]);
		relax(rank[par[root]],rank[root]+1);
	}
	bool same(int x,int y) { return Find(x).first==Find(y).first; }
	int dist(int x,int y) { return Find(x).second^Find(y).second; }
	
	void back(int tim)
	{
		while(top>tim) {
			PII u=stk[top--];
			rank[par[u.first]]=u.second;
			par[u.first]=u.first;
			d[u.first]=0;
		}
	}
}dsu;

int n,m;

int main()
{
//	freopen("1.in","r",stdin);
	scanf("%d%d",&n,&m);
	dsu.build(n);
	for(int i=1;i<=m;i++) {
		int x,y;
		scanf("%d%d",&x,&y);
		if(!dsu.same(x,y)) dsu.Join(x,y);
		else if(!dsu.dist(x,y)) return puts("No")&0;
	}
	puts("Yes");
	return 0;
}

