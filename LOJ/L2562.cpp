#include<stack>
#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>

using namespace std;

const int N=8e5+5;

int one[N],hs[N],idx;
int Next[N],ver[N];
inline void AddEdge(int h[],int a,int b)
{
	Next[idx]=h[a]; ver[idx]=b; h[a]=idx++;
	Next[idx]=h[b]; ver[idx]=a; h[b]=idx++;
}

int dfn[N],low[N],times;
stack<int> S;
int cnt; // pay attention to cnt start with n;

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
				cnt++;
				while(S.size() && S.top()!=y) {
					AddEdge(hs,S.top(),cnt);
					S.pop();
				}
				AddEdge(hs,y,cnt); S.pop();
				AddEdge(hs,x,cnt);
			}
		}
		else low[x]=min(low[x],dfn[y]);
	}
}

int n,m,Q,T;
int vn,vir[N];
int dfc[N],timc;
int son[N],fat[N],siz[N],top[N],dep[N],w[N];
bool cmp(const int& a,const int& b) { return dfc[a]<dfc[b]; } 

void dfs(int x,int fa)
{
	fat[x]=fa;
	dep[x]=dep[fa]+1;
	siz[x]=1;
	w[x]=w[fa]+(x<=n);
	
	for(int i=hs[x],y;~i;i=Next[i]) {
		y=ver[i];
		if(y==fa) continue;
		dfs(y,x);
		siz[x]+=siz[y];
		if(siz[y]>siz[son[x]]) 
			son[x]=y;
	}
}

void dfs(int x)
{
	if(son[fat[x]]==x) top[x]=top[fat[x]];
	else top[x]=x;
	dfc[x]=++timc;
	
	for(int i=hs[x],y;~i;i=Next[i]) {
		y=ver[i];
		if(y==fat[x]) continue;
		dfs(y);
	}
}

int lca(int x,int y)
{
	while(top[x]!=top[y]) {
		if(dep[top[x]]<dep[top[y]]) 
			swap(x,y);
		x=top[x]; x=fat[x];
	}
	if(dep[x]<dep[y]) return x;
	else return y;
}

int main()
{
//	freopen("1.in","r",stdin);
	int i;
	int x,y,z;
	
	scanf("%d",&T);
	while(T--) {
		memset(one,-1,sizeof one);
		memset(hs,-1,sizeof hs);
		idx=0;
		
		memset(low,0,sizeof low);
		memset(dfn,0,sizeof dfn);
		times=0;
		while(S.size()) S.pop();
		
		memset(dfc,0,sizeof dfc);
		timc=0;
		memset(son,0,sizeof son);
		memset(fat,0,sizeof fat);
		memset(siz,0,sizeof siz);
		memset(top,0,sizeof top);
		memset(dep,0,sizeof dep);
		memset(w,0,sizeof w);
		
		scanf("%d%d",&n,&m);
		for(i=1;i<=m;i++) {
			scanf("%d%d",&x,&y);
			AddEdge(one,x,y);
		}
		
		cnt=n;
		for(i=1;i<=n;i++) 
			if(!dfn[i]) tarjan(i);
		
		dfs(1,0); dfs(1);
		scanf("%d",&Q);
		while(Q--) {
			scanf("%d",&vn);
			for(i=0;i<vn;i++) 
				scanf("%d",&vir[i]);
			sort(vir,vir+vn,cmp);
			int ans=0;
			for(i=0;i<vn;i++) {
				x=vir[i],y=vir[(i+1)%vn];
				z=lca(x,y);
				ans+=w[x]+w[y]-2*w[z];
			}
			printf("%d\n",ans/2+(lca(vir[0],vir[vn-1])<=n)-vn);
		}
	}
	return 0;
}

