#include<bits/stdc++.h>
using namespace std;
int m,n;//M (背包容量，M≤200)和N(物品数量，N≤30)；
int w[256],c[256];
int f[1024];
int main()
{
//	freopen("1.in","r",stdin);
	int i,j;
	cin>>m>>n;
	for(i=1;i<=n;i++) 
		cin>>w[i]>>c[i];
	for(i=1;i<=n;i++) {
		for(j=1;j<=m;j++) {
			if(j-w[i]>=0) f[j]=max(f[j],f[j-w[i]]+c[i]);
		}
	}
	cout<<"max="<<f[m];
	return 0;
}

