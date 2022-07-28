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

int n,m;
int f[N][25];
// f[j][i] ±Ì æ max{a[j---- j+(1<<i)-1]}
int query(int x,int y)
{
	if(x>y) swap(x,y);
	int k=(int)log2(y-x+1);
	return max(f[x][k],f[y-(1<<k)+1][k]);
}
int main()
{
//	freopen("1.in","r",stdin);
	int i,j;
	int x,y;
	scanf("%d",&n);
	for(i=1;i<=n;i++) 
		scanf("%d",&f[i][0]);
	for(i=1;(1<<i)<=n;i++) 
		for(j=1;j+(1<<i)-1<=n;j++) 
			f[j][i]=max(f[j][i-1],f[j+(1<<(i-1))][i-1]);
	scanf("%d",&m);
	while(m--) {
		scanf("%d%d",&x,&y);
		printf("%d\n",query(x,y));
	}
	return 0;
}

