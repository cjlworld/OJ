#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>

using namespace std;
typedef pair<int,int> PII;

template<class T>
inline void relax(T& a,const T& b) { a=((a>b) ? a : b); }

const int N=2e5+5;

struct DSU
{
	int par[N],rank[N],d[N];
	PII stk[N];
	int top;
	
	void build(int n)
	{
		for(int i=1;i<=n;i++) {
			par[i]=i; rank[i]=1;
			d[i]=0;
		}	
		top=0;
	}
	PII Find(int x)
	{
		if(par[x]!=x) {
			PII res=Find(par[x]);
			res.second^=d[x];
			return res;
		}
		else return PII(x,0);
	}	
	void Join(int x,int y) // x -> y , cost = 1 
	{
		PII x_=Find(x),y_=Find(y);
		if(x_.first==y_.first) return;
		if(rank[x_.first]>rank[y_.first]) swap(x_,y_),swap(x,y); // °´ÖÈºÏ²¢¡£ 
		int root=x_.first;
		// x_.second + d[root] - y_second = 1 (mod 2) 
		d[root]=1^x_.second^y_.second;
		par[root]=y_.first;
		stk[++top]=PII(root,rank[par[root]]);
		relax(rank[par[root]],rank[root]+1);
	}
	bool same(int x,int y) { return Find(x).first==Find(y).first; }
	int dist(int x,int y) { return Find(x).second^Find(y).second; }
	
	void back(int tim)
	{
		while(top>tim) {
			PII u=stk[top--];
			rank[par[u.first]]=u.second;
			par[u.first]=u.first;
			d[u.first]=0;
		}
	}
}dsu;

PII e[N];

vector<int> t[N<<2];

#define lc (now<<1)
#define rc (now<<1|1)

void Modify(int now,int x,int y,int id,int l,int r)
{
	if(x<=l && r<=y) {
		t[now].push_back(id);
		return;
	}
	int mid=(l+r)>>1;
	if(x<=mid) Modify(lc,x,y,id,l,mid);
	if(y>=mid+1) Modify(rc,x,y,id,mid+1,r);
}

int n,m,k;

void dfs(int now,int l,int r,bool can)
{
	int tim=dsu.top;
	
	for(int i=0;i<(int)t[now].size();i++) {
		int x=e[t[now][i]].first,y=e[t[now][i]].second;
		if(!dsu.same(x,y)) dsu.Join(x,y);
		else if(!dsu.dist(x,y)) can=false; 
	}
	
	if(l==r) {
		if(r!=k) {
			if(can) puts("Yes");
			else puts("No");
		} 
		dsu.back(tim);
		return;
	}
	
	int mid=(l+r)>>1;
	dfs(lc,l,mid,can); dfs(rc,mid+1,r,can);
	dsu.back(tim);
}

int main()
{
//	freopen("1.in","r",stdin);
	int x,y,l,r;
	
	scanf("%d%d%d",&n,&m,&k);
	for(int i=1;i<=m;i++) {
		scanf("%d%d%d%d",&x,&y,&l,&r);
		r--;
		e[i]=PII(x,y);
		Modify(1,l,r,i,0,k);
	}
	
	dsu.build(n);
	dfs(1,0,k,true);
	return 0;
}

