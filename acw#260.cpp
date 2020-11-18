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

const int N=2e5+5;

struct Node
{
	int lc,rc;
	int siz,val,pri;
}t[N];
int root,idx;
void Update(int now) { t[now].siz=t[t[now].lc].siz+t[t[now].rc].siz+1; }

int merge(int x,int y)
{
	if(!x||!y) return x|y;
	return (t[x].pri>t[y].pri) 
	? (t[x].rc=merge(t[x].rc,y),Update(x),x)
	: (t[y].lc=merge(x,t[y].lc),Update(y),y);
}

void split(int now,int rank,int &x,int &y)
{
	if(!now) return x=y=0,void();
	if(t[t[now].lc].siz+1<=rank) x=now,split(t[x].rc,rank-t[t[now].lc].siz-1,t[x].rc,y);
	else y=now,split(t[y].lc,rank,x,t[y].lc);
	Update(now);
}

int NewNode(int val)
{
	idx++;
	t[idx].val=val;
	t[idx].siz=1;
	t[idx].pri=rand();
	t[idx].lc=t[idx].rc=0;
	return idx;
}

void ldr(int now)
{
	if(!now) return;
	ldr(t[now].lc);
	printf("%d ",t[now].val);
	ldr(t[now].rc);
}

int n;

int main()
{
//	freopen("1.in","r",stdin);
	srand((unsigned)time(0));
	int i;
	int x,y,p,v;
	while(~scanf("%d",&n)) {
		idx=root=0;
		for(i=1;i<=n;i++) {
			scanf("%d%d",&p,&v);
			split(root,p,x,y);
			root=merge(merge(x,NewNode(v)),y);
		}
		ldr(root);
		printf("\n");
	}
	return 0;
}

