#include<set>
#include<cmath>
#include<cstdio>
#include<vector>
#include<cstring>
#include<iostream>
#include<cstdlib>
#include<algorithm>
#define LL long long
using namespace std;
const int N=50000+5;
const int SQ=1000;
LL a[N];
vector<LL> v[SQ];
int n;
struct block
{
	int siz,k;
	int L[SQ],R[SQ],F[N];
	int tag[SQ];
	inline void reset(int x)
	{
		int i,j;
		v[x].clear();
		for(i=L[x];i<=R[x];i++) 
			v[x].push_back(a[i]);
		sort(v[x].begin(),v[x].end());
		return;
	}
	inline void Build()
	{
		memset(L,0,sizeof L);
		memset(R,0,sizeof R);
		memset(F,0,sizeof F);
		memset(tag,0,sizeof tag);
		int i,j;
		siz=sqrt(n);
		k=n/siz;
		if(n%siz>0) k++;
		for(i=1;i<=k;i++) {
			L[i]=R[i-1]+1;
			R[i]=i*siz;
		}
		R[k]=n;
		for(i=1;i<=k;i++) {
			for(j=L[i];j<=R[i];j++) 
				F[j]=i;
			reset(i);
		}	
		return;
	}
	inline void modify(int x,int y,LL z)
	{
		int i,j;
		if(F[x]==F[y]) {
			for(i=x;i<=y;i++) 
				a[i]+=z;
			reset(F[x]);
			return;
		}	
		for(i=x;i<=R[F[x]];i++) 
			a[i]+=z;
		reset(F[x]);
		for(i=F[x]+1;i<=F[y]-1;i++) 
			tag[i]+=z;
		for(i=L[F[y]];i<=y;i++) 
			a[i]+=z;
		reset(F[y]);
		return;
	} 
	inline int query(int x,int y,LL z)
	{
		int i,j,tmp;
		int res=0;
		if(F[x]==F[y]) {
			for(i=x;i<=y;i++) 
				if(a[i]+tag[F[x]]<z) res++;
			return res;
		}
		for(i=x;i<=R[F[x]];i++) 
			if(a[i]+tag[F[x]]<z) res++;
		for(i=F[x]+1;i<=F[y]-1;i++) {
			tmp=z-tag[i];
			res+=lower_bound(v[i].begin(),v[i].end(),tmp)-v[i].begin();
		}
		for(i=L[F[y]];i<=y;i++) 
			if(a[i]+tag[F[y]]<z) res++;
		return res;
	}
}B;
int main()
{
//	freopen("1.in","r",stdin);
	int i,j;
	int x,y,opt;
	LL z;
	scanf("%d",&n);
	for(i=1;i<=n;i++) 
		scanf("%lld",&a[i]);
	B.Build();
	for(i=1;i<=n;i++) {
		scanf("%d%d%d%lld",&opt,&x,&y,&z);
		if(opt==0) 
			B.modify(x,y,z);
		else {
			printf("%d\n",B.query(x,y,z*z));
		}
	}
	return 0;
}

