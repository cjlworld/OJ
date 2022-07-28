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

int T;

int main()
{
//	freopen("1.in","r",stdin);
	LL a,b;
	scanf("%d",&T);
	while(T--) {
		LL i=0;
		cin>>a>>b;
		if(a>b) swap(a,b);
		while(a<b) a+=++i;
		if((a-b)%2==0) printf("%lld\n",i);
		else if((i+1)%2) printf("%lld\n",i+1);
		else printf("%lld\n",i+2);
	}
	return 0;
}

