#include<iostream>
#include<cstdio>
#define LL long long
#define INF 0x3f3f3f3f3f
using namespace std;
const int L=100;
LL gcd(LL a,LL b) //最大公约数 
{
	if(b==0) 
		return a;
	return gcd(b,a%b);
}
LL lcm(LL a,LL b) //最小公倍数 
{
	return a*b/gcd(a,b);
}
struct Fraction //分数 
{
	LL a,b;
	void update()
	{
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
bool operator<(Fraction x,Fraction y)
{
	return x.a*y.b<y.a*x.b;
}
bool operator<=(Fraction x,Fraction y)
{
	return x.a*y.b<=y.a*x.b;
}
bool operator>(Fraction x,Fraction y)
{
	return x.a*y.b>y.a*x.b;
}
bool operator>=(Fraction x,Fraction y)
{
	return x.a*y.b>=y.a*x.b;
}
bool operator==(Fraction x,Fraction y)
{
	return x.a*y.b==y.a*x.b;
}
Fraction t;
Fraction x,y;
Fraction ans;
Fraction Min,tmp;
int l;
int main()
{
//	freopen("1.in","r",stdin);
	scanf("%lld%lld",&t.a,&t.b);
	t.update();
	scanf("%d",&l);
	Min.a=INF;
	Min.b=1;
	for(int i=1;i<=l;i++) {
		x.a=i;
		for(int j=1;j<=l;j++) {
			x.b=j;
			if(x<t) continue;
			tmp=x-t;
			if(tmp<Min)
				Min=tmp,ans=x;
		}
	}
	ans.update();
	printf("%lld %lld\n",ans.a,ans.b);
	return 0;
}

