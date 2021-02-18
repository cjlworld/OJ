#include<vector>
#include<cstdio>
#include<iostream>
#include<algorithm>

using namespace std;
typedef long long LL;
typedef pair<LL,LL> PLL;

const int N=1e6+5;
const LL INF=0x3f3f3f3f3f3f3f3f;

int pm[N],tot;
bool tag[N];
void prime(int n)
{
	int i,j;
	for(i=2;i<=n;i++) {
		if(!tag[i]) pm[++tot]=i;
		for(j=1;j<=tot && pm[j]*i<=n;j++) {
			tag[pm[j]*i]=true;
			if(i%pm[j]==0) break;
		}
	}
}

LL power(LL x,LL k)
{
	LL res=1;
	while(k) {
		if(k&1) res=res*x;
		x=x*x; k>>=1;
	}
	return res;
}

void divide(LL x,vector<PLL>& v)
{
	v.clear();
	for(int i=1;i<=tot && pm[i]*pm[i]<=x;i++) {
		if(x%pm[i]==0) {
			v.push_back(PLL(pm[i],0));
			while(x%pm[i]==0) x/=pm[i],v[v.size()-1].second++;
		}
	}
	if(x>1) v.push_back(PLL(x,1));
}

LL T,p,q;

int main()
{
//	freopen("1.in","r",stdin);
	prime(N-1);
	cin>>T;
	while(T--) {
		cin>>p>>q;
		LL ans=p,minnum=INF;
		vector<PLL> vq;
		divide(q,vq);
		for(int i=0;i<(int)vq.size();i++) {
			int cnt=0;
			LL x=vq[i].first;
			while(p%x==0) {
				cnt++;
				p/=x;
			}
			if(cnt<vq[i].second) minnum=1;
			else minnum=min(minnum,power(x,cnt-vq[i].second+1));
		}
		printf("%lld\n",ans/minnum);
	}
	return 0;
}

