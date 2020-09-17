#include<set>
#include<map>
#include<queue>
#include<stack>
#include<ctime>
#include<cmath>
#include<vector>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
typedef long long LL;
typedef unsigned long long ULL;
using namespace std;
const int N=20,INF=1e9+5;
int n,W;
int w[N],c[N],tot=0;
int ans=INF;
void dfs(int step,int cost)
{
	if(cost>=ans) return;
	if(step==n+1) {
		ans=cost;
		return;
	}
	// together
	for(int i=1;i<=tot;i++) {
		if(w[i]>=c[step]) {
			w[i]-=c[step];
			dfs(step+1,cost);
			w[i]+=c[step];
		}
	}
	// alone
	w[++tot]=W-c[step];
	dfs(step+1,cost+1);
	tot--;
	return;
}
int main()
{
//	freopen("1.in","r",stdin);
	cin>>n>>W;
	for(int i=1;i<=n;i++) 
		cin>>c[i];
	sort(c+1,c+n+1,greater<int>());
	dfs(1,0);
	cout<<ans;
	return 0;
}

