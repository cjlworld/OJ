#include<cmath>
#include<cstdio>
#include<cstring>
#include<iostream>
#define LL long long
using namespace std;
const int N=1e5+5;
const int SQ=1000;
int n,m;
int a[N];
struct block
{
	int siz,k;
	int L[SQ],R[SQ],F[N];
	int sum[SQ],tag[SQ];
	inline void Build()
	{
		memset(L,0,sizeof L);
		memset(R,0,sizeof R);
		memset(F,0,sizeof F);
		memset(sum,0,sizeof sum);
		int i,j;
		siz=sqrt(n);
		k=n/siz;
		if(n%k>0) k++;
		for(i=1;i<=k;i++) {
			L[i]=R[i-1]+1;
			R[i]=siz*i;
		}
		R[k]=n;
		for(i=1;i<=k;i++) 
			for(j=L[i];j<=R[i];j++) 
				F[j]=i;
		return;
	}
	inline void modify(int x,int y)
	{
		int i,j;
		if(F[x]==F[y]) {
			for(i=x;i<=y;i++) {
				if(a[i]) sum[F[x]]--;
				else sum[F[x]]++;
				a[i]=!a[i];
			}
			return;
		}
		for(i=x;i<=R[F[x]];i++) {
			if(a[i]) sum[F[x]]--;
			else sum[F[x]]++;
			a[i]=!a[i];
		}
		for(i=F[x]+1;i<=F[y]-1;i++) 
			tag[i]=!tag[i];
		for(i=L[F[y]];i<=y;i++) {
			if(a[i]) sum[F[y]]--;
			else sum[F[y]]++;
			a[i]=!a[i];
		}
		return;
	}
	inline int query(int x,int y)
	{
		int i,j;
		int res=0;
		if(F[x]==F[y]) {
			for(i=x;i<=y;i++) 
				res+=a[i]^tag[F[x]];
			return res;
		}
		for(i=x;i<=R[F[x]];i++) 
			res+=a[i]^tag[F[x]];
		for(i=F[x]+1;i<=F[y]-1;i++) 
			res+=(tag[i]) ? (R[i]-L[i]+1-sum[i]) : sum[i];
		for(i=L[F[y]];i<=y;i++) 
			res+=a[i]^tag[F[y]];
		return res;
	}
}B;
int main()
{
//	freopen("1.in","r",stdin);
	int i,j;
	int x,y,z,opt;
	scanf("%d%d",&n,&m);
	B.Build();
	while(m--) {
		scanf("%d%d%d",&opt,&x,&y);
		if(opt==0) B.modify(x,y);
		else printf("%d\n",B.query(x,y));
	}
	return 0;
}

