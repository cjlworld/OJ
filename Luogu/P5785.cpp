#include<cstdio>
#include<cstring>
#include<iostream>

using namespace std;
typedef long long LL;

const int N=3e5+5;
const double INF=1e16+5;

LL f[N];
LL sc[N],st[N];
int n;
LL S; 
#define double long double
inline LL X(int j) { return sc[j]; }
inline LL Y(int j) { return f[j]-S*sc[j]+sc[n]*S; }
inline bool cmp(int i,int j,int k) 
{
	return (Y(j)-Y(i))*(X(k)-X(j))>=(X(j)-X(i))*(Y(k)-Y(j));
}
// 斜率 k=st[] 不是递增的，但 x=sc[] 单调不降。
// 所以每次插入时仍从最后插入，但 查找决策点需要二分。

int q[N];

int main()
{
//	freopen("1.in","r",stdin);
    int i,j;
    scanf("%d%lld",&n,&S);
    for(i=1;i<=n;i++) {
        scanf("%lld%lld",&st[i],&sc[i]);
        sc[i]+=sc[i-1];
        st[i]+=st[i-1];
    }
    
    memset(f,0x3f,sizeof f);
    f[0]=0;
    int tt=0,L,R,mid;
    for(i=1;i<=n;i++) {
    	L=-1,R=tt;
    	while(L+1<R) {
			mid=(L+R)>>1;
			if(Y(q[mid+1])-Y(q[mid])<=st[i]*(X(q[mid+1])-X(q[mid]))) L=mid;
			else R=mid;
		}
        j=q[R];

        f[i]=f[j]+(sc[n]-sc[j])*S+(sc[i]-sc[j])*st[i];
        while(tt>0 && cmp(q[tt-1],q[tt],i) ) tt--;
        q[++tt]=i;
    }
    cout<<f[n];
    return 0;
}
