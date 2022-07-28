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

int p[N],tot;
bool tag[N];
int mobius[N];

void prime(int n)
{
	int i,j,t;
	mobius[1]=1;
	for(i=2;i<=n;i++) {
		if(!tag[i]) p[++tot]=i,mobius[i]=-1;
		for(j=1;j<=tot && p[j]*i<=n;j++) {
			t=p[j]*i;
			tag[t]=true;
			if(i%p[j]) mobius[t]=mobius[i]*(-1);
			else {
				mobius[t]=0;
				break;
			}
 		}
	}
}

int n,m;
int cnt[N]; 
int a[N],c[N]; // c[] 是 a[] 的桶。 

LL C(LL n,LL m)
{
	if(m>n||m<0) return 0;
	LL up=1,down=1;
	for(LL i=n,j=1;j<=m;j++,i--)
		up*=i,down*=j;
	return up/down;
}

int main()
{
//	freopen("1.in","r",stdin);
	int i,j;
	int cnt;
	LL ans;
	
	prime(N-1);
	
	while(scanf("%d",&n)==1) {
		memset(c,0,sizeof c);	
		m=0;
		for(i=1;i<=n;i++) {
			scanf("%d",&a[i]);
			c[a[i]]++;
			m=max(m,a[i]);
		}
		ans=0;
		for(i=1;i<=m;i++) {
			if(mobius[i]==0) continue;
			cnt=0; // cnt[d] 为有多少个数有约数d
			for(j=i;j<=m;j+=i) 
				cnt+=c[j];
			ans+=mobius[i]*C(cnt,4);
		}
		printf("%lld\n",ans);
	}
	
	return 0;
}

