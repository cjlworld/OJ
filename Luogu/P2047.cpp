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

const int N=256;

int n,m;
int w[N][N];
LL c[N][N];

int main()
{
//	freopen("1.in","r",stdin);
	int i,j,k;
	int x,y,z;
	memset(w,0x3f,sizeof w);
	cin>>n>>m;
	for(i=1;i<=m;i++) {
		cin>>x>>y>>z;
		w[x][y]=w[y][x]=z;
		c[x][y]=c[y][x]=1;
	}
	for(k=1;k<=n;k++) 
		for(i=1;i<=n;i++) 
			for(j=1;j<=n;j++) {
				if(w[i][k]+w[k][j]==w[i][j]) 
					c[i][j]+=c[i][k]*c[k][j];
				else if(w[i][k]+w[k][j]<w[i][j]) {
					w[i][j]=w[i][k]+w[k][j];
					c[i][j]=c[i][k]*c[k][j];
				}
			}
	
	double ans;
	for(i=1;i<=n;i++) {
		ans=0.0;
		for(x=1;x<=n;x++) {
			if(x==i) continue;
			for(y=1;y<=n;y++) {
				if(y==i||y==x) continue;
				if(w[x][i]+w[i][y]==w[x][y])
					ans+=c[x][i]*1.0*c[i][y]/(c[x][y]*1.0);
			}
		}
		printf("%.3lf\n",ans);
	}
	return 0;
}

