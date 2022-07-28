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

const int N=32;

LL exgcd(LL a,LL b,LL &x,LL &y)
{
	if(b==0) {
		x=1,y=0;
		return a;
	}
	LL z=exgcd(b,a%b,y,x);
	y-=a/b*x;
	return z;
}

LL Solve(LL a,LL b,LL c,LL &k0,LL &k)
{
	// ax+by=c;
	LL x,y,z,t;
	z=exgcd(a,b,x,y);
	if(c%z) return k0=k=-1;
	// x=k0+p*k;
	t=c/z,x*=t,y*=t,k=b/z;
	k0=(x%k+k)%k;
//	cout<<k0<<" "<<k<<endl;
	return 0;
}

int n;
LL a[N],m[N];

int main()
{
//	freopen("1.in","r",stdin);
	int i;
	LL x,y,z;
	
	cin>>n;
	for(i=1;i<=n;i++) cin>>a[i]>>m[i];

	LL k0=m[1],k=a[1];
	for(i=2;i<=n;i++) {
		z=Solve(k,a[i],m[i]-k0,x,y);
		if(z==-1) break;
		else k0+=k*x,k*=y;
//		
//		cout<<x<<" "<<y<<endl;
//		cout<<k0<<" "<<k<<endl;
	}
	if(i==n+1) printf("%lld\n",(k0%k+k)%k);
	else printf("-1\n");
	return 0;
}

