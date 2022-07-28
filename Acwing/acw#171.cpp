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
//折半搜索
const int N=56;
const LL INF=1e16;

LL n,m,w[N],ans; 
vector<LL> v;

void dfs1(int step,int limit,LL sum)
{
	if(sum>m) return;
	if(step==limit+1) {
		ans=max(ans,sum);
		v.push_back(sum);
		return;
	}
	dfs1(step+1,limit,sum+w[step]);
	dfs1(step+1,limit,sum);
}

void dfs2(int step,int limit,LL sum)
{
	if(sum>m) return;
	if(step==limit+1) {
		// sum+v[u] <= m ---> v[u]<=m-sum
		ans=max(ans,sum);
		int id=(int)(upper_bound(v.begin(),v.end(),m-sum)-v.begin())-1;
		if(id>=0&&v[id]+sum<=m) ans=max(ans,v[id]+sum);
		return; 
	}
	dfs2(step+1,limit,sum+w[step]);
	dfs2(step+1,limit,sum);
}

int main()
{
//	freopen("1.in","r",stdin);
	srand((unsigned)time(0));
	cin>>m>>n;
	for(int i=1;i<=n;i++)
		scanf("%lld",&w[i]);
//	random_shuffle(w+1,w+n+1); // 打乱序列，使剪枝均匀分布。 
	sort(w+1,w+n+1);
	int tmp=min(n,20ll);
	dfs1(1,tmp,0);
	sort(v.begin(),v.end());
	v.erase(unique(v.begin(),v.end()),v.end());
	dfs2(tmp+1,n,0);
	cout<<ans;
	return 0;
}

