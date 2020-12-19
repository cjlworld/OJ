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

const int N=2e5+5;

int n,m,cnt;

struct Bits
{
    int c[N];
    inline int lowbit(int x) { return x&(-x); }
    void Update(int x,int y) 
    {
        for(;x<=m;x+=lowbit(x)) 
            c[x]+=y;
    }
    int Sum(int x)
    {
        int res=0;
        for(;x>=1;x-=lowbit(x)) 
            res+=c[x];
        return res;
    }
}C;

struct Node
{
    int a,b,c,s,res;
    bool operator<(const Node &t) const
    {
        if(a!=t.a) return a<t.a;
        if(b!=t.b) return b<t.b;
        return c<t.c;
    }
    bool operator==(const Node &t) const
    {
        return (a==t.a)&&(b==t.b)&&(c==t.c);
    }
}q[N];

inline bool cmp(const Node &a,const Node &b) { return a.b<b.b; }

void cdq(int l,int r)
{
    if(l>=r) return;
    int mid=(l+r)>>1;
    cdq(l,mid),cdq(mid+1,r);

    int i,j,k;
    for(i=l,j=mid+1;j<=r;j++) {
    	for(;i<=mid && q[i].b<=q[j].b;i++) 
    		C.Update(q[i].c,q[i].s);
    	q[j].res+=C.Sum(q[j].c);
	}
    for(k=l;k<i;k++) C.Update(q[k].c,-q[k].s);
    sort(q+l,q+r+1,cmp);
}

int ans[N];

int main()
{
//	freopen("1.in","r",stdin);
    int i;
    scanf("%d%d",&n,&m);
    for(i=1;i<=n;i++) {
        scanf("%d%d%d",&q[i].a,&q[i].b,&q[i].c);
        q[i].s=1;
    }

    sort(q+1,q+n+1);
    for(i=2,cnt=1;i<=n;i++) {
        if(q[i]==q[cnt]) q[cnt].s++;
        else q[++cnt]=q[i];
    }

    cdq(1,cnt);
    for(i=1;i<=cnt;i++) {
        q[i].res+=q[i].s-1;
        ans[q[i].res]+=q[i].s;
    }

    for(i=0;i<n;i++) printf("%d\n",ans[i]);
    return 0;
}

