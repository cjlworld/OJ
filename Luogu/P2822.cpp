#include<cmath>
#include<vector>
#include<cstdio>
#include<iostream>
typedef long long LL;
typedef unsigned long long ULL;
using namespace std;
const int N=2000+5;
LL f[N][N],sum[N][N],a[N][N];
int n=2000,m=2000;
int T,k;
LL s[N][N];
void calc(int x)
{
	int tmp=x;
	for(int i=2;i*i<=tmp;i++) 
		while(x%i==0) 
			a[tmp][i]++,x=x/i;
	if(x>1) a[tmp][x]++;
	return;
}
vector<int> v;
int main()
{
//	freopen("1.in","r",stdin);
	int i,j;
	vector<int>::iterator it;
	cin>>T>>k;
	for(i=1;i<=n;i++) calc(i);
	for(i=1;i<=n;i++)
		for(j=1;j<=n;j++) 
			s[i][j]=s[i-1][j]+a[i][j];
	for(i=1;i<=n;i++) 
		if(a[k][i])
			v.push_back(i);
	for(i=1;i<=n;i++) {
		for(j=1;j<=i;j++) {
			LL cmin=1e9;
			for(it=v.begin();it!=v.end();it++) 
				cmin=min(cmin,(s[i][*it]-s[j][*it]-s[i-j][*it])/a[k][*it]);
			f[i][j]=(cmin>0);
		}
	}
	for(i=1;i<=n;i++) 
		for(j=1;j<=m;j++) 
			sum[i][j]=sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1]+f[i][j];
	while(T--) {
		scanf("%d%d",&n,&m);
		printf("%lld\n",sum[n][m]);
	}
	return 0;
}
