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

int main()
{
//	freopen("1.in","r",stdin);
	LL p,q;
	cin>>p>>q;
	cout<<f(q,0,p,p/2)+f(p,0,q,q/2);
	return 0;
}

