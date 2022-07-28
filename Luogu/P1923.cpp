#include<cstdio>
#include<iostream>
#include<algorithm>
typedef long long LL;
typedef unsigned long long ULL;
using namespace std;
const int N=5e6+5;
int n,k;
int a[N];
int main()
{
//	freopen("1.in","r",stdin);
	scanf("%d%d",&n,&k);
	for(register int i=1;i<=n;i++) 
		scanf("%d",&a[i]);
	nth_element(a+1,a+k+1,a+n+1);
	cout<<a[k+1];
	return 0;
}

