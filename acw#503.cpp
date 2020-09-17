#include<cstdio>
#include<cstring>
#include<iostream>

using namespace std;
typedef long long LL;
const int N=1e6+5;
LL a[N],cc[N],c[N];
int n,m;

struct Request
{
    int x,y;
    LL z;
}r[N];
bool check(int lit)
{
    memcpy(c,cc,sizeof c);
    int i;
    for(i=1;i<=lit;i++) 
        c[r[i].x]-=r[i].z,c[r[i].y+1]+=r[i].z;
    for(i=1;i<=n;i++) {
        c[i]+=c[i-1];
        if(c[i]<0) return false;
    }
    return true;
}
int main()
{
    int i,j;
    int x,y; LL z;
    scanf("%d%d",&n,&m);
    for(i=1;i<=n;i++) {
        scanf("%lld",&a[i]);
        cc[i]=a[i]-a[i-1];
    }
    for(i=1;i<=m;i++) 
        scanf("%lld%d%d",&r[i].z,&r[i].x,&r[i].y);
    int L=0,R=m+1,mid;
    while(L+1<R) {
        mid=(L+R)>>1;
        if(check(mid)) L=mid;
        else R=mid;
    }
    if(L==m) printf("0\n");
    else printf("-1\n%d\n",R);
    return 0;
        
}
