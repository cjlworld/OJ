#include<set>
#include<map>
#include<cmath>
#include<ctime>
#include<stack>
#include<queue>
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

const int N=256;
const LL INF=1e18;
int g[N]={6,2,5,5,4,5,6,3,7,6};

vector<LL> nums[N];
// num[i] 表示花 i 根火柴棒能获得的数字的集合 <=10e18

void dfs(int u,LL cur,int sum,int st)
{
	if(sum==0||cur>INF) {
		nums[st].push_back(cur);
		return;
	}
	for(LL i=0;i<=9;i++) {
		if(u==1&&i==0) continue;
		if(sum<g[i]) continue;
		
		dfs(u+1,cur*10+i,sum-g[i],st);
	}
}
int n;

LL ans=0;

int main()
{
//	freopen("1.in","r",stdin);
	int i,j,k,r,e;
	LL x,y,z;
	scanf("%d",&n);
	n-=4; // 加号与等号各自需要两根火柴棍?
	for(i=1;i<=n;i++) 
		dfs(1,0,i,i);
	nums[6].push_back(0);
	for(i=1;i<=n;i++) {
		for(j=0;j<(int)nums[i].size();j++) {
			x=nums[i][j];
			for(k=1;k+i<=n;k++) {
				for(r=0;r<(int)nums[k].size();r++) {
					y=nums[k][r];
					if(y<x) continue;
					for(e=0;e<(int)nums[n-k-i].size();e++) {
						z=nums[n-k-i][e];
						if(x+y==z) {
							if(y==x) ans++;
							else ans+=2;
//							printf("%lld+%lld=%lld\n",x,y,z);
						}
					}
				}
			}
		}
	}
	cout<<ans;
	return 0;
}

