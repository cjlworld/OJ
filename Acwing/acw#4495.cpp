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
typedef pair<int,int> PII;
typedef unsigned long long ULL;

const int N=1e5+5;

int n,m;
int a[N];

int main()
{
//	freopen("1.in","r",stdin);
	
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) 
		scanf("%d",&a[i]);
	
	sort(a+1,a+n+1);
	
	for(int i=1,j=1,base=0;i<=m;i++) {
		while(j<=n && a[j]-base==0) j++;
		if(j>n) {
			puts("0");
			continue;
		}
		printf("%d\n",a[j]-base);  
		base+=a[j]-base;
	}
	
	return 0;
}

