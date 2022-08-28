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

const int N=1e5+5;

struct Edge
{
	int a,b,c;	
}e[N];
int n,m;

bool cmp(const Edge& a,const Edge& b) { return a.c<b.c; }

int par[N];
int Find(int x) { return (par[x]==x) ? x : par[x]=Find(par[x]); }
void Join(int x,int y) { par[Find(x)]=Find(y); }

int Kruscal()
{
	sort(e+1,e+m+1,cmp);
	for(int i=0;i<=n;i++) par[i]=i;
	
	int res=0;
	for(int i=1;i<=m;i++) {
		if(Find(e[i].a)==Find(e[i].b)) 
			continue;
		Join(e[i].a,e[i].b);
		res+=e[i].c;
	}
	return res;
}

int main()
{
//	freopen("1.in","r",stdin);
	
	scanf("%d",&n);
	for(int i=1,x;i<=n;i++) {
		scanf("%d",&x);
		++m; 
		e[m].a=0;
		e[m].b=i;
		e[m].c=x; 
	}
	
	for(int i=1;i<=n;i++) 
		for(int j=1,x;j<=n;j++) {
			scanf("%d",&x);
			if(i<j) continue;
			++m;
			e[m].a=i;
			e[m].b=j;
			e[m].c=x;
		}
		
	printf("%d\n",Kruscal());
	return 0;
}

