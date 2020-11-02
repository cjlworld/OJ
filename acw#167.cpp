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

using namespace std;
typedef long long LL;
typedef unsigned long long ULL;

const int N=100+5;

int a[N],p[N];
int n,W;
int w[N],tot,cnt;

bool dfs(int u)
{
	if(cnt>tot) return false;
	else if(u==n+1) return true;
	
	for(int i= (u>1&&a[u]==a[u-1]) ? p[u-1] : 1;i<=cnt;i++) {
		if(i>1&&w[i]==w[i-1]) continue;
		if(w[i]>=a[u]) {
			w[i]-=a[u];
			p[u]=i;
			if(dfs(u+1)) return true;
			w[i]+=a[u];
			p[u]=0;
			if(w[i]==a[u]) return false;
		}
	}
	if(cnt<tot) {
		cnt++;
		w[cnt]-=a[u];
		p[u]=cnt;
		if(dfs(u+1)) return true;
		w[cnt]+=a[u];
		p[u]=0;
		cnt--;
	}
	return false;
}
int main()
{
//	freopen("1.in","r",stdin);
	int i;
	while(scanf("%d",&n),n) {
		int sum=0; 
		for(i=1;i<=n;i++)
			scanf("%d",&a[i]),sum+=a[i];
		sort(a+1,a+n+1,greater<int>());
		for(i=a[1];i<=sum;i++) {
			if(sum%i) continue;
			tot=sum/i,cnt=0;
			fill(w+1,w+tot+1,i);
			if(dfs(1)) {
				printf("%d\n",i);
				break;
			}
		}
	}
	return 0;
}

