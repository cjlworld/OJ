#include<cstdio>
#include<iostream>
typedef long long LL;
using namespace std;
const int N=1025;
char a[N];
int s[N];
struct Node
{
	int lc,rc;
	char C;
}t[4*N];
int cnt=0;
int build(int l,int r)
{
	int now=++cnt;
	if(s[r]-s[l-1]==0) t[now].C='B';
	else if(s[r]-s[l-1]==r-l+1) t[now].C='I';
	else t[now].C='F';
	if(l==r) 
		return now;
	int mid=(l+r)>>1;
	t[now].lc=build(l,mid);
	t[now].rc=build(mid+1,r);
	return now;
}
void lrd(int now)
{
	if(now==0) 
		return;
	lrd(t[now].lc);
	lrd(t[now].rc);
	cout<<t[now].C;
	return;
}
int main()
{
	int i;
	int n;
	cin>>n; n=1<<n;
	scanf("%s",a+1);
	for(i=1;i<=n;i++) 
		s[i]=s[i-1]+(a[i]-'0');
	build(1,n);
	lrd(1);
	return 0;
}


