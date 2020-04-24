#include<bits/stdc++.h>
using namespace std;
int n,m;//n(物品数量，n≤3500)和m(背包容量,m≤12880)。
int w[3505],c[3505];//每行二个整数w[i]，c[i]，表示每个物品的重量和价值。
long long f[13000];
int main()
{
//	freopen("1.in","r",stdin);
	int i,j;
	cin>>n>>m;
	for(i=1;i<=n;i++) cin>>w[i]>>c[i];
	for(i=1;i<=n;i++) {
		for(j=m;j>=0;j--) {
			if(j-w[i]<0) break;
			f[j]=max(f[j],f[j-w[i]]+c[i]);
		}
	}
	cout<<f[m];
	return 0;
}

