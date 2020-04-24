#include<cstdio>
#include<iostream>
#define LL long long
using namespace std;
namespace FastIO
{
template<class T>
inline void read(T &x)
{
	x=0;
	char c=getchar();
	bool sign=false;
	while(c<'0'||c>'9') {
		if(c=='-') sign=true;
		c=getchar();
	}
	while(c>='0'&&c<='9') {
		x=(x<<1)+(x<<3)+(c-'0');
		c=getchar();
	}
	if(sign) x=~x+1;
	return;
}
template<class T>
void print(T x)
{
	if(x<0) x=~x+1,putchar('-');
	if(x>9) print(x/10);
	putchar(x%10+48);
	return;
}
template<class T>
inline void swap(T &x,T &y)
{
	T temp=x;
	x=y;
	y=temp;
	return;
}
}
#define read(x) FastIO::read(x) 
#define print(x) FastIO::print(x)
#define swap(x,y) FastIO::swap(x,y)
#define rint register int 
//=================================
const int N=1e6+5;
int n,m,p,q;
int par[N];
int a[N];
int Find(int x)
{
	if(x!=par[x]) return par[x]=Find(par[x]);
	return x;
}
int main()
{
//	freopen("1.in","r",stdin);
	rint i,j;
	int x,y,z;
	read(n); read(m); read(p); read(q);
	for(i=1;i<=n+3;i++) 
		par[i]=i;
	for(i=m;i>=1;i--) {
		x=(i*p+q)%n+1;
		y=(i*q+p)%n+1;
		if(x>y) swap(x,y);
		z=Find(y+1);
		for(j=Find(x);j<=y;j=Find(j+1)) {
			a[j]=i;
			par[j]=z;
		} 
	}
	for(i=1;i<=n;i++) {
		printf("%d\n",a[i]);
	}
	return 0;
}

