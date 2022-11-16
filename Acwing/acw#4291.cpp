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

int n,m;

struct Edge
{
	int a,b,c;
}e[N];

bool cmp(Edge a,Edge b)
{
	return a.c<b.c;
}

int par[N];
int Find(int x) { return (par[x]==x) ? x : par[x]=Find(par[x]); }

int main()
{
//	freopen("1.in","r",stdin);
	while(cin>>n,n) {
		m=0;
		for(int i=1;i<=n-1;i++) {
			char c; int k,x;
			cin>>c>>k;
			for(int j=1;j<=k;j++) {
				cin>>c>>x;
				m++;
				e[m].a=i;
				e[m].b=c-'A'+1;
				e[m].c=x;
			}
		}
		sort(e+1,e+m+1,cmp);
		for(int i=1;i<=n;i++) par[i]=i;
		
		int ans=0;
		for(int i=1;i<=m;i++) {
			int x=e[i].a,y=e[i].b;
			if(Find(x)==Find(y)) 
				continue;
		//	printf("(%d, %d, %d)\n",x,y,e[i].c);
			par[Find(x)]=Find(y);
			ans+=e[i].c;
		}
		printf("%d\n",ans);
	}
	return 0;
}

