#include<map>
#include<vector>
#include<cstdio>
#include<iostream>

using namespace std;
typedef pair<int,int> PII;
typedef map<PII,int>::iterator mit;

template<class T>
inline void relax(T& a,const T& b) { a=((a>b) ? a : b); }
template<class T>
inline void tense(T& a,const T& b) { a=((a<b) ? a : b); }

const int N=5e5+5;

PII e[N],q[N];
int idx;
map<PII,int> mp;

struct Dsu
{
	int par[N],rank[N];
	PII stk[N];
	int top;
	
	void build(int n)
	{
		for(int i=1;i<=n;i++) 
			par[i]=i,rank[i]=1;
		top=0;
	}
	int Find(int x) 
	{
		if(par[x]!=x) return Find(par[x]);
		else return x;
	}
	void Join(int x,int y)
	{
//		printf("Join ( %d , %d )\n",x,y);
		x=Find(x); y=Find(y);
		if(x==y) return;
		if(rank[x]>rank[y]) swap(x,y); // 让 x 更小，把 x 往 y 上合并。 
		stk[++top]=PII(x,rank[y]);
		par[x]=y; 
		relax(rank[y],rank[x]+1);
	}
	bool same(int x,int y) { return Find(x)==Find(y); }
	void back(int tim)
	{
		while(top>tim) {
			PII u=stk[top--];
			rank[par[u.first]]=u.second;
			par[u.first]=u.first;
		}
	}
}dsu;

vector<int> t[N<<2];

#define lc (now<<1)
#define rc (now<<1|1)

void Modify(int now,int x,int y,int id,int l,int r) // 在时间 [x,y] 内加上边 id 
{
	if(x<=l && r<=y) {
		t[now].push_back(id);
		return;
	}
	int mid=(l+r)>>1;
	if(x<=mid) Modify(lc,x,y,id,l,mid);
	if(y>=mid+1) Modify(rc,x,y,id,mid+1,r);
}

bool ans[N];
void dfs(int now,int l,int r)
{
	int tim=dsu.top;
	for(int i=0;i<(int)t[now].size();i++) 
		dsu.Join(e[t[now][i]].first,e[t[now][i]].second);
	if(l==r) {
		if(q[l].first) 	
			ans[l]=dsu.same(q[l].first,q[l].second);
		dsu.back(tim);
		return;
	}
	int mid=(l+r)>>1;
	dfs(lc,l,mid); dfs(rc,mid+1,r);
	dsu.back(tim);
}

int n,m;

int main()
{
//	freopen("1.in","r",stdin);
	int i;
	int opt,x,y;
	
	scanf("%d%d",&n,&m);
	for(i=1;i<=m;i++) {
		scanf("%d%d%d",&opt,&x,&y);
		if(x>y) swap(x,y);
		if(opt==0) // insert a edge;
			mp[PII(x,y)]=i;
		else if(opt==1) { // erase a Edge
			e[++idx]=PII(x,y);
			Modify(1,mp[PII(x,y)],i-1,idx,1,m);
			mp.erase(mp.find(PII(x,y)));
		}
		else q[i]=PII(x,y);
	}
	for(mit it=mp.begin();it!=mp.end();++it) {
		e[++idx]=it->first;
		Modify(1,it->second,m,idx,1,m);
	}

	dsu.build(n);
	dfs(1,1,m);
	for(i=1;i<=m;i++) 
		if(q[i].first) {
			if(ans[i]) puts("Y");
			else puts("N");
		} 
	return 0;
}

