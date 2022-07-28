#include<cmath>
#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>

using namespace std;
typedef long long LL;

const int N=1e5+5,SQ=1024;

int n,m,siz;
int a[N];
vector<int> nums;

struct Query
{
	int l,r,id;
	inline bool operator<(const Query& t) const
	{
		if(l/siz!=t.l/siz) return l<t.l;
		else return r<t.r;
	}
}q[N];

struct Range
{
	int posl,posr;
	int id,sign;
	Range(int posl=0,int posr=0,int id=0,int sign=0)
		: posl(posl),posr(posr),id(id),sign(sign) {};
};

struct Block
{
	int siz,k;
	int L[SQ],R[SQ],F[N];
	int tag[SQ],b[N];
	
	inline void clear()
	{
		memset(tag,0,sizeof tag);
		memset(b,0,sizeof b);		
	}
	inline void Build(int n)
	{
		siz=sqrt(n);
		k=(n/siz)+(n%siz>0);
		int i,j;
		for(i=1;i<=k;i++) {
			L[i]=R[i-1]+1;
			R[i]=i*siz;
		}
		R[k]=n;
		for(i=1;i<=k;i++) 
			for(j=L[i];j<=R[i];j++) 
				F[j]=i;
		clear();
	}
	
	inline void Modify(int x,int y,int key)
	{
		if(x>y) return; // 特判 
		if(F[x]==F[y]) {
			for(int i=x;i<=y;i++) b[i]+=key;
			return;
		}
		int i;
		for(i=x;i<=R[F[x]];i++) b[i]+=key;
		for(i=F[x]+1;i<=F[y]-1;i++) tag[i]+=key;
		for(i=L[F[y]];i<=y;i++) b[i]+=key;
	}
	
	inline int ask(int x) { return b[x]+tag[F[x]]; }
}B;

vector<Range> quiz[N][2];

LL ans[N];
inline void Add(int l,int r,int isright,int border,int id,int sign)
{
//	printf("Add %d %d %d %d %d %d\n",l,r,isright,border,id,sign);
	quiz[border][isright].push_back(Range(l,r,id,sign));
} 

int pre[N],nxt[N];
// 其实只要前面比它大，后面比它小的就可以了。 
int main()
{
//	freopen("1.in","r",stdin);
//	freopen("1.out","w",stdout);
	int i,j;
	
	scanf("%d%d",&n,&m);
	for(i=1;i<=n;i++) {
		scanf("%d",&a[i]);
		nums.push_back(a[i]);
	}
	sort(nums.begin(),nums.end());
	nums.erase(unique(nums.begin(),nums.end()),nums.end());
	for(i=1;i<=n;i++) 
		a[i]=upper_bound(nums.begin(),nums.end(),a[i])-nums.begin();
	B.Build(nums.size()+1);
	
	// 预处理 前面比它大，后面比它小 的数的个数 
	B.clear();
	for(i=1;i<=n;i++) {
		pre[i]=B.ask(a[i]);
		B.Modify(1,a[i]-1,1);
	}
	B.clear();
	for(i=n;i>=1;i--) {
		nxt[i]=B.ask(a[i]);
		B.Modify(a[i]+1,nums.size(),1);
	}
	
//	printf("pre[] is {");
//	for(i=1;i<=n;i++) 
//		printf("%d,",pre[i]);
//	printf("}\n");
//	printf("nxt[] is {");
//	for(i=1;i<=n;i++) 
//		printf("%d,",nxt[i]);
//	printf("}\n");

	// 读入询问 
	for(i=1;i<=m;i++) {
		scanf("%d%d",&q[i].l,&q[i].r);
		q[i].id=i;
	}
	siz=sqrt(n);
	sort(q+1,q+m+1);
	
	// 一次离线。 
	int hh=1,tt=0;
	for(i=1;i<=m;i++) {	
		if(hh>q[i].l) Add(q[i].l,hh-1,1,tt+1,q[i].id,-1);
		while(hh>q[i].l) ans[q[i].id]+=nxt[--hh];  
		
		if(tt<q[i].r) Add(tt+1,q[i].r,0,hh-1,q[i].id,-1);
		while(tt<q[i].r) ans[q[i].id]+=pre[++tt];
		
		if(hh<q[i].l) Add(hh,q[i].l-1,1,tt+1,q[i].id,1);
		while(hh<q[i].l) ans[q[i].id]-=nxt[hh++];
		
		if(tt>q[i].r) Add(q[i].r+1,tt,0,hh-1,q[i].id,1);
		while(tt>q[i].r) ans[q[i].id]-=pre[tt--];
		
		// 由于存的是偏移量，所以不能用 cur; 
	}
	
	// 二次离线。
	// 左边都是求比它大的，右边都是求比它小的。 
	
	// 处理左半部分。 
	B.clear();
	for(i=1;i<=n;i++) {
		B.Modify(1,a[i]-1,1);
		vector<Range>& v=quiz[i][0];
		for(;v.size();v.pop_back()) {
			Range& t=v.back();
			for(j=t.posl;j<=t.posr;j++) 
				ans[t.id]+=t.sign*B.ask(a[j]);
		}
	}
	
	// 处理右半部分。
	B.clear();
	for(i=n;i>=1;i--) {
		B.Modify(a[i]+1,nums.size(),1);
		vector<Range>& v=quiz[i][1];
		for(;v.size();v.pop_back()) {
			Range& t=v.back();
			for(j=t.posl;j<=t.posr;j++) 
				ans[t.id]+=t.sign*B.ask(a[j]);
		} 
	} 
	
	for(i=1;i<=m;i++) ans[q[i].id]+=ans[q[i-1].id];
	for(i=1;i<=m;i++) 
		printf("%lld\n",ans[i]);
	return 0;
}

