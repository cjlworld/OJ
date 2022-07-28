#pragma GCC optimize(2)
#include<vector>
#include<cstdio>
#include<iostream>
#include<algorithm>
#define rint register int 
typedef long long LL;
using namespace std;
const int N=512;
vector<int> v[N];
int n,m;
int fa[N];
void dfs1(int now,int father)
{
	fa[now]=father;
	for(rint i=0;i<(int)v[now].size();i++) 
		if(v[now][i]!=father) 
			dfs1(v[now][i],now);
	return;
}
int ill;
int ans=300;
void dfs(const vector<int> &p)
{
	if(ill>=ans) 
		return;
	rint i,j,u,tmp;
	vector<int> now; now.clear();
	for(i=0;i<(int)p.size();i++) {
		u=p[i];
		for(j=0;j<(int)v[u].size();j++) {
			if(v[u][j]==fa[u]) 
				continue;
			now.push_back(v[u][j]);
		}
	}
	if(now.size()==0) {
		ans=min(ans,ill);
		return;
	}
	ill+=now.size()-1;
	sort(now.begin(),now.end());
	for(i=0;i<(int)now.size();i++) {
		tmp=now[i];
		now.erase(lower_bound(now.begin(),now.end(),tmp));
		dfs(now);
		now.insert(lower_bound(now.begin(),now.end(),tmp),tmp);
	}
	ill-=now.size()-1;
	return;
}
int main()
{
//	freopen("1.in","r",stdin);
	rint i;
	int x,y;
	cin>> n >> m ;
	for(i=1;i<=m;i++) {
		cin>> x >> y;
		v[x].push_back(y);
		v[y].push_back(x);
	}
	dfs1(1,0);
	v[0].push_back(1);
	ill++;
	dfs(v[0]);
	cout<<ans;
	return 0;
}

