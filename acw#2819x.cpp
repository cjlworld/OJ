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
#include<iostream>
#include<algorithm>

using namespace std;
typedef long long LL;
typedef unsigned long long ULL;

const int N=1e5+5;

int n,m;
struct Bits
{
    LL c[N];
    int n;
    inline int lowbit(int x) { return x&(-x); }
    inline void Update(int x,int y)
    {
        for(;x<=n;x+=lowbit(x)) 
            c[x]+=y;
    } 
    inline LL Sum(int x)
    {
        LL res=0;
        for(;x>=1;x-=lowbit(x))
            res+=c[x];
        return res;
    }   
}C;

struct Node
{
	int a,b,c; // val , pos , tim 
	LL res;
	bool operator<(const Node &t) const
	{
		if(a!=t.a) return (a>t.a);
		if(b!=t.b) return (b<t.b);
		return c<t.c;
	}
}q[N],w[N];

void cdq(int l,int r)
{
	if(l==r) return;
	int mid=(l+r)>>1;
	cdq(l,mid),cdq(mid+1,r);
	
	int i=l,j=mid+1,tot=l-1;
	while(i<=mid && j<=r) {
		if(q[i].b<q[j].b) C.Update(q[i].c,1),w[++tot]=q[i++];
		else q[j].res+=C.Sum(q[j].c),w[++tot]=q[j++];
	}
	while(i<=mid) C.Update(q[i].c,1),w[++tot]=q[i++];
	while(j<=r) q[j].res+=C.Sum(q[j].c),w[++tot]=q[j++];
	
	for(i=l;i<=mid;i++) C.Update(q[i].c,-1);
	for(i=l;i<=r;i++) q[i]=w[i];
}


int p[N],qy[N];

int main()
{
//	freopen("1.in","r",stdin);
	int i;
	
	scanf("%d%d",&n,&m);
	for(i=1;i<=n;i++) {
		scanf("%d",&q[i].a);
		p[q[i].a]=i;
		q[i].b=i,q[i].c=1;
	}
	for(i=1;i<=m;i++) {
		scanf("%d",&qy[i]);
		q[p[qy[i]]].c=m-i+2;
	}
	C.n=m+1;
	
	sort(q+1,q+n+1);
	for(i=1;i<=n;i++)
		printf("%d %d %d\n",q[i].a,q[i].b,q[i].c);	
	cdq(1,n);

	LL ans=0;
	sort(q+1,q+n+1);
	reverse(q+1,q+n+1);
	
	for(i=1;i<=n;i++) 
		ans+=q[i].res;
	for(i=1;i<=m;i++) {
		printf("%lld\n",ans);
		ans-=q[qy[i]].res;
	}
	return 0;
}

