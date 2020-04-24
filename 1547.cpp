#include<iostream>
#include<cstdio>
using namespace std;
long long n,m;
const int N=500000+5;
long long c[N];
inline int lowbit(int n) 
{
	return n&(-n);
} 
inline void update(long long x,long long y)
{
	for(;x<=n;x+=lowbit(x)) c[x]+=y;
}
inline long long sum(long long x)
{
	long long res=0;
	for(;x;x-=lowbit(x)) res+=c[x];
	return res;
}
/*��һ��2������n,m(n��ʾ����n������m��ʾm������
�ڶ���n������
������ÿ��������k,a,b(k=0,��ʾ��������[a,b]�������ͣ�k=1,��ʾ��a������b)��*/ 
int main()
{
//	freopen("1.in","r",stdin);
	scanf("%lld %lld",&n,&m);
	long long opt,x,k;
	long long a,b;
	for(register long long i=1;i<=m;i++) {
		scanf("%lld%lld%lld",&opt,&a,&b);
		if(opt) printf("%lld\n",sum(b)-sum(a-1));
		else update(a,b);
	}
	return 0;
}
