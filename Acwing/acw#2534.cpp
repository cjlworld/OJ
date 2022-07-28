#include<cmath>
#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>

using namespace std;

const int N=2e5+5; // 注意要开 2 倍。 

int one[N],idx;
int ver[N],Next[N];
inline void AddEdge(int a,int b)
{
	Next[idx]=one[a]; ver[idx]=b; one[a]=idx++;
	Next[idx]=one[b]; ver[idx]=a; one[b]=idx++;
}

int fat[N],dep[N],son[N],top[N]; // 树链剖分求 lca 
int bts[N],lb[N],rb[N],tot;   
// bts[] = brackets , 括号序。
// lb[i] = left-bracket 是 i 的左括号在括号序中的下标。
// rb[i] = right-bracket 是 i 的右括号在括号序中的下标。
// tot 是括号序的时间戳。 

void dfs1(int x,int fa)
{
	static int siz[N]; // 与莫队的 siz 会重 qwq; 
	fat[x]=fa;
	dep[x]=dep[fa]+1;
	siz[x]=1;
	
	for(int i=one[x],y;~i;i=Next[i]) {
		y=ver[i];
		if(y==fat[x]) continue;
		dfs1(y,x);
		siz[x]+=siz[y];
		if(siz[y]>siz[son[x]])
			son[x]=y;
	}
}

void dfs2(int x)
{
	bts[++tot]=x;
	lb[x]=tot;
	
	if(x==son[fat[x]]) top[x]=top[fat[x]];
	else top[x]=x;
	for(int i=one[x],y;~i;i=Next[i]) {
		y=ver[i];
		if(y==fat[x]) continue;
		dfs2(y);
	}
	bts[++tot]=x;
	rb[x]=tot;
}

int lca(int x,int y)
{
	while(top[x]^top[y]) {
		if(dep[top[x]]<dep[top[y]])
			swap(x,y);
		x=top[x]; x=fat[x];
	}
	if(dep[x]<dep[y]) return x;
	else return y;
}

int n,m,siz;
int a[N];
vector<int> nums; // 离散化 

struct Query
{
	int l,r,id,ancestor;
	inline bool operator<(const Query &t) const
	{
		if(l/siz!=t.l/siz) return l<t.l;
		else return r<t.r;
	}
	Query(int l=0,int r=0,int id=0,int ancestor=0) 
		: l(l),r(r),id(id),ancestor(ancestor) {}
}q[N];

bool st[N];
int cnt[N],cur,ans[N];

void Add(int pos)
{
	st[pos]^=1;
	if(st[pos]) {
		if(!cnt[a[pos]]) cur++;
		cnt[a[pos]]++;
	}
	else {
		cnt[a[pos]]--;
		if(!cnt[a[pos]]) cur--;
	}
}

int main()
{
//	freopen("1.in","r",stdin);
	int i;
	int x,y,z;
	
	scanf("%d%d",&n,&m);
	for(i=1;i<=n;i++) {
		scanf("%d",&a[i]);
		nums.push_back(a[i]);
	}
	sort(nums.begin(),nums.end());
	nums.erase(unique(nums.begin(),nums.end()),nums.end());
	for(i=1;i<=n;i++) 
		a[i]=lower_bound(nums.begin(),nums.end(),a[i])-nums.begin();
	
	memset(one,-1,sizeof one);
	for(i=1;i<=n-1;i++) {
		scanf("%d%d",&x,&y);
		AddEdge(x,y);
	}
	
	dfs1(1,0); dfs2(1);
	for(i=1;i<=m;i++) {
		scanf("%d%d",&x,&y);
		if(dep[x]>dep[y]) swap(x,y); // 让 x 在上面。 
		z=lca(x,y);
		if(z==x) q[i]=Query(lb[x],lb[y],i);
		else q[i]=Query(rb[x],lb[y],i,z);
	}
	
	siz=sqrt(2*n);
	sort(q+1,q+m+1);
	
	int hh=1,tt=0;
	for(i=1;i<=m;i++) {
		while(hh>q[i].l) Add(bts[--hh]);
		while(tt<q[i].r) Add(bts[++tt]);
		while(hh<q[i].l) Add(bts[hh++]);
		while(tt>q[i].r) Add(bts[tt--]);
		if(q[i].ancestor) Add(q[i].ancestor);
		ans[q[i].id]=cur;
		if(q[i].ancestor) Add(q[i].ancestor);
	}
	
	for(i=1;i<=m;i++) 
		printf("%d\n",ans[i]);
	return 0;
}

