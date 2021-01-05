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

const int N=2e5+5;

struct Node
{
	int ch[2],fa;
	int siz;
	bool rev;
	int val,mx;
}t[N];

void pushup(int x) 
{
	t[x].siz=t[t[x].ch[0]].siz+t[t[x].ch[1]].siz;
	t[x].mx=t[x].val;
	relax(t[x].mx,t[t[x].ch[0]].mx);
	relax(t[x].mx,t[t[x].ch[1]].mx);
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
void preview(int x) { if(!isroot(x)) preview(t[x].fa); pushdown(x); }

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

void splay(int x)
{
	int y,z;
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
	if(findroot(y)!=x) 
		t[x].fa=y;
}
int n;

int main()
{
//	freopen("1.in","r",stdin);
	int i;
	int x,y,z;
	char opt[20];
	
	scanf("%d",&n);
	for(i=0;i<=2*n;i++) {
		t[x].siz=1;
		t[x].ch[0]=t[x].ch[1]=t[x].fa=0;
		t[x].rev=0;
		t[x].mx=t[x].val=0;
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
	return 0;
}

/*
Input :

10
1 2 2
1 4 3
1 5 8
2 3 5
2 6 10
4 7 9
6 9 6
7 8 9
7 10 2
CHANGE 7 8
CHANGE 3 5
QUERY 3 9
CHANGE 2 9
QUERY 3 5
QUERY 1 4
QUERY 4 1
CHANGE 4 2
CHANGE 5 6
DONE

Output :

10
5
9
9

*/

