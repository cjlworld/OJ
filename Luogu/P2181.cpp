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

LL n,ans;

int main()
{
	cin>>n;
	for(LL i=0;i<=n-2;i++) 
		ans+=n*i*(n-2-i)/2;
	cout<<ans/2<<endl;
	return 0;
}

