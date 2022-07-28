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
int bcc[21];
template<class T>
inline void print(T x)
{
	if(x<0) putchar('-'),x=-x;
	int top=0;
	while(x>0) {
		bcc[++top]=x%10;
		x=x/10;
	}
	while(top>0) {
		putchar('0'+bcc[top]);
		top--;
	}
	putchar(10);
	return;
}
template<class T>
inline void max(const T &x,const T &y)
{
	if(x>y) return x;
	else return y;
}
template<class T>
inline void min(const T &x,const T &y)
{
	if(x>y) return y;
	else return x;
}
}
#define read(x) FastIO::read(x) 
#define print(x) FastIO::print(x)
#define min(x,y) FastIO::min(x,y) 
#define max(x,y) FastIO::max(x,y)
//=================================
const int N=1e5+5;
int n,m;
int c[N];
inline int lowbit(int x)
{
	return x&(-x);
}
inline void update(int x,int y)
{
	for(;x<=n;x+=lowbit(x)) 
		c[x]+=y;
	return;
}
inline int sum(int x)
{
	int res=0;
	for(;x>=1;x-=lowbit(x)) 
		res+=c[x];
	return res;
}
int main()
{
//	freopen("1.in","r",stdin);
	int i,j;
	int x,y,z;
	int opt=0;
	read(n); read(m);
	for(i=1;i<=m;i++) {
		read(opt);
		if(opt==1) {
			read(x); read(y);
			update(x,1);
			update(y+1,-1);
		}
		else {
			read(x);
			if(sum(x)&1) puts("1");
			else puts("0");
		}
	}
	return 0;
}

