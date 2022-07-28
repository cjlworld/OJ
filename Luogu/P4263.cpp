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

const int N=1e5+5;
int T,n;
vector<int> nums,ans;
int a[N],cnt[N];
int main()
{
//	freopen("1.in","r",stdin);
	int i;
	int cmax;
	scanf("%d",&T);
	while(T--) {
		nums.clear(),ans.clear();
		memset(cnt,0,sizeof cnt);
		scanf("%d",&n);
		for(i=1;i<=n;i++) {
			scanf("%d",&a[i]);
			nums.push_back(a[i]);
		}
		sort(nums.begin(),nums.end());
		nums.erase(unique(nums.begin(),nums.end()),nums.end());
		for(i=1;i<=n;i++) {
			a[i]=(int)(lower_bound(nums.begin(),nums.end(),a[i])-nums.begin());
			cnt[a[i]]++;
		}
		cmax=0;
		for(i=0;i<(int)nums.size();i++) 
			cmax=max(cmax,cnt[i]);
		for(i=0;i<(int)nums.size();i++) 
			if(cnt[i]==cmax)
				ans.push_back(i);
		if(ans.size()==nums.size()) printf("-1\n");
		else {
			printf("%llu\n",ans.size());
			for(i=0;i<(int)ans.size();i++) 
				printf("%d ",nums[ans[i]]);
			printf("\n");
		}
	}
	return 0;
}

