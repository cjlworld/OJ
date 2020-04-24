#include<cmath>
#include<cstdio>
#include<cstring>
#include<iostream>
#define LL long long
using namespace std;
const int N=50000+5;
const int SQ=1000;
LL a[N];
int n;
struct block
{
	int siz,k;
	int L[SQ],R[SQ],F[N];
	LL tag[SQ],sum[SQ];
	inline void Build()
	{
		memset(L,0,sizeof L);
		memset(R,0,sizeof R);
		memset(F,0,sizeof F);
		memset(tag,0,sizeof tag);
		memset(sum,0,sizeof sum);
		int i,j;
		siz=sqrt(n);
		k=n/siz;
		if(n%siz>0) k++;
		for(i=1;i<=k;i++) 
			R[i]=i*siz,L[i]=R[i-1]+1;
		R[k]=n;
		for(i=1;i<=k;i++) 
			for(j=L[i];j<=R[i];j++) {
				F[j]=i;
				sum[i]+=a[j];
			}				
		return;
	}
	inline void modify(int x,int y,LL z) //from x to y ,+z;
	{
		int i,j;
		if(F[x]==F[y]) {
			sum[F[x]]+=(y-x+1)*z;
			for(i=x;i<=y;i++) 
				a[i]+=z;
			return;
		}
		sum[F[x]]+=(R[F[x]]-x+1)*z;
		for(i=x;i<=R[F[x]];i++) 
			a[i]+=z;
		for(i=F[x]+1;i<=F[y]-1;i++) 
			tag[i]+=z;
		sum[F[y]]+=(y-L[F[y]]+1)*z;
		for(i=L[F[y]];i<=y;i++) 
			a[i]+=z;
		return;
	}
	inline void edit(int x,LL y) //..x,+y
	{
		a[x]+=y;
		sum[F[x]]+=y;
		return;
	}
	inline LL want(int x)
	{
		return (a[x]+tag[F[x]]);
	}
	inline LL query(int x,int y) //sum from x to y
	{
		int i,j;
		LL res=0;
		if(F[x]==F[y]) {
			for(i=x;i<=y;i++)
				res+=a[i];
			res+=tag[F[x]]*(y-x+1);
			return res;
		}
		res+=(R[F[x]]-x+1)*tag[F[x]];
		for(i=x;i<=R[F[x]];i++) 
			res+=a[i];
		for(i=F[x]+1;i<=F[y]-1;i++) 
			res+=sum[i]+tag[i]*(R[i]-L[i]+1);
		res+=(y-L[F[y]]+1)*tag[F[y]];
		for(i=L[F[y]];i<=y;i++) 
			res+=a[i];
		return res;
	}
};
block B;
int main()
{
//	freopen("1.in","r",stdin);
	int i,j;
	int x,y,z,opt;
	scanf("%d",&n);
	for(i=1;i<=n;i++) 
		scanf("%lld",&a[i]);
	B.Build();
	for(i=1;i<=n;i++) {
		scanf("%d%d%d%d",&opt,&x,&y,&z);
		if(opt==0) B.modify(x,y,z);
		else printf("%lld\n",B.query(x,y)%(z+1));
	}
	return 0;
}

