#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
typedef long long LL;
typedef unsigned long long ULL;
using namespace std;
namespace _Bignum
{
//char _c;
//inline void reads(char *a)
//{
//	for(_c=getchar();_c<'0'||_c>'9';_c=getchar());
//	for(int i=0;_c>='0'&&_c<='9';_c=getchar(),i++) 
//		a[i]=_c;
//	return;
//}
#define reads(a) scanf("%s",a)
//========================
char _ch[1024];
template<class CFA,int LFA>
struct Bignum
{
	CFA a[LFA];
	int len;
	inline void clear() 
	{
		memset(a,0,sizeof a); len=0;
		return;
	}
	Bignum() { clear(); }
	
	void equal(CFA x) 
	{
		clear();
		for(;x;a[++len]=x%10,x/=10);
		return;
	}
//	Bignum(CFA x) { equal(x); }
	void output()
	{
		if(len==0) putchar('0');
		else for(int i=len;i>=1;i--) 
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
	inline void copy(const Bignum &x,const int &lenx) 
	{
		memcpy(a,x.a,sizeof a);
		len=lenx;
		return; 
	}
	
	friend bool operator<(const Bignum &x,const Bignum &y)
	{
		if(x.len!=y.len) return x.len<y.len;
		for(int i=x.len;i>=1;i--) 
			if(x.a[i]!=y.a[i]) 
				return x.a[i]<y.a[i];
		return false;
	}
	friend bool operator==(const Bignum &x,const Bignum &y)
	{
		if(x.len!=y.len) return false;
		for(int i=x.len;i>=1;i--) 
			if(x.a[i]!=y.a[i]) 
				return false;
		return true;
	}
	friend bool operator!=(const Bignum &x,const Bignum &y) { return (!(x==y)); }
	friend bool operator>(const Bignum &x,const Bignum &y) { return (!(x==y||x<y)); }
	friend bool operator<=(const Bignum &x,const Bignum &y) { return (x<y||x==y); }
	friend bool operator>=(const Bignum &x,const Bignum &y) { return (!(x<y)); }
	
	friend Bignum trnum(CFA x)
	{
		Bignum z; z.clear();
		z.equal(x);
		return z;
	}
	
	friend Bignum operator+(Bignum x,Bignum y)
	{
		Bignum z;
		z.len=max(x.len,y.len)+1;
		CFA tmp=0;
		for(int i=1;i<=z.len;i++) {
			z.a[i]=x.a[i]+y.a[i]+tmp;
			tmp=z.a[i]/10;
			z.a[i]=z.a[i]%10;
		}
		while(z.len>1&&z.a[z.len]==0) z.len--;
		return z;
	}
	friend Bignum operator-(Bignum x,const Bignum &y)
	{
		Bignum z;
		z.len=x.len;
		for(int i=1;i<=x.len;i++) {
			if(x.a[i]<y.a[i]) 
				x.a[i]+=10,x.a[i+1]--;
			z.a[i]=x.a[i]-y.a[i];
		}
		while(z.len>1&&z.a[z.len]==0) z.len--;
		return z;
	}
	friend Bignum operator*(const Bignum &x,const Bignum &y)
	{
		int i,j;
		Bignum z;
		CFA tmp=0;
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
	friend Bignum operator*(const Bignum &x,CFA y)
	{
		Bignum z;
		CFA tmp=0;
		for(int i=1;i<=x.len;i++) {
			z.a[i]=x.a[i]*y+tmp;
			tmp=z.a[i]/10;
			z.a[i]=z.a[i]%10;
		}
		for(z.len=x.len;tmp>0;) {
			z.a[++z.len]=tmp%10;
			tmp=tmp/10;
		}
		return z;
	}
	friend Bignum operator<<(Bignum x,int y)
	{
		int i;
		for(i=x.len;i>=1;i--) x.a[i+y]=x.a[i];
		x.len+=y;
		for(i=1;i<=y;i++) x.a[i]=0;
		return x;
	}
	friend Bignum operator/(Bignum x,const Bignum &y)
	{
		Bignum z,tmp,tmp1;
		z.len=x.len-y.len+1;
		for(int i=z.len;i>=0;i--) {
			tmp=y<<i;
			tmp1.a[i+1]=1; tmp1.len=i;
			while(x>=tmp) {
				z=z+tmp1;
				x=x-tmp;
			}
			tmp1.a[i+1]=0;
		}
		while(z.len>0&&z.a[z.len]==0) z.len--;
		return z;
	}
	friend Bignum operator%(const Bignum &x,const Bignum &y) 
	{
		Bignum z;
		z=x-(x/y)*y;
		return z;
	}
};
}
using namespace _Bignum;
//================================================
using namespace std;
const int N=1000+5;
struct chen
{
	long long a,b,c;
	friend inline bool operator<(const chen &a,const chen &b) 
	{
		return a.c<b.c;
	}
}t[N];
int n;
const int LEN=5000;
Bignum<long long,LEN> a,b;
Bignum<long long,LEN> trans(long long x)
{
	Bignum<long long,LEN> z; z.clear();
	z.equal(x);
	return z;
}
int main()
{
//	freopen("1.in","r",stdin);
	int i;
	scanf("%d",&n);
	a.input(); b.input();
	for(i=1;i<=n;i++) {
		cin>>t[i].a>>t[i].b;
		t[i].c=t[i].a*t[i].b;
	}
	sort(t+1,t+n+1);
	Bignum<long long,LEN> ans,a1=a;
	int p=1;
	for(i=1;i<=n;i++) {
		if(a1*t[i].b<a*t[p].b) 
			a1=a,p=i;
		a=a*t[i].a;

	}
	ans=a1/trans(t[p].b);
//	trans(t[p].b).output();
//	a1.output(); 
//	printf("%lld\n",t[p].b);
	ans.output();
	return 0;
}


