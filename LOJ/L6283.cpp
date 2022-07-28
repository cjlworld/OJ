#include<set>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<iostream>
#define LL long long
using namespace std;
const int N=1e5+5;
const LL MOD=10007;
const int SQ=1000;
LL a[N];
int n;
struct block
{
	int siz,k;
	int L[SQ],R[SQ],F[N];
	LL atag[SQ],mtag[SQ];
	inline void Build()
	{
		memset(L,0,sizeof L);
		memset(R,0,sizeof R);
		memset(F,0,sizeof F);
		memset(atag,0,sizeof atag);
		fill(mtag,mtag+SQ-5,1ll);
		int i,j;
		siz=sqrt(n);
		k=n/siz+(n%siz>0);
		for(i=1;i<=k;i++) {
			L[i]=R[i-1]+1;
			R[i]=i*siz;
		}
		R[k]=n;
		for(i=1;i<=k;i++) 
			for(j=L[i];j<=R[i];j++) 
				F[j]=i;
		return;
	}
	inline void push_down(int now)
	{
		int i,j;
		for(i=L[now];i<=R[now];i++)
			a[i]=(a[i]*mtag[now]+atag[now])%MOD;
		mtag[now]=1;
		atag[now]=0;
		return;
	}
	inline void modify(int x,int y,LL z) //first ? second ?
	{
		int i,j;
		if(F[x]==F[y]) {
			push_down(F[x]);
			for(i=x;i<=y;i++) 
				a[i]=(a[i]+z)%MOD;
			return;
		}
		push_down(F[x]);
		for(i=x;i<=R[F[x]];i++)
			a[i]=(a[i]+z)%MOD;
		for(i=F[x]+1;i<=F[y]-1;i++) 
			atag[i]=(atag[i]+z)%MOD;
		push_down(F[y]);
		for(i=L[F[y]];i<=y;i++)
			a[i]=(a[i]+z)%MOD;
		return;
	}
	inline void multiply(int x,int y,LL z)
	{
		int i,j;
		if(F[x]==F[y]) {
			push_down(F[x]);
			for(i=x;i<=y;i++) 
				a[i]=(a[i]*z)%MOD;
			return;
		}
		push_down(F[x]);
		for(i=x;i<=R[F[x]];i++) 
			a[i]=(a[i]*z)%MOD;
		for(i=F[x]+1;i<=F[y]-1;i++) {
			mtag[i]=(mtag[i]*z)%MOD;
			atag[i]=(atag[i]*z)%MOD;
		}
		push_down(F[y]);
		for(i=L[F[y]];i<=y;i++) 
			a[i]=(a[i]*z)%MOD;
		return;
	}
	inline LL want(int x)
	{
		return (a[x]*mtag[F[x]]+atag[F[x]])%MOD;
	}
}B;
int main()
{
//	freopen("1.in","r",stdin);
	int i,j;
	int opt,x,y;
	LL z;
	scanf("%d",&n);
	for(i=1;i<=n;i++) {
		scanf("%lld",&a[i]);
		a[i]=a[i]%MOD;
	}
	B.Build();
	for(i=1;i<=n;i++) {
		scanf("%d%d%d%lld",&opt,&x,&y,&z);
		if(opt==0) B.modify(x,y,z);
		else if(opt==1) B.multiply(x,y,z);
		else printf("%lld\n",B.want(y));
	}
	return 0;
}

