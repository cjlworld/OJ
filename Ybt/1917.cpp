#include<cstdio>
#include<iostream>
#include<algorithm>
#define LL long long
using namespace std;
const int N=20000+5;
bool f[N];
int a[N];
int m,n;
int main()
{
//	freopen("1.in","r",stdin);
	scanf("%d%d",&m,&n);
	int i,j;
	int x,y,z;
	for(i=1;i<=n;i++) 
		scanf("%d",&a[i]);
	sort(a+1,a+n+1);
	f[0]=true;
	for(j=1;j<=n;j++) {
		for(i=m;i>=a[j];i--) {
			f[i]=(f[i-a[j]]) ? true : f[i];
		}
	}
	for(i=m;i>=0;i--) 
		if(f[i]) {
			printf("%d",m-i);
			return 0;
		}
	return 0;
}

