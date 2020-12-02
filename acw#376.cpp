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

const int N=200+5,M=2000+5;

int one[M],idx;
int ver[M],Next[M];
inline void AddEdge(int a,int b)
{
	Next[++idx]=one[a];
	one[a]=idx;
	ver[idx]=b;
}

int match[N];
bool vis[N];

bool dfs(int x)
{
	for(int i=one[x],y;i;i=Next[i]) {
		if(!vis[y=ver[i]]) {
			vis[y]=true;
			if(!match[y] || dfs(match[y])) {
				match[y]=x;
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
	int i;
	int x,y,z;
	while(scanf("%d%d%d",&n1,&n2,&m)==3) {
		memset(one,0,sizeof one);
		idx=0;
		memset(match,0,sizeof match);
		for(i=1;i<=m;i++) {
			scanf("%d%d%d",&z,&x,&y);
			if(!x||!y) continue; // 贪心，直接不要转换完成。
			AddEdge(x,n1+y); AddEdge(n1+y,x); 
		}
		int ans=0;
		for(i=1;i<n1;i++) {
			memset(vis,0,sizeof vis);	
			if(dfs(i)) ans++;
		}
		printf("%d\n",ans);
	}

	return 0;
}
// 注意事项： N ,M 要分别开，否则 memset 的时间复杂度不对。 
