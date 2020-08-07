#include<cstdio>
#include<cstring>
#include<iostream>
typedef long long LL;
typedef unsigned long long ULL;
using namespace std;
const int N=5e4+5;
const LL INF=1e16;
// f[i] 表示装下前 i 个物品的费用最小值
// f[i] = min{ f[j]+[(s[i]-s[j]+i-j-1)-L]^2 } 0<=j<i;
int n; 
LL L;
LL a[N];
LL f[N],s[N],p[N];
#define val(i,j) ((s[i]-s[j]+i-j-1-L)*(s[i]-s[j]+i-j-1-L))
int main()
{
//	freopen("1.in","r",stdin);
	register int i,j;
	scanf("%d%lld",&n,&L);
	for(i=1;i<=n;i++) 
		scanf("%lld",&a[i]),s[i]=s[i-1]+a[i];
	memset(f,0x3f,sizeof f);
	f[0]=0;
	for(i=1;i<=n;i++) {
		for(j=p[i-1];j<i;j++) {
			if(f[j]+val(i,j)<f[i]) {
				f[i]=f[j]+val(i,j);
				p[i]=j;	
			}
		}
	}
	printf("%lld\n",f[n]);
	return 0;
}

