#include<iostream>
#include<cstdio>
#include<algorithm>
#define LL long long
using namespace std;
const int N=1000+5;
const LL MOD=998244353;
LL gcd(LL a,LL b) //最大公约数 const LL MOD=998244353;
{
	if(b==0) 
		return a;
	return gcd(b,a%b);
}
struct Fraction //分数 
{
	LL a,b;
	void update()
	{
		a=a%MOD;
		b=b%MOD;
		LL k=gcd(a,b);
		a/=k; 
		b/=k;
		return;
	}
};
Fraction operator+(Fraction x,Fraction y)
{
	Fraction z;
	z.a=x.a*y.b+x.b*y.a;
	z.b=x.b*y.b;
	z.update();
	return z;
}
Fraction operator-(Fraction x,Fraction y)
{
	Fraction z;
	z.a=x.a*y.b-x.b*y.a;
	z.b=x.b*y.b;
	z.update();
	return z;
}
Fraction operator*(Fraction x,Fraction y)
{
	Fraction z;
	z.a=x.a*y.a;
	z.b=x.b*y.b;
	z.update();
	return z;
}
Fraction operator/(Fraction x,Fraction y)
{
	Fraction z;
	z.a=x.a*y.b;
	z.b=x.b*y.a;
	z.update();
	return z;
}

int n;
LL a[N];
LL s[N];
Fraction po[N];
LL f[N][N];
Fraction ans,tmp;
Fraction mo; 
inline LL quickpow(LL x,LL k,LL mod)
{
	LL res=1;
	while(k>0) {
		if(k&1) res=res*x%mod;
		x=x*x%mod; k>>=1;
	}
	return res%mod;
}
int main()
{
//	freopen("1.in","r",stdin);
	scanf("%d",&n);
	int i,j;
	for(i=1;i<=n;i++) 
		scanf("%lld",&a[i]);
	sort(a+1,a+n+1);
	for(i=n;i>=0;i--) 
		s[i]=(s[i+1]+a[i+1])%MOD;
	for(i=1;i<=n-1;i++) {
		po[i].a=s[i];
		po[i].b=n-i;
		po[i].update();
	}
	po[n].a=(s[0]-a[n])%MOD;
	po[n].b=n-1;
	po[n].update();
	f[0][0]=1;
	for(i=1;i<=n-1;i++) {
		ans.a=0;
		ans.b=1;
		mo.a=1;
		mo.b=0;
		for(j=1;j<=n;j++) 
			f[i][j]=(f[i][j-1]+f[i-1][j-1])%MOD,mo.b=(mo.b+f[i][j])%MOD;
		for(j=1;j<=n;j++) {
			if(f[i][j]==0) continue;
			tmp.a=f[i][j];
			tmp.b=1;
			ans=ans+tmp*po[j];
		}
		ans=ans*mo;
		if(ans.b==1) 
			printf("%lld ",ans.a%MOD);
		else printf("%lld ",((ans.a%MOD)*quickpow(ans.b,MOD-2,MOD)%MOD)%MOD);
//		printf("%lld/%lld ",ans.a,ans.b);
	}
//	puts("");
//	for(i=1;i<=n;i++) {
//		printf("%lld/%lld ",po[i].a,po[i].b);
//	}
//	puts("");
//	for(i=1;i<=n-1;i++) {
//		for(j=0;j<=n;j++) {
//			printf("%lld ",f[i][j]);
//		}
//		puts("");
//	}
	return 0;
}
