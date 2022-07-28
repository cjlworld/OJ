#include<cstdio>
#include<vector>
#include<iostream>
#define LL long long
using namespace std;
inline void _readin(int *arr,int len)
{
	register char c;
	for(register int i=1;i<=len;i++) {
		for(c=getchar();c<'A'||c>'Z';c=getchar());
		arr[i]=c-'A'+1;
	}
	return;
}
const int N=1e6+5;
int n;
int a[N],b[N];
vector<int> v[28];
int cnt[28];
int pri[N];
int tmp[N];
LL Inverse(int *arr,int l,int r)
{
	if(l==r) 
		return 0ll;
	int mid=(l+r)>>1;
	LL res=Inverse(arr,l,mid)+Inverse(arr,mid+1,r);
	int i=l,j=mid+1;
	int tot=l-1;
	LL ago=0ll;
	while(i<=mid&&j<=r) {
		if(arr[i]>arr[j])
			ago++,j++;
		else res+=ago,i++;
	}
	while(i<=mid) res+=ago,i++;
	i=l,j=mid+1;
	while(i<=mid&&j<=r) {
		if(arr[i]<arr[j]) 
			tmp[++tot]=arr[i],i++;
		else tmp[++tot]=arr[j],j++;
	}
	while(i<=mid) tmp[++tot]=arr[i],i++;
	while(j<=r) tmp[++tot]=arr[j],j++;
	for(i=l;i<=r;i++) 
		arr[i]=tmp[i];
	return res;
}
int main()
{
//	freopen("1.in","r",stdin);
	int i,j;
	int x,y,z;
	char c;
	scanf("%d",&n);
	_readin(a,n);
	_readin(b,n);
	for(i=1;i<=n;i++) 
		v[b[i]].push_back(i);
	for(i=1;i<=n;i++) 
		pri[i]=v[a[i]][cnt[a[i]]++];
	cout<<Inverse(pri,1,n);
	return 0;
}

