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

const int N=1e5+5;

int n;
int a[N],c[N];

int main()
{
//	freopen("1.in","r",stdin);
	int i;
	scanf("%d",&n);
	for(i=1;i<=n;i++) scanf("%d",&a[i]);
	for(i=1;i<=n;i++) c[i]=a[i]-a[i-1];
	LL cnt1=0,cnt2=0;
	for(i=2;i<=n;i++) {
		if(c[i]<0) cnt1-=c[i];
		else cnt2+=c[i];
	}
	printf("%lld\n%lld\n",max(cnt1,cnt2),max(cnt1,cnt2)-min(cnt1,cnt2)+1);
	return 0;
}

