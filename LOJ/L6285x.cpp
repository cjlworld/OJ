#include<cmath>
#include<vector>
#include<cstdio>
#include<iostream>
#include<algorithm>

using namespace std;

const int N=2e5+5;

int n,siz,bc;
int L[N],R[N],F[N];

struct Query
{
	int l,r;
	int id;
	inline bool operator<(const Query& t) const
	{
		if(F[l]!=F[t.l]) return l<t.l;
		else return r<t.r;
	}
}q[N];

int a[N];
int cnt[N],cur;
int ans[N];

inline void Add(int v,int &res)
{
	cnt[v]++;
	if(cnt[v]>cnt[res]) res=v;
	else if(cnt[v]==cnt[res])
		res=min(res,v);
}

vector<int> nums;

int main()
{
//	freopen("1.in","r",stdin);
	int i,j;
	
	scanf("%d",&n);
	for(i=1;i<=n;i++) {
		scanf("%d",&a[i]);
		nums.push_back(a[i]);
	}
	sort(nums.begin(),nums.end());
	nums.erase(unique(nums.begin(),nums.end()),nums.end());
	for(i=1;i<=n;i++) 
		a[i]=lower_bound(nums.begin(),nums.end(),a[i])-nums.begin();
	
	for(i=1;i<=n;i++) {
		scanf("%d%d",&q[i].l,&q[i].r);
		q[i].id=i;
	}
	
	siz=sqrt(n);
	bc=(n/siz)+(n%siz>0);
	for(i=1;i<=bc;i++) {
		L[i]=R[i-1]+1;
		R[i]=i*siz;
	}
	R[bc]=n;
	for(i=1;i<=bc;i++) 
		for(j=L[i];j<=R[i];j++) 
			F[j]=i;
	
	sort(q+1,q+n+1);
	int hh=1,tt=0;
	for(i=1;i<=n;i++) {
		if(F[q[i].l]^F[q[i-1].l]) {
			for(j=hh;j<=tt;j++) --cnt[a[j]];
			cur=0;
			hh=R[F[q[i].l]]+1,tt=R[F[q[i].l]];
		}
		
		if(F[q[i].l]==F[q[i].r]) {
			int res=0;
			for(j=q[i].l;j<=q[i].r;j++) Add(a[j],res);
			for(j=q[i].l;j<=q[i].r;j++) --cnt[a[j]];
			ans[q[i].id]=nums[res];
			continue;
		}
	
		while(tt<q[i].r) Add(a[++tt],cur);
		
		int res=cur;
		for(j=q[i].l;j<hh;j++) Add(a[j],res);
		for(j=q[i].l;j<hh;j++) --cnt[a[j]];
		ans[q[i].id]=nums[res];
	}
	
	for(i=1;i<=n;i++)
		printf("%d\n",ans[i]);
	return 0;
}
