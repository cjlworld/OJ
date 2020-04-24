#include<cstdio>
#include<iostream>
#include<algorithm>
#define LL long long
using namespace std;
const int N=1e5+5;
const LL MOD=99999997;
int n;
LL a[N],b[N],e[N],t[N];
struct numline
{
	LL num;
	int o;
};
numline c[N],d[N];
inline bool cmp(const numline &a,const numline &b)
{
	return a.num<b.num;
}
LL tmp[N];
LL Merge(int l,int r)
{
	if(l==r) return 0;
	int mid=(l+r)>>1;
	LL res=0;
	res=(res+Merge(l,mid))%MOD;
	res=(res+Merge(mid+1,r))%MOD;
	int i=l,j=mid+1,tot=l-1;
	int ago=0;
	while(i<=mid&&j<=r) {
		if(a[i]>a[j]) {
			ago++;
			j++;
		}
		else res=(res+ago)%MOD,i++;
	}
	while(i<=mid) res=(res+ago)%MOD,i++;
	i=l,j=mid+1;
	while(i<=mid&&j<=r) {
		if(a[i]>a[j]) 
			tmp[++tot]=a[j],j++;
		else tmp[++tot]=a[i],i++;
	}
	while(i<=mid) tmp[++tot]=a[i],i++;
	while(j<=r) tmp[++tot]=a[j],j++;
	for(i=l;i<=r;i++) 
		a[i]=tmp[i];
	return res;
}
void print(numline *arr)
{
	int i;
	putchar('\n');
	for(i=1;i<=n;i++)
		cout<<arr[i].num<<" ";
	putchar('\n');
	for(i=1;i<=n;i++) 
		printf("%d ",arr[i].o);
	puts("");
	return;
}
int main()
{
//	freopen("1.in","r",stdin);
	scanf("%d",&n);
	int i,j,k;
	for(i=1;i<=n;i++) {
		scanf("%lld",&a[i]);
		c[i].num=a[i];
		c[i].o=i;
	}
	for(i=1;i<=n;i++) {
		scanf("%lld",&b[i]);
		d[i].num=b[i];
		d[i].o=i;
	}
	sort(c+1,c+n+1,cmp);
	sort(d+1,d+n+1,cmp);
//	print(c);
//	print(d);
	for(i=1;i<=n;i++) {
		e[d[i].o]=c[i].num;
	}	
//	puts("");
//	for(i=1;i<=n;i++) 
//		printf("%d ",e[i]);
//	puts("");
	for(i=1;i<=n;i++) {
		c[i].num=a[i];
		c[i].o=i;
	}
	sort(c+1,c+n+1,cmp);
	for(i=1;i<=n;i++) {
		a[i]=c[i].num;
		b[i]=c[i].o;
	}
	for(i=1;i<=n;i++) {
		int x=lower_bound(a+1,a+n,e[i])-a;
		t[b[x]]=i;
	}
//	puts("");
//	for(i=1;i<=n;i++) 
//		printf("%d ",t[i]);
//	puts("");
	for(i=1;i<=n;i++) 	
		a[i]=t[i];
	cout<<Merge(1,n)%MOD;
	return 0;
}

