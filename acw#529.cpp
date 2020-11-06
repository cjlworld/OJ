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
int g[N][S]; // g[i][j] ��ʾ��i���㵽����j��ĵ����̾��롣 
int f[N][S]; // f[i][j] ��ʾ�Ѿ���������i��,�Ѿ�����ĵ㼯Ϊj����С���ѡ�
 // ������Ҫ�ѵ�i+1����� 
int main()
{
//	freopen("1.in","r",stdin);
	int i,j,k,r;
	int x,y,z;
	scanf("%d%d",&n,&m);
	memset(w,0x3f,sizeof w);
	for(i=1;i<=m;i++) {
		scanf("%d%d%d",&x,&y,&z);
		x--,y--; // ��0��ʼ 
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
			for(k=(j-1)&j;k;k=(k-1)&j) { // ö���Ӽ����� j-k ���� k 
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

