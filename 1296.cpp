#include<set>
#include<map>
#include<queue>
#include<stack>
#include<ctime>
#include<cmath>
#include<vector>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
typedef long long LL;
typedef unsigned long long ULL;
using namespace std;
const int N=256,INF=1e9+5;
int n,k;
int a[N],v[N];
int f[N];
int main()
{
//	freopen("1.in","r",stdin);
	int T;
	int i,j;
	cin>>T;
	while(T--) {
		scanf("%d%d",&n,&k);
		for(i=1;i<=n;i++) scanf("%d",&a[i]);
		for(i=1;i<=n;i++) scanf("%d",&v[i]);
		memset(f,0,sizeof f);
		a[0]=-INF;
		for(i=1;i<=n;i++) {
			for(j=i-1;j>=0;j--) {
				if(a[i]-a[j]>k) 
					f[i]=max(f[i],f[j]+v[i]); 
			}
		}
		int ans=0;
		for(i=1;i<=n;i++) 
			ans=max(ans,f[i]);
		printf("%d\n",ans);
	}
	return 0;
}

