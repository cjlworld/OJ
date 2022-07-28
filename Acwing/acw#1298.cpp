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
const int N=15;
// x = ai (mod bi)
// ami * bmi = 1 (mod bi)
LL A[N],B[N];
LL am[N],bm[N];
void exgcd(LL a,LL b,LL &x,LL &y)
{
	if(b==0) {
		x=1; y=0;
		return;
	}
	exgcd(b,a%b,y,x);
	y=y-a/b*x;
	return;
}
LL crt(int n)
{	
	int i;
	LL gm=1,res=0,y;
	for(i=1;i<=n;i++) gm*=B[i];
	for(i=1;i<=n;i++) {
		am[i]=gm/B[i];
		exgcd(am[i],B[i],bm[i],y);
		res=(res+am[i]*bm[i]%gm*A[i]%gm+gm)%gm;
	}
	return res;
}
int n;
int main()
{
//	freopen("1.in","r",stdin);
	scanf("%d",&n);
	for(int i=1;i<=n;i++) 
		scanf("%lld%lld",&B[i],&A[i]);
	cout<<crt(n);
	return 0;
}

