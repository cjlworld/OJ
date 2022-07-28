#include<bits/stdc++.h>
using namespace std;
int n,m;//n(n≤500)，m(m≤6000)，其中n代表希望购买的奖品的种数，m表示拨款金额
int w[512],c[512],s[512];//w---weight,c---price,s---how many
int f[6005];
int main()
{
//	freopen("1.in","r",stdin);
	int i,j,k;
	cin>>n>>m;
	for(i=1;i<=n;i++) {
		cin>>w[i]>>c[i]>>s[i];
	}
	for(i=1;i<=n;i++) {
		for(j=m;j>=0;j--) {
			for(k=1;k<=s[i];k++) {
				if(j-k*w[i]<0) break;
				f[j]=max(f[j],f[j-k*w[i]]+k*c[i]);
			}
		}
	}
	cout<<f[m];
	return 0;
}

