#include<ctime>
#include<cstdio>
#include<cstdlib>
#include<iostream>

using namespace std;

const int N=1e5+5;

inline unsigned rnd()
{
	static unsigned A=133,B=233,C=998244353;
	A=A*B+C;
	C=C*B-A;
	B=C*B+A*B;
	return C;
}

struct node
{
	int lc,rc;
	int val;
	int id;
	unsigned size;
	#define lc(x) t[x].lc
	#define rc(x) t[x].rc
	#define v(x) t[x].val
	#define id(x) t[x].id
	#define s(x) t[x].size
}t[N];

int root[N],cnt;

inline void update(const int &now) { s(now)=s(lc(now))+s(rc(now))+1; }

void split(int now,const int &key,int &x,int &y) //<= >
{
	if(now==0) 
		return x=y=0,void();
	if(v(now)<=key) x=now,split(rc(now),key,rc(x),y);
	else y=now,split(lc(now),key,x,lc(y));
	update(now);
}

int set_merge(int x,int y)
{
	if(!x||!y) return x+y;
	int u,v;	
	if(rnd()%(s(x)+s(y))>s(x)) swap(x,y);
	split(y,v(x)-1,u,v);
	lc(x)=set_merge(lc(x),u);
	rc(x)=set_merge(rc(x),v);
	update(x);
	return x;
}

inline int getid(int now,unsigned rank)
{
	if(rank<=0||rank>s(now)) 
		return -1;
	while(now>0&&rank>0) {
		if(s(lc(now))+1==rank) 
			return id(now);
		if(s(lc(now))+1>rank) 
			now=lc(now);
		else rank-=s(lc(now))+1,now=rc(now);
	}
	return -1;
}

inline int newnode(const int &id,const int &key)
{
	cnt++;
	v(cnt)=key;
	id(cnt)=id;
	lc(cnt)=rc(cnt)=0;
	s(cnt)=1;
	return cnt;
}

int par[N];
int Find(int x)
{
	if(x!=par[x]) return par[x]=Find(par[x]);
	return x;
}

void AddEdge(int x,int y)
{
	x=Find(x),y=Find(y);
	if(x==y) return;
	par[x]=y;
	root[y]=set_merge(root[x],root[y]);
	return;
}

int n,m,q;
int main()
{
//	freopen("1.in","r",stdin);
	srand(unsigned(time(0)));
	int i;
	int x,y;
	char opt[2];
	
	scanf("%d%d",&n,&m);
	for(i=1;i<=n+2;i++) par[i]=i;
	
	for(i=1;i<=n;i++) {
		scanf("%d",&x);
		root[i]=newnode(i,x);
	}
	for(i=1;i<=m;i++) {
		scanf("%d%d",&x,&y);
		AddEdge(x,y);
	}
	
	scanf("%d",&q);
	while(q--) {
		scanf("%s%d%d",opt,&x,&y);
		if(*opt=='Q') 
			printf("%d\n",getid(root[Find(x)],y));
		else AddEdge(x,y);
	}
	return 0;
}
