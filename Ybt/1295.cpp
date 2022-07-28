#include<bits/stdc++.h>
using namespace std;
long long v,n;
long long w[1000];
long long f[20005];
int main()
{
//	freopen("1.in","r",stdin);
	cin>>v>>n;
	long long i,j;
	for(i=1;i<=n;i++) cin>>w[i];
	for(i=1;i<=n;i++) {
		for(j=v;j>=0;j--) {
			if(j-w[i]<0) break;
			f[j]=max(f[j],f[j-w[i]]+w[i]);
		}
	}
	cout<<v-f[v];
	return 0;
}

