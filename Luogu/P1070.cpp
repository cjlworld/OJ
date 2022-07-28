#include<cstdio>
#include<cstring>
#include<iostream>
typedef long long LL;
typedef unsigned long long ULL;
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
		if(c=='-')
			sign=true;
	for(;c>='0'&&c<='9';c=getchar()) 
		x=(x<<1)+(x<<3)+(c&15);
	if(sign) x=~x+1;
	return;
}
}
using FastIO::read;
//=======================================
using namespace std;
const int N=1000+5,INF=1e9;
int a[N][N],g[N][N],p[N];
// g[i][j] 表示在 i 时间，买了次数为 j 的机器人获得的最大金币 
int f[N];
int s[N][N];
int n,m,k;
#define pre(x) ((x==1) ? n : x-1)
#define nxt(x) ((x==n) ? 1 : x+1) 
int main()
{
//	freopen("1.in","r",stdin);
	register int i,j,u;
	read(n); read(m); read(k);
	for(i=1;i<=n;i++)
		for(j=1;j<=m;j++) 
			read(a[i][j]);
	for(i=1;i<=n;i++) 
		read(p[i]);
	for(j=1;j<=m;j++) 		
		for(i=1;i<=n;i++) 
			s[i][j]=a[i][j]+s[pre(i)][j-1];
	memset(g,0xc0,sizeof g);
	for(i=1;i<=m;i++) 
		for(j=1;j<=k&&i+j-1<=m;j++) 
			for(u=1;u<=n;u++) 
				g[i][j]=max(g[i][j],s[((u+j-1)%n==0) ? n : (u+j-1)%n][i+j-1]-s[pre(u)][i-1]-p[u]);
	memset(f,0xc0,sizeof f);
	f[0]=0;
	for(i=1;i<=m;i++) {
		for(j=1;j<=k&&i-j>=0;j++)
			f[i]=max(f[i],f[i-j]+g[i-j+1][j]);
	}
	cout<<f[m];
	return 0;
}
