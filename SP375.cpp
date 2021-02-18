#pragma GCC optimize(2)

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
#define rint register int
typedef long long LL;
typedef unsigned long long ULL;

inline void relax(int& a,const int& b) { a=((a>b) ? a : b); }

const int N=2e5+5;

struct Node
{
	int ch[2],fa;
	int siz;
	bool rev;
	int val,mx;
}t[N];

inline void pushup(rint x) 
{
	t[x].siz=t[t[x].ch[0]].siz+t[t[x].ch[1]].siz;
	t[x].mx=t[x].val;
	relax(t[x].mx,t[t[x].ch[0]].mx);
	relax(t[x].mx,t[t[x].ch[1]].mx);
}

inline void Addrev(rint x) { t[x].rev^=1; swap(t[x].ch[0],t[x].ch[1]); }
inline void pushdown(rint x)
{
	if(t[x].rev) {
		Addrev(t[x].ch[0]);
		Addrev(t[x].ch[1]);
		t[x].rev=false;
	}
}

inline bool isroot(rint x) { return (t[t[x].fa].ch[0]!=x && t[t[x].fa].ch[1]!=x); }
void preview(rint x) { if(!isroot(x)) preview(t[x].fa); pushdown(x); }

inline void rotate(rint x)
{
	if(isroot(x)) return;
	rint y=t[x].fa,z=t[y].fa;
	rint k=(t[y].ch[1]==x);
	pushdown(z); pushdown(y); pushdown(x);
	if(!isroot(y)) t[z].ch[t[z].ch[1]==y]=x;
	t[x].fa=z;
	t[y].ch[k]=t[x].ch[k^1]; t[t[x].ch[k^1]].fa=y;
	t[x].ch[k^1]=y; t[y].fa=x;
	pushup(y); pushup(x);
}

inline void splay(rint x)
{
	rint y,z;
	preview(x);
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

inline void access(rint x)
{
	rint z=x,y;
	for(y=0;x;y=x,x=t[x].fa) {
		splay(x);
		t[x].ch[1]=y;
		pushup(x);
	}
	splay(z);
}

inline void makeroot(rint x) { access(x); Addrev(x); }
inline void split(rint x,rint y) { makeroot(x); access(y); }
inline int findroot(rint x)
{
	access(x);
	while(pushdown(x),t[x].ch[0])
		x=t[x].ch[0];
	return x;
}
inline void link(int x,int y) 
{
	makeroot(x);
	if(findroot(y)!=x) t[x].fa=y;
}
int T,n;

int main()
{
//	freopen("1.in","r",stdin);
	rint i;
	rint x,y,z;
	char opt[20];
	
	scanf("%d",&T);
	while(T--) {
		scanf("%d",&n);
		for(i=0;i<=2*n;i++) {
			t[i].siz=1;
			t[i].ch[0]=t[i].ch[1]=t[i].fa=0;
			t[i].rev=0;
			t[i].mx=t[i].val=0;
		} 
		for(i=1;i<=n-1;i++) {
			scanf("%d%d%d",&x,&y,&z);
			t[i+n].val=t[i+n].mx=z;
			link(x,i+n);
			link(y,i+n);
		}
		
		while(scanf("%s",opt),strcmp(opt,"DONE")) {
			scanf("%d%d",&x,&y);
			if(!strcmp(opt,"QUERY")) {
				split(x,y);
				printf("%d\n",t[y].mx);
			}
			else {
				access(n+x);
				t[n+x].val=y;
				pushup(n+x);
			}
		}		
	}
	return 0;
}

