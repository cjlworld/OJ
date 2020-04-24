#include<bits/stdc++.h>
using namespace std;
int m,n;//M(背包容量，M≤200)，N(物品数量，N≤30)；
int w[256],c[256],p[256];
int f[1024];
int main()
{
//	freopen("1.in","r",stdin);
	int i,j,k;
	cin>>m>>n;
	for(i=1;i<=n;i++) {
		cin>>w[i]>>c[i]>>p[i];
		if(p[i]==0) p[i]=m/w[i]+1;
	}
	for(i=1;i<=n;i++) {
		for(j=m;j>=1;j--) {
			for(k=1;k<=p[i];k++) {
				if(j-k*w[i]<0) break;
				f[j]=max(f[j],f[j-k*w[i]]+k*c[i]);
			}
		}
	}
	cout<<f[m];
	return 0;
}

