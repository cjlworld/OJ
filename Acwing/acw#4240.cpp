#include<set>
#include<map>
#include<queue>
#include<stack>
#include<cmath>
#include<ctime>
#include<bitset>
#include<vector>
#include<cstdio>
#include<complex>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>

using namespace std;
typedef long long LL;
typedef long double LD;
typedef pair<int,int> PII;
typedef unsigned long long ULL;

const int N=256;

int n;
priority_queue<pair<double,PII>,vector<pair<double,PII> >,greater<pair<double,PII> > > q;
PII a[N];

double dist(PII x,PII y)
{
	return sqrt(pow(x.first-y.first,2)+pow(x.second-y.second,2));
}

double dis[N];
bool vis[N];

void Prim()
{
	while(q.size()) q.pop();
	memset(vis,false,sizeof vis);
	
	dis[1]=0; vis[1]=true;
	for(int i=2;i<=n;i++)
		q.push(pair<double,PII>(dist(a[1],a[i]),PII(1,i)));
	int cnt=1;
	while(cnt<n) {
		int x=q.top().second.first,y=q.top().second.second;
		q.pop();
		if(vis[y]) continue;
		vis[y]=true; cnt++;
		dis[y]=max(dis[x],dist(a[x],a[y]));
		for(int i=1;i<=n;i++) {
			if(vis[i]) continue;
			q.push(pair<double,PII>(dist(a[y],a[i]),PII(y,i)));
		}
	}
}

int main()
{
//	freopen("1.in","r",stdin);
	int times=0;
	while(scanf("%d",&n),n) {
		for(int i=1;i<=n;i++) 
			scanf("%d%d",&a[i].first,&a[i].second);
		Prim();
		printf("Scenario #%d\nFrog Distance = %.3lf\n\n",++times,dis[2]);
	}
	return 0;
}

