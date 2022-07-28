#include<set>
#include<map>
#include<ctime>
#include<queue>
#include<stack>
#include<vector>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
#define rint register int
typedef long long LL;
typedef unsigned long long ULL;
using namespace std;
const int N=1e5+5;
int cnt[N],a[N];
int T,n;
int main()
{
//	freopen("1.in","r",stdin);
	int i;
	scanf("%d",&T);
	int maxcnt,sum,others;
	while(T--) {
		scanf("%d",&n);
		fill(cnt,cnt+n+2,0);
		for(i=1;i<=n;i++) {
			scanf("%d",&a[i]);
			cnt[a[i]]++;
		}
		maxcnt=-1,sum=0,others=0;
		for(i=1;i<=n;i++) 
			maxcnt=max(maxcnt,cnt[i]);
		for(i=1;i<=n;i++) 
			sum+=(cnt[i]==maxcnt);
		others=n-sum*maxcnt;
		if(maxcnt==1) printf("%d\n",n);
		else printf("%d\n",sum-1+(others/(maxcnt-1)));
	}
	return 0;
}
