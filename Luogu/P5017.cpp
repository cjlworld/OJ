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

const int N=5e6+5;
const LD INF=1e9+5;

int n,m;
int maxt;
int s[N],c[N];
int f[N],ans=INF;

LD X(int j) { return c[j]; }
LD Y(int j) { return f[j]+s[j]; }
//LD slope(int i,int j) { return (X(i)-X(j)==0) ? INF : (LD)(Y(i)-Y(j))/(X(i)-X(j)); }
LD slope(int i,int j) 
{
	if(X(i)==X(j)) return ((Y(j)>Y(i)) ? INF : -INF);
	else return (LD)(Y(i)-Y(j))/(X(i)-X(j));
}

int q[N];
int main()
{
//	freopen("1.in","r",stdin);
	int i,j;
	int x;
	
	cin>>n>>m;
	for(i=1;i<=n;i++) {
		cin>>x,s[x]+=x,c[x]++;
		maxt=max(maxt,x);
	}
	
	for(i=1;i<=maxt+m;i++) 
		s[i]+=s[i-1],c[i]+=c[i-1];
	
	memset(f,0x3f,sizeof f);
	f[0]=0;
	int hh=0,tt=0;
	q[hh]=0;
	for (i=1; i<m; i++ ) f[i]=c[i]*i-s[i];
	for(i=m;i<=maxt+m;i++) {
		while(hh<tt&&slope(q[hh],q[hh+1])<=1.0*i) hh++;
		j=q[hh];
//		cerr<<i<<" "<<j<<" : ";
		f[i]=f[j]+(c[i]-c[j])*i-(s[i]-s[j]);
		
//		cerr<<f[i]<<endl;
		j=i+1-m;
		while(hh<tt&&slope(q[tt-1],q[tt])>=slope(q[tt],j)) tt--;
		q[++tt]=j;
		
		if(i>=maxt) ans=min(ans,f[i]); 
	}
	cout<<ans<<endl;
	return 0;
}

