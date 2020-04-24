#include<iostream>
#include<cstdio>
#include<algorithm>
#define LL long long
using namespace std;
int n;
const int N=50000+5;
struct range
{
	int l,r;
};
range a[N];
inline bool cmp(const range &a,const range &b)
{
	if(a.l!=b.l)
		return a.l<b.l;
	return a.r<b.r;
}
int main()
{
//	freopen("1.in","r",stdin);
	scanf("%d",&n);
	for(int i=1;i<=n;i++) 
		scanf("%d%d",&a[i].l,&a[i].r);
	sort(a+1,a+n+1,cmp);
	int Maxr=0;
	for(int i=1;i<=n-1;i++) 
	{
		Maxr=max(Maxr,a[i].r);
		if(Maxr>=a[i+1].l) { continue; }
		puts("no");
		return 0;
	}
	Maxr=max(Maxr,a[n].r);
	printf("%d %d",a[1].l,Maxr);
	return 0;
}

