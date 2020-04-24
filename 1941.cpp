#include<cstdio>
#include<iostream>
#include<cstring>
#define LL long long
using namespace std;
const int N=1024;
struct Bignum
{
	int a[N];
	int len;
	void clear()
	{
		memset(a,0,sizeof a);
		len=0;
		return;
	}
	void print()
	{
		for(int i=len;i>=1;i--) 
			putchar(a[i]+'0');
		return;
	}
};
Bignum operator+(const Bignum &x,const Bignum &y)
{
	int i,j;
	Bignum z;
	z.clear();
	z.len=max(x.len,y.len)+1;
	int tmp=0;
	for(i=1;i<=z.len;i++) {
		z.a[i]=x.a[i]+y.a[i]+tmp;
		tmp=z.a[i]/10;
		z.a[i]=z.a[i]%10;
	}
	while(z.len>=1&&z.a[z.len]==0) z.len--;
	return z;
}
Bignum f[201];
Bignum two;
int n;
int main()
{
//	freopen("1.out","w",stdout);
	int i,j;
	int x,y,z;
	cin>>n;
	f[1].len=1; f[1].a[1]=2;
	two.len=1; two.a[1]=2;
	for(i=2;i<=n;i++) 
		f[i]=f[i-1]+f[i-1]+two;
	f[n].print();
	return 0;
}

