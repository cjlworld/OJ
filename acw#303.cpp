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
typedef double LD;
typedef unsigned long long ULL;

const int N=1e5+5,P=105;

LL f[N][P]; 

LL d[N],a[N],t[N],s[N];
int h[N];
int q[N];

int n,m,p;
int cur;

inline LD X(int j) { return j; }
inline LD Y(int j) { return f[j][cur]+s[j]; }
inline bool comp(int i,int j,int k)
{
	return (Y(j)-Y(i))*(X(k)-X(j))>=(Y(k)-Y(j))*(X(j)-X(i));
}

int main()
{
//	freopen("1.in","r",stdin);
	int i,j,k;
	scanf("%d%d%d",&n,&m,&p);
	for(i=2;i<=n;i++) {
		scanf("%lld",&d[i]);
		d[i]+=d[i-1];
	}
	for(i=1;i<=m;i++) {
		scanf("%d%lld",&h[i],&t[i]);
		a[i]=t[i]-d[h[i]];
	} 
	sort(a+1,a+m+1);
	for(i=1;i<=m;i++) 
		s[i]=s[i-1]+a[i];
	
	memset(f,0x3f,sizeof f);
	f[0][0]=0;
	int hh,tt;
	for(cur=0,j=1;j<=p;cur++,j++) {
		q[hh=tt=0]=0;
		
		for(i=1;i<=m;i++) {
			while(hh<tt && Y(q[hh+1])-Y(q[hh])<=a[i]*(X(q[hh+1])-X(q[hh]))) hh++;
			k=q[hh];
			f[i][j]=f[k][j-1]+(i-k)*a[i]-s[i]+s[k];
			while(hh<tt && comp(q[tt-1],q[tt],i)) tt--;
			q[++tt]=i;
		}
	}
	
	printf("%lld\n",f[m][p]);
	return 0;
}

