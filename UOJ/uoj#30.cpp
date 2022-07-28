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
#include<complex>
#include<iostream>
#include<algorithm>

using namespace std;
typedef long long LL;
typedef unsigned long long ULL;

const int N=8e5+5,INF=0x3f3f3f3f;

int one[N],hs[N],idx;
int Next[N],ver[N];
inline void AddEdge(int h[],int a,int b)
{
	Next[idx]=h[a]; ver[idx]=b; h[a]=idx++;
	Next[idx]=h[b]; ver[idx]=a; h[b]=idx++;
}

int n,m,Q,cnt;
int a[N];

namespace Tarjan
{
	int dfn[N],low[N],times;
	stack<int> S;

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
}

namespace Segtree
{
	int t[4*N];
	#define lc (now<<1)
	#define rc (now<<1|1)
	void build() { memset(t,0x3f,sizeof t); }
	void Update(int now,int pos,int key,int l,int r)
	{
		if(l==r) {
			t[now]=key;
			return;
		}
		int mid=(l+r)>>1;
		if(pos<=mid) Update(lc,pos,key,l,mid);
		else Update(rc,pos,key,mid+1,r);
		
		t[now]=min(t[lc],t[rc]);
	}
	
	int query(int now,int x,int y,int l,int r) 
	{
		if(x<=l && r<=y) 
			return t[now];
		int mid=(l+r)>>1,res=INF;
		if(x<=mid) res=min(res,query(lc,x,y,l,mid));
		if(y>=mid+1) res=min(res,query(rc,x,y,mid+1,r));
		return res;
	}
}

namespace HID
{
	int siz[N],son[N],dep[N],fat[N];
	int dfn[N],top[N],times;

	void dfs(int x,int fa)
	{
		fat[x]=fa;
		dep[x]=dep[fa]+1;
		siz[x]=1;
		
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
		dfn[x]=++times;
		if(son[fat[x]]==x) top[x]=top[fat[x]];
		else top[x]=x;
		
		if(son[x]) dfs(son[x]);
		
		for(int i=hs[x],y;~i;i=Next[i]) {
			y=ver[i];
			if(y==fat[x] || y==son[x]) continue;
			dfs(y);
		}
	}
	int Tquery(int x,int y)
	{
		int res=INF;
		while(top[x]!=top[y]) {
			if(dep[top[x]]<dep[top[y]]) 
				swap(x,y);
			res=min(res,Segtree::query(1,dfn[top[x]],dfn[x],1,cnt));
			x=top[x]; x=fat[x];
		}
		if(dep[x]<dep[y]) swap(x,y);
		res=min(res,Segtree::query(1,dfn[y],dfn[x],1,cnt));
		if(y>n && fat[y]) res=min(res,a[fat[y]]);
		return res;
	}
}

multiset<int> s[N];

int main()
{
//	freopen("1.in","r",stdin);
	int i;
	int x,y,z;
	char opt[2];
	
	scanf("%d%d%d",&n,&m,&Q);
	for(i=1;i<=n;i++) 
		scanf("%d",&a[i]);
	
	memset(one,-1,sizeof one);
	for(i=1;i<=m;i++) {
		scanf("%d%d",&x,&y);
		AddEdge(one,x,y);
	}
	
	memset(hs,-1,sizeof hs);
	cnt=n;
	for(i=1;i<=n;i++) 
		if(!Tarjan::dfn[i]) Tarjan::tarjan(i);

	HID::dfs(1,0); HID::dfs(1);
	for(x=1;x<=n;x++) 
		s[HID::fat[x]].insert(a[x]);
	for(i=n+1;i<=cnt;i++) 
		a[i]=*s[i].begin();
		
	Segtree::build();
	for(i=1;i<=cnt;i++) 
		Segtree::Update(1,HID::dfn[i],a[i],1,cnt);
	
	while(Q--) {
		scanf("%s%d%d",opt,&x,&y);
		if(*opt=='C') {
			z=HID::fat[x];
			if(z) {
				s[z].erase(s[z].find(a[x]));
				s[z].insert(y);
				Segtree::Update(1,HID::dfn[z],a[z]=*s[z].begin(),1,cnt);				
			}

			Segtree::Update(1,HID::dfn[x],a[x]=y,1,cnt);
		}
		else printf("%d\n",HID::Tquery(x,y));
	}
	return 0;
}

