#include<set>
#include<map>
#include<queue>
#include<stack>
#include<ctime>
#include<cmath>
#include<bitset>
#include<vector>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>

using namespace std;
typedef long long LL;
typedef unsigned long long ULL;

const int N=2e5+5;
const LL INF=1e16;
LL a[N];
int n;

int main()
{
//	freopen("1.in","r",stdin);
	int i,j;
	scanf("%d",&n);
	for(i=1;i<=n;i++) 
		scanf("%lld",&a[i]);
	LL ans,cmax;
	ans=cmax=a[1]; 
	for(i=2;i<=n;i++) {
		cmax=max(a[i],cmax+a[i]);
		ans=max(ans,cmax);
	}
	cout<<ans;
	return 0;
}

