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
#include<complex>
#include<iostream>
#include<algorithm>

using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
typedef pair<int,int> PII;

const int N=2e6+5,INF=0x3f3f3f3f;

struct Edges
{
	int a,b;
	Edges(int a=0,int b=0) : a(a),b(b) {}
}e[N];

int n,m;
vector<int> nums;
int getnw(int x)
{
	return upper_bound(nums.begin(),nums.end(),x)-nums.begin();
}

int par[N],d[N];
PII a[N];

int Find(int x)
{
	if(par[x]!=x) return par[x]=Find(par[x]);
	else return x;
}

PII Join(PII a,PII b)
{
	vector<int> v;
	v.push_back(a.first); v.push_back(a.second);
	v.push_back(b.first); v.push_back(b.second);
	sort(v.begin(),v.end());
	reverse(v.begin(),v.end());
	return PII(v[0],v[1]);
}

int main()
{
//	freopen("1.in","r",stdin);
	int i;
	int x,y;
	
	scanf("%d",&m);
	for(i=1;i<=m;i++) {
		scanf("%d%d",&x,&y);
		nums.push_back(x); nums.push_back(y);
		e[i]=Edges(x,y);
	}
	sort(nums.begin(),nums.end());
	nums.erase(unique(nums.begin(),nums.end()),nums.end());
	for(i=1;i<=m;i++) {
		e[i].a=getnw(e[i].a);
		e[i].b=getnw(e[i].b);	
	}
	
	n=nums.size();
	for(i=1;i<=n;i++) par[i]=i,d[i]=0,a[i]=PII(i,-INF);
	for(i=1;i<=m;i++) {
		x=e[i].a; y=e[i].b;
		x=Find(x),y=Find(y);
		if(x!=y && !(d[x]&d[y])) d[x]|=d[y],par[y]=x,a[x]=Join(a[x],a[y]);
		else if(x==y && !d[x]) d[x]=1;
		else {
			puts("-1");
			return 0;
		}
	}
	
	int ans=1;
	for(i=1;i<=n;i++) 
		if(par[i]==i) {
			if(d[i]==0) ans=max(ans,a[i].second);
			else ans=max(ans,a[i].first);
		}
	
	cout<<nums[ans-1]<<endl;
	return 0;
}

