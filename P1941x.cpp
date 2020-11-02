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

const int N=1e4+5,M=1e3+5;
const int INF=0x3f3f3f3f;

int n,m,kk;
int f[M],g[M],t[M];
bool v[N][M];
int a[N],b[N];
int ach;

int main()
{
	int i,j,k;
	int x,y,z;
	scanf("%d%d%d",&n,&m,&kk);
	for(i=1;i<=n;i++)  // 在上一个位置点击，这一个位置上升/下降的高度。 
		scanf("%d%d",&a[i],&b[i]);
	for(i=1;i<=kk;i++) {
		scanf("%d%d%d",&x,&y,&z);
		for(j=z;j<=m;j++) v[x][j]=true;
		for(j=y;j>=1;j--) v[x][j]=true;
	}
	for(i=1;i<=m;i++) 
		if(v[0][i]) f[i]=INF;
	for(i=1;i<=n;i++) {
		memcpy(g,f,sizeof g);
		memset(f,0x3f,sizeof f);
		memset(t,0x3f,sizeof t);

		for(j=1;j<=m-1;j++) {
			if(j-a[i]>=1) t[j]=min(g[j-a[i]]+1,t[j-a[i]]+1);
			if(v[i][j]) continue;
			if(j-a[i]>=1) f[j]=min(g[j-a[i]]+1,t[j-a[i]]+1);
		}
		for(j=1;j+b[i]<=m;j++) 
			if(!v[i][j])
				f[j]=min(f[j],g[j+b[i]]);
				
		if(!v[i][m]) {
			for(k=1;k<=m;k++) 
				f[m]=min(f[m],g[k]+max(1,(m-k)/a[i]+((m-k)%a[i]>0)));
		}
		for(j=1;j<=m;j++) 
			if(f[j]<INF) ach=i;
	}
	if(ach==n) {
		int ans=INF;
		for(i=1;i<=m;i++) 
			ans=min(ans,f[i]);
		printf("1\n%d\n",ans);
	}
	else {
		int ans=0;
		for(i=0;i<=n;i++)
			if(v[i][m]&&ach>=i) ans++;
		printf("0\n%d\n",ans);
	}
	return 0;
}
