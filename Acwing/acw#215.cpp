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

const int N=5e4+5;

int p[N],mobius[N],tot=0;
bool tag[N];
void prime(int n)
{
	mobius[1]=1;
	int i,j;
	for(i=2;i<=n;i++) {
		if(!tag[i]) 
			p[++tot]=i,mobius[i]=-1;
		for(j=1;j<=tot && p[j]*i<=n;j++) {
			tag[p[j]*i]=true;
			if(i%p[j]==0) {
				mobius[p[j]*i]=0;
				break;
			}
			else mobius[p[j]*i]=mobius[i]*(-1);
		}
	}
	return;
}

int s[N]; // Ç°×ººÍ 

int main()
{
//	freopen("1.in","r",stdin);
	int i,j;
	int a,b,d,n;
	int T;
	LL ans;
	prime(N-1);
	for(i=1;i<=N-1;i++) 
		s[i]=s[i-1]+mobius[i];
	
	scanf("%d",&T);
	while(T--) {
		scanf("%d%d%d",&a,&b,&d);
		a=a/d,b=b/d;
		ans=0;
		n=min(a,b);
		for(i=1;i<=n;i=j+1) {
			j=min(n,min(a/(a/i),b/(b/i)));
			ans+=(LL)(a/i)*(b/i)*(s[j]-s[i-1]);
		}
		printf("%lld\n",ans);
	}
	return 0;
}

