#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>

using namespace std;
typedef long long LL;
const int N=5e5+5;

LL a[N],c[N];
int n,m;

LL gcd(LL a,LL b) 
{
    if(b==0) return a;
    else return gcd(b,a%b);
}
#define lc (now<<1)
#define rc (now<<1|1)
LL sum[4*N],d[4*N];
void Update(int now,int pos,LL key,int l,int r)
{
    if(l==r&&l==pos) {
        sum[now]+=key;
        d[now]+=key;
        return;
    }
    int mid=(l+r)>>1;
    if(pos<=mid) Update(lc,pos,key,l,mid);
    else Update(rc,pos,key,mid+1,r);
    
    sum[now]=sum[lc]+sum[rc];
    d[now]=gcd(d[lc],d[rc]);
}

LL QuerySum(int now,int pos,int l,int r)
{
    if(r<=pos) return sum[now];
    int mid=(l+r)>>1;
    LL res=QuerySum(lc,pos,l,mid);
    if(pos>=mid+1) res+=QuerySum(rc,pos,mid+1,r);
    return res;
}

LL QueryGcd(int now,int x,int y,int l,int r)
{
    if(x<=l&&r<=y) return d[now];
    int mid=(l+r)>>1;
    LL res=0;
    if(x<=mid) res=gcd(res,QueryGcd(lc,x,y,l,mid));
    if(y>=mid+1) res=gcd(res,QueryGcd(rc,x,y,mid+1,r));
    return res;
}


int main()
{
    int i;
    int x,y;
    LL z;
    char opt;
    scanf("%d%d",&n,&m);
    for(i=1;i<=n;i++) {
        scanf("%lld",&a[i]);
        c[i]=a[i]-a[i-1];
        Update(1,i,c[i],1,n);
    }
    while(m--) {
        for(opt=getchar();opt!='C'&&opt!='Q';opt=getchar());
        scanf("%d%d",&x,&y);
        if(opt=='Q') printf("%lld\n",abs(gcd(QueryGcd(1,x+1,y,1,n),QuerySum(1,x,1,n))));
        else {
            scanf("%lld",&z);
            Update(1,x,z,1,n);
            if(y+1<=n) Update(1,y+1,-z,1,n);
        }
    }
    return 0;
}
