//http://noip.ybtoj.com.cn/contest/59/problem/1
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
#include<iostream>
#include<algorithm>

using namespace std;
typedef long long LL;
typedef unsigned long long ULL;

const int S=(1<<17);
LL n;
LL f[S];

int main()
{
//	freopen("1.in","r",stdin);
	int i,j;
	scanf("%lld",&n);
	for(i=1;i<(1<<n);i++) {
		scanf("%lld",&f[i]);
		for(j=(i-1)&i;j;j=(j-1)&i) 
			f[i]=max(f[i],f[j]+f[i-j]);
	}
	cout<<f[(1<<n)-1]<<endl;
	return 0;
}

