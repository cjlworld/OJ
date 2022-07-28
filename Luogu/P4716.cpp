#include<cstdio>
#include<cstring>
#include<iostream>

using namespace std;

const int N=256,M=2e4+5,INF=0x3f3f3f3f;

struct Edges
{
	int u,v,val;
	Edges(int u=0,int v=0,int val=0) :
		u(u),v(v),val(val) {}
	// 从 u 到 v 权值为 val 的有向边。 
}e[M];

int n,m,rt;
int col[N],all; // 所在环的编号，编号计数器。 
int fa[N],min_pre[N]; // 最小入边的起点，最小入边的权值。 
int vis[N];

int DMST()
{
	int ans=0;
	while(true) {
		// 初始化 
		all=0;
		memset(col,0,sizeof col);
		memset(fa,0,sizeof fa);
		memset(vis,0,sizeof vis);
		memset(min_pre,0x3f,sizeof min_pre);
		
		// 找每个点的最小入边
		for(int i=1;i<=m;i++) 
			if(e[i].u!=e[i].v && e[i].val<min_pre[e[i].v])
				fa[e[i].v]=e[i].u,min_pre[e[i].v]=e[i].val;
		
		for(int i=1;i<=n;i++) 
			if(i!=rt && min_pre[i]==INF) return -1; // 如果存在一个点没有入边，则不存在树形图。
		for(int i=1;i<=n;i++) {
			if(i==rt) continue;
			ans+=min_pre[i]; // 加入该边的权值，其实也是隐藏的环内部断边的操作。
			
			// 找环 
			int u=i;
			while(u!=rt && !vis[u] && !col[u])
				vis[u]=i,u=fa[u]; // 找过了就标记，避免重复扫描。
			// 如果用暴力跳是 O(n^2) 的。 
			// 从i不断往选定的入边跳，
			// 如果跳到了其他已经判定的环 或者 rt 
			// 因为我们保证了连的点入度至多为 1 ，所以一个环一定没有入边，可能有出边。 
			// 所以跳到了 环 或者 rt 就一定可以保证跳不回去了。
			
			if(u!=rt && vis[u]==i) { // 注意 i 不一定在环里。 
				col[u]=++all; // 把环扒出来并标记。 
				for(int v=fa[u];v!=u;v=fa[v]) 
					col[v]=all;
			} 
		}
		if(!all) return ans; // 无环说明算法结束。
		
		// 缩点,重新建图。 
		for(int i=1;i<=n;i++) //给不在环中的点也赋一个标号
			if(!col[i]) col[i]=++all;
		int tot=0;
		for(int i=1;i<=m;i++) {
			int u=col[e[i].u],v=col[e[i].v];
			if(u==v) continue; // 由于 u==v 的边已经没用了，删去。 
			e[++tot]=Edges(u,v,e[i].val-min_pre[e[i].v]);
			// 由于 e[i].v (指缩点前的环) 只会并且一定连上一条外面的边，
			// e[i].val-val 就是让连上外面的边时内部隐式断边。
			// 对于在链上的点，则将边权修改成 0，避免重复计入答案。 
		}
		n=all; m=tot; rt=col[rt];
	}
}

int main()
{
	scanf("%d%d%d",&n,&m,&rt);
	for(int i=1;i<=m;i++) 
		scanf("%d%d%d",&e[i].u,&e[i].v,&e[i].val);
	int ans=DMST();
	if(ans!=-1) printf("%d\n",ans);
	else puts("-1");
	return 0;
}

