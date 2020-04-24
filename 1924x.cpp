#include<cstdio>
#include<iostream>
#define LL long long
using namespace std;
LL f[20]={0ll,1ll,2ll,5ll,14ll,42ll,132ll,429ll,1430ll,4862ll,16796ll,58786ll,208012ll,742900ll,2674440ll,9694845ll,35357670ll,129644790ll,477638700ll,};
int main()
{
	int n;
	cin>>n;
	cout<<f[n];
	return 0;
}

