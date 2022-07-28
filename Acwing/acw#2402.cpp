#include<stack>
#include<cstdio>
#include<iostream>
using namespace std;
const int N=2e6+10,M=2e6+10;
int one[N],idx=1;
int Next[M],ver[M];
inline void AddEdge(int a,int b)
{
    Next[++idx]=one[a];
    one[a]=idx;
    ver[idx]=b;
    return;
}
//==============================
int n,m;
stack<int> S;
int dfn[N],low[N],times=0;
int col[N],all=0;
void tarjan(int u)
{
	dfn[u]=low[u]=++times;
	S.push(u);
	int i,v;
	for(i=one[u];i>0;i=Next[i]) {
		v=ver[i];
		if(!dfn[v]) {
			tarjan(v);
			low[u]=min(low[u],low[v]);
		}
		else if(col[v]==0) 
			low[u]=min(low[u],dfn[v]);
	}
	if(low[u]==dfn[u]) {
		v=0; all++;
		while(S.size()&&v!=u) {
			v=S.top(); S.pop();
			col[v]=all;
		}
	}
	return;
}
int main()
{
//	freopen("1.in","r",stdin);
 	int i,j;
	int x,y,z;
	scanf("%d%d",&n,&m);
	for(i=1;i<=m;i++) {
		scanf("%d%d%d%d",&x,&y,&z,&j);
		AddEdge(2*x+!y,2*z+j);
		AddEdge(2*z+!j,2*x+y);
	}   
	for(i=2;i<=2*n+1;i++) 
		if(!dfn[i]) 
			tarjan(i);
	for(i=1;i<=n;i++) {
		if(col[i<<1]==col[i<<1|1]) {
			printf("IMPOSSIBLE\n");
			return 0;
		}
	}
	printf("POSSIBLE\n");
	for(i=1;i<=n;i++) {
		if(col[i<<1]<col[i<<1|1]) printf("0 ");
		else printf("1 ");
	}
	return 0;
}
