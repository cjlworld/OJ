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
LL a,b,p;
LL gmul(LL x,LL k,LL mod)
{
	LL res=0;
	while(k) {
		if(k&1) res=(res+x)%mod;
		x=(x+x)%mod; k>>=1;
	}
	return res;
}
int main()
{
	cin>>a>>b>>p;
	cout<<gmul(a,b,p);
	return 0;
}

