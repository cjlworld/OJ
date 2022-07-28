#include<cmath>
#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>

using namespace std;
typedef long long LL;

LL gcd(LL a,LL b)
{
	if(b==0) return a;
	else return gcd(b,a%b);
}

int main()
{
//	freopen("1.in","r",stdin);
	LL a,b;
	cin>>a>>b;
	cout<<gcd(a,b)<<endl;
	return 0;
}

