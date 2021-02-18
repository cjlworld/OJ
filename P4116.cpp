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

struct Node
{
	int ch[2],fa;
	int sum,val,siz;
	bool rev;
}t[N];

void pushup(int x)
{
	t[x].sum=t[t[x].ch[0]].sum+t[t[x].ch[1]].sum+t[x].val;
	t[x].siz=t[t[x].ch[0]].siz+t[t[x].ch[1]].siz+1;
}
void Addrev(int x) { t[x].rev^=1; swap(t[x].ch[0],t[x].ch[1]); }
void pushdown(int x)
{
	if(t[x].rev) {
		Addrev(t[x].ch[0]); Addrev(t[x].ch[1]);
		t[x].rev=false;
	}
}
inline bool isroot(int x) { return (t[t[x].fa].ch[0]!=x && t[t[x].fa].ch[1]!=x); }
void rotate(int x)
{
	if(isroot(x)) return;
	int y=t[x].fa,z=t[y].fa;
	int k=(t[y].ch[1]==x);
	if(!isroot(y)) t[z].ch[t[z].ch[1]==y]=x;
	t[x].fa=z;
	t[y].ch[k]=t[x].ch[k^1]; t[t[x].ch[k^1]].fa=y;
	t[x].ch[k^1]=y; t[y].fa=x;
	pushup(y); pushup(x);
}
void preview(int x) { if(!isroot(x)) preview(t[x].fa); pushdown(x); }
void splay(int x)
{
	preview(x);
	while(!isroot(x)) {
		int y=t[x].fa,z=t[y].fa;
		if(!isroot(y)) {
			if((t[z].ch[1]==y)^(t[y].ch[1]==x)) 
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
void split(int x,int y) { makeroot(x); access(y); }
int findroot(int x)
{
	access(x);
	while(pushdown(x),t[x].ch[0]) 
		x=t[x].ch[0];
	return x;
}
void link(int x,int y) 
{
	makeroot(x);	
	access(y);
	if(findroot(y)!=x) 
		t[x].fa=y;
}

int Find(int x)
{
	if(t[x].ch[0] && t[t[x].ch[0]].sum)
		return Find(t[x].ch[0]);
	else if(t[x].val) return x;
	else return Find(t[x].ch[1]);
}

int n,m;
int main()
{
//	freopen("1.in","r",stdin);
	int i;
	int opt,x,y,z;
	
	scanf("%d%d",&n,&m);
	for(i=1;i<=n;i++) {
		t[i].ch[0]=t[i].ch[1]=t[i].fa=0;
		t[i].val=t[i].sum=0;
		t[i].siz=1; t[i].rev=false;
	}
	for(i=1;i<=n-1;i++) {
		scanf("%d%d",&x,&y);
		link(x,y);
	}
	
	while(m--) {
		scanf("%d%d",&opt,&x);
		if(opt==0) {
			splay(x);
			t[x].val^=1;
			pushup(x);
		}
		else {
			makeroot(1);
			access(x);
			if(!t[x].sum) puts("-1");
			else printf("%d\n",z=Find(x)),splay(z);
		}
	}
	return 0;
}

