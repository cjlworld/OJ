#include<cstdio>
#include<cstring>
#include<iostream>
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
const int _N=27;
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
//==================================
template<class T>
inline void read(T &x)
{
	x=0;
	char c;
	bool sign=false;
	for(c=getchar();c<'0'||c>'9';c=getchar()) 
		if(c=='-') 
			sign=true;
	for(;c>='0'&&c<='9';c=getchar()) 
		x=x*10+(c&15);
	if(sign) x=~x+1;
	return;
}
//===================
const int N=1e6+5;
const LL INF=1e18;
LL a[N];
LL f[N];
Bignum s[N];
int n;
Bignum MOD;
LL sum;
Bignum ans;
bool sign[N];
bool flag=false;
inline Bignum add(bool ff,Bignum x,LL y,bool &ss)
{
	Bignum z;
	bool d=false;
	z.clear();
	if(y<0) d=true,y=-y;
	z.equal(y);
	if(ff==false&&d==false) {
		ss=false;
		return x+z;
	}
	if(ff==false&&d==true) {
		if(x>=z) {
			ss=false;
			return x-z;
		}
		else {
			ss=true;
			return z-x;
		}
	}
	if(ff==true&&d==false) {
		if(z>=x) {
			ss=false;
			return z-x;
		}
		else {
			ss=true;
			return x-z;
		}
	}
	if(ff==true&&d==true) {
		ss=true;
		return x+z;
	}
	return crnum(0);
}
int main()
{
//	freopen("1.in","r",stdin);
	int i;
	read(n); MOD.input();
	for(i=1;i<=n;i++) 
		read(a[i]);
	f[0]=-INF;
	for(i=1;i<=n;i++) {
		f[i]=max(f[i-1],a[i]);
		f[i]=max(f[i],sum+a[i]);
		sum=max(a[i],sum+a[i]);
	}
	if(f[1]<0) {
		s[1].equal(-f[1]);
		sign[1]=true;
		flag=true;
	}	
	else s[1].equal(f[1]);
	ans=s[1]+s[1];
	Bignum tmp;
	bool ff;
	tmp.clear();
	for(i=2;i<=n;i++) {
		s[i]=ans;
		sign[i]=flag;
		tmp=add(flag,s[i],f[i],ff);
		if(flag&&ff) 
			ans=min(ans,tmp);
		else if(flag&&ff==false) 
			ans=tmp,flag=false;
		else if(flag==false&&ff==false) 
			ans=max(ans,tmp);
	}
	ans=s[1];
	flag=sign[1];
	for(i=2;i<=n;i++) {
		tmp=s[i];
		if(flag&&sign[i]) {
			ans=min(ans,tmp);
		}
		else if(flag&&sign[i]==false) 
			ans=tmp,flag=false;
		else if(flag==false&&sign[i]==false) 
			ans=max(ans,tmp);
	}
	ans=ans%MOD;
	if(flag) putchar('-');
	ans.output();
	return 0;
}

