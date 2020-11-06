#include<set>
#include<map>
#include<cmath>
#include<ctime>
#include<stack>
#include<queue>
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
typedef pair<int,int> PII;

const int N=16,M=1e5+5;
int n=4;
char a[N][N];
int get(int x,int y)
{
	return x*4+y;
}

int g[M],tot;
queue<int> q;
int dis[M],pre[M];
bool vis[M];

void bfs(int x)
{
	int i,j;
	int y,z;
	q.push(x); dis[x]=0,vis[x]=true;
	while(q.size()) {
		x=q.front(); q.pop();
		for(i=0;i<tot;i++) {
			y=x^g[i];
			if(!vis[y]) {
				dis[y]=dis[x]+1;
				pre[y]=i;
				vis[y]=true;
				q.push(y);
			}
		}
	}
	return;
}

int main()
{
	int i,j,k;
	int x,s=0,t=(1<<(n*n))-1;
	for(i=0;i<n;i++) 
		scanf("%s",a[i]);
	for(i=0;i<n;i++) 
		for(j=0;j<n;j++) 
			if(a[i][j]=='-') s^=(1<<get(i,j)); // 初始状态 
	// 先预处理出每一种操作 
	for(i=0;i<n;i++) 
		for(j=0;j<n;j++) {
			x=0;
			x^=(1<<get(i,j));
			for(k=0;k<n;k++) {
				if(k!=j) x^=(1<<get(i,k));
				if(k!=i) x^=(1<<get(k,j));
			}
			g[tot++]=x;
		}
	bfs(s);
	printf("%d\n",dis[t]);
	vector<int> ans;
	for(i=t;i!=s;i^=g[pre[i]]) 
		ans.push_back(pre[i]); 
	// 因为 s-->t 操作满足从上到下，从左到右，t-->s 就相反。
	while(ans.size()) {
		printf("%d %d\n",ans.back()/4+1,ans.back()%4+1);
		ans.pop_back();
	}	
	return 0;
}

