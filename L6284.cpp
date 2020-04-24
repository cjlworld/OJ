#include<cmath>
#include<cstdio>
#include<cstring>
#include<iostream>
#define LL long long
using namespace std;
const int N=1e5+5;
const int SQ=1000;
const int INF=(-1u)>>1;
int n;
int a[N];
struct block
{
	int siz,k;
	int L[SQ],R[SQ],F[N];
	int tag[SQ];
	inline void Build()
	{
		memset(L,0,sizeof L);
		memset(R,0,sizeof R);
		memset(F,0,sizeof F);
		fill(tag,tag+SQ-5,-INF);
		siz=sqrt(n);
		k=n/siz+(n%siz>0);
		int i,j;
		for(i=1;i<=k;i++) {
			L[i]=R[i-1]+1;
			R[i]=i*siz;
		}
		R[k]=n;
		for(i=1;i<=k;i++) {
			for(j=L[i];j<=R[i];j++) 
				F[j]=i;
		} 
		return; 
	}
	inline void push_down(int now)
	{
		for(int i=L[now];i<=R[now];i++) 
			a[i]=tag[now];
		tag[now]=-INF;
		return;
	}
	inline int cntblo(int x,int y,int z)
	{
		int i,j;
		int res=0;
		if(tag[F[x]]==z) return y-x+1;
		if(tag[F[x]]==-INF) {
			for(i=x;i<=y;i++) {
				if(a[i]==z) res++;
				else a[i]=z;
			}
			return res;
		}
		else {
			push_down(F[x]);
			for(i=x;i<=y;i++) 
				a[i]=z;
			return 0;
		}
	}
	inline int modify(int x,int y,int z)
	{
		int res=0;
		int i,j;
		if(F[x]==F[y]) 
			return cntblo(x,y,z);
		res+=cntblo(x,R[F[x]],z);
		for(i=F[x]+1;i<=F[y]-1;i++) {
			if(tag[i]==z) res+=R[i]-L[i]+1;
			else if(tag[i]==-INF) {
				for(j=L[i];j<=R[i];j++) 
					if(a[j]==z) 
						res++;
			} 
			tag[i]=z;
		}
		res+=cntblo(L[F[y]],y,z);
		return res;
	}
}B;
int main()
{
//	freopen("1.in","r",stdin);
	int i,j;
	int opt,x,y,z;
	scanf("%d",&n);
	for(i=1;i<=n;i++) 
		scanf("%d",&a[i]);
	B.Build();
	for(i=1;i<=n;i++) {
		scanf("%d%d%d",&x,&y,&z);
		printf("%d\n",B.modify(x,y,z));
	}
	return 0;
}

