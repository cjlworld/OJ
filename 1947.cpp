#include<cmath>
#include<vector>
#include<cstdio>
#include<iostream>
#include<algorithm>
typedef long long LL;
typedef unsigned long long ULL;
using namespace std;
const LL INF=0x3f3f3f;
const int N=1e4+5;
LL s[N];
LL m1,m2;
int n;
vector< pair<LL,int> > v,k;
inline void calc(LL num,vector< pair<LL,int> > &p)
{
	p.clear();
	for(LL i=2;i*i<=num;i++) {
		if(num%i==0) {
			p.push_back(make_pair(i,0));
			while(num%i==0) num=num/i,p[p.size()-1].second++;
		}
	}
	if(num!=1) p.push_back(make_pair(num,1));
	return;
}
inline bool cmp(const pair<LL,int> &a,const pair<LL,int> &b)
{
	return a.first<b.first;
}
int main()
{
//	freopen("1.in","r",stdin);
	int i,j;
	scanf("%d",&n);
	scanf("%lld%lld",&m1,&m2);
	for(i=1;i<=n;i++) 
		scanf("%lld",&s[i]);
	calc(m1,v);
	for(i=0;i<(int)v.size();i++) 
		v[i].second=v[i].second*m2;
	vector< pair<LL,int> > :: iterator it;
	LL ans=INF;
	for(i=1;i<=n;i++) {
		calc(s[i],k);
		LL res=0;
		j=0;
		for(;j<(int)v.size();j++) {
			it=lower_bound(k.begin(),k.end(),v[j],cmp);
			if(it==k.end()||it->first!=v[j].first)
				break;
			else res=max(res,(LL)ceil(v[j].second*1.0/(it->second*1.0)));
		}
		if(j==(int)v.size()) 
			ans=min(ans,res);
	}
	if(ans==INF) printf("-1");
	else printf("%lld",ans);
	return 0;
}
