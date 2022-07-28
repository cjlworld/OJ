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

const int N=1e5+5;
const LL MOD=51061;

inline void mul(LL &x,const LL &key) { x=(x*(key%MOD))%MOD; }
inline void add(LL &x,const LL &key) { x=(x+key)%MOD; }

struct Node
{
	int ch[2],fa;
	bool rev;
	LL val,sum,atag,mtag; 
		// mtag,atag 仅为要给子树加的 tag ; val 和 sum 的值都是最新的。 
	LL siz;
}t[N];

void pushup(int x) 
{
	t[x].siz=t[t[x].ch[0]].siz+t[t[x].ch[1]].siz+1;
	t[x].sum=t[x].val;
	add(t[x].sum,t[t[x].ch[0]].sum);
	add(t[x].sum,t[t[x].ch[1]].sum);
//	t[x].sum=t[t[x].ch[0]].sum+t[t[x].ch[1]].sum+t[x].val;
}

void Addrev(int x) { t[x].rev^=1; swap(t[x].ch[0],t[x].ch[1]); }
void Addmul(int x,LL key) 
{ 
	if(!x) return;
	mul(t[x].sum,key);
	mul(t[x].atag,key);
	mul(t[x].mtag,key);
	mul(t[x].val,key);
}
void Addadd(int x,LL key) 
{ 
	if(!x) return;
	add(t[x].sum,t[x].siz*key);
	add(t[x].atag,key);
	add(t[x].val,key);
}

void pushdown(int x)
{
	if(t[x].rev) {
		Addrev(t[x].ch[0]);
		Addrev(t[x].ch[1]);
		t[x].rev=false;
	}
	if(t[x].mtag!=1) {
		Addmul(t[x].ch[0],t[x].mtag);
		Addmul(t[x].ch[1],t[x].mtag);
		t[x].mtag=1;
	}
	if(t[x].atag) {
		Addadd(t[x].ch[0],t[x].atag);
		Addadd(t[x].ch[1],t[x].atag);
		t[x].atag=0;
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
	pushup(y); pushup(x);
}

inline void preview(int x) { if(!isroot(x)) preview(t[x].fa); pushdown(x); }
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
		t[x].fa=t[y].ch[t[y].ch[1]==x]=0;
		pushup(x); pushup(y);
	}
}

int n,m;

int main()
{
//	freopen("1.in","r",stdin);
	int i;
	int x,y;
	LL z;
	char opt[2];
	
	scanf("%d%d",&n,&m);
	for(i=1;i<=n;i++) {
		t[i].ch[0]=t[i].ch[1]=t[i].fa=0;
		t[i].mtag=1;
		t[i].atag=0;
		t[i].sum=1;
		t[i].val=1;
		t[i].rev=0;
		t[i].siz=1;
	}
	
	for(i=1;i<=n-1;i++) {
		scanf("%d%d",&x,&y);
		link(x,y);
	}
	
	while(m--) {
		scanf("%s",opt);
		if(*opt=='+') {
			scanf("%d%d%lld",&x,&y,&z);
			split(x,y);
			Addadd(y,z);
		}
		else if(*opt=='-') {
			scanf("%d%d",&x,&y);
			cut(x,y);
			scanf("%d%d",&x,&y);
			link(x,y);
		}
		else if(*opt=='*') {
			scanf("%d%d%lld",&x,&y,&z);
			split(x,y);
			Addmul(y,z);
		}
		else {
			scanf("%d%d",&x,&y);
			split(x,y);
			printf("%lld\n",t[y].sum%MOD);
		}
	}
	return 0;
}

// DeBug : 
//  1. 记得 pushdown 特判 ch[]==0 的情况。 
//  2. pushup 忘记取模了。
//  3. 忘记 read x,y; 
