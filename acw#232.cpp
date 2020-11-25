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
typedef pair<int,double> PID;

const int N=256;

// f[i][j][k] 表示经过 i 次挑战，背包剩余容量为 j ，已经成功 k 次的概率。
int n,win,m;

double p[N];
int a[N];
PID c[N];
double f[N][N][N];

int main()
{
//	freopen("1.in","r",stdin);
	int i,j,k;
	int x;
	
	cin>>n>>win>>m;
	m=min(m,n);
	for(i=1;i<=n;i++) {
		cin>>x;
		c[i].second=x/100.0;
	}
	for(i=1;i<=n;i++) cin>>c[i].first;
	
	sort(c+1,c+n+1);
	reverse(c+1,c+n+1);
	
	for(i=1;i<=n;i++) 
		a[i]=c[i].first,p[i]=c[i].second;
		
	f[0][m][0]=1;
	for(i=1;i<=n;i++) {
		for(j=0;j<=n-1;j++) {
			for(k=0;k<=i;k++) {
				// win
				if(j>=a[i]&&k>=1) 
					f[i][j][k]+=f[i-1][j-a[i]][k-1]*p[i];
					
				// lose
				f[i][j][k]+=f[i-1][j][k]*(1-p[i]);
				
//				printf("f[%d][%d][%d] = %.6lf\n",i,j,k,f[i][j][k]);
			}
		}
		for(k=0;k<=i;k++) 
				f[i][n][k]+=f[i-1][n][k]*(1-p[i]);
		if(a[i]==-1) continue;
		else {
			for(j=max(n-a[i],0);j<=n;j++) {
				for(k=1;k<=i;k++) 
					f[i][n][k]+=f[i-1][j][k-1]*p[i];
			}
		}
	}
	
	double ans=0;
	for(i=0;i<=n;i++) 
		for(k=win;k<=n;k++) 
			ans+=f[n][i][k];
	printf("%.6lf\n",ans);
	return 0;
}

