#include<cmath>
#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>

using namespace std;
typedef long long LL;

const int N=1e6+5;

int n,m;
int cnt[N];

int main()
{
//	freopen("1.in","r",stdin);
	int i,j;
	int x;
	
	scanf("%d",&n);
	for(i=1;i<=n;i++) {
		scanf("%d",&x);
		cnt[x]++;
		m=max(m,x);
	}
	
	int ans=0;
	for(i=1;i<=m;i++) {
		x=0;
		for(j=i;j<=m;j+=i) 
			x+=cnt[j];
		if(x>=2) ans=max(ans,i);
	}
	cout<<ans<<endl;
	return 0;
}

