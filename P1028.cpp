#include<cstdio>
#include<iostream>
#define LL long long
using namespace std;
//不作任何处理;
//在它的左边加上一个自然数,但该自然数不能超过原数的一半;
//加上数后,继续按此规则进行处理,直到不能再加自然数为止.
const int N=1000+5;
unsigned long long f[N];
int n;
int main()
{
	scanf("%d",&n);
	int i,j;
	f[0]=1;
	for(i=1;i<=n;i++) {
		if(i&1) f[i]=f[i-1];
		else f[i]=f[i>>1]+f[i-1];
	}
	cout<<f[n];
	return 0;
}

