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
	int ch[2],p,v; // 儿子，父亲，权值 
	int sum,rev;
}t[N];

void addrev(int x)
{
	swap(t[x].ch[0],t[x].ch[1]);
	t[x].rev^=1;
}

void pushup(int x)
{
	t[x].sum=t[t[x].ch[0]].sum^t[x].v^t[t[x].ch[1]].sum;
}

void pushdown(int x)
{
	if(t[x].rev) {
		addrev(t[x].ch[0]),addrev(t[x].ch[1]);
		t[x].rev=0;
	}
}
bool isroot(int x)  
{
	return (t[t[x].p].ch[0]!=x)&&(t[t[x].p].ch[1]!=x);
}

void rotate(int x)
{
	int y=t[x].p,z=t[y].p;
	int k=(t[y].ch[1]==x);
	if(!isroot(y)) t[z].ch[t[z].ch[1]==y]=x;
	t[x].p=z;
	t[y].ch[k]=t[x].ch[k^1],t[t[x].ch[k^1]].p=y;
	t[x].ch[k^1]=y,t[y].p=x; 
	pushup(y),pushup(x);
}

void preview(int x)
{
	if(!isroot(x)) preview(t[x].p);
	pushdown(x);
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
	int z=x,y=0;
	for(y=0;x;y=x,x=t[x].p) {
		splay(x);
		t[x].ch[1]=y,pushup(x);
	}
	splay(z);
}
void makeroot(int x)
{
	access(x),addrev(x);
}

int findroot(int x) // 找到x所在原树的根节点, 再将原树的根节点旋转到splay的根节点
{
	access(x);
	while(t[x].ch[0]) pushdown(x),x=t[x].ch[0];
	splay(x);
	return x;
}

void split(int x,int y)
{
	makeroot(x),access(y);
}

void link(int x,int y)
{
	makeroot(x);
	if(findroot(y)!=x) t[x].p=y;
}

void cut(int x,int y)
{
	split(x,y);
	if(t[y].ch[0]==x&&!t[x].ch[1]) {
		t[x].p=t[y].ch[0]=0;
		pushup(y);
	}
}

int n,m;

int main()
{
//	freopen("1.in","r",stdin);
	int i;
	int x,y,opt;
	scanf("%d%d",&n,&m);
	for(i=1;i<=n;i++) scanf("%d",&t[i].v);
	while(m--) {
		scanf("%d%d%d",&opt,&x,&y);
		if(opt==0) split(x,y),printf("%d\n",t[y].sum);
		else if(opt==1) link(x,y);
		else if(opt==2) cut(x,y);
		else splay(x),t[x].v=y,pushup(x);
	}
	return 0;
}

