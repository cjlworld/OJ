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

const int N=20,INF=0x3f3f3f3f;

int n;
int ans=INF;
int a[N];
vector<int> G[N];

int calc()
{
	int res=0;
	for(int i=1;i<=n;i++) 
		for(int j=0;j<3;j++) 
			res+=abs(a[i]-a[G[i][j]]);
	res/=2;
	ans=min(ans,res);
	return res;
}

void SA()
{
	for(int i=1;i<=n;i++) a[i]=i;
	random_shuffle(a+1,a+n+1);
	int cur=calc(),nw,dt;
	for(double t=1e4;t>1e-4;t*=0.99) {
		int x=rand()%n+1,y=rand()%n+1;
		if(x==y) continue;
		swap(a[x],a[y]);
		nw=calc();
		dt=nw-cur;
		if(exp(-dt/t)*RAND_MAX>rand()) cur=nw;
		else swap(a[x],a[y]);
	}
}

int main()
{
//	freopen("1.in","r",stdin);
	int i,j;
	int x;
	
	cin>>n;
	for(i=1;i<=n;i++) {
		for(j=1;j<=3;j++) {
			cin>>x;
			G[i].push_back(x);
		}
	}
	
	while(clock()<0.8*CLOCKS_PER_SEC) SA();
	
	cout<<ans<<endl;
	return 0;
}

