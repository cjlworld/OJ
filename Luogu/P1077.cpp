#include<cstdio>
#include<iostream>
#define LL long long
using namespace std;
const int N=100+5;
const LL MOD=1000007;
LL f[N][N][N];
//f[M][N][ai]
//f[i][j][k] 已经摆了花i盆，第j种花最多再摆k盆的状态
LL s[N][N]; //s[i][j] = sum{f[i][j][k]} k<{0..a[j]} 
int a[N];
int n,m;
int main()
{
//	freopen("1.in","r",stdin);
	int i,j,k;
	int x,y,z;
	scanf("%d%d",&n,&m);
	for(i=1;i<=n;i++) 
		scanf("%d",&a[i]);
	s[0][0]=1ll;
	for(i=1;i<=m;i++) {
		for(j=1;j<=n;j++) {	
			if(a[j]>=1)
				for(k=0;k<=j-1;k++) 
					f[i][j][a[j]-1]=(f[i][j][a[j]-1]+s[i-1][k])%MOD;
			s[i][j]=(s[i][j]+f[i][j][a[j]-1])%MOD;
		//	printf("f[%d,%d,%d] = %lld\n",i,j,a[j]-1,f[i][j][a[j]-1]);
			for(k=a[j]-2;k>=0;k--) {
				f[i][j][k]=(f[i][j][k]+f[i-1][j][k+1])%MOD;
				s[i][j]=(s[i][j]+f[i][j][k])%MOD;
			//	printf("f[%d,%d,%d] = %lld\n",i,j,k,f[i][j][k]);
			}
		}
	}
	LL ans=0ll;
	for(j=1;j<=n;j++) {
		for(k=a[j];k>=0;k--) {
			ans=(ans+f[m][j][k])%MOD;
		}
	}
	cout<<ans;
	return 0;
}

