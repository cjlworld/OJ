#include<cstdio>
#include<iostream>
#include<cstring>
#define LL long long
using namespace std;
const int N=1e7+5;
LL f[256][256];
LL dim[256];
LL dp(int k,LL last,bool bj)
{
	if(bj==false&&f[k][last]!=-1) 
		return f[k][last];
	if(k==0) return 1;
	LL res=0;
	int maxn=bj ? dim[k] : 9;
	for(int i=0;i<=maxn;i++) {
		if(i==4) continue;
		if(i==2&&last==6) 
			continue;
		res+=dp(k-1,i,bj&&i==maxn);
	}
	if(bj) return res;
	else 
		return f[k][last]=res;
}
LL prefix(int x)
{
	int i,j,k;
	int cnt=0,res=0;
	memset(dim,0,sizeof dim);
	while(x) {
		dim[++cnt]=x%10;
		x/=10;
	}
	return dp(cnt,0,true);
}
int main()
{
//	freopen("1.in","r",stdin);
	int n,m;
	while(true) {
		memset(f,-1,sizeof f);
		scanf("%d%d",&n,&m);
		if(n==0&&m==0) break;
		cout<<prefix(m)-prefix(n-1)<<endl;
	}
	return 0;
}

