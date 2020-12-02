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
typedef long double LD;

const int N=4e7+5; 

int n,m,type;

LL s[N];
int q[N],g[N];
LL b[N];

const LL BASE=1e17;
struct HP
{
	LL x,y;
	HP(LL num=0) { x=0,y=num; }
	inline HP operator+(const HP &b) const
	{
		HP c;
		c.x=x+b.x,c.y=y+b.y;
		c.x+=c.y/BASE,c.y%=BASE;
		return c;
	}
	inline void print()
	{
		if(x) printf("%lld%017lld",x,y);
		else printf("%lld",y);
	}
};

inline HP mul(const LL &a,const LL &b)
{
	HP c;
	c.x=(LD)a*b/BASE;
	c.y=((a*b-c.x*BASE)%BASE+BASE)%BASE;
	return c;
}


int main()
{
//	freopen("1.in","r",stdin);
	int i,j;
	LL x,y,z,p,l,r;
	
	scanf("%d%d",&n,&type);
	if(type==0) {
		for(i=1;i<=n;i++) {
			scanf("%lld",&x);
			s[i]=s[i-1]+x;
		}
	}
	else {
		const LL Mod=(1ll<<30);
		scanf("%lld%lld%lld%lld%lld%d",&x,&y,&z,&b[1],&b[2],&m);
		for(i=3;i<=n;i++)
			b[i]=(x*b[i-1]%Mod+y*b[i-2]%Mod+z)%Mod;
		for(i=1,j=1;i<=m;i++) {
			scanf("%lld%lld%lld",&p,&l,&r);
			for(;j<=p;j++)
				s[j]=s[j-1]+(b[j]%(r-l+1))+l;
		}
	}
	
	int hh,tt;
	q[hh=tt=0]=0;
	
	for(i=1;i<=n;i++) {
		while(hh<tt && 2*s[q[hh+1]]-s[g[q[hh+1]]]<=s[i]) hh++;
		g[i]=q[hh];
		while(hh<=tt && 2*s[i]-s[g[i]]<2*s[q[tt]]-s[g[q[tt]]]) tt--;
		q[++tt]=i;
	}
	
	HP ans;
	for(i=n;i>=1;i=g[i]) 
		ans=ans+mul(s[i]-s[g[i]],s[i]-s[g[i]]);
	
	ans.print();
	return 0;
}

