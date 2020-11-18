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

const int N=16000+5;

int n,m;
int l[N],s[N];
LL p[N];

LL f[N]; // f[i] 表示 [1,i] 已经不能再刷了，的最小贡献。 

int main()
{
//	freopen("1.in","r",stdin);
	int i,j,k;
	scanf("%d%d",&n,&m);
	for(i=1;i<=m;i++)
		scanf("%d%lld%d",&l[i],&p[i],&s[i]);
	
	for(i=1;i<=n;i++) {
		f[i]=f[i-1];
		for(j=1;j<=m;j++) {
			if(i<s[j]) continue;
			for(k=max(i-l[j],0);k<=s[j]-1;k++) 
				f[i]=max(f[i],f[k]+(i-k)*p[j]);
		}
//		printf("%lld ",f[i]);
	}
//	printf("\n");
	LL ans=0;
	for(i=1;i<=n;i++) 
		ans=max(ans,f[i]);
	printf("%lld\n",ans);
	return 0;
}

