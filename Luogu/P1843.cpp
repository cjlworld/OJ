#include<bits/stdc++.h>
#define rint register int
#define INF 2147483646
#define LL long long
using namespace std;
LL n,A,B;
const int N=500000+5;
LL a[N];
LL tmp[N];
inline bool check(const LL &t)
{
	memset(tmp,0,sizeof(tmp));
	LL sum=0;
	for(rint i=1;i<=n;i++) tmp[i]=a[i];
	for(rint i=1;i<=n;i++) {
		tmp[i]-=A*t;
	}
	for(rint i=1;i<=n;i++) {
		if(tmp[i]<=0) continue;
		sum+=tmp[i]/B;
		if(tmp[i]-(tmp[i]/B)*B>0) sum++;
	}
	if(sum>t) return false;
	return true;
}
int main()
{
//	freopen("1.in","r",stdin);
	scanf("%d%d%d",&n,&A,&B);
	for(rint i=1;i<=n;i++) scanf("%d",&a[i]);
	LL right=INF,left=0,mid;
	while(left+1<right) {
		mid=(left+right)>>1;
		if(check(mid)) right=mid;
		else left=mid;
	}
	printf("%lld",right);
	return 0;
} 
