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
			a[i]=_ch[len-i+1];
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
	while(z.a[z.len]==0) z.len--;
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
	while(z.a[z.len]==0) z.len--;
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
const int N=256;
int c[N];
int a[N];
int n,m;
Bignum cmax;
void calc()
{
	Bignum tmp,res;
	tmp.equal(1);
	res.equal(0);
	int i,j;
	for(i=1;i<=m+1;i++) {
		res.equal(0);
		for(j=a[i-1]+1;j<=a[i];j++) {
			res=res*(create_num(10))+create_num(c[j]);
		}
		tmp=tmp*res;
	}
	if(tmp>cmax) 
		cmax=tmp;
	return;
}
void dfs(int step)
{
	for(int i=a[step-1]+1;i<=n-1;i++) {
		a[step]=i;
		if(step==m) calc();
		else dfs(step+1);
		a[step]=0;
	}
	return;
}
int main()
{
//	freopen("1.in","r",stdin);
	int i,j;
	int x,y,z;
	char inc;
	scanf("%d%d",&n,&m);
	for(i=1;i<=n;i++) {
		cin>>inc;
		c[i]=inc-'0';
	}
	a[m+1]=n;
	dfs(1);
	cmax.put();
	return 0;
}
