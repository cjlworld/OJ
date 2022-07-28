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

int n;
int par[N];
int Find(int x) 
{
	if(par[x]!=x) return par[x]=Find(par[x]);
	else return x;
}

struct Node
{
	int val,o; // 权值，插入的时间。
	int lc,rc; 
	Node(int val,int o,int lc,int rc) 
		: val(val),o(o),lc(lc),rc(rc) {}
	Node() {}
	bool operator<(const Node &t) const
	{
		return val<t.val||(val==t.val&&o<t.o);
	}
}t[N];
int idx;

int merge(int x,int y) // 合并 以x,y为根的两个小根堆，并返回新的根节点的编号。
{
	if(!x||!y) return x|y;
	if(t[y]<t[x]) swap(x,y);
	if(rand()&1) t[x].lc=merge(t[x].lc,y);
	else t[x].rc=merge(t[x].rc,y);
	return x;
}

int main()
{
//	freopen("1.in","r",stdin);
	srand((unsigned)time(0));
	int i,opt,x,y;
	scanf("%d",&n);
	for(i=1;i<=n;i++) par[i]=i;
	while(n--) {
		scanf("%d%d",&opt,&x);
		if(opt==1) idx++,t[idx]=Node(x,idx,0,0);
		else if(opt==2) {
			scanf("%d",&y);
			x=Find(x),y=Find(y);
			if(x!=y) par[x]=par[y]=merge(x,y);
		}
		else if(opt==3) printf("%d\n",t[Find(x)].val);
		else if(opt==4) {
			x=Find(x);
			par[t[x].lc]=par[t[x].rc]=par[x]=merge(t[x].lc,t[x].rc);
		}
	}
	return 0;
}

