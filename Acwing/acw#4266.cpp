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
typedef pair<int,int> PII;
typedef unsigned long long ULL;

const int N=1e4+5;

int n,m;
PII a[N];
int par[N];
bool open[N];

double dist(PII x,PII y) { return sqrt(pow(x.first-y.first,2)+pow(x.second-y.second,2)); }
int Find(int x) { return (par[x]==x) ? x : par[x]=Find(par[x]); }

int main()
{
//	freopen("1.in","r",stdin);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) 
		scanf("%d%d",&a[i].first,&a[i].second);
	for(int i=1;i<=n;i++) par[i]=i;
	
	char opt;
	int x,y;
	while(cin>>opt) {
		if(opt=='O') {
			scanf("%d",&x);
			open[x]=true;
			for(int i=1;i<=n;i++) {
				if(!open[i]) continue;
				if(dist(a[x],a[i])<=m && Find(x)!=Find(i)) par[Find(x)]=i;
			}
		}
		else {
			scanf("%d%d",&x,&y);
			if(!open[x] || !open[y] || Find(x)!=Find(y)) 
				puts("FAIL");
			else puts("SUCCESS");
		}
	}
	
	return 0;
}

