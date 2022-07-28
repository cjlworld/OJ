#include<set>
#include<map>
#include<queue>
#include<stack>
#include<ctime>
#include<cmath>
#include<vector>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
typedef long long LL;
typedef unsigned long long ULL;
using namespace std;
const int N=5000+5;
int n,m;
vector< pair<int,int> > v[N];
int idx=0;
namespace Tree
{
void dfs(int x,int fa)
{
	int i,y;
	printf("%d ",x);
	for(i=0;i<(int)v[x].size();i++) {
		y=v[x][i].first;
		if(y==fa) continue;
		dfs(y,x);
	}
	return;
}	
}
namespace Circle
{
int ans[N];
int t[N],tot=0;
int Not;
int vis[N];
void dfs(int x,int fa)
{
	int i,y;
	if(vis[x]) return;
	vis[x]=true;
	t[++tot]=x;
	for(i=0;i<(int)v[x].size();i++) {
		y=v[x][i].first;
		if(y==fa||v[x][i].second==Not) continue;
		dfs(y,x);
	}
	vis[x]=false;
	return;
}
stack<int> S,E;
int pp;
bool Find(int x,int fa)
{
	int i,y;
	S.push(x);
	for(i=0;i<(int)v[x].size();i++) {
		y=v[x][i].first;
		if(y==fa) continue;
		if(vis[y]) {
			pp=vis[y];
			return true;
		}
		E.push(v[x][i].second);
		vis[y]=v[x][i].second;
		if(Find(y,x)) return true;
		E.pop();
		vis[y]=0;
	}
	S.pop();
	return false;	
}
bool Compare(const int *a,const int *b)
{
	for(int i=1;i<=n;i++) {
		if(a[i]!=b[i]) 
			return a[i]<b[i];
	}
	return false;
}
void main()
{
	memset(ans,0x3f,sizeof ans);
	Find(1,0);
	memset(vis,0,sizeof vis);
	while(E.size()) {
		Not=E.top(); E.pop();
//		printf("%d\n",Not);
		tot=0;
//		memset(vis,0,sizeof vis);
		dfs(1,0);
		if(tot<n) continue;
		if(Compare(t,ans)) 
			memcpy(ans,t,sizeof ans);
		if(Not==pp) break;
	}
	for(int i=1;i<=n;i++) 
		printf("%d ",ans[i]);
	return;
}
}
int main()
{
//	freopen("1.in","r",stdin);
	int i;
	int x,y;
	cin>>n>>m;
	for(i=1;i<=m;i++) {
		cin>>x>>y;
		++idx;
		v[x].push_back(make_pair(y,idx));
		v[y].push_back(make_pair(x,idx));
	}
	for(i=1;i<=n;i++) 
		sort(v[i].begin(),v[i].end());
	if(m==n-1) Tree::dfs(1,0);
	else Circle::main();
	return 0;
}
/*
Input

10 9
10 4
1 4
5 7
8 7
2 3
1 6
5 6
1 2
9 1

Output
1 2 3 4 10 6 5 7 8 9
*/
