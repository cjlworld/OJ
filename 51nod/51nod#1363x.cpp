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
typedef pair<LL,LL> PLL;

const LL MOD=1000000007;
const int N=1e7+5;

int p[N],tot;
bool tag[N];

void prime(int n)
{
	int i,j;
	for(i=2;i<=n;i++) {
		if(!tag[i]) p[++tot]=i;
		for(j=1;j<=tot && i*p[j]<=n;j++) {
			tag[i*p[j]]=true;
			if(i%p[j]==0) break;
		}
	}
}

void divide(LL n,vector<PLL>& v)
{
	v.clear();
	for(int i=1;p[i]*p[i]<=n;i++) {
		if(n%p[i]==0) {
			LL cnt=0;
			while(n%p[i]==0) n/=p[i],cnt++;
			v.push_back(PLL(p[i],cnt));
		}
	}
	if(n>1) v.push_back(PLL(n,1));
}

vector<PLL> fac;
LL ans;
void dfs(int u,LL cur,LL curphi)
{
	if(u==(int)fac.size()) {
//		printf("%lld %lld \n",cur,curphi);
		ans=(ans+cur*curphi)%MOD;
		return;
	}
	dfs(u+1,cur,curphi); // 不选 
	for(int i=1;i<=fac[u].second;i++) {
		cur*=fac[u].first;
		curphi*=(fac[u].first-(i==1));
		dfs(u+1,cur,curphi);
	}
}

int T;
LL n;

int main()
{
//	freopen("1.in","r",stdin);
	prime(N-1);
	scanf("%d",&T);
	while(T--) {
		scanf("%lld",&n);
		divide(n,fac);
		ans=1;
		dfs(0,1,1);
		ans=ans*n%MOD;
		if(ans&1) ans=(ans+MOD)/2%MOD;
		else ans/=2; 
		printf("%lld\n",ans);
	}
	return 0;
}
// idsum() 不要封装，拿出来还能推。
// mu * 1 = epsilon
// mu * id = phi
// 枚举约数求 phi 的快速方法。 
