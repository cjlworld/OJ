#include<set>
#include<map>
#include<queue>
#include<stack>
#include<ctime>
#include<cmath>
#include<bitset>
#include<vector>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>

using namespace std;
typedef long long LL;
typedef unsigned long long ULL;

LL gcd(LL a,LL b)
{
	if(b==0) return a;
	else return gcd(b,a%b);
}
LL g;
int n;
int main()
{
//	freopen("1.in","r",stdin);
	LL x;
	scanf("%d",&n);
	for(int i=1;i<=n;i++) {
		scanf("%lld",&x);
		g=gcd(g,x);
	}
	cout<<((g<0) ? -g : g)<<endl;
	return 0;
}


