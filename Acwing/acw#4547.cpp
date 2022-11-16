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

const int N=1e7+5;

int n;
int a[N];

bool check(int x) 
{
	int cnt=0;
	for(int i=1;i<=n;i++) 
		if(a[i]==x) cnt++;
	return (cnt>=(n+1)/2);
}

int main()
{
//	freopen("1.in","r",stdin);
	srand(time(0));
	while(scanf("%d",&n)!=EOF) {
		for(int i=1;i<=n;i++) 
			scanf("%d",&a[i]);
		int x=(unsigned)rand()*rand()%n+1;
		while(!check(a[x])) x=(unsigned)rand()*rand()%n+1;
		printf("%d\n",a[x]);
	}
	return 0;
}

