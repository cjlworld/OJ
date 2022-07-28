#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>

using namespace std;
typedef long long LL;
typedef unsigned long long ULL;

const int N=1024;
const LL MOD=1e9+7;

int T,n,m;
vector<int> nums;
int a[N];
LL f[N][N];

inline void add(LL &a,const LL &b) 
{ 
    a=(a+b)%MOD;
}

struct Bits
{
	LL c[N];
	inline int lowbit(int x) { return x&(-x); }
	void Update(int x,LL y)
	{
		for(;x<=n;x+=lowbit(x)) 
			add(c[x],y);
	}
	LL Sum(int x)
	{
		LL res=0;
		for(;x>=1;x-=lowbit(x)) 
			add(res,c[x]);
		return res;
	}
	void clear() { memset(c,0,sizeof c); }
}C;

int main()
{
//	freopen("1.in","r",stdin);
	int i,j;
	
	scanf("%d",&T);
	
	for(int testcase=1;testcase<=T;testcase++) {
		scanf("%d%d",&n,&m);
		nums.clear();
		for(i=1;i<=n;i++) {
			scanf("%d",&a[i]);
			nums.push_back(a[i]);
		}
		sort(nums.begin(),nums.end());
		nums.erase(unique(nums.begin(),nums.end()),nums.end());
		for(i=1;i<=n;i++) 
			a[i]=(upper_bound(nums.begin(),nums.end(),a[i])-nums.begin());
			
		C.clear();
		for(i=1;i<=n;i++) f[1][i]=1;
		for(j=2;j<=m;j++) {
			C.clear();
			for(i=1;i<=n;i++) {
				if(i>1) C.Update(a[i-1],f[j-1][i-1]);
				f[j][i]=C.Sum(a[i]-1);
			}
		}
		LL ans=0;
		for(i=1;i<=n;i++) 
			add(ans,f[m][i]);
		printf("Case #%d: %lld\n",testcase,ans);
	}
	return 0;
}

