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
	int pre,nxt;
}t[N];
int hh,tt,idx;
void init()
{
	memset(t,0,sizeof t);
	hh=1,tt=2,idx=2;
	t[hh].nxt=tt,t[tt].pre=hh;
}

void insert(int pos) // 插入新节点到 pos 的后面。 
{
	t[++idx].pre=pos;
	t[idx].nxt=t[pos].nxt;
	
	t[t[idx].nxt].pre=idx;
	t[pos].nxt=idx;
}

void del(int pos)
{
	t[t[pos].pre].nxt=t[pos].nxt;
	t[t[pos].nxt].pre=t[pos].pre;
}

bool vis[N];
int n,m;
int main()
{
//	freopen("1.in","r",stdin);
	int i;
	int x,y;
	init();
	scanf("%d",&n);
	insert(hh);
	for(i=2;i<=n;i++) {
		scanf("%d%d",&x,&y); x+=2;
		if(!y) insert(t[x].pre);
		else insert(x);
	}
//	for(i=1;i<=idx;i++) 
//		printf("%d %d \n",t[i].pre,t[i].nxt);
	scanf("%d",&m);
	for(i=1;i<=m;i++) {
		scanf("%d",&x); x+=2;
		if(vis[x]) continue;
		vis[x]=true;
		del(x);
	}
	for(i=t[hh].nxt;i!=tt;i=t[i].nxt) 
		printf("%d ",i-2);
	printf("\n");
	return 0;
}

