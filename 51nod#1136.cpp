#include<cmath>
#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>

using namespace std;
typedef long long LL;

int n;
int phi(int n)
{
	int res=n;
	for(int i=2;i*i<=n;i++) {
		if(n%i==0) {
			res=res/i*(i-1);
			while(n%i==0) n/=i;
		}
	}
	if(n>1) res=res/n*(n-1);
	return res;
}

int main()
{
//	freopen("1.in","r",stdin);
	cin>>n;
	cout<<phi(n);
	return 0;
}

