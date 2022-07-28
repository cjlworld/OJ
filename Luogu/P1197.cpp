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

const int N=4e5+5;

int n,m,k;

int par[N];
int Find(int x) { return ((par[x]==x) ? x : par[x]=Find(par[x])); }
inline void Join(int x,int y) { par[Find(x)]=Find(y); }

vector<int> v[N];
bool vis[N];
int a[N];

int ans;
void add(int x)
{
	vis[x]=false;
	int cnt=0;
	for(int i=0,y;i<(int)v[x].size();i++) {
		y=v[x][i];
		if(!vis[y] && Find(x)^Find(y)) Join(x,y),cnt++;
	}
	ans-=cnt-1;
}

stack<int> Sans;

int main()
{
//	freopen("1.in","r",stdin);
	int i;
	int x,y;
	
	scanf("%d%d",&n,&m);
	for(i=1;i<=n;i++) par[i]=i;
	for(i=1;i<=m;i++) {
		scanf("%d%d",&x,&y);
		x++,y++;
		v[x].push_back(y),v[y].push_back(x);
	}
	
	scanf("%d",&k);
	for(i=1;i<=k;i++) {
		scanf("%d",&a[i]);
		a[i]++;
		vis[a[i]]=true;
	}
	for(i=1;i<=n;i++) 
		if(!vis[i]) add(i);
	Sans.push(ans);
	for(i=k;i>=1;i--) {
		add(a[i]);
		Sans.push(ans);
	}
	
	for(;Sans.size();Sans.pop()) 
		printf("%d\n",Sans.top());
	return 0;
}

