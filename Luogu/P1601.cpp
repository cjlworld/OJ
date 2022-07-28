#include<iostream>
#include<cstdio>
#include<cstring>
#define LL long long 
using namespace std;
namespace _Bignum
{
const int _N=1024;
char _ch[_N];
struct Bignum
{
	int a[_N];
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
	void put()
	{
		for(int i=len;i>=1;i--) 
			printf("%d",a[i]);
		printf("\n");
		return;
	}
	void get()
	{
		clear();
		scanf("%s",_ch+1);
		len=strlen(_ch+1);
		for(int i=1;i<=len;i++) 
			a[i]=_ch[len-i+1]-'0';
		return;
	}
};
template<class T>
Bignum create_num(T x)
{
	Bignum z;
	z.equal(x);
	return z;
}
Bignum operator+(Bignum x,Bignum y)
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
}
using namespace _Bignum;
#define Bignum _Bignum::Bignum
int main()
{
	Bignum a,b,c;
	a.get(); b.get();
	c=a+b;
	c.put();
	return 0;
}
