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
	if(a==0) return (b/c)*(n+1);
	if(a>=c || b>=c) return f(a%c,b%c,c,n)+n*(n+1)/2*(a/c)+(n+1)*(b/c);
	LL m=(a*n+b)/c;
	return n*m-f(c,c-b-1,a,m-1);
}

int main()
{
//	freopen("1.in","r",stdin);
	LL a,b,c;
	cin>>a>>b>>c;	
	if(b<a) swap(a,b);
	cout<<f(b-a,c+b,b,c/a)-(0+c/a)*(c/a+1)/2;
	return 0;
}

