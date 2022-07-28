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

const int N=1e6+5,M=256;

int L;
int s,t,m;
int a[M],b[M];
int f[N];

int main()
{
//	freopen("1.in","r",stdin);
	int i,j,k;
	scanf("%d%d%d%d",&L,&s,&t,&m);
	for(i=1;i<=m;i++) 
		scanf("%d",&a[i]);
	sort(a+1,a+m+1);
	if(s==t) {
		int ans=0;
		for(i=1;i<=m;i++)
			ans+=(a[i]%s==0);
		printf("%d\n",ans);	
		return 0;
	}
	memcpy(b,a,sizeof b);
	for(i=1;i<=m;i++) {
		if(b[i]<=b[i-1]+100) 
			a[i]=a[i-1]+b[i]-b[i-1];
		else a[i]=a[i-1]+100;
	}
		
	L=a[m]+1;
	j=1;
	memset(f,0x3f,sizeof f);
	f[0]=0;
	for(i=1;i<=L+100;i++) {
		for(;a[j]<i&&j<=m;j++);
		for(k=max(i-t,0);k<=i-s;k++) 
			f[i]=min(f[i],f[k]);
		if(a[j]==i) f[i]++;
	}
	int ans=0x3f3f3f3f;
	for(i=L;i<=L+100;i++) 
		ans=min(ans,f[i]);
	cout<<ans<<endl;
	return 0;
}

