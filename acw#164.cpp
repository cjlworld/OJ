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
typedef long long LL;
typedef unsigned long long ULL;
using namespace std;
const int N=30000+5;
vector<int> v[N];
bitset<30000+5> f[N];
int n,m;
void dfs(int x)
{
	if(f[x].count()) return;
	int i,y;
	f[x].set(x);
	for(i=0;i<(int)v[x].size();i++) {
		y=v[x][i];
		dfs(y);
		f[x]=f[x]|f[y];
	}
	return;
}
int main()
{
//	freopen("1.in","r",stdin);
	int i;
	int x,y;
	cin>>n>>m;
	for(i=1;i<=m;i++) {
		scanf("%d%d",&x,&y);
		v[x].push_back(y);
	}
	for(i=1;i<=n;i++) {
		sort(v[i].begin(),v[i].end());
		v[i].erase(unique(v[i].begin(),v[i].end()),v[i].end());
	}
	for(i=1;i<=n;i++)  {
		dfs(i);
		printf("%llu\n",f[i].count());
	}
//	cout<<(sizeof(f));
	return 0;
}

