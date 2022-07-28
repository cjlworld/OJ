#include<set>
#include<map>
#include<queue>
#include<stack>
#include<ctime>
#include<cmath>
#include<bitset>
#include<vector>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>

using namespace std;
typedef long long LL;
typedef unsigned long long ULL;

const int N=1e5+5;

struct Node
{
	int prv,nxt;
	int val;
}t[N];
int idx,hh,tt; 
// 令hh,tt为链表两头的节点，数据节点在hh,tt之间,避免分类讨论 
void init()
{
	memset(t,0,sizeof t);
	idx=2;
	hh=1,tt=2;
	t[hh].nxt=tt,t[tt].prv=hh;
}
void insert(int p,int val)
{
	t[++idx].val=val;
	t[t[p].nxt].prv=idx;
	t[idx].nxt=t[p].nxt;
	t[p].nxt=idx;
	t[idx].prv=p;
}
void remove(int p)
{
	t[t[p].nxt].prv=t[p].prv;
	t[t[p].prv].nxt=t[p].nxt;
}

int n;

int main()
{
//	freopen("1.in","r",stdin);
	int i,k,x;
	char opt[4];
	init();
	scanf("%d",&n);
	while(n--) {
		scanf("%s",opt);
		if(*opt=='L') 
			scanf("%d",&x),insert(hh,x);
		else if(*opt=='R') 
			scanf("%d",&x),insert(t[tt].prv,x);
		else if(*opt=='D')
			scanf("%d",&k),remove(k+2);
		else if(!strcmp(opt,"IL")) 
			scanf("%d%d",&k,&x),insert(t[k+2].prv,x);
		else scanf("%d%d",&k,&x),insert(k+2,x);
		
//		for(i=t[hh].nxt;i!=tt;i=t[i].nxt) 
//			printf("%d ",t[i].val);
//		printf("\n");
	}
	for(i=t[hh].nxt;i!=tt;i=t[i].nxt) 
		printf("%d ",t[i].val);
	return 0;
}

