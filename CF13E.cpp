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
#include<iostream>
#include<algorithm>

using namespace std;
typedef long long LL;
typedef unsigned long long ULL;

const int N=4e5+5;

struct Node
{
	int ch[2],fa;
	int siz;
	bool rev;
}t[N];
inline void pushup(int x) { t[x].siz=t[t[x].ch[0]].siz+t[t[x].ch[1]].siz+1; }
inline bool isroot(int x) { return (t[t[x].fa].ch[0]!=x && t[t[x].fa].ch[1]!=x); }
inline void Addrev(int x) { swap(t[x].ch[0],t[x].ch[1]),t[x].rev^=1; }
inline void pushdown(int x)
{
	if(t[x].rev) {
		Addrev(t[x].ch[0]),Addrev(t[x].ch[1]);
		t[x].rev=0;
	}
}
inline void preview(int x) { if(!isroot(x)) preview(t[x].fa); pushdown(x); }

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

void splay(int x)
{
	int y,z;
	preview(x); // 别忘了。 
	while(!isroot(x)) {
		y=t[x].fa; z=t[y].fa;
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
	int z=x,y=0; 
	for(y=0;x;y=x,x=t[x].fa) {
		splay(x);
		t[x].ch[1]=y;
//		t[y].fa=x;  t[y].fa 本来就是 x, 所以不需要。 
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
	splay(x);
	return x;
}
void split(int x,int y) { makeroot(x); access(y); }
void link(int x,int y) 
{
//	printf("now link (%d , %d)\n",x,y);
	makeroot(x);
	if(findroot(y)!=x) t[x].fa=y; // ?
}
void cut(int x,int y)
{
//	printf("now cut (%d , %d)\n",x,y);
	split(x,y);
	if(t[y].siz==2 && t[y].ch[0]==x && t[x].fa==y) {
		t[y].ch[0]=t[x].fa=0;
		pushup(y);
	}
}

int n,m;
int a[N];

int main()
{
//	freopen("1.in","r",stdin);
//	freopen("1.out","w",stdout);
	int i;//j;
	int opt,x,y;
	
	scanf("%d%d",&n,&m);
	for(i=1;i<=n+1;i++) {
		t[i].ch[0]=t[i].ch[1]=t[i].fa=0;
		t[i].rev=false;
		t[i].siz=1;
	}
	for(i=1;i<=n;i++) {
		scanf("%d",&a[i]);
		if(i+a[i]<=n) link(i,i+a[i]);
		else link(i,n+1);
	}
	while(m--) {
		scanf("%d",&opt);
		if(opt==1) {
			scanf("%d",&x);
			split(x,n+1);
			for(y=t[n+1].ch[0];pushdown(y),t[y].ch[1];y=t[y].ch[1]);
			printf("%d %d\n",y,t[n+1].siz-1);
		}
		else {
			scanf("%d%d",&x,&y);
			if(x+a[x]<=n) cut(x,x+a[x]);
			else cut(x,n+1);
			if(x+y<=n) link(x,x+y);
			else link(x,n+1);
			a[x]=y;
		}
	}
	return 0;
}

