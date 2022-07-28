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
	
	// ��һ���򵥵���ɢ�������ڲ��ñȴ�С���������ԡ� 
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
	
	// ��ֿ������ֿ� 
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
		if(F[q[i].l]==F[q[i].r]) { // ѯ����һ����������ɨ�衣 
			LL res=0; // ע��ɨ���ʱ��Ҫ����Ͱ�� 
			for(j=q[i].l;j<=q[i].r;j++) 
				s[a[j]]++,res=max(res,s[a[j]]*d[j]);
			for(j=q[i].l;j<=q[i].r;j++) s[a[j]]--;
			ans[q[i].id]=res;
			continue;
		}
		
		// ���ʵ����µĿ������³�ʼ��Ͱ 
		if(F[q[i].l]!=last) {
			// ��ʼ��Ͱ 
			for(j=hh;j<=tt;j++) cnt[a[j]]=0;
			cur=0;
			// �ı�ָ�롣 
			hh=R[F[q[i].l]]+1,tt=R[F[q[i].l]];
			last=F[q[i].l]; // ������һ���顣 
		}
		// �ڴ���һ�����ڵ�����ʱ��hh �ǲ����;
		// [hh, tt] �Ĳ����ǵ�ǰ���ڵ�ѯ�ʹ��õ� ���Ѿ��� r �������ڵ�ȥ���ˣ� 
		// �ⲿ�ֵĹ��׼ӵ� cur � 
		while(tt<q[i].r) ++tt,Add(a[tt],d[tt],cur);
		
		// [q[i].l, hh) �Ĳ��ֲ��ǹ��õģ�һ����͵�ɾ����  
		LL res=cur;
		for(j=q[i].l;j<hh;j++) Add(a[j],d[j],res);
		for(j=q[i].l;j<hh;j++) cnt[a[j]]--;
		ans[q[i].id]=res;
	}
	
	for(i=1;i<=m;i++) 
		printf("%lld\n",ans[i]);
	return 0;
}

