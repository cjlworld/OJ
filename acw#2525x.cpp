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
	int type,id,sign; // 0 是小于，1 是大于。 
	Range(int posl=0,int posr=0,int type=0,int id=0,int sign=0)
		: posl(posl),posr(posr),type(type),id(id),sign(sign) {};
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

vector<Range> quiz[N];

LL ans[N];

int tiny[N],huge[N];
// 这一种和前一版的区别就是只预处理 前面比它 大/小 的。
 
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
		tiny[i]=B.ask(a[i]);
		B.Modify(a[i]+1,nums.size(),1);
	}
	B.clear();
	for(i=1;i<=n;i++) {
		huge[i]=B.ask(a[i]);
		B.Modify(1,a[i]-1,1);
	}
	
//	printf("tiny[] is {");
//	for(i=1;i<=n;i++) 
//		printf("%d,",tiny[i]);
//	printf("}\n");
//	printf("huge[] is {");
//	for(i=1;i<=n;i++) 
//		printf("%d,",huge[i]);
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
		if(hh>q[i].l) quiz[tt].push_back(Range(q[i].l,hh-1,0,q[i].id,1));
		while(hh>q[i].l) ans[q[i].id]-=tiny[--hh];  
		
		if(tt<q[i].r) quiz[hh-1].push_back(Range(tt+1,q[i].r,1,q[i].id,-1));
		while(tt<q[i].r) ans[q[i].id]+=huge[++tt];
		
		if(hh<q[i].l) quiz[tt].push_back(Range(hh,q[i].l-1,0,q[i].id,-1));
		while(hh<q[i].l) ans[q[i].id]+=tiny[hh++];
		
		if(tt>q[i].r) quiz[hh-1].push_back(Range(q[i].r+1,tt,1,q[i].id,1));
		while(tt>q[i].r) ans[q[i].id]-=huge[tt--];
		
		// 由于存的是偏移量，所以不能用 cur; 
	}
	
	// 二次离线。
	B.clear();
	for(i=1;i<=n;i++) {
		B.Modify(a[i],nums.size(),1);
		vector<Range>& v=quiz[i];
		for(;v.size();v.pop_back()) {
			Range& t=v.back();
			for(j=t.posl;j<=t.posr;j++) {
				if(!t.type) ans[t.id]+=t.sign*B.ask(a[j]-1);
				else ans[t.id]+=t.sign*(B.ask(nums.size())-B.ask(a[j]));
			}
		}
	}
	
	for(i=1;i<=m;i++) ans[q[i].id]+=ans[q[i-1].id];
	for(i=1;i<=m;i++) 
		printf("%lld\n",ans[i]);
	return 0;
}

