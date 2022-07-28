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

const int N=3e5+5;

struct Node
{
	int ch[2],fa;
	int siz;
	LL val,sum;
}t[N];

inline void pushup(int x) 
{ 
	t[x].siz=t[t[x].ch[0]].siz+t[t[x].ch[1]].siz+1; 
	t[x].sum=t[t[x].ch[0]].sum+t[t[x].ch[1]].sum+t[x].val; 
}

void rotate(int x)
{
	int k=(t[t[x].fa].ch[1]==x);
	int y=t[x].fa,z=t[y].fa;
	t[z].ch[t[z].ch[1]==y]=x; t[x].fa=z;
	t[y].ch[k]=t[x].ch[k^1]; t[t[x].ch[k^1]].fa=y;
	t[x].ch[k^1]=y; t[y].fa=x;
	pushup(y); pushup(x);
}

void splay(int x,int top=0)
{
	int y,z;
	while(t[x].fa!=top) {
		y=t[x].fa; z=t[y].fa;
		if(z!=top) {
			if((t[y].ch[1]==x)^(t[z].ch[1]==y)) 
				rotate(x);
			else rotate(y);
		}
		rotate(x);
	}
}

int findroot(int x)
{
	while(t[x].fa)
		x=t[x].fa;
	return x;
}

void merge(int x,int y)
{
	splay(x); splay(y);
	while(t[x].ch[0])
		x=t[x].ch[0];
	splay(x);
	t[x].ch[0]=y;
	t[y].fa=x;
	pushup(x);
	splay(y);
}

void split(int x)
{
	splay(x);
	if(t[x].ch[0]) {
		t[t[x].ch[0]].fa=0;
		t[x].ch[0]=0;
	}
}

LL prefix(int x)
{
	splay(x);
	return t[t[x].ch[0]].sum+t[x].val;
}

int rank(int x)
{
	splay(x);
	return t[t[x].ch[0]].siz+1;
}

int n,m;
int main()
{
//	freopen("1.in","r",stdin);
	int i;
	int x,y;
	char opt[2];
	
	scanf("%d%d",&n,&m);
	for(i=1;i<=n;i++) {
		scanf("%lld",&t[i].val);
		t[i].sum=t[i].val;
		t[i].siz=1;
		t[i].ch[0]=t[i].ch[1]=t[i].fa=0;
	}
	
	while(m--) {
		scanf("%s",opt);
		if(*opt=='M') {
			scanf("%d%d",&x,&y);
			x=findroot(x); y=findroot(y);
			if(x!=y) merge(x,y);
		}
		else if(*opt=='D') {
			scanf("%d",&x);
			split(x);
		}
		else {
			scanf("%d%d",&x,&y);
			if(findroot(x)!=findroot(y)) 	
				printf("-1\n");
			else {
				if(rank(x)>rank(y)) swap(x,y);
				printf("%lld\n",prefix(y)-prefix(x)+t[x].val);	
			}
		}
	}
	return 0;
}

