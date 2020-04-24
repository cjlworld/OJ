#include<cstdio>
#include<iostream>
#define LL long long
using namespace std;
const int N=20+1;
int a[N];
int n,k;
int t[N];
int tmp=0;
LL ans=0;
inline void ifprime(int x)
{
	int i,j;
	for(i=2;i*i<=x;i++) {
		if(x%i==0) 
			return;
	}
	ans++;
	return;
}
void dfs(int step)
{
	for(int i=t[step-1]+1;i<=n;i++) {
		t[step]=i;
		tmp+=a[i];
		if(step==k) ifprime(tmp);
		else dfs(step+1);
		t[step]=0;
		tmp-=a[i];
	}
	return;
}
int main()
{
//	freopen("1.in","r",stdin);
	scanf("%d%d",&n,&k);
	int i,j;
	for(i=1;i<=n;i++) 
		scanf("%d",&a[i]);
	dfs(1);
	printf("%lld",ans);
	return 0;
}

