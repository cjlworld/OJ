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
typedef pair<LL,int> PLI;

const int N=1e5+5;
priority_queue<PLI,vector<PLI>,greater<PLI> > q;
int n,k;
LL w[N];

int main()
{
//	freopen("1.in","r",stdin);
	int i,depth;
	LL sum,ans=0;
	scanf("%d%d",&n,&k);
	for(i=1;i<=n;i++) 
		scanf("%lld",&w[i]),q.push(PLI(w[i],0));
	while((n-1)%(k-1)) q.push(PLI(0,0)),n++;
	while(q.size()>1) {
		depth=0,sum=0;
		for(i=1;i<=k;i++) {
			sum+=q.top().first;
			depth=max(depth,q.top().second);
			q.pop();
		}
		ans+=sum;
		q.push(PLI(sum,depth+1));
	}
	printf("%lld\n%d\n",ans,q.top().second);
	return 0;
}

