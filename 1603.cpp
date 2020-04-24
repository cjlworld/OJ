#include<cstdio>
#include<iostream>
#include<cstring>
#define LL long long
using namespace std;
const int N=5e4+5;
int a[N];
int n,t;
int q[3*N],num[3*N];
int f[N]; //min t in(copy homework i)
//f[i] = a[i]+min(f[i-k-1]...f[i-1]);
bool check(int k)
{
	memset(q,0,sizeof(q));
	memset(num,0,sizeof(num));
	memset(f,0,sizeof(f));
	int head=1,tail=0;
	int i,j;
	for(i=0;i<=n;i++) {
		while(head<=tail&&num[head]<i-k-1) head++;
		f[i]=a[i]+q[head];
		while(head<=tail&&f[i]<=q[tail]) q[tail]=0,num[tail]=0,tail--;
		tail++;
		q[tail]=f[i];
		num[tail]=i;
	}
	int res=1e9;
	for(i=n-k;i<=n;i++) 
		res=min(res,f[i]);
	if(res>t) return false;
	return true;
}
int main()
{
//	freopen("1.in","r",stdin);
	int i,j;
	scanf("%d%d",&n,&t);
	for(i=1;i<=n;i++) 
		scanf("%d",&a[i]);
	int L=0,R=n+5,mid;
	while(L+1<R) {
		mid=(L+R)>>1;
		if(check(mid)) R=mid;
		else L=mid;
	}
	cout<<R;
	return 0;
}

