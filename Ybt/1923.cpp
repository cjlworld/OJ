#include<cstdio>
#include<iostream>
#define LL long long
#define rint register int
using namespace std;
const int N=256;
const LL MOD=10;
const LL M=6e5;
LL a[N];
LL s[N];
int n,m;
LL ans2=0;
LL ans1=1000000000000;
LL tot=0;
void dfs1(int now,int begin,int last,int use,LL tmp)
{
	if(tmp>ans1) 
		return;
	// end
	if(now==begin+n&&use==m-1) {
		tmp=tmp*((s[now-1]-s[last-1]+M)%MOD);
		ans1=min(ans1,tmp);
		return;
	}
	// cut
	// [ ]
	if(use<m-1&&now!=begin+n-1) {
		dfs1(now+1,begin,now+1,use+1,tmp*((s[now]-s[last-1]+M)%MOD));
	}	
	// not cut
	if(m-1-use<=begin+n-now) 
		dfs1(now+1,begin,last,use,tmp);
//	cout<<++tot<<endl;
	return;
}
const LL POW[]={9,81,729,6561,59409,531441,4782969,43046721,387420489};
void dfs2(int now,int begin,int last,int use,LL tmp)
{
	// end
	if(tmp*POW[m-use-1]<=ans2) 
		return;
	if(now==begin+n) {
		tmp=tmp*((s[now-1]-s[last-1]+M)%MOD);
		ans2=max(ans2,tmp);
		return;
	}
	// cut
	// [ ]
	if(use<m-1&&now!=begin+n-1) {
		dfs2(now+1,begin,now+1,use+1,tmp*((s[now]-s[last-1]+M)%MOD));
	}	
	// not cut
	if(m-1-use<=begin+n-now)
		dfs2(now+1,begin,last,use,tmp);
//	cout<<++tot<<endl;
	return;
}
int main()
{
//	freopen("1.in","r",stdin);
	rint i;
	cin>>n>>m;
	for(i=1;i<=n;i++) {
		cin>>a[i];
		a[i]=(a[i]+M)%MOD;
		a[i+n]=a[i];
	}
	for(i=1;i<=2*n;i++) 
		s[i]=s[i-1]+a[i];
	for(i=1;i<=n-1;i++) {
		dfs1(i,i,i,0,1ll);
		dfs2(i,i,i,0,1ll);
	}
	cout<<ans1<<endl<<ans2;
	return 0;
}

