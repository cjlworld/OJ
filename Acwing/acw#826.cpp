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
	int val,nxt;
}t[N];
int idx,hh;
void init()
{
	memset(t,0,sizeof t);
	idx=1,hh=1;
}
void insert(int p,int x)
{
	t[++idx].val=x;
	t[idx].nxt=t[p].nxt;
	t[p].nxt=idx;
}
void remove(int p)
{
	t[p].nxt=t[t[p].nxt].nxt;
}
int n;

int main()
{
//	freopen("1.in","r",stdin);
	int i,k,x;
	char opt[2];
	init();
	scanf("%d",&n);
	for(i=1;i<=n;i++) {
		scanf("%s",opt);
		if(*opt=='H') 
			scanf("%d",&x),insert(hh,x);
		else if(*opt=='D')
			scanf("%d",&k),remove(k+1);
		else if(*opt=='I') 	
			scanf("%d%d",&k,&x),insert(k+1,x);
	}
	for(i=t[hh].nxt;i;i=t[i].nxt) 
		printf("%d ",t[i].val);
	return 0;
}
