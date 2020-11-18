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
typedef long double LD;
typedef unsigned long long ULL;

const int N=1e5+5;
const LL INF=1e18;

int T,n;
LL m,P;
LL a[N],s[N];
char sentence[N];
LD f[N]; // f[i] 表示 arrange 了前i首诗的不协调度的最小值。 

LL mabs(LL a) { return (a<0) ? -a : a; }
LD fpow(LD x,LL k)
{
	LD res=1;
	while(k) {
		if(k&1) res=res*x;
		x=x*x; k>>=1;
	}
	return res;
}

inline LD val(int i,int j) { return fpow(mabs(s[i]-s[j]+i-j-1-m),P); }

struct State
{
	int j,l,r;
	State(int j,int l,int r) : j(j),l(l),r(r) {}
	State() {}
}q[N];

void Dp()
{
	int i,pos;
	int hh,tt;
	int L,R,mid;
	
	memset(f,0x3f,sizeof f);
	f[0]=0;
	hh=tt=0,q[hh]=State(0,1,n);
	
	for(i=1;i<=n;i++) {
		if(q[hh].r<i) hh++;
		else q[hh].l=i;
		
//		if(f[q[hh].j]>INF||f[q[hh].j]<0) continue;
		f[i]=f[q[hh].j]+val(i,q[hh].j);
		
		pos=n+1;
		while(hh<=tt) {
			if(f[q[tt].j]+val(q[tt].r,q[tt].j)<=f[i]+val(q[tt].r,i)) break;
			else if(f[q[tt].j]+val(q[tt].l,q[tt].j)>=f[i]+val(q[tt].l,i)) pos=q[tt].l,tt--;
			else {
				L=q[tt].l,R=q[tt].r; 
				while(L+1<R) {
					mid=(L+R)>>1;
					if(f[q[tt].j]+val(mid,q[tt].j)<=f[i]+val(mid,i)) L=mid;
					else R=mid;
				}
				q[tt].r=L,pos=R;
				break;
			}
		}
		if(pos<=n) q[++tt]=State(i,pos,n);
	}
}

int main()
{
//	freopen("1.in","r",stdin);
	int i;
	scanf("%d",&T);
	while(T--) {
		scanf("%d%lld%lld",&n,&m,&P);
		for(i=1;i<=n;i++) {
			scanf("%s",sentence);
			a[i]=strlen(sentence);
			s[i]=s[i-1]+a[i];
		}
		Dp();
		if(f[n]>INF) printf("Too hard to arrange\n");
		else printf("%lld\n",(LL)f[n]);
		printf("--------------------\n");
	}
	return 0;
}

