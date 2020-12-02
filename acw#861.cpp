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

const int N=1000+5,M=2e5+5;

int one[M],idx;
int Next[M],ver[M];
void AddEdge(int a,int b)
{
	Next[++idx]=one[a];
	one[a]=idx;
	ver[idx]=b;
}

int match[N]; // 二分图的一边存已经匹配的节点 
bool vis[N]; 

bool dfs(int x)
{
	for(int i=one[x],y;i;i=Next[i]) {
		if(!vis[y=ver[i]]) { // 不在已经 被预定 或 确认不行 的节点中选。 
			vis[y]=true; // 先把 ta 预定了,如果可以,返回 true,不行,说明没有增广路,不用重复扫描.
			if(!match[y] || dfs(match[y])) { // 1. 没有匹配的点 ||2. 已经匹配的点能找到增广 
				match[y]=x; //找到增广路,并更新 match[]; 
				return true;
			}
		}
	}
	return false;
}

int n1,n2,m;
int main()
{
//	freopen("1.in","r",stdin);
	int i,x,y;
	scanf("%d%d%d",&n1,&n2,&m);
	for(i=1;i<=m;i++) {
		scanf("%d%d",&x,&y);
		AddEdge(x,y+n1),AddEdge(y+n1,x);
	}
	int ans=0;
	for(i=1;i<=n1;i++) {
		memset(vis,0,sizeof vis);
		if(dfs(i)) ans++;
	}
	printf("%d\n",ans);
	return 0;
}

