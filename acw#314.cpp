#include<set>
#include<cstdio>
#include<iostream>
typedef long long LL;
typedef unsigned long long ULL;
using namespace std;
const int N=5000+5;
int a[N],f[N];
LL g[N];
int n;
set<int> S;
int main()
{
//	freopen("1.in","r",stdin);
	int i,j;
	scanf("%d",&n);
	for(i=1;i<=n;i++) 
		scanf("%d",&a[i]);
	a[0]=1e9+5;
	for(i=1;i<=n;i++) {
		for(j=0;j<=i-1;j++) 
			if(a[j]>a[i]) 
				f[i]=max(f[i],f[j]+1);
	}
//	for(i=1;i<=n;i++) 
//		cout<<f[i]<<" ";
//	cout<<endl;
//	for(i=2;i<=n;i++) 
//		f[i]=max(f[i],f[i-1]);
	g[0]=1;
	for(i=1;i<=n;i++) {
		S.clear();
		for(j=i-1;j>=0;j--) {
			if(a[i]<a[j]&&f[i]==f[j]+1&&(!S.count(a[j]))) {
				g[i]+=g[j];
				S.insert(a[j]);
			}
		}
	}
	int ans1=0; LL ans2=0;
	for(i=1;i<=n;i++) 
		ans1=max(ans1,f[i]);
	S.clear();
	for(i=n;i>=1;i--) 
		if(f[i]==ans1&&(!S.count(a[i])))
			ans2+=g[i],S.insert(a[i]);
//	cout<<f[n]<<" "<<g[n];
	cout<<ans1<<" "<<ans2;
	return 0;
}

