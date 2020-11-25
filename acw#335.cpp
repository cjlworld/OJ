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
#include<iostream>
#include<algorithm>

using namespace std;
typedef long long LL;
typedef long double LD;
typedef unsigned long long ULL;

const int N=1e6+5;

int n;
LL A,B,C;
LL s[N],f[N];
// f[j]-A*s[j]*s[j]-B*s[j]+C = (2*A*s[i]) * (s[j]) + (f[i]-A*s[i]*s[i]-B*s[i]);
// y=kx+b, k= 2*A*s[i] 单调递减。
// max ---> 维护一个上凸包 ---> 两点斜率单调递减。

inline LD X(int j) { return s[j]; }
inline LD Y(int j) { return f[j]+A*s[j]*s[j]-B*s[j]+C; }
inline bool cmp(int i,int j,int k)
{
	return (Y(j)-Y(i))*(X(k)-X(j))<=(X(j)-X(i))*(Y(k)-Y(j));
}

int q[N];

int main()
{
//	freopen("1.in","r",stdin);
	int i,j;
	
	scanf("%d%lld%lld%lld",&n,&A,&B,&C);
	for(i=1;i<=n;i++) {
		scanf("%lld",&s[i]);
		s[i]+=s[i-1];
	}
	
	int hh=0,tt=0;
	q[hh]=0; 
	for(i=1;i<=n;i++) {
		while(hh<tt && Y(q[hh]+1)-Y(q[hh])>=2*A*s[i]*(X(q[hh+1])-X(q[hh]))) hh++;
		j=q[hh]; 
		f[i]=f[j]+A*(s[i]-s[j])*(s[i]-s[j])+B*(s[i]-s[j])+C;
		while(hh<tt&&cmp(q[tt-1],q[tt],i)) tt--;
		q[++tt]=i;
	}
	
	printf("%lld\n",f[n]);
	return 0;
}
