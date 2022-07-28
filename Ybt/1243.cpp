#include<iostream>
#include<cstring>
#include<cstdio>
#include<cmath>
#include<cstdlib>
#include<algorithm>
using namespace std;
long long n,m;
long long a[100005];
bool check(long long t)
{
	long long s=0,tot=0;//register
	for(long long i=1;i<=n;i++) {
		if(s+a[i]>t) {
			s=0; tot++; i--;
			if(tot>m) return false;
			continue;
		}
		s+=a[i];
	}
	if(s!=0) tot++;
	if(tot>m) return false;
	return true;
}
//bool check(long long mid)
//{
//	long long s=0,ans=0;
//	for(int i=1;i<=n;i++) {
//		s+=a[i];
//		if(s>mid) { s=0; ans++; i--; }
//		if(ans>m) return false;
//	}		
//	if(s!=0) ans++;
//	if(ans>m) return false;
//	return true;		
//}		
int main()
{
//	freopen("1.in","r",stdin);
	
	int i,j;
	cin>>n>>m;
	for(i=1;i<=n;i++) scanf("%d",&a[i]);
	
	long long left=1,right=1e10+5,mid;
	while(left+1<right) {
		mid=(left+right)/2;
		if(check(mid)) right=mid;
		else left=mid;
	}
	cout<<right;
	
	return 0;
}

