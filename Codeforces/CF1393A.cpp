#include<set>
#include<map>
#include<ctime>
#include<queue>
#include<stack>
#include<vector>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
#define rint register int
typedef long long LL;
typedef unsigned long long ULL;
using namespace std;
int T;
int n;
int main()
{
//	freopen("1.in","r",stdin);
	scanf("%d",&T);
	while(T--) {
		scanf("%d",&n);
		if(n==1) printf("1\n");
		else if(n==2) printf("2\n");
		else printf("%d\n",n/2+1);
	}
	return 0;
}
