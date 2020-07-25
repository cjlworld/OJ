#include<cstdio>
#include<iostream>
#include<algorithm>
typedef long long LL;
typedef unsigned long long ULL;
using namespace std;
const int N=2e5+5;
int n,r,q;
struct Node
{
	int mark;
	int force;
	int o;
	friend inline bool operator<(const Node &a,const Node &b)
	{
		return (a.mark>b.mark)||(a.mark==b.mark&&a.o<b.o);
	}
	friend inline bool operator>(const Node &a,const Node &b)
	{
		return !(a<b);
	}
}a[N],tmp[N];
int main()
{
//	freopen("1.in","r",stdin);
	int i,j,tot;
	scanf("%d%d%d",&n,&r,&q);
	for(i=1;i<=n*2;i++) 
		scanf("%d",&a[i].mark),a[i].o=i;
	for(i=1;i<=n*2;i++) 
		scanf("%d",&a[i].force);
	sort(a+1,a+2*n+1);
	while(r--) {
		for(i=1;i<=(n<<1);i+=2) {
			if(a[i].force>a[i+1].force) 
				a[i].mark++;
			else {
				a[i+1].mark++;
				swap(a[i],a[i+1]);
			}
		}
		i=1; j=2; tot=0;
		while(i<=(n<<1)&&j<=(n<<1)) {
			if(a[i]<a[j]) 
				tmp[++tot]=a[i],i+=2;
			else tmp[++tot]=a[j],j+=2;
		}
		while(i<=(n<<1)) tmp[++tot]=a[i],i+=2;
		while(j<=(n<<1)) tmp[++tot]=a[j],j+=2;
		for(i=1;i<=(n<<1);i++) 
			a[i]=tmp[i];
	}
	cout<<a[q].o;
	return 0;
}

