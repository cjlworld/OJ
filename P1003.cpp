#include<iostream>
#include<iomanip>
#include<cmath>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<cstdlib>
using namespace std;
int a[10001],b[10001],g[10001],k[10001];
int main()
{
//	freopen("1.in","r",stdin);
	int n;
	int i,j;
	int o=-1;
	int x,y;
	cin>>n;
	for(i=1;i<=n;i++) {
		cin>>a[i]>>b[i]>>g[i]>>k[i];
	}
	cin>>x>>y;
	for(i=1;i<=n;i++) {
		if(x>=a[i]&&x<=a[i]+g[i]&&y>=b[i]&&y<=b[i]+k[i])
			o=i;
	}
	cout<<o;
}
