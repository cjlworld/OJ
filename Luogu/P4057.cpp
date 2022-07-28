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

LL gcd(LL a,LL b)
{
	if(b==0) return a;
	else return gcd(b,a%b);
}

LL lcm(LL a,LL b)
{
	return a/gcd(a,b)*b;
}

int main()
{
//	freopen("1.in","r",stdin);
	LL a,b,c;
	cin>>a>>b>>c;
	cout<<lcm(lcm(a,b),c);
	return 0;
}

