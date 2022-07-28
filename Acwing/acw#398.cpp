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
const int N=4e5+5;

int one[N],hs[N],idx;
int ver[N],Next[N];
void AddEdge(int h[],int a,int b)
{
	Next[idx]=h[a]; ver[idx]=b; h[a]=idx++;
	Next[idx]=h[b]; ver[idx]=a; h[b]=idx++;
}

int dfn[N],low[N],times;
stack<int> S;

// 割点的判定法则：
// 1. 如果是根节点，则有两个以上儿子.
// 2. 如果非根，则 low[son] >= dfn[x]. 

// 但建圆方树不需要考虑这一点 ， 因为
// 1. 若根节点只有一个儿子，则建一个方点与根节点所在点双连，符合题意。
// 2. 否则，也符合题意。 
// 所以建圆方树不用考虑根节点，但割点要。 

int cnt; // 方点的计数器的编号。 

void tarjan(int x)
{
	dfn[x]=low[x]=++times;
	S.push(x);
	for(int i=one[x],y;~i;i=Next[i]) {
		y=ver[i];
		if(!dfn[y]) {
			tarjan(y);
			low[x]=min(low[x],low[y]);
			
			if(low[y]>=dfn[x]) {
				cnt++; // 新的点双的方点。 
				while(S.size() && S.top()!=y) { 
					// 注意这里只能出栈到 y, 因为栈中可能还有 x 的其他子树。 
					AddEdge(hs,S.top(),cnt);
					S.pop();
				}	
				AddEdge(hs,y,cnt); S.pop();
				AddEdge(hs,x,cnt); // 别漏了; 同时注意这里不能删去 x, 因为 x 可能存在于其他点双。 
			}
		}
		else low[x]=min(low[x],dfn[y]);
	}
}

int up[N][21],dep[N],w[N];

void deal_first(int x,int fa)
{
	dep[x]=dep[fa]+1;
	up[x][0]=fa;
	w[x]+=w[fa];
	
	int i,y;
	for(i=1;i<=20;i++) {
		if(!up[x][i-1]) break;
		up[x][i]=up[up[x][i-1]][i-1];
	}
	for(i=hs[x];~i;i=Next[i]) {
		y=ver[i];
		if(y==fa) continue;
		deal_first(y,x);
	}
}

int lca(int x,int y)
{
	int i;
	if(dep[x]<dep[y]) swap(x,y);
	for(i=20;i>=0;i--) 
		if(dep[up[x][i]]>=dep[y]) 
			x=up[x][i];
	
	if(x==y) return x;
	
	for(i=20;i>=0;i--) 
		if(up[x][i]!=up[y][i]) 
			x=up[x][i],y=up[y][i];
	
	return up[x][0];
}

int dist(int x,int y) // 树上两点之间的圆点数量。 
{
	int z=lca(x,y);
	return w[x]+w[y]-w[z]-w[up[z][0]];
}

int n,m,Q;
int id[N]; // 编号为 id 的边对应的方点。 

int main()
{
//	freopen("1.in","r",stdin);
	int i;
	int x,y;
	while(scanf("%d%d",&n,&m),n||m) {
		memset(id,0,sizeof id);
		memset(one,-1,sizeof one); 
		memset(hs,-1,sizeof hs);
		idx=0; 
		
		memset(low,0,sizeof low);
		memset(dfn,0,sizeof dfn);
		times=0;
		while(S.size()) S.pop();
		cnt=n;
		
		memset(dep,0,sizeof dep);
		memset(up,0,sizeof up);
		memset(w,0,sizeof w);
		
		for(i=1;i<=m;i++) {
			scanf("%d%d",&x,&y);
			AddEdge(one,x,y);
		}
		
		// 对点双建圆方树。 
		for(i=1;i<=n;i++) 
			if(!dfn[i]) tarjan(i);
		
//		for(x=n+1;x<=cnt;x++) {
//			printf("%d : ",x);
//			for(i=hs[x];~i;i=Next[i]) {
//				y=ver[i];
//				printf("%d, ",y);
//			}
//			printf("\n");
//		}
		// 性质：a->b 的必经点 = a->b 在树上经过圆点的数量。
		// 所以把 圆点设为 1 , 方点设为 0 即可。 
		for(i=1;i<=cnt;i++) w[i]=(i<=n);
		for(i=1;i<=n;i++)
			if(!dep[i])	deal_first(i,0); // 不一定保证联通，可能是森林，所以要多次dfs
		
		// 对每条边标记其所对应的方点。 
		for(x=1;x<=n;x++) 
			for(i=one[x];~i;i=Next[i]) {
				y=ver[i];
				if(y<x) { 
					// y<x 保证每条边只标记一次；
					// dist(x,y) 保证二者同连接一个方点。 
					if(dep[y]==dep[x] || dep[y]<dep[x]) id[i/2+1]=up[x][0];
					else id[i/2+1]=up[y][0];
				}
			}
			
		scanf("%d",&Q);
		while(Q--) {
			scanf("%d%d",&x,&y);
			printf("%d\n",dist(id[x],id[y]));
		}
	}
	return 0;
}

