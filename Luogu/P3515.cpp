#include<cmath>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
typedef long long LL;
typedef unsigned long long ULL;
using namespace std;
const int N=5e5+5;
int n;
double a[N],f[N];
struct State
{
	int j,l,r;
	State(int j,int l,int r) : j(j),l(l),r(r) {}
	State() {}
}q[2*N];
#define val(i,j) (double)(a[j]+sqrt(i-j)-a[i])
void calc()
{
	register int i,pos,L,R,mid;
	int hh=0,tt=0;
	q[hh]=State(1,1,n);
	for(i=2;i<=n;i++) {
		if(q[hh].r==i-1) hh++;
		else q[hh].l=i;
		
		f[i]=max(f[i],val(i,q[hh].j));
		
		pos=n+1;
		while(tt>=hh) {
			if(val(q[tt].l,q[tt].j)<=val(q[tt].l,i))
				pos=q[tt].l,tt--;
			else if(val(q[tt].r,q[tt].j)>=val(q[tt].r,i)) 
				break;
			else {
				L=q[tt].l,R=q[tt].r;
				while(L+1<R) {
					mid=(L+R)>>1;
					if(val(mid,q[tt].j)>=val(mid,i)) 
						L=mid;
					else R=mid;
				}
				q[tt].r=L;
				pos=R;
			}
		}
		if(pos<=n) q[++tt]=State(i,pos,n);
	}
	return;
}

int main()
{
//	freopen("1.in","r",stdin);
	int i;
	scanf("%d",&n);
	for(i=1;i<=n;i++) 
		scanf("%lf",&a[i]);
	calc();
	reverse(a+1,a+n+1);
	reverse(f+1,f+n+1);
	calc();
	reverse(f+1,f+n+1);
	for(i=1;i<=n;i++) 
		printf("%d\n",(int)ceil(f[i]));
	return 0;
}

