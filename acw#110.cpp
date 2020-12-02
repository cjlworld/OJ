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
typedef pair<int,int> PII;

const int N=10000+5;
int n,m;
priority_queue<PII,vector<PII>,greater<PII> > q;
PII a[N],b[N];

int main()
{
//	freopen("1.in","r",stdin);
	int i,j;
	cin>>n>>m;
	for(i=1;i<=n;i++) 
		cin>>a[i].first>>a[i].second;
	for(i=1;i<=m;i++) 
		cin>>b[i].first>>b[i].second;
	
	sort(a+1,a+n+1);
	sort(b+1,b+m+1);
	
	PII t;
	int ans=0;
	for(i=1,j=1;i<=m;i++) {
		for(;j<=n && a[j].first<=b[i].first;j++) 
			q.push(PII(a[j].second,a[j].first));
		while(q.size() && b[i].second) {
			t=q.top(); q.pop();
			swap(t.first,t.second);
			if(t.second<b[i].first) continue;
			else b[i].second--,ans++;
		}
	}
	cout<<ans<<endl;
	return 0;
}

