#include<cmath>
#include<cstdio>
#include<iostream>
typedef long long LL;
typedef unsigned long long ULL;
using namespace std;
const int N=256;
int a[N];
int n;
int main()
{
//	freopen("1.in","r",stdin);
	int i;
	cin>>n;
	for(i=1;i<=n+1;i++) 
		cin>>a[i];
	for(i=1;i<=n;i++) {
		if(a[i]==0) continue;
		if(i==1&&a[i]>0);
		else printf((a[i]<0) ? "-" : "+");
		
		if(a[i]==1||a[i]==-1);
		else printf("%d",abs(a[i]));
		
		printf("x");
		if(n-i+1==1);
		else printf("^%d",n-i+1); 
	}
	if(a[n+1]!=0) {
		printf((a[n+1]>0) ? "+" : "-");
		printf("%d",abs(a[n+1]));
	}
	return 0;
}


