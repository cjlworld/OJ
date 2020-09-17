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

int n,m;
int root[N];
struct Node
{
	int lc,rc;
	int val,pos;
	inline bool operator<(const Node &other)
	{
		return val<other.val||(val==other.val&&pos<other.pos);
	}
}t[N];
int idx;

int merge(int x,int y)
{
	if(!x||!y) return x+y;
	if(t[y]<t[x]) swap(x,y);
	if(rand()&1) swap(t[x].lc,t[x].rc);
	t[x].lc=merge(t[x].lc,y);
	return x;
}

int par[N];
int Find(int x)
{
	if(par[x]!=x) return par[x]=Find(par[x]);
	else return x;
}

bool vis[N];
int main()
{
//	freopen("1.in","r",stdin);
	srand((unsigned)time(0));
	int i,x,y,opt;
	scanf("%d%d",&n,&m);
	for(i=1;i<=n;i++) {
		scanf("%d",&x);
		t[++idx].val=x;
		t[idx].pos=i;
		par[i]=i;
		root[i]=i;
	}
	while(m--) {
		scanf("%d%d",&opt,&x);
		if(opt==1) {
			scanf("%d",&y);
			if(vis[x]||vis[y]||Find(x)==Find(y)) continue;
			x=Find(x); y=Find(y);
			par[y]=x;
			root[x]=merge(root[x],root[y]);
		}
		else {
			if(vis[x]) {
				printf("-1\n");
				continue;
			}
			x=Find(x); y=root[x];
			vis[t[y].pos]=true;
			printf("%d\n",t[y].val);
			root[x]=merge(t[y].lc,t[y].rc);
		}
	}
	return 0;
}

