#include<set>
#include<map>
#include<queue>
#include<stack>
#include<cmath>
#include<ctime>
#include<bitset>
#include<vector>
#include<cstdio>
#include<complex>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>

using namespace std;
typedef long long LL;

LL idsum(LL x) { return x*(x+1)/2; }
LL f(LL n)
{
	LL res=0;
	for(LL i=1,j,t;i<=n;i=j+1) {
		t=n/i; j=n/t;
		res+=(idsum(j)-idsum(i-1))*t;
	}
	return res;
}

int main()
{
//	freopen("1.in","r",stdin);
	LL x,y;
	cin>>x>>y;
	cout<<f(y)-f(x-1);
	return 0;
}

