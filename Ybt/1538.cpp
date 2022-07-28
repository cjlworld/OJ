#include<cstdio>
#include<iostream>
#define LL long long
using namespace std;
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
short bcc[22],top=0;
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
const int N=5e5+5;
int n,m;
int a[N];
int ans;
int main()
{
//	freopen("1.in","r",stdin);
	int i,j;
	int x,y,z;
	char opt;
	int pos=0;
	read(n); read(m);
	for(i=1;i<=m;i++) {
		for(opt=getchar();opt!='A'&&opt!='B'&&opt!='C';opt=getchar());
		if(opt=='A') {
			read(x);
			while(pos<x) ans+=a[++pos];
			print(ans),putchar('\n');
		}
		else if(opt=='B') {
			read(x); read(y);
			if(x<=pos) ans+=y;
			else a[x]+=y;
		}
		else if(opt=='C') {
			read(x); read(y);
			if(x<=pos) ans-=y;
			else a[x]-=y;
		}
	}
	return 0;
}

