#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
typedef unsigned long long ULL;
using namespace std;
const int N=1e6+5;
char a[N];
int n;
int sa[N];
inline bool rule(int p,int q)
{
	for(int i=0;p+i<=n&&q+i<=n;i++) {
		if(a[p+i]!=a[q+i])
			return a[p+i]<a[q+i];
	}
	return p>q;
}
int main()
{
//	freopen("1.in","r",stdin);
	int i;
	scanf("%s",a+1);
	n=strlen(a+1);
	for(i=1;i<=n;i++) sa[i]=i;
	sort(sa+1,sa+n+1,rule);
	for(i=1;i<=n;i++) 
		printf("%d ",sa[i]);
	return 0;
}

