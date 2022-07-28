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

const int N=256;

int n,m;
int a[N],b[N];
int ans;

int calc()
{
	int res=0;
	for(int i=1;i<=m;i++) {
		res+=a[i]+b[i];
		if(a[i]==10 && b[i]==0) 
			res+=a[i+1]+b[i+1];
		else if(a[i]+b[i]==10)
			res+=a[i+1];
	}
	ans=max(ans,res);  // 2.
	return res;
}

void SA()
{
	int cur=calc(),nw,dt;
	for(double t=1e4;t>1e-4;t*=0.99) { // 5.
		int x=rand()%m+1,y=rand()%m+1;
		if(x==y || (a[x]==10 && x==n && m>n) || (a[y]==10 && y==n && m>n))
			continue;

		swap(a[x],a[y]),swap(b[x],b[y]);
		nw=calc();
		dt=nw-cur; // 4.
		
		if(exp(dt/t)*RAND_MAX>rand())  cur=nw; // 3. 
		else swap(a[x],a[y]),swap(b[x],b[y]);
	}
}

int main()
{
//	freopen("1.in","r",stdin);
	srand((unsigned) time(0)); // 1.
	
	cin>>n;
	for(int i=1;i<=n;i++) 
		cin>>a[i]>>b[i];
	if(a[n]==10 && b[n]==0) m=n+1,cin>>a[m]>>b[m];
	else m=n;
	
	while(clock()<0.8*CLOCKS_PER_SEC) SA(); // 6.
	cout<<ans<<endl;
	return 0;
}

