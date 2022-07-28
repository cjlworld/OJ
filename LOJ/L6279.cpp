#include<set>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<iostream>
#define LL long long
using namespace std;
const int N=1e5+5;
const int SQ=1000+5;
const LL INF=1e12;
LL a[N];
multiset<LL> S[SQ];
int n;
struct block
{
	int siz,k;
	int L[SQ],R[SQ],F[N];
	LL tag[SQ]; //+ tag
	inline void Build()
	{
		memset(L,0,sizeof L);
		memset(R,0,sizeof R);
		memset(F,0,sizeof F);
		memset(tag,0,sizeof tag);
		int i,j;
		siz=sqrt(n);
		k=n/siz;
		if(n%k>0) k++;
		for(i=1;i<=k;i++) {
			L[i]=R[i-1]+1;
			R[i]=i*siz;
		}
		R[k]=n;
		for(i=1;i<=k;i++) {
			for(j=L[i];j<=R[i];j++) {
				S[i].insert(a[j]);
				F[j]=i;
			}
		}
		return;
	}
	inline void modify(int x,int y,LL z)
	{
		int i,j;
		if(F[x]==F[y]) {
			for(i=x;i<=y;i++) {
				S[F[x]].erase(S[F[x]].find(a[i]));
				a[i]+=z;
				S[F[x]].insert(a[i]);
			}
			return;
		}
		for(i=x;i<=R[F[x]];i++) {
			S[F[x]].erase(S[F[x]].find(a[i]));
			a[i]+=z;
			S[F[x]].insert(a[i]);
		}
		for(i=F[x]+1;i<=F[y]-1;i++) 
			tag[i]+=z;
		for(i=L[F[y]];i<=y;i++) {
			S[F[y]].erase(S[F[y]].find(a[i]));
			a[i]+=z;
			S[F[y]].insert(a[i]);
		}
		return;
	}
	inline LL query(int x,int y,LL z)
	{
		int i,j;
		LL res=-INF;
		LL tmp;
		if(F[x]==F[y]) {
			for(i=x;i<=y;i++) 
				if(a[i]+tag[F[x]]<z&&a[i]+tag[F[x]]>res) 
					res=a[i]+tag[F[x]];
			if(res==-INF) 
				return -1;
			else return res;
		}
		for(i=x;i<=R[F[x]];i++) {
			if(a[i]+tag[F[x]]<z&&a[i]+tag[F[x]]>res) 
				res=a[i]+tag[F[x]];
		}
		for(i=F[x]+1;i<=F[y]-1;i++) {
			tmp=z-tag[i];
			if((*S[i].begin())>tmp) continue;
			multiset<LL>::iterator it=S[i].lower_bound(tmp);
			it--;
 			if(*it>=tmp) continue;
			res=max(res,*it+tag[i]);
			res=max(res,*S[i].begin()+tag[i]);
		}
		for(i=L[F[y]];i<=y;i++) {
			if(a[i]+tag[F[y]]<z&&a[i]+tag[F[y]]>res) 
				res=a[i]+tag[F[y]];
		}
		if(res==-INF) return -1;
		else return res;
	}
}B;
int main()
{
	int i,j;
	int opt,x,y;
	LL z;
	scanf("%d",&n);
	for(i=1;i<=n;i++) 
		scanf("%lld",&a[i]);
	B.Build();
	for(i=1;i<=n;i++) {
		scanf("%d%d%d%lld",&opt,&x,&y,&z);
		if(opt==0) B.modify(x,y,z);
		else printf("%lld\n",(LL)B.query(x,y,z));
	}
	return 0;
}

