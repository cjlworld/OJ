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
#include<complex>
#include<iostream>
#include<algorithm>

using namespace std;
typedef long long LL;
typedef unsigned long long ULL;

LL f(LL a,LL b,LL c,LL n)
{
	if(a==0) return (n+1)*(b/c);
	if(a>=c || b>=c) return f(a%c,b%c,c,n)+n*(n+1)/2*(a/c)+(n+1)*(b/c);
	LL m=(a*n+b)/c;
	return n*m-f(c,c-b-1,a,m-1);
}

LL gcd(LL a,LL b)
{
	if(b==0) return a;
	else return gcd(b,a%b);
}

int main()
{
//	freopen("1.in","r",stdin);
	LL a,b,c,d,z;
	while(cin>>a>>b>>c>>d) {
		z=d/gcd(c,d);
		LL L=0,R=1e10,mid;
		while(L+1<R) {
			mid=(L+R)>>1;
			if(f(a,0,b,mid)+(mid/z)==f(c,0,d,mid)) L=mid;
			else R=mid;
		}
		LL p=ceil((double)a*R/b);
		while(p*b<=a*R) p++;
		while(p*d>=c*R) p--;
		cout<<p<<"/"<<R<<endl;
	}
	return 0;
}

