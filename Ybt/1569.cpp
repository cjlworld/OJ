#include<bits/stdc++.h>
using namespace std;
const int N=1000+5;
int f[N][N];
int a[N],s[N];
int n;
int ans;
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
	for(i=n+1;i<=2*n;i++) { s[i]=s[i-1]+a[i-n]; }
	memset(f,127,sizeof(f));
	ans=f[0][0]-1;
	Dp(1,2*n);
	for(i=1;i<=n;i++) { ans=min(ans,f[i][i+n-1]); }
	cout<<ans;
//-----------------------------------------------------
	memset(f,0,sizeof(f));
	int len,k;
	for(len=2;len<=2*n;len++) {
		for(i=1;i<=2*n+1-len;i++) {
			j=i+len-1;
			for(k=i;k<=j-1;k++) {
				f[i][j]=max(f[i][j],f[i][k]+f[k+1][j]+s[j]-s[i-1]);
			}
		}
	}
	ans=-1;
	for(i=1;i<=n;i++) {
		ans=max(ans,f[i][i+n-1]);
	}
	cout<<endl<<ans;
//-----------------------------------------
	return 0;
}

