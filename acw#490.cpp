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

const int N=2e5+5;
int a[N];
int n;
int main()
{
//	freopen("1.in","r",stdin);
	int i,cnt=0;
	cin>>n;
	for(i=1;i<=n;i++) 
		scanf("%d",&a[i]);
	sort(a+1,a+n+1);
	a[n+1]=-1;
	for(i=1;i<=n;i++) {
		if(a[i+1]==a[i]) cnt++;
		else {
			printf("%d %d\n",a[i],cnt+1);
			cnt=0;
		}
	}
	return 0;
}

