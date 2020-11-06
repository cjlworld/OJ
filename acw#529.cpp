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

const int N=15,S=1<<N,INF=0x3f3f3f3f;

int n,m;
int w[N][N];
int g[N][S]; // g[i][j] 表示第i个点到集合j里的点的最短距离。 
int f[N][S]; // f[i][j] 表示已经搜索到第i层,已经加入的点集为j的最小花费。
 // 接下来要把第i+1层加入 
int main()
{
//	freopen("1.in","r",stdin);
	int i,j,k,r;
	int x,y,z;
	scanf("%d%d",&n,&m);
	memset(w,0x3f,sizeof w);
	for(i=1;i<=m;i++) {
		scanf("%d%d%d",&x,&y,&z);
		x--,y--; // 从0开始 
		w[x][y]=min(w[x][y],z);
		w[y][x]=min(w[y][x],z);
	}
	memset(g,0x3f,sizeof g);
	for(i=0;i<n;i++) 
		for(j=0;j<(1<<n);j++) 
			for(k=0;k<n;k++) 
				if((j>>k)&1) 
					g[i][j]=min(g[i][j],w[i][k]);
	memset(f,0x3f,sizeof f);
	for(i=0;i<n;i++) 
		f[0][1<<i]=0;
	for(i=1;i<n;i++) {
		for(j=1;j<(1<<n);j++) {
			for(k=(j-1)&j;k;k=(k-1)&j) { // 枚举子集，把 j-k 加入 k 
				if(f[i-1][k]>=INF) continue;
				x=j-k,y=0;
				for(r=0;r<n;r++) {
					if((x>>r)&1) y+=g[r][k];
					if(y>=INF) break;
				}
				if(r==n) f[i][j]=min(f[i][j],f[i-1][k]+y*i);
			}
		}
	}
	int ans=INF;
	for(i=0;i<n;i++) 
		ans=min(ans,f[i][(1<<n)-1]);
	printf("%d\n",ans);
	return 0;
}

