#include<set>
#include<map>
#include<queue>
#include<stack>
#include<ctime>
#include<cmath>
#include<bitset>
#include<vector>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<complex>
#include<iostream>
#include<algorithm>

using namespace std;
typedef long long LL;
typedef unsigned long long ULL;

const int N=2e5+5;

int n,m,siz,bc;
int L[N],R[N],F[N];

struct Query
{
	int l,r;
	int id;
	inline bool operator<(const Query &t) const
	{
		if(F[l]!=F[t.l]) return l<t.l;
		else return r<t.r;
	}
}q[N];

LL a[N],d[N],tot;
LL ans[N],cur,cnt[N],s[N];

inline void Add(LL id,LL val,LL& res)
{
	cnt[id]++;
	res=max(res,cnt[id]*val);
}

int main()
{
//	freopen("1.in","r",stdin);
	int i,j;

	scanf("%d%d",&n,&m);
	
	// 来一个简单的离散化，用于不用比大小，这样足以。 
	map<LL,LL> mp;
	for(i=1;i<=n;i++) {
		scanf("%lld",&d[i]);
		if(mp.count(d[i])) a[i]=mp[d[i]];
		else a[i]=mp[d[i]]=++tot;
	}
	for(i=1;i<=m;i++) {
		scanf("%d%d",&q[i].l,&q[i].r);
		q[i].id=i;
	}
	
	// 像分块那样分块 
	siz=sqrt(n)+1;
	bc=(n/siz)+(n%siz>0);
	for(i=1;i<=bc;i++) {
		L[i]=R[i-1]+1;
		R[i]=i*siz;
	}
	R[bc]=n;
	for(i=1;i<=bc;i++) 
		for(j=L[i];j<=R[i];j++)
			F[j]=i;
	
	sort(q+1,q+m+1);
	
	int hh=1,tt=0,last=0;
	for(i=1;i<=m;i++) {
		if(F[q[i].l]==F[q[i].r]) { // 询问在一个块内则暴力扫描。 
			LL res=0; // 注意扫描的时候要换个桶。 
			for(j=q[i].l;j<=q[i].r;j++) 
				s[a[j]]++,res=max(res,s[a[j]]*d[j]);
			for(j=q[i].l;j<=q[i].r;j++) s[a[j]]--;
			ans[q[i].id]=res;
			continue;
		}
		
		// 访问到了新的块则重新初始化桶 
		if(F[q[i].l]!=last) {
			// 初始化桶 
			for(j=hh;j<=tt;j++) cnt[a[j]]=0;
			cur=0;
			// 改变指针。 
			hh=R[F[q[i].l]]+1,tt=R[F[q[i].l]];
			last=F[q[i].l]; // 标记最后一个块。 
		}
		// 在处理一个块内的问题时，hh 是不变的;
		// [hh, tt] 的部分是当前块内的询问共用的 （已经把 r 在区间内的去掉了） 
		// 这部分的贡献加到 cur 里。 
		while(tt<q[i].r) ++tt,Add(a[tt],d[tt],cur);
		
		// [q[i].l, hh) 的部分不是共用的，一用完就得删掉。  
		LL res=cur;
		for(j=q[i].l;j<hh;j++) Add(a[j],d[j],res);
		for(j=q[i].l;j<hh;j++) cnt[a[j]]--;
		ans[q[i].id]=res;
	}
	
	for(i=1;i<=m;i++) 
		printf("%lld\n",ans[i]);
	return 0;
}

