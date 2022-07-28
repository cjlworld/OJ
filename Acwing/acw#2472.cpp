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

const int N=1e5+5;
struct Node
{
	int ch[2],p;
	int rev;
}t[N];
#define lc t[x].ch[0]
#define rc t[x].ch[1]
void addrev(int x) { swap(lc,rc),t[x].rev^=1; }
void pushdown(int x) { if(t[x].rev) addrev(lc),addrev(rc),t[x].rev=0; }
bool isroot(int x) { return (t[t[x].p].ch[0]!=x&&t[t[x].p].ch[1]!=x); }
void preview(int x) { if(!isroot(x)) preview(t[x].p); pushdown(x); }
void rotate(int x)
{
	int y=t[x].p,z=t[y].p;
	int k=t[y].ch[1]==x;
	if(!isroot(y)) t[z].ch[t[z].ch[1]==y]=x;
	t[x].p=z;
	t[y].ch[k]=t[x].ch[k^1]; t[t[x].ch[k^1]].p=y;
	t[x].ch[k^1]=y; t[y].p=x;
}
void splay(int x)
{
	int y,z;
	preview(x);
	while(!isroot(x)) {
		y=t[x].p,z=t[y].p;
		if(!isroot(y)) {
			if((t[z].ch[1]==y)^(t[y].ch[1]==x)) rotate(x);
			else rotate(y);
		}
		rotate(x);
	}
}
void access(int x)
{
	int z=x,y;
	for(y=0;x;y=x,x=t[x].p) {
		splay(x);
		t[x].ch[1]=y;
	}
	splay(z);
}
void makeroot(int x) { access(x),addrev(x); }
int findroot(int x)
{
	access(x);
	while(lc) pushdown(x),x=lc;
	splay(x);
	return x;
}
void link(int x,int y) { makeroot(x),t[x].p=y; }
void cut(int x,int y) { makeroot(x),access(y),t[x].p=t[y].ch[0]=0; }

int n,m;

int main()
{
//	freopen("1.in","r",stdin);
	int x,y;
	char opt[20];
	scanf("%d%d",&n,&m);
	while(m--) {
		scanf("%s%d%d",opt,&x,&y);
		if(!strcmp(opt,"Connect")) link(x,y);
		else if(!strcmp(opt,"Destroy")) cut(x,y);
		else {
			makeroot(x);
			if(findroot(y)==x) printf("Yes\n");
			else printf("No\n"); 
		}
	}
	return 0;
}
