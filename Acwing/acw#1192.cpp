#include<set>
#include<map>
#include<queue>
#include<stack>
#include<cmath>
#include<ctime>
#include<bitset>
#include<vector>
#include<cstdio>
#include<complex>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>

using namespace std;
typedef long long LL;
typedef long double LD;
typedef pair<int,int> PII;
typedef unsigned long long ULL;

const int N=2e5+5;

int n,m;
PII a[N];
int b[N];

int main()
{
//	freopen("1.in","r",stdin);
	srand((unsigned)time(0));
	
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++) 
		scanf("%d%d",&a[i].first,&a[i].second);
	for(int i=1;i<=n;i++) b[i]=100;
	while(clock()<0.9*CLOCKS_PER_SEC) {
		random_shuffle(a+1,a+m+1);
		for(int i=1;i<=m;i++) {
			if(b[a[i].first]<=b[a[i].second]) 
				b[a[i].first]=b[a[i].second]+1;
		}
	}
	for(int i=1;i<=m;i++) 
		if(b[a[i].first]<=b[a[i].second]) 
			return puts("Poor Xed")&0;
	LL ans=0;
	for(int i=1;i<=n;i++) ans+=b[i];
	printf("%lld\n",ans);
	return 0;
}

