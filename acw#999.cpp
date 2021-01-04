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

inline void relax(int& a,const int& b) { a=((a>b) ? a : b); }
inline void tense(int& a,const int& b) { a=((a<b) ? a : b); }

const int N=3e5+5,INF=0x3f3f3f3f;

struct Node
{
	int ch[2],fa;
	int siz,val;
	bool rev;
	int mx;
}t[N];

void pushup(int x)
{
	t[x].mx=t[x].val;
	relax(t[x].mx,t[t[x].ch[0]].mx);
	relax(t[x].mx,t[t[x].ch[1]].mx);
	t[x].siz=t[t[x].ch[0]].siz+t[t[x].ch[1]].siz+1;
}

inline void Addrev(int x) { t[x].rev^=1; swap(t[x].ch[0],t[x].ch[1]); }
void pushdown(int x)
{
	if(t[x].rev) {
		Addrev(t[x].ch[0]);
		Addrev(t[x].ch[1]);
		t[x].rev=false;
	}
}

inline bool isroot(int x) { return (t[t[x].fa].ch[0]!=x && t[t[x].fa].ch[1]!=x); }
void rotate(int x)
{
	if(isroot(x)) return;
	int y=t[x].fa,z=t[y].fa;
	int k=(t[y].ch[1]==x);
	pushdown(z); pushdown(y); pushdown(x);
	if(!isroot(y)) t[z].ch[t[z].ch[1]==y]=x;
	t[x].fa=z;
	t[y].ch[k]=t[x].ch[k^1]; t[t[x].ch[k^1]].fa=y;
	t[x].ch[k^1]=y; t[y].fa=x;
	pushup(y); pushup(x); pushup(z);
}

void preview(int x) { if(t[x].fa) preview(t[x].fa); pushdown(x); }
void splay(int x)
{
	int y,z;
	preview(x);
	while(!isroot(x)) {
		y=t[x].fa; z=t[y].fa;
		if(!isroot(y)) {
			if((t[y].ch[1]==x)^(t[z].ch[1]==y)) 
				rotate(x);
			else rotate(y);
		}
		rotate(x);
	}
}

void access(int x)
{
	int z=x,y;
	for(y=0;x;y=x,x=t[x].fa) {
		splay(x);
		t[x].ch[1]=y;
		pushup(x);
	}
	splay(z);
}

void makeroot(int x) { access(x); Addrev(x); }
int findroot(int x) 
{
	access(x);
	while(pushdown(x),t[x].ch[0])
		x=t[x].ch[0];
	return x;
}

void split(int x,int y) { makeroot(x); access(y); }
void link(int x,int y)
{
	makeroot(x);
	if(findroot(y)!=x)
		t[x].fa=y;
}
void cut(int x,int y)
{
	split(x,y);
	if(t[y].siz==2 && t[x].fa==y) {
		t[y].ch[t[y].ch[1]==x]=t[x].fa=0;
		pushup(x); pushup(y);
	}
}

int search(int x)
{
	if(!x) return -1; // DeBug;
	pushdown(x);
	if(t[x].val==t[x].mx) return x;
	else if(t[x].ch[0] && t[t[x].ch[0]].mx==t[x].mx) 
		return search(t[x].ch[0]);
	else return search(t[x].ch[1]);
}

struct Edge
{
	int x,y,a,b;
	inline bool operator<(const Edge& t) const
	{
		return a<t.a;
	}
}e[N];

int n,m;

int main()
{
//	freopen("1.in","r",stdin);
	int i;
	int x,y,z,tmp;
	
	scanf("%d%d",&n,&m);
	for(i=1;i<=m;i++) 
		scanf("%d%d%d%d",&e[i].x,&e[i].y,&e[i].a,&e[i].b);
	
	sort(e+1,e+m+1);
	
	int ans=INF;
	for(i=1;i<=n;i++) t[i].siz=1;
	for(i=n+1;i<=n+m;i++) t[i].siz=1,t[i].val=e[i].b;
	for(i=1;i<=m;i++) {
		x=e[i].x; y=e[i].y; z=e[i].b;
		split(x,y);
		// 若 x,y 不联通或路径上有权值大于 z 的边 ,则换边.
		if(findroot(y)==x && t[y].mx<z) continue; 
		else if(findroot(y)==x) {
			tmp=search(y); splay(tmp);
			cut(e[tmp-n].a,tmp);
			cut(e[tmp-n].b,tmp);
		}
		link(x,i+n);
		link(y,i+n);
		
		split(1,n);
		if(findroot(n)==1) // 联通才能计入答案。 
			tense(ans,e[i].a+t[n].mx);
	}
	
	if(ans==INF) puts("-1");
	else printf("%d\n",ans);
	return 0;
}

