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

const int N=1e6+5;

int pm[N],tot;
bool tag[N];
void prime(int n)
{
	int i,j;
	for(i=2;i<=n;i++) {
		if(!tag[i]) pm[++tot]=i;
		for(j=1;j<=tot && pm[j]*i<=n;j++) {
			tag[i*pm[j]]=true;
			if(i%pm[j]==0) break;
		}
	}
}

void divide(int x,vector<int>& v)
{
	v.clear();
	for(int i=1;i<=tot && pm[i]*pm[i]<=x;i++) {
		if(x%pm[i]==0) {
			v.push_back(pm[i]);
			while(x%pm[i]==0) x/=pm[i];
		}
	}
	if(x>1) v.push_back(x); 
}

int varphi(int x)
{
	vector<int> v;
	divide(x,v);
	int res=x;
	for(int i=0;i<(int)v.size();i++) 
		res=res/v[i]*(v[i]-1);
	return res;
}

LL power(LL x,LL k,LL MOD)
{
	LL res=1; x%=MOD;
	while(k) {
		if(k&1) res=res*x%MOD;
		x=x*x%MOD; k>>=1;
	}
	return res%MOD;
}

LL gcd(LL a,LL b)
{
	if(b==0) return a;
	else return gcd(b,a%b);
}

int T;
LL g,p;
int d;
vector<LL> rt;

int main()
{
//	freopen("1.in","r",stdin);
	int i;
	cin>>T;
	
	prime(N-1);
	while(T--) {
		cin>>p>>d;
		vector<int> v;
		int phi=varphi(p);
		divide(phi,v);
		for(g=1;g<=p-1;g++) {
			if(gcd(g,p)>1) continue;
			for(i=0;i<(int)v.size();i++) 
				if(power(g,phi/v[i],p)==1) break;
			if(i==(int)v.size()) break;
		}
		if(g==p) { // 找不到原根。 
			puts("0\n");
			continue;
		}
		rt.clear();
		for(i=1;i<=phi;i++) 
			if(gcd(i,phi)==1) 
				rt.push_back(power(g,i,p));
		
		sort(rt.begin(),rt.end());
		printf("%llu\n",rt.size());
		for(i=d-1;i<(int)rt.size();i+=d)
			printf("%lld ",rt[i]);
		puts("");
	}
	return 0;
}

