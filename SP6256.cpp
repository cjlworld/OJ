#include<cstdio>
#include<cstring>
#include<iostream>
#define LL long long
using namespace std;
const int N=200000+5;
int a[N],tmp[N];
int T,n;
LL Merge(int l,int r)
{
	if(l==r) return 0;
	int mid=(l+r)>>1;
	LL res=0;
	res+=Merge(l,mid);
	res+=Merge(mid+1,r);
	int i=l,j=mid+1;
	LL ago=0;
	while(i<=mid&&j<=r) {
		if(a[i]>a[j]) 
			j++,ago++;
		else i++,res+=ago;
	}
	while(i<=mid) res+=ago,i++;
	int tot=l-1;
	i=l,j=mid+1;
	while(i<=mid&&j<=r) {
		if(a[i]<a[j]) 
			tmp[++tot]=a[i],i++;
		else tmp[++tot]=a[j],j++;
	}
	while(i<=mid) tmp[++tot]=a[i],i++;
	while(j<=r) tmp[++tot]=a[j],j++;
	for(i=l;i<=r;i++) 
		a[i]=tmp[i];
	return res;
}
int main()
{
//	freopen("1.in","r",stdin);
	int i,j;
	int x,y,z;
	scanf("%d",&T);
	while(T--) {
		scanf("%d",&n);
		memset(a,0,sizeof a);
		memset(tmp,0,sizeof tmp);
		for(i=1;i<=n;i++)
			scanf("%d",&a[i]);
		cout<<Merge(1,n)<<endl;
	}
	return 0;
}

