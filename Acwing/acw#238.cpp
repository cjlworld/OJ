#include<set>
#include<map>
#include<cmath>
#include<ctime>
#include<stack>
#include<queue>
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

int par[N],d[N],siz[N];
// par[] : father 节点编号
// d[] : x 到 father 节点的边权
// siz[] : 若是某并查集的根，则是当前并查集的大小，否则是0 
int Find(int x)
{
	if(par[x]!=x) {
		int root=Find(par[x]);
		d[x]+=d[par[x]];
		par[x]=root;
	}
	return par[x];
}

int n;

int main()
{
//	freopen("1.in","r",stdin);
	int i,x,y;
	char opt[3];
	
	for(i=1;i<=30000+5;i++) 
		par[i]=i,siz[i]=1,d[i]=0;
		
	scanf("%d",&n);
	while(n--) {
		scanf("%s%d%d",opt,&x,&y);
		if(*opt=='M') {
			x=Find(x); y=Find(y);
			par[x]=y;
			d[x]=siz[y]; // 原来并查集到根距离 0,1,2,....,siz[y]-1 
			siz[y]+=siz[x];
			siz[x]=0;
		}
		else {
			if(Find(x)!=Find(y)) 
				printf("-1\n");
			else printf("%d\n",abs(d[x]-d[y])-1);
		}
	}
	return 0;
}

