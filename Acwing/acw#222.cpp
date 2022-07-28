#include<set>
#include<map>
#include<queue>
#include<stack>
#include<ctime>
#include<cmath>
#include<vector>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
typedef long long LL;
typedef unsigned long long ULL;
using namespace std;
/*
mt+sx=nt+sy (mod L)
(m-n)t+Lb=sy-sx;
*/
LL sx,sy,m,n,L;
LL exgcd(LL a,LL b,LL &x,LL &y)
{
	if(b==0) {
		x=1; y=0;
		return a;
	}
	LL z=exgcd(b,a%b,y,x);
	y=y-a/b*x;
	return z;
}
int main()
{
//	freopen("1.in","r",stdin);
	LL x,y,z;
	cin>>sx>>sy>>m>>n>>L;
	if(m<n) swap(n,m),swap(sx,sy);
	z=exgcd(m-n,L,x,y);
	if((sy-sx)%z) 
		printf("Impossible");
	else printf("%lld",(x*((sy-sx)/z)%(L/z)+(L/z))%(L/z));
	return 0;
}

