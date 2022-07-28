#include<cmath>
#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;
const int N=1024;
struct kk
{
	int a,b,d;
	int o;
	friend bool operator<(const kk &x,const kk &y)
	{
		if(x.d==y.d) {
			if(x.d==-1) return x.a<y.a;
			else if(x.d==1) return x.b>y.b;
			else return x.o<y.o;
		}
		else return x.d<y.d;
	}
}c[N];
int n;
int f[N],s[N];
int main()
{
//	freopen("1.in","r",stdin);
	int i;
	cin>>n;
	for(i=1;i<=n;i++) cin>>c[i].a;
	for(i=1;i<=n;i++) cin>>c[i].b,c[i].o=i,c[i].d=(c[i].a-c[i].b==0 ? 0 : (c[i].a-c[i].b)/abs(c[i].a-c[i].b));
	sort(c+1,c+n+1);
	for(i=1;i<=n;i++) 
			s[i]=s[i-1]+c[i].a;
	for(i=1;i<=n;i++) 
			f[i]=max(s[i],f[i-1])+c[i].b;
	cout<<f[n]<<endl;
	for(i=1;i<=n;i++) 
		cout<<c[i].o<<" ";
	return 0;
}

