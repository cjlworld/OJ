#include<cstdio>
#include<cstring>
#include<iostream>
#define LL long long
#define rint register int
using namespace std;
const int N=256;
const LL MOD=10;
const LL M=6e6;
LL a[N];
LL s[N];
LL f[20][N][N]; // f[l][r] stand for cut l and r and maxmize or minmize the ans between it;(with k used)
int n,m;
LL ans=0;
int main()
{
//	freopen("1.in","r",stdin);
	cin>>n>>m;
	rint i,j,k,e,r;
	for(i=1;i<=n;i++) {
		cin>>a[i];
		a[i]=(a[i]+M)%MOD;
		a[i+n]=a[i];
	}
	for(i=1;i<=2*n;i++) 
		s[i]=s[i-1]+a[i];
	memset(f,0x3f,sizeof f);
	for(i=1;i<=2*n;i++) 
		for(j=i;j<=2*n;j++) 
			f[2][i][j]=(s[j]-s[i-1]+M)%MOD;
	for(i=2;i<=n;i++) { // len
		for(j=1;j+i-1<=2*n;j++) { //start
			for(k=j;k<j+i-1;k++) {// [] (]
				for(e=2;e<=m+2;e++) {
					for(r=2;e+r-1<=m+1;r++) {
						if(f[e][j][k]==f[0][0][0]||f[r][k+1][i+j-1]==f[0][0][0]) 
							continue;
						f[e+r-1][j][i+j-1]=min(f[e+r-1][j][i+j-1],f[e][j][k]*f[r][k+1][i+j-1]);
			//			printf("%d %d %d : %lld\n",e+r-1,j,i+j-1,f[e+r-1][j][i+j-1]);
					}
				}
			}
		}
	}
	ans=0x3f3f3f;
	for(i=1;i<=n-1;i++) 
		ans=min(ans,f[m+1][i][i+n-1]);
	cout<<ans<<endl;	
	memset(f,0,sizeof f);
	for(i=1;i<=2*n;i++) 
		for(j=i;j<=2*n;j++) 
			f[2][i][j]=(s[j]-s[i-1]+M)%MOD;
	for(i=2;i<=n;i++) { // len
		for(j=1;j+i-1<=2*n;j++) { //start
			for(k=j;k<j+i-1;k++) {// [] (]
				for(e=2;e<=m+2;e++) {
					for(r=2;e+r-1<=m+1;r++) {
						f[e+r-1][j][i+j-1]=max(f[e+r-1][j][i+j-1],f[e][j][k]*f[r][k+1][i+j-1]);
			//			printf("%d %d %d : %d\n",e+r-1,j,i+j-1,f[e+r-1][j][i+j-1]);
					}
				}
			}
		}
	}
	ans=0ll;
	for(i=1;i<=n-1;i++) 
		ans=max(ans,f[m+1][i][i+n-1]);
	cout<<ans<<endl;
	return 0;
}

