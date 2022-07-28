#include<cstdio>
#include<iostream>
#define ULL long long
#define rint register int  
using namespace std;
char _c;
bool _sign;
template<class T>
inline void read(T &x)
{
	x=0;
	_sign=false;
	for(_c=getchar();_c<'0'||_c>'9';_c=getchar()) 
		if(_c=='-') 
			_sign=true;
	for(;_c>='0'&&_c<='9';_c=getchar()) 
		x=(x<<1)+(x<<3)+(_c&15);
	if(_sign) x=~x+1;
	return;
}
ULL gcd(ULL a,ULL b)
{
	if(b==0) 
		return a;
	return gcd(b,a%b);
}
int main()
{
	rint i;
	rint t;
	register ULL a,b,k;
	register ULL x;
	read(t);
	for(i=1;i<=t;i++) {
		read(a); read(b); read(k);
		if(k==1ll) {
			puts("No");
			continue;
		} 
		if(a>b) swap(a,b);
		x=gcd(b,a);
		if(a*(k-1ll)+2ll*(x-1ll)+1ll<b) 
			puts("No");
		else puts("Yes");
	}
	return 0;
}
