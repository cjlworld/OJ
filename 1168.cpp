#include<iostream>
#include<cstdio>
#include<cstring>
#define LL long long 
using namespace std;
namespace _Bignum
{
char _c;
inline void reads(char *a)
{
	for(_c=getchar();_c<'0'||_c>'9';_c=getchar());
	for(int i=0;_c>='0'&&_c<='9';_c=getchar(),i++) 
		a[i]=_c;
	return;
}
//========================
const int _N=1024;
char _ch[_N];
struct Bignum
{
	short a[_N];
	int len;
	void clear() 
	{
		memset(a,0,sizeof a);
		len=0;
		return;
	}
	template<class T>
	void equal(T x) 
	{
		clear();
		while(x) {
			a[++len]=x%10;
			x/=10;
		} 
		return;
	}
	void output()
	{
		if(len==0)
			putchar('0');
		else 
			for(int i=len;i>=1;i--) 
				putchar('0'+a[i]);
		putchar('\n');
		return;
	}
	void input()
	{
		clear();
		memset(_ch,'\0',sizeof _ch);
		reads(_ch+1);
		len=strlen(_ch+1);
		for(int i=1;i<=len;i++) 
			a[i]=_ch[len-i+1]-'0';
		return;
	}
	void copy(Bignum x,int lenx) 
	{
		clear();
		len=lenx;
		for(int i=1;i<=len;i++) 
			a[i]=x.a[i];
		return; 
	}
};
bool operator<(Bignum x,Bignum y)
{
	if(x.len!=y.len) 
		return x.len<y.len;
	for(int i=x.len;i>=1;i--) {
		if(x.a[i]!=y.a[i]) 
			return x.a[i]<y.a[i];
	}
	return false;
}
bool operator==(Bignum x,Bignum y)
{
	if(x.len!=y.len) 
		return false;
	for(int i=x.len;i>=1;i--) {
		if(x.a[i]!=y.a[i]) 
			return false;
	}
	return true;
}
bool operator!=(Bignum x,Bignum y)
{
	return (!(x==y));
}
bool operator>(Bignum x,Bignum y)
{
	if(x==y||x<y) return false;
	else return true;
}
bool operator<=(Bignum x,Bignum y)
{
	if(x<y||x==y) return true;
	else return false;
}
bool operator>=(Bignum x,Bignum y)
{
	if(x<y) return false;
	else return true; 
}

template<class T>
Bignum crnum(T x)
{
	Bignum z;
	z.equal(x);
	return z;
}
Bignum operator+(Bignum x,Bignum y)
{
	int i;
	Bignum z;
	z.clear();
	z.len=max(x.len,y.len)+1;
	int tmp=0;
	for(i=1;i<=z.len;i++) {
		z.a[i]=x.a[i]+y.a[i]+tmp;
		tmp=z.a[i]/10;
		z.a[i]=z.a[i]%10;
	}
	while(z.len>1&&z.a[z.len]==0) z.len--;
	return z;
}
Bignum operator-(Bignum x,Bignum y)
{
	Bignum z;
	z.clear();
	z.len=x.len;
	for(int i=1;i<=x.len;i++) {
		if(x.a[i]<y.a[i]) 
			x.a[i]+=10,x.a[i+1]--;
		z.a[i]=x.a[i]-y.a[i];
	}
	while(z.len>1&&z.a[z.len]==0) z.len--;
	return z;
}
Bignum operator*(Bignum x,Bignum y)
{
	int i,j;
	Bignum z;
	z.clear();
	int tmp=0;
	for(i=1;i<=x.len;i++) {
		for(j=1;j<=y.len;j++) {
			z.a[i+j-1]+=x.a[i]*y.a[j]+tmp;
			tmp=z.a[i+j-1]/10;
			z.a[i+j-1]=z.a[i+j-1]%10;
		}
		z.a[i+y.len]+=tmp;
		tmp=0;
	}
	z.len=x.len+y.len;
	while(z.len>1&&z.a[z.len]==0) z.len--;
	return z;
}
Bignum operator<<(Bignum x,int y)
{
	int i;
	for(i=x.len;i>=1;i--) 
		x.a[i+y]=x.a[i];
	x.len+=y;
	for(i=1;i<=y;i++) 
		x.a[i]=0;
	return x;
}
Bignum operator/(Bignum x,Bignum y)
{
	int i;
	Bignum z,tmp;
	z.clear(); tmp.clear();
	z.len=x.len-y.len+1;
	for(i=z.len;i>=0;i--) {
		tmp.clear();
 		tmp=y;
		tmp=tmp<<i;
		while(x>=tmp) {
			z=z+(crnum(1)<<i);
			x=x-tmp;
		}
	}
	while(z.len>0&&z.a[z.len]==0) 
		z.len--;
	return z;
}
Bignum operator%(Bignum x,Bignum y) 
{
	Bignum z;
	z.clear();
	z=x-(x/y)*y;
	return z;
}
}
using namespace _Bignum;
int main()
{
	Bignum x,y,z;
	x.input();
	y.input();
	z=x+y;
	z.output();
	return 0;
}
