#include<cstdio>
#include<cstring>
#include<iostream>
typedef long long LL;
typedef unsigned long long ULL;
using namespace std;
const int N=5e4+5;
const LL INF=1e16;
// f[i] 表示装下前 i 个物品的费用最小值
// f[i] = min{ f[j]+[(s[i]-s[j]+i-j-1)-L]^2 } 0<=j<i;
int n; 
LL L__L;
LL a[N];
LL f[N],s[N],p[N];
#define val(i,j) ((s[i]-s[j]+i-j-1-L__L)*(s[i]-s[j]+i-j-1-L__L))
struct State
{
	int j,l,r;
	State(int j,int l,int r) : j(j),l(l),r(r) {}
	State() {}
}q[2*N];
void Dp()
{
	memset(f,0x3f,sizeof f);
	f[0]=0;
	int i,pos,L,R,mid;
	int hh=0,tt=0;
	q[0]=State(0,1,n);
	for(i=1;i<=n;i++) {
		if(q[hh].r==i-1) hh++;
		else q[hh].l=i;
		
		f[i]=f[q[hh].j]+val(i,q[hh].j);
		
		pos=n+1;
		while(hh<=tt) {
			if(f[i]+val(q[tt].l,i)<=f[q[tt].j]+val(q[tt].l,q[tt].j)) 
				pos=q[tt].l,tt--;
			else if(f[i]+val(q[tt].r,i)>=f[q[tt].j]+val(q[tt].r,q[tt].j))
				break;
			else {
				L=q[tt].l; R=q[tt].r;
				while(L+1<R) {
					mid=(L+R)>>1;
					if(f[q[tt].j]+val(mid,q[tt].j)<=f[i]+val(mid,i)) 
						L=mid;
					else R=mid;
				}
				q[tt].r=L; pos=R;
				break;
			}
		}
		if(pos<=n) q[++tt]=State(i,pos,n);
	}
}
int main()
{
//	freopen("1.in","r",stdin);
	register int i;
	scanf("%d%lld",&n,&L__L);
	for(i=1;i<=n;i++) 
		scanf("%lld",&a[i]),s[i]=s[i-1]+a[i];
	Dp();
	printf("%lld\n",f[n]);
	return 0;
}
