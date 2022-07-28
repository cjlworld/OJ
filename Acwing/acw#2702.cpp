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
typedef unsigned long long ULL;

const int N=1e5+5;

int p[N],miu[N],sum[N],tot;
bool tag[N];

void prime(int n)
{
	int i,j;
	miu[1]=1;
	for(i=2;i<=n;i++) {
		if(!tag[i]) miu[p[++tot]=i]=-1;
		for(j=1;j<=tot && i*p[j]<=n;j++) {
			tag[i*p[j]]=true;
			if(i%p[j]==0) break;
			miu[i*p[j]]=-miu[i];
		}
	}
	for(i=1;i<=n;i++) 
		sum[i]=sum[i-1]+miu[i];
//	for(i=1;i<=10;i++) 
//		cout<<i<<" : "<<miu[i]<<endl;
}

int Calc(int n,int m)
{
	int i,j;
	int res=0;
	for(i=1;i<=n && i<=m;i=j+1) {
		j=min(n/(n/i),m/(m/i));
		res+=(n/i)*(m/i)*(sum[j]-sum[i-1]);
	}
//	printf("%d %d %d\n",n,m,res);
	return res;
}

int Work(int n,int m,int k) { return Calc(n/k,m/k); }

int main()
{
//	freopen("1.in","r",stdin);
	prime(N-1);
	
	int n,a,b,c,d,k;
	cin>>n;
	while(n--) {
		cin>>a>>b>>c>>d>>k;
		cout<<Work(b,d,k)-Work(b,c-1,k)-Work(a-1,d,k)+Work(a-1,c-1,k)<<endl;
	} 
	return 0;
}

