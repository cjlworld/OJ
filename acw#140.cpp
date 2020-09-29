#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>

using namespace std;
typedef long long LL;
typedef unsigned long long ULL;

const int N=3e5+5;
const ULL P=131;

char a[N];
int n;
int sa[N],Height[N];
ULL h[N],POW[N];

inline ULL get(int l,int r)
{
	return h[r]-h[l-1]*POW[r-l+1];
}
//int lcp(int p,int q)
//{
//	int base=1,res=0;
//	while(base>0) {
//		if(p+res+base-1>n||q+res+base-1>n) base>>=1;
//		else if(get(p,p+res+base-1)==get(q,q+res+base-1)) 
//			res+=base,base<<=1;
//		else base>>=1;
//	}
//	return res;
//}
int lcp(int p,int q)
{
	int L=-1,R=min(n-p,n-q)+1,mid;
	while(L+1<R) {
		mid=(L+R)>>1;
		if(get(p,p+mid)==get(q,q+mid)) L=mid;
		else R=mid;
	}
	return L+1;
}
inline bool rule(int p,int q)
{
	int k=lcp(p,q);
	p+=k,q+=k;
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
	for(i=2;i<=n;i++) Height[i]=lcp(sa[i],sa[i-1]);
	for(i=1;i<=n;i++) printf("%d ",sa[i]-1);
	printf("\n");
	for(i=1;i<=n;i++) printf("%d ",Height[i]);
	return 0;
}

