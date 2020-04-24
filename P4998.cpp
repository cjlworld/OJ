#include<bits/stdc++.h>
using namespace std;
const int N=10000005;
const int MM=1e5;
int n,k;
int a[N];
long long f[N],s1[N],g[N],s2[N];
long long ans;
int m=1e6+1e6;
void Init()
{
	cin>>n>>k;
	int x;
	for(register int i=1;i<=n;i++) { 
		scanf("%d",&x); 
//		if(x>m) m=x; 
		a[x+MM]++;
	}
	return;
}
void pre_deal()
{
	for(register int i=1;i<=m;i++) {
		s1[i]=s1[i-1]+a[i];
	}
	for(register int i=m;i>=1;i--) {
		s2[i]=s2[i+1]+a[i];
	}
	for(register int i=1;i<=m;i++) {
		f[i]=f[i-1]+s1[i-1];
	}
	for(register int i=m;i>=1;i--) g[i]=g[i+1]+s2[i+1];
    for(register int i=1;i<=m;i++) f[i]+=g[i];
	sort(f+1,f+m+1);
	ans=0;
	for(int i=1;i<=k;i++) ans+=f[i];
	cout<<ans;
}
int main()
{
//	freopen("1.in","r",stdin);
	Init();
	pre_deal();
	return 0;
}


