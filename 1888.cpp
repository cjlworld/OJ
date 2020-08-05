#include<queue>
#include<cstdio>
#include<iostream>
typedef long long LL;
typedef unsigned long long ULL;
using namespace std;
const int INF=(-1u)>>1;
const int N=200000+5;
int dep[N];
int t[N];
int n;
bool vis[N];
queue<int> q;
void topsort()
{
	int i;
	int x;
	for(i=1;i<=n;i++) 
		if(dep[i]==0) 
			q.push(i),vis[i]=true;
	while(q.size()) {
		x=q.front(); q.pop();
		dep[t[x]]--;
		if(dep[t[x]]==0) {
			vis[t[x]]=true;
			q.push(t[x]);
		}		
	}
	return;
}
int dfs(int now)
{
	vis[now]=true;
	if(vis[t[now]]) return 1;
	else return dfs(t[now])+1;
}
int Find()
{
	int i;
	int ans=INF;
	for(i=1;i<=n;i++) {
		if(vis[i]) continue;
		ans=min(ans,dfs(i));
	}
	return ans;
}
int main()
{
//	freopen("1.in","r",stdin);
	int i;
	scanf("%d",&n);
	for(i=1;i<=n;i++) {
		scanf("%d",&t[i]);
		dep[t[i]]++;
	}
	topsort();
	cout<<Find();
	return 0;
}


