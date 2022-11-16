#include<set>
#include<map>
#include<queue>
#include<stack>
#include<cmath>
#include<ctime>
#include<bitset>
#include<vector>
#include<cstdio>
#include<complex>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>

using namespace std;
typedef long long LL;

const int N=3e6+1,M=10001;

namespace FastIO
{
	char c;
	bool sign;
	template<class T>
	inline void read(T &x)
	{
		x=0;
		sign=false;
		for(c=getchar();c<'0'||c>'9';c=getchar()) 
			if(c=='-') sign=true;
		for(;c>='0'&&c<='9';c=getchar())
			x=(x<<1)+(x<<3)+(c&15);
		if(sign) x=~x+1;
	 	return;
	}
}
using FastIO::read;


int n,m;
LL s[N];
LL f[M],g[M],h[M]; // f[i][j] , g[j]=max{f[i][j]-s[i]} h[j]=max{f[i][j]}
// f[i][j] = max{h[j],g[j-1]+s[i]}

#define max(x,y) ((x) > (y) ? (x) : (y))

int main()
{
//	freopen("1.in","r",stdin);
//	cout<<1.0*sizeof(f)/1024/1024<<endl;
	while(~scanf("%d%d",&m,&n)) {
		memset(g,-0x3f,sizeof g);
		memset(h,-0x3f,sizeof h);
		
		g[0]=0; h[0]=0;
		for(int i=1;i<=n;i++) {
			read(s[i]);
			s[i]+=s[i-1];
		}
		for(int i=1;i<=n;i++) {
			for(int j=1;j<=m;j++) 
				f[j]=max(h[j],g[j-1]+s[i]);
			for(int j=1;j<=m;j++) {
				h[j]=max(h[j],f[j]);
				g[j]=max(g[j],f[j]-s[i]);
			}
			g[0]=max(g[0],-s[i]);
		}
		printf("%lld\n",f[m]);
	}
	return 0;
}

