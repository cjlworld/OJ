#include<cstdio>
#include<iostream>
using namespace std;
const int N=1024;
struct kk
{
	int a,b;
	int o;
}c[N];
int n;
int f[N],s[N];
int main()
{
	int i,j;
	cin>>n;
	for(i=1;i<=n;i++) cin>>c[i].a;
	for(i=1;i<=n;i++) cin>>c[i].b,c[i].o=i;
	for(i=1;i<=n;i++) 
		for(j=1;j<=n-i;j++) 
			if(min(c[j+1].a,c[j].b)<=min(c[j].a,c[j+1].b)) 
				swap(c[j],c[j+1]);
	for(i=1;i<=n;i++) 
			s[i]=s[i-1]+c[i].a;
	for(i=1;i<=n;i++) 
			f[i]=max(s[i],f[i-1])+c[i].b;
	
	cout<<f[n]<<endl;
	for(i=1;i<=n;i++) 
		cout<<c[i].o<<" ";
	return 0;
}

