#include<cstdio>
#include<iostream>
typedef long long LL;
typedef unsigned long long ULL;
using namespace std;
int n;
int main()
{
	int i;
	cin>>n;
	int ans=0;
	for(i=1;i<=n;i++) 
		ans+=n/i;
	cout<<ans;
	return 0;
}


