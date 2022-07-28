#include<cstdio>
#include<iostream>
#include<cstring>
#define LL long long
using namespace std;
const int N=1e5+5;
LL a[N];
LL f[N]; //don't choose cow i;
int num[N];
LL q[3*N]; //min
int n,k;
int main()
{
//	freopen("1.in","r",stdin);
	int i,j;
	scanf("%d%d",&n,&k);
	for(i=1;i<=n;i++) 
		scanf("%lld",&a[i]);
	memset(num,0,sizeof num);
	memset(q,0,sizeof q);
	int head=1,tail=0;
	for(i=0;i<=n;i++) {
		while(head<=tail&&num[head]<i-k-1) head++; //?? 
		f[i]=a[i]+q[head];
		while(head<=tail&&f[i]<=q[tail]) q[tail]=0,num[tail]=0,tail--;
		tail++;
		q[tail]=f[i];
		num[tail]=i;
	}
	LL ans=1e16;
	LL sum=0;
	for(i=1;i<=n;i++) 
		sum+=a[i];
	for(i=n-k;i<=n;i++) 
		ans=min(ans,f[i]);
	ans=sum-ans;
//	for(i=1;i<=n;i++) 
//		printf("%lld ",f[i]);
//	puts("");
	printf("%lld",ans);
	return 0;
}

