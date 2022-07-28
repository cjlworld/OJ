#include<set>
#include<map>
#include<cmath>
#include<ctime>
#include<stack>
#include<queue>
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
int s[N],tt;
LL h[N];
int l[N],r[N];

int main()
{
//	freopen("1.in","r",stdin);
	int i;
	while(scanf("%d",&n),n) {
		for(i=1;i<=n;i++) 
			scanf("%lld",&h[i]);
		h[0]=h[n+1]=0; // ±ß½ç 
		tt=1,s[tt]=0;
		for(i=1;i<=n;i++) {
			while(tt>0&&h[s[tt]]>=h[i]) tt--;
			l[i]=s[tt];
			s[++tt]=i;
		}
		tt=1,s[tt]=n+1;
		for(i=n;i>=1;i--) {
			while(tt>0&&h[s[tt]]>=h[i]) tt--;
			r[i]=s[tt];
			s[++tt]=i;
		}
		LL ans=0;
		for(i=1;i<=n;i++) 
			ans=max(ans,(r[i]-l[i]-1)*h[i]);
		printf("%lld\n",ans);
	}
	return 0;
}

