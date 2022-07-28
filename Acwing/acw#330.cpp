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

const int N=2000+5,SI=4e4+5,M=30;
const LL INF=0x3f3f3f3f3f3f3f3f;

LL maxA,minA;

struct Bits
{
	LL c[SI];
	inline int lowbit(int x) { return x&(-x); }
	void Update(int x,LL y)
	{
		for(;x<=maxA;x+=lowbit(x)) 
			c[x]+=y;
	}
	LL Sum(int x)
	{
		LL res=0;
		for(;x>=1;x-=lowbit(x)) 
			res+=c[x];
		return res;
	}
	LL Findkth(int rk)
	{
		int pos=0,sum=0;
		for(int k=log2(maxA);k>=0;k--) 
			if(pos+(1<<k)<maxA&&sum+c[pos+(1<<k)]<rk)
				pos+=(1<<k),sum+=c[pos];
		return pos+1ll;
	}
}C,Cs;

int n,m;
LL f[N][M];
LL a[N];

int main()
{
//	freopen("1.in","r",stdin);
	int i,j,k;
	LL t;
	
	while(scanf("%d%d",&n,&m),n||m) {
		maxA=-INF,minA=INF;
		for(i=1;i<=n;i++) {
			scanf("%lld",&a[i]);
			minA=min(minA,a[i]),maxA=max(maxA,a[i]);
		}
		minA--,maxA-=minA;
		for(i=1;i<=n;i++) a[i]-=minA;
		
		memset(f,0x3f,sizeof f);
		f[0][0]=0;
		for(i=1;i<=n;i++) {
			for(k=i-1;k>=0;k--) {
				C.Update(a[k+1],1),Cs.Update(a[k+1],a[k+1]);
				t=C.Findkth((i-k+1)/2);
				t=t*C.Sum(t)-Cs.Sum(t)+Cs.Sum(maxA)-Cs.Sum(t)-(C.Sum(maxA)-C.Sum(t))*t;
//				if(tt<0) {
//					printf("here! : %lld\n",t);
//					cout<<(i-k+1)/2<<endl;
//					cout<<C.Sum(t)<<" "<<Cs.Sum(t)<<" "<<Cs.Sum(maxA)<<" "<<C.Sum(maxA)<<endl;
//				}
				for(j=1;j<=m;j++) 
					f[i][j]=min(f[i][j],f[k][j-1]+t);
			}
			for(k=i;k>=1;k--) C.Update(a[k],-1),Cs.Update(a[k],-a[k]);
//			for(j=1;j<=m;j++) 
//				printf("f[%d,%d]=%lld\n",i,j,f[i][j]);
		}
		printf("%lld\n",f[n][m]);
	}
	return 0;
}

