#include<cstdio>
#include<iostream>
#define LL long long
using namespace std;
LL n,k;
LL ans=0;
int main()
{
//	freopen("1.in","r",stdin);
	int i,j,t;
	int x,y,z;
	cin>>n>>k;
	LL end=min(k,n);	
	for(i=1;i<=end;i=j+1) {
		t=k/i; j=k/t;
		if(j>end) 
			j=end;
		ans+=(k%i+k%j)*(j-i+1)/2;
	}
	if(n>k) 
		ans+=(n-k)*k;
	cout<<ans;
	return 0;
}

