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
typedef long double LD;
typedef unsigned long long ULL;

const LL M=29;

int n;
map<int,LL> H;

int main()
{
//	freopen("1.in","r",stdin);
	
	while(scanf("%d",&n),n) {
		if(H.count(n)) {
			printf("%lld\n",H[n]);
			continue;
		}
		for(LL i=1;i<(1ll<<M);i++) {
			LL x=0;
			for(LL j=M-1;j>=0;j--) 
				x=x*10+((i>>j)&1);
			if(x%n==0) {
				printf("%lld\n",x);
				H[n]=x;
				break;
			}
		}
	}
	
	return 0;
}

