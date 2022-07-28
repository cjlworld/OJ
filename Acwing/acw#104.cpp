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

const int N=1e5+5;
int n;
int a[N];
int main()
{
	int i,t;
	LL ans=0;
	cin>>n;
	for(i=1;i<=n;i++) 
		scanf("%d",&a[i]);
	sort(a+1,a+n+1);
	t=a[(n+1)/2];
	for(i=1;i<=n;i++)
		ans+=(LL)abs(a[i]-t);
	cout<<ans;
	return 0;
}

