#include<cmath>
#include<cstdio>
#include<iostream>
#include<algorithm>
#define LL long long
using namespace std;
const int N=5e4+5;
int n,m,k;
LL a[N],c[N];
LL ans;
int siz;
struct quiz
{
	int l,r;
	int o;
	LL ans;
}q[N];
inline bool cmp(const quiz &a,const quiz &b)
{
	if(a.l/siz!=b.l/siz)
		return a.l<b.l;
	else return a.r<b.r;
}
inline bool rule(const quiz &a,const quiz &b)
{
	return a.o<b.o;
}
inline void Add(int pos)
{
	ans+=2ll*c[a[pos]]+1;
	c[a[pos]]++;
	return;
}
inline void Sub(int pos)
{
	ans-=2ll*c[a[pos]]-1;
	c[a[pos]]--;
	return;
}
int main()
{
//	freopen("1.in","r",stdin);
	int i,j;
	int x,y,z;
	scanf("%d%d%d",&n,&m,&k);
	siz=sqrt(n);
	for(i=1;i<=n;i++) 
		scanf("%lld",&a[i]);
	for(i=1;i<=m;i++) {
		scanf("%d%d",&q[i].l,&q[i].r);
		q[i].o=i;
	}
	sort(q+1,q+m+1,cmp);
	int head=1,tail=0;
	for(i=1;i<=m;i++) {
		while(head>q[i].l) Add(--head);
		while(tail<q[i].r) Add(++tail);
		while(head<q[i].l) Sub(head++);
		while(tail>q[i].r) Sub(tail--);
		q[i].ans=ans;
	}
	sort(q+1,q+m+1,rule);
	for(i=1;i<=m;i++) 
		printf("%lld\n",q[i].ans);
	return 0;
}

