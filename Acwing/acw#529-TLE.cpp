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

const int N=256,INF=0x3f3f3f3f;
int w[N][N];
vector< pair<int,int> > v[N];
int n,m;

int dep[N];
int ans=INF;
int sum;
void dfs(int step,int cost)
{
	if(cost+sum>=ans) return;
	if(step==n) {
		ans=cost;
		return;
	}
	int x,y,z,i;
	for(x=1;x<=n;x++) {
		if(!dep[x]) continue;
		for(i=0;i<(int)v[x].size();i++) {
			y=v[x][i].second; z=v[x][i].first;
			if(dep[y]) continue;
			sum-=v[y][0].first;
			dep[y]=dep[x]+1;
			dfs(step+1,cost+dep[x]*z);
			dep[y]=0;
			sum+=v[y][0].first;
		}
	}
	return;
}

int main()
{
//	freopen("1.in","r",stdin);
	int i,j,u,k;
	int x,y,z;
	cin>>n>>m;
	memset(w,0x3f,sizeof w);
	for(i=1;i<=m;i++) {
		scanf("%d%d%d",&x,&y,&z);
		w[x][y]=min(w[x][y],z);
		w[y][x]=min(w[y][x],z);
	}
	for(i=1;i<=n;i++) {
		for(j=1;j<=n;j++) {
			if(w[i][j]<INF) 
				v[i].push_back(make_pair(w[i][j],j));
		}
		sort(v[i].begin(),v[i].end());
//		for(j=0;j<(int)v[i].size();j++) 
//			printf("%d --> %d : %d \n",i,v[i][j].second,v[i][j].first);
	}
	for(i=1;i<=n-i;i++) 
	    for(j=1;j<=n-1;j++) 
	        if(v[j].size()>v[j+1].size()) {
	        	swap(v[j],v[j+1]);
	        	for(u=1;u<=n;u++) {
	        		for(k=0;k<(int)v[u].size();k++) {
	        			if(v[u][k].second==j) v[u][k].second=j+1;
	        			else if(v[u][k].second==j+1) v[u][k].second=j;
					}
				}
			}
	
	for(i=1;i<=n;i++) {
		dep[i]=1;
		for(j=1;j<=n;j++) 
			if(j!=i) 
				sum+=v[j][0].first;
		dfs(1,0);
		dep[i]=0;
		sum=0;
	}
	cout<<ans;
	return 0;
}
/* Input
5 4
1 2 3
1 3 3
1 4 3
1 5 3
*/
//		for(j=0;j<(int)v[i].size();j++) 
//			S.insert(v[i][j].second);
//		S.clear();
//	for(set<int>::iterator it=S.begin();it!=S.end();it++) {
//		x=*it;
//		for(i=0;i<(int)v[x].size();i++) {
//			y=v[x][i].second; z=v[x][i].first;
//			if(!dep[y]) continue;
//			dep[x]=dep[y]+1;
//			S.erase(it);
//			for(k=0;k<(int)v[x].size();k++) {
//				j=v[x][k].second;
//				if(cnt[j]==0) S.insert(j);
//				cnt[j]++;
//			}
//			dfs(step+1,cost+dep[x]*z);
//			S.insert(x);
//			for(k=0;k<(int)v[x].size();k++) {
//				j=v[x][k].second;
//				if(cnt[j]==1) S.erase(j);
//				cnt[j]--;
//			}			
//			dep[x]=0;
//		}
//	}
