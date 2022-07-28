#include<bits/stdc++.h>
#define rint register int
#define INF 2147483646
using namespace std;
const int T=1e5+5;
const int M=1e4+5;
int c[M],w[M],f[T];
int t,m;
int main()
{
//	freopen("1.in","r",stdin);
	scanf("%d%d",&t,&m);
	for(int i=1;i<=m;i++) 
		scanf("%d%d",&w[i],&c[i]);
	for(int i=1;i<=m;i++) {
		for(int j=w[i];j<=t;j++) {
			f[j]=max(f[j],f[j-w[i]]+c[i]);
		}
	}
	cout<<f[t]<<endl;
	return 0;
}

