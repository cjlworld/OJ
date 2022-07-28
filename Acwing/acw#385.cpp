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

const int N=256;

int n,m;
int w[N][N];

int main()
{
//	freopen("1.in","r",stdin);
	int i,j,k;
	int x,y;
	memset(w,0x3f,sizeof w);
	scanf("%d%d",&n,&m);
	for(i=1;i<=m;i++) {
		scanf("%d%d",&x,&y);
		w[x][y]=w[y][x]=1;
	}
	for(i=1;i<=n;i++) w[i][i]=0;
	for(k=1;k<=n;k++)
		for(i=1;i<=n;i++) 
			for(j=1;j<=n;j++) 
				w[i][j]=min(w[i][j],w[i][k]+w[j][k]);
	
	int ans=0;
	for(i=1;i<=n;i++) 
		for(j=1;j<=n;j++) 
			if(i!=j) ans=max(ans,w[i][j]);
	printf("%d\n",ans);
	return 0;
}

