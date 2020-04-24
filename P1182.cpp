#include<bits/stdc++.h>
using namespace std;
long long n,r;//n-ÊýÁ¿,r-¶Î;
long long a[100005]; 
bool check(long long t)
{
	long long s=0,tot=0;//register
	for(long long i=1;i<=n;i++) {
		if(s+a[i]>t) {
			s=0; tot++; i--;
			if(tot>r) return false;
			continue;
		}
		s+=a[i];
	}
	if(s!=0) tot++;
	if(tot>r) return false;
	return true;
}
void work()
{
	cin>>n>>r;//register 
	for(long long i=1;i<=n;i++) scanf("%d",&a[i]);
	long long right=1e9+1,left=1,mid;
	while(left+1<right) {
		mid=(right+left)/2;
		if(check(mid)) right=mid;
		else left=mid;
	}
	cout<<right;
	return;
}
int main()
{
//	freopen("1.in","r",stdin);
	work();
	return 0;
}

