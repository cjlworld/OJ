#include<bits/stdc++.h>
using namespace std;
const int N=100+5;
int f[N][N];
int a[N],s[N];
int INF;
int n;
int Dp(int l,int r)
{
	if(f[l][r]!=f[0][0]) return f[l][r];
	if(l==r) return f[l][r]=0;
	for(int k=l;k<=r-1;k++) {
		f[l][r]=min(f[l][r],Dp(l,k)+Dp(k+1,r)+s[r]-s[l-1]);
	}
	return f[l][r];
}
int main()
{
//	freopen("1.in","r",stdin);
//	freopen(".out","w",stdout);
	cin>>n;
	int i,j;
	for(i=1;i<=n;i++) {
		scanf("%d",&a[i]);
		s[i]=s[i-1]+a[i];
	}
	memset(f,127,sizeof(f));
//	INF=f[0][0];
	Dp(1,n);
	cout<<f[1][n];
	return 0;
}

