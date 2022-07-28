#include<iostream>

using namespace std;
typedef long long LL;

const LL MOD=10007;
LL n;

int main()
{
	char c;
	while(cin>>c) n=(n*10+c-'0')%MOD;
	cout<<n*(n+1)*(n+2)/6%MOD<<endl;
	return 0;
}

