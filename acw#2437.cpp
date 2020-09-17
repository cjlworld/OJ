#include<cstdio>
#include<cstring>
#include<iostream>

using namespace std;

const int N=100010;

int n,m;
struct Node
{
	int ch[2],v,p; // v表示当前元素在原始序列中的下标 
	int size;      // p 表示当前节点的父亲节点 
	bool rev;      // size---子树大小,res---翻转标记 
	Node(int v,int p) : v(v),p(p) 
	{
		size=1;
		ch[0]=ch[1]=0;
		return;
	} 
	Node() {}
}t[N];
int root=0,idx=0;

void pushup(int now)
{
	t[now].size=t[t[now].ch[0]].size+t[t[now].ch[1]].size+1;
	return;
}

void pushdown(int now)
{
	if(t[now].rev) {
		swap(t[now].ch[0],t[now].ch[1]);
		t[t[now].ch[0]].rev^=1;
		t[t[now].ch[1]].rev^=1;
		t[now].rev=0;
	}
	return;
}

void rotate(int x)
{
	int y=t[x].p,z=t[y].p;
	int k=(t[y].ch[1]==x);
	t[z].ch[t[z].ch[1]==y]=x,t[x].p=z;
	t[y].ch[k]=t[x].ch[k^1],t[t[x].ch[k^1]].p=y;
	t[x].ch[k^1]=y,t[y].p=x;
	pushup(y); pushup(x);
	return;
} 

void splay(int x,int top)
{
	int y,z;
	while(t[x].p!=top)
	{
		y=t[x].p; z=t[y].p;
		if(z!=top) {
			if((t[y].ch[1]==x)^(t[z].ch[1]==y))	rotate(x);
			else rotate(y);
		}	
		rotate(x);
	}
	if(!top) root=x;
	return;
}

void insert(int pos)
{
	int now=root,p=0;
	while(now) p=now,now=t[now].ch[pos>t[now].v];
	now=++idx;
	if(p) t[p].ch[pos>t[p].v]=now;
	t[now]=Node(pos,p);
	splay(now,0);
}

int get_k(int k)
{
	int now=root,y;
	while(now) {
		pushdown(now);
		y=t[t[now].ch[0]].size;
		if(y+1==k) return now;
		else if(y>=k) now=t[now].ch[0];
		else k-=y+1,now=t[now].ch[1];
	}
	return -1;
}

void ldr(int now)
{
	if(!now) return;
	pushdown(now);
	ldr(t[now].ch[0]);
	if(t[now].v>=1&&t[now].v<=n) printf("%d ",t[now].v);
	ldr(t[now].ch[1]);
}
#define DeBug ldr(root),printf("\n") 
int main()
{
//	freopen("1.in","r",stdin);
	int i,x,y;
	scanf("%d%d",&n,&m);
	for(i=0;i<=n+1;i++) insert(i);
//	for(i=1;i<=n+2;i++) pushup(i);
//	DeBug;
	while(m--) {
		scanf("%d%d",&x,&y);
		x=get_k(x); y=get_k(y+2);
		splay(x,0); splay(y,x);
		t[t[y].ch[0]].rev^=1; 
	}
	ldr(root);
	return 0;
}
