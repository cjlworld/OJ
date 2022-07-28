#include<cstdio>
#include<cstring>
#include<iostream>
#define rint register int 
typedef long long LL;
typedef unsigned long long ULL;
using namespace std;
const int N=3005;
int n,m;
LL a[N],s[N];
LL f[N][N];
#define val(j,k) ((s[j]-s[k])*(s[j]-s[k]))
#define less(P,j,k) (f[i][j]+val(P,j)<=f[i][k]+val(P,k))
struct State 
{
	int j,l,r;
	State(int j,int l,int r) : j(j),l(l),r(r) {}
	State() {}
}q[2][2*N];
void calc()
{
	rint hh[2],tt[2];
	rint i,j,L,R,mid,pos;
	memset(f,0x3f,sizeof f);
	for(i=0;i<=m;i++) 
		f[i][0]=0;
	for(i=1;i<=m;i++) {
		hh[(i+1)&1]=0,tt[(i+1)&1]=0;
		q[(i+1)&1][0]=State(0,1,n);
		for(j=1;j<=n;j++) {
			if(q[i&1][hh[i&1]].r==j-1) hh[i&1]++;
			else q[i&1][hh[i&1]].l=j;
			
			f[i][j]=f[i-1][q[i&1][hh[i&1]].j]+val(j,q[i&1][hh[i&1]].j);
			
			pos=n+1;
			while(hh[(i+1)&1]<=tt[(i+1)&1]) {
				State &u=q[(i+1)&1][tt[(i+1)&1]];
				if(less(u.l,j,u.j)) 
					pos=u.l,tt[(i+1)&1]--;
				else if(less(u.r,u.j,j)) 
					break;
				else {
					L=u.l; R=u.r;
					while(L+1<R) {
						mid=(L+R)>>1;
						if(less(mid,u.j,j)) L=mid;
						else R=mid;
					}
					u.r=L;
					pos=R;
				}
			}
			if(pos<=n) q[(i+1)&1][++tt[(i+1)&1]]=State(j,pos,n);
		}
	}
}
int main()
{
//	freopen("1.in","r",stdin);
	int i;
	scanf("%d%d",&n,&m);
	for(i=1;i<=n;i++) 
		scanf("%lld",&a[i]),s[i]=s[i-1]+a[i];
	calc();
	cout<<f[m][n]*m-s[n]*s[n];
	return 0;
}

