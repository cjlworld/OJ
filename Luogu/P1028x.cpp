#include<cstdio>
#include<iostream>
#define LL long long
using namespace std;
const int N=1000+5;
unsigned long long f[N];
unsigned long long count(int x)
{
	if(f[x]) return f[x];
	f[x]=1;
	for(int i=1;i<=x/2;i++) {
		f[x]+=count(i);
	}
	return f[x];
}
int n;
int main()
{
	cin>>n;
	cout<<count(n)<<endl;
	return 0;
}

