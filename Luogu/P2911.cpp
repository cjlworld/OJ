#include<set>
#include<map>
#include<queue>
#include<stack>
#include<cmath>
#include<ctime>
#include<bitset>
#include<vector>
#include<cstdio>
#include<complex>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>

using namespace std;
typedef long long LL;
typedef unsigned long long ULL;

const int N=1e5+5;

int cnt[N];
int main()
{
//	freopen("1.in","r",stdin);
	int a,b,c;
	int i,j,k;
	
	cin>>a>>b>>c;
	for(i=1;i<=a;i++) 
		for(j=1;j<=b;j++) 
			for(k=1;k<=c;k++) 
				cnt[i+j+k]++;
				
	int ans=0;
	for(i=1;i<=a+b+c;i++) 
		if(cnt[i]>cnt[ans]) ans=i;
	cout<<ans<<endl;
	return 0;
}

