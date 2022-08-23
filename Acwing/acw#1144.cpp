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

const int N=1e6+5;

int n,m;
int id(int x,int y) { return (x-1)*m+(y-1); }

int par[N];
int Find(int x) { return (par[x]==x) ? x : par[x]=Find(par[x]); }
void Join(int x,int y) { par[Find(x)]=Find(y); }

int main()
{
//	freopen("1.in","r",stdin);
	for(int i=0;i<N;i++) par[i]=i;
	
	scanf("%d%d",&n,&m);
	int x_1,y_1,x_2,y_2;
	while(~scanf("%d%d%d%d",&x_1,&y_1,&x_2,&y_2))
		Join(id(x_1,y_1),id(x_2,y_2));
	
	int ans=0;
	for(int i=1;i<n;i++) 
		for(int j=1;j<=m;j++) {
			if(Find(id(i,j))!=Find(id(i+1,j))) 
				Join(id(i,j),id(i+1,j)),ans++;
		}
	
	for(int i=1;i<=n;i++) 
		for(int j=1;j<m;j++) {
			if(Find(id(i,j))!=Find(id(i,j+1))) 
				Join(id(i,j),id(i,j+1)),ans+=2;
		}
			
	printf("%d\n",ans);
	return 0;
}

