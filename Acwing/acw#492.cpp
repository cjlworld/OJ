#include<set>
#include<map>
#include<queue>
#include<stack>
#include<ctime>
#include<cmath>
#include<bitset>
#include<vector>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>

using namespace std;
typedef long long LL;
typedef unsigned long long ULL;

LL base=1e14,width=14;

vector<LL> add(vector<LL> a,vector<LL> b)
{
	vector<LL> c;
	if(a.size()<b.size()) swap(a,b);
	LL t=0;
	for(int i=0;i<(int)a.size();i++) {
		t+=a[i];
		if(i<(int)b.size()) t+=b[i];
		c.push_back(t%base);
		t/=base;
	}
	if(t) c.push_back(t);
	while(!c.back()&&c.size()>1) c.pop_back();
	return c;
}

vector<LL> mul(vector<LL> a,LL b)
{
	vector<LL> c;
	LL t=0;
	for(int i=0;i<(int)a.size();i++) {
		t+=a[i]*b;
		c.push_back(t%base);
		t/=base;
	}
	while(t) c.push_back(t%base),t/=base;
	while(!c.back()&&c.size()>1) c.pop_back();
	return c;
}

vector<LL> Max(vector<LL> a,vector<LL> b)
{
	if(a.size()<b.size()) return b;
	else if(b.size()<a.size()) return a;
	for(int i=a.size()-1;i>=0;i--) {
		if(a[i]<b[i]) return b;
		else if(a[i]>b[i]) return a;
	}
	return a;
}

const int N=256;
int n,m;
LL a[N];
bool vis[N][N];
vector<LL> f[N][N];
vector<LL> POW[N];


vector<LL> Dp(int l,int r)
{
	if(l==0&&r==m+1) return vector<LL>();
	if(vis[l][r]) return f[l][r];
	vis[l][r]=true;
	vector<LL> &v=f[l][r];
	v.clear(); v.push_back(0);
	int k=l+m-r+1;
	if(l>0) v=Max(v,add(Dp(l-1,r),mul(POW[k],a[l])));
	if(r<=m) v=Max(v,add(Dp(l,r+1),mul(POW[k],a[r])));
	return v; 
}

int main()
{
//	freopen("1.in","r",stdin);
	int i;
	scanf("%d%d",&n,&m);
	vector<LL> ans;
	ans.push_back(0);
	POW[0].push_back(1);
	for(i=1;i<=90;i++)
		POW[i]=mul(POW[i-1],2);
	while(n--) {
		memset(a,0,sizeof a);
		memset(vis,0,sizeof vis);
		for(i=1;i<=m;i++) 
			scanf("%lld",&a[i]);
		vector<LL> sum;
		for(i=0;i<=m;i++)
			sum=Max(sum,Dp(i,i+1));
		ans=add(ans,sum);
	}
	for(i=ans.size()-1;i>=0;i--) {
		if(i==(int)ans.size()-1) printf("%lld",ans[i]);
		else printf("%014lld",ans[i]);
	}
	printf("\n");
	return 0;
}

