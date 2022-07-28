#include<cstdio>
#include<iostream>
#include<algorithm>
typedef long long LL;
typedef unsigned long long ULL;
using namespace std;
const int N=1024;
int n,m,k,l,d;
struct passage
{
	int o;
	int sum;
	inline friend bool operator<(const passage &a,const passage &b)
	{
		return a.sum>b.sum;		
	}	
}a[N],b[N];
inline bool cmp(const passage &a,const passage &b)
{
	return a.o<b.o;
}
int main()
{
//	freopen("1.in","r",stdin);
	int i;
	int x,y,z,r;
	scanf("%d%d%d%d%d",&n,&m,&k,&l,&d);
	for(i=1;i<=max(n,m);i++) 
		a[i].o=i,b[i].o=i;
	for(i=1;i<=d;i++) {
		scanf("%d%d%d%d",&x,&y,&z,&r);
		if(x==z) b[min(y,r)].sum++;
		else a[min(x,z)].sum++;
	}
	sort(a+1,a+n+1);
	sort(b+1,b+m+1);
	sort(a+1,a+k+1,cmp);
	sort(b+1,b+l+1,cmp);
	for(i=1;i<=k;i++) 
		printf("%d ",a[i].o);
	printf("\n");
	for(i=1;i<=l;i++) 
		printf("%d ",b[i].o);
	return 0;
}

