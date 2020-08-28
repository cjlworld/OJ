#include<cstdio>
#include<iostream>
typedef long long LL;
typedef unsigned long long ULL;
using namespace std;
const int INF=(-1u)>>1;
const int N=1e5+5;
int a[N];
int n;
int main()
{
//	freopen("1.in","r",stdin);
	int i;
	int ans=0,cmin;
	scanf("%d",&n);
	for(i=1;i<=n;i++) 
		scanf("%d",&a[i]);
	cmin=a[1];
	for(i=2;i<=n;i++) {
		ans=max(ans,a[i]-cmin);
		cmin=min(cmin,a[i]);
	}
	cout<<ans;
	return 0;
}

