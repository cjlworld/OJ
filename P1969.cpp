#include<cstdio>
#include<iostream>
#define LL long long
#define rint register int
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
int bcc[22],top=0;
template<class T>
inline void print(T x)
{
	top=0;
	if(!x) {
		putchar('0');
		return;
	}
	if(x<0) putchar('-'),x=~x+1;
	while(x) {
		bcc[++top]=x%10;
		x=x/10;
	}
	while(top>=1) {
		putchar(48+bcc[top]);
		--top;
	}
	return;
}
}
using FastIO::read;
using FastIO::print;
//=====================================
const int N=100000+5;
int a[N],c[N];
int n;
int main()
{
//	freopen("1.in","r",stdin);
	rint i;
	int ans=0;
	read(n);
	for(i=1;i<=n;i++) 
		read(a[i]);
	for(i=1;i<=n+1;i++) 
		c[i]=a[i]-a[i-1];
	for(i=1;i<=n;i++) 
		if(c[i]>0) 
			ans+=c[i];
	print(ans);
	return 0;
}

