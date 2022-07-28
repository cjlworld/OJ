#include<set>
#include<map>
#include<cmath>
#include<ctime>
#include<stack>
#include<queue>
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

namespace GenHelper
{
    unsigned z1,z2,z3,z4,b;
    unsigned rand_()
    {
    b=((z1<<6)^z1)>>13;
    z1=((z1&4294967294U)<<18)^b;
    b=((z2<<2)^z2)>>27;
    z2=((z2&4294967288U)<<2)^b;
    b=((z3<<13)^z3)>>21;
    z3=((z3&4294967280U)<<7)^b;
    b=((z4<<3)^z4)>>12;
    z4=((z4&4294967168U)<<13)^b;
    return (z1^z2^z3^z4);
    }
}
void srand(unsigned x)
{using namespace GenHelper;
z1=x; z2=(~x)^0x233333333U; z3=x^0x1234598766U; z4=(~x)+51;}
int read()
{
    using namespace GenHelper;
    int a=rand_()&32767;
    int b=rand_()&32767;
    return a*32768+b;
}

const int N=2e7+5,SQ=6000,INF=1e8;

int a[N];

struct Block
{
	int F[N];
	int fmax[SQ][SQ],cmax[SQ];
	int L[SQ],R[SQ];
	int sl[N],sr[N];
	int siz,k;
	
	void Build(int n)
	{
		memset(fmax,0xcf,sizeof fmax);
		memset(sl,0xcf,sizeof sl);
		memset(sr,0xcf,sizeof sr);
		
		int i,j;
		siz=sqrt(n);
		if(siz>25) siz-=25;
		k=n/siz+(n%siz>0);
		for(i=1;i<=k;i++) {
			L[i]=R[i-1]+1;
			R[i]=i*siz;
		}
		R[k]=n;
		for(i=1;i<=k;i++) {
			for(j=L[i];j<=R[i];j++) F[j]=i;
			sl[L[i]]=a[L[i]];
			for(j=L[i]+1;j<=R[i];j++) sl[j]=max(sl[j-1],a[j]);
			sr[R[i]]=a[R[i]];
			for(j=R[i]-1;j>=L[i];j--) sr[j]=max(sr[j+1],a[j]);
			
			cmax[i]=sr[L[i]];
		}
		
		for(i=1;i<=k;i++) {
			fmax[i][i]=cmax[i];
			for(j=i+1;j<=k;j++) 
				fmax[i][j]=max(fmax[i][j-1],cmax[j]);
		}
	}
	int query(int x,int y)
	{
		if(F[x]==F[y]) {
			int res=-INF;
			for(int i=x;i<=y;i++) 
				res=max(res,a[i]);
			return res;
		}
		else return max(max(sr[x],sl[y]),fmax[F[x]+1][F[y]-1]);
	}
}Bl;

int n,m,s;

int main()
{
//	freopen("1.in","r",stdin);
	int i,x,y;
	scanf("%d%d%d",&n,&m,&s);
	srand(s);
	
	for(i=1;i<=n;i++) a[i]=read();
	Bl.Build(n);
	ULL ans=0;
	while(m--) {
		x=read()%n+1,y=read()%n+1;
		if(x>y) swap(x,y);
		ans+=Bl.query(x,y);
	}
	printf("%llu\n",ans);
	return 0;
}

