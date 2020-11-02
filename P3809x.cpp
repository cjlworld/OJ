#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
typedef long long LL;
typedef unsigned long long ULL;
using namespace std;
const int N=1e6+5;
const ULL P=131;
char a[N];
int n;
int sa[N];
ULL h[N],POW[N];
inline ULL get(int l,int r)
{
	return h[r]-h[l-1]*POW[r-l+1];
}
inline bool rule(int p,int q)
{
	int L=-1,R=min(n-p,n-q)+1,mid;
	while(L+1<R) {
		mid=(L+R)>>1;
		if(get(p,p+mid)==get(q,q+mid)) L=mid;
		else R=mid;
	}
	p=p+L+1; q=q+L+1;
	if(p==n+1||q==n+1) return (p==n+1);
	else return a[p]<a[q];
}
int main()
{
//	freopen("1.in","r",stdin);
	int i;
	scanf("%s",a+1);
	n=strlen(a+1);
	POW[0]=1;
	for(i=1;i<=n;i++) {
		sa[i]=i;
		h[i]=h[i-1]*P+a[i];
		POW[i]=POW[i-1]*P;
	}
	sort(sa+1,sa+n+1,rule);
	for(i=1;i<=n;i++) 
		printf("%d ",sa[i]);
	return 0;
}

