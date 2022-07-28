#include<set>
#include<map>
#include<queue>
#include<stack>
#include<ctime>
#include<cmath>
#include<bitset>
#include<vector>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<complex>
#include<iostream>
#include<algorithm>

using namespace std;
typedef long long LL;
typedef unsigned long long ULL;

int T;
LL p,a,b,x1,t,q,c1;

LL power(LL x,LL k,LL MOD)
{
	LL res=1; x%=MOD;
	while(k) {
		if(k&1) res=res*x%MOD;
		x=x*x%MOD; k>>=1;
	}
	return res%MOD;
}

LL inv(LL x,LL MOD)
{
	return power(x,MOD-2,MOD);
}

LL bsgs(LL a,LL b,LL p)
{
	if(b%p==1%p) return 0;
	map<LL,LL> mp;
	LL k=sqrt(p)+1,ak=power(a,k,p);
	for(LL i=0,j=b;i<k;i++,j=j*a%p)	mp[j]=i;
	for(LL i=1,j=ak;i<=k;i++,j=j*ak%p)
		if(mp.count(j)) return i*k-mp[j];
	return -2;
}

int main()
{
//	freopen("1.in","r",stdin);
	
	cin>>T;
	while(T--) {
		cin>>p>>a>>b>>x1>>t;
		if(t==x1) printf("1\n");
		else if(a==0) {
			if(t==b) printf("2\n");
			else printf("-1\n");
		}
		else if(a==1) {
			if(b==0) printf("-1\n");
			else printf("%lld\n",((t-x1)*inv(b,p)%p+p)%p+1);
		}
		else {
			q=b*inv(a-1,p)%p;
			c1=(x1+q)%p;
//			printf("p = %lld\n",p);
//			printf("a = %lld\n",a);
//			printf("b = %lld\n",b);
//			printf("x1 = %lld\n",x1);
//			printf("t = %lld\n",t);
//			printf("q = %lld\n",q);
//			printf("c1 = %lld\n",c1);
			printf("%lld\n",bsgs(a,(t+q)%p*inv(c1,p)%p,p)+1);
		}
	}
	return 0;
}
/*
*
*　　┏┓　　　┏┓+ +
*　┏┛┻━━━┛┻┓ + +
*　┃　　　　　　　┃
*　┃　　　━　　　┃ ++ + + +
*  ████━████+
*  ◥██◤　◥██◤ +
*　┃　　　┻　　　┃
*　┃　　　　　　　┃ + +
*　┗━┓　　　┏━┛
*　　　┃　　　┃ + + + +Code is far away from 　
*　　　┃　　　┃ + bug with the animal protecting
*　　　┃　 　 ┗━━━┓ 神兽保佑,代码无bug　
*　　　┃ 　　　　　　 ┣┓
*　　  ┃ 　　　　　 　┏┛
*　    ┗┓┓┏━┳┓┏┛ + + + +
*　　　　┃┫┫　┃┫┫
*　　　　┗┻┛　┗┻┛+ + + +
*/

