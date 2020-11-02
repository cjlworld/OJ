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

const int N=2e5+5;
const LL INF=1e17+5;

int n,m;
LL st;
struct Stone
{
	LL w,v;
}a[N];
LL c[N],s[N];

vector<LL> nums;
LL ans=INF;
int l[N],r[N];
inline LL mabs(LL x)
{
	if(x<0) return -x;
	else return x;
}

LL calc(LL pos)
{
	LL W=nums[pos];
	int i;
	memset(c,0,sizeof c);
	memset(s,0,sizeof s);
	for(i=1;i<=n;i++) {
		c[i]=c[i-1]+(a[i].w>=W);
		s[i]=s[i-1]+(a[i].w>=W)*a[i].v;
	}
	LL sum=0;
	for(i=1;i<=m;i++) 
		sum+=(c[r[i]]-c[l[i]-1])*(s[r[i]]-s[l[i]-1]);
	return mabs(sum-st);
}

int main()
{
//	freopen("1.in","r",stdin);
	int i;
	scanf("%d%d%lld",&n,&m,&st);
	for(i=1;i<=n;i++) {
		scanf("%lld%lld",&a[i].w,&a[i].v);
		nums.push_back(a[i].w);
	}
	sort(nums.begin(),nums.end());
	nums.erase(unique(nums.begin(),nums.end()),nums.end());
	for(i=1;i<=m;i++) 
		scanf("%d%d",&l[i],&r[i]);
	ans=st;
	int L=0,R=nums.size()-1,midl,midr;
	ans=min(ans,calc(L)),ans=min(ans,calc(R));
	while(L+1<R) {
		if(R-L<=3) {
			for(i=L;i<=R;i++) 
				ans=min(ans,calc(i));
			break;
		}
		midl=(L+R)>>1,midr=midl+1;
		if(calc(midl)<calc(midr)) R=midr;
		else L=midl;
 	}
	cout<<ans<<endl;
	return 0;
}
