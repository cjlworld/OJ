#include<queue>
#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
typedef long long LL;
typedef unsigned long long ULL;
using namespace std;
const int N=36,M=10000+5;
vector<int> v[N];
bool vis[N];
int dep[N];
void dfs(int x)
{
	int i,y;
	vis[x]=true;
	for(i=0;i<(int)v[x].size();i++) {
		y=v[x][i];
		if(!vis[y]) 
			dfs(y);
	}
	return;
}
queue<int> q;
int f[N],d[N];
int n,m;
bool topsort()
{
	while(q.size()) q.pop();
	memset(f,0,sizeof f);
	memset(vis,0,sizeof vis);
	memcpy(d,dep,sizeof d);
	int i,x,y;
	for(i=1;i<=n;i++) 
		if(d[i]==0) 
			q.push(i),f[i]=1;
	if(q.size()>=2) return false;
	vis[1]=true;
	while(q.size()) {
		x=q.front(); q.pop();
		for(i=0;i<(int)v[x].size();i++) {
			y=v[x][i];
			f[y]=max(f[y],f[x]+1);
			d[y]--;
			if(d[y]==0) {
				q.push(y);
				if(vis[f[y]]) return false;
				vis[f[y]]=true;
			}
		}
	}
	for(i=1;i<=n;i++) 
		if(f[i]==0) 
			return false;
	return true;
}

int main()
{
//	freopen("1.in","r",stdin);
	int i,j,ii;
	int x,y;
	char ch;
	while(scanf("%d%d",&n,&m)==2) {
		if(n==0&&m==0) break;
		for(i=1;i<=n;i++)
			v[i].clear();
		memset(dep,0,sizeof dep);
		for(i=1;i<=m;i++) {
			cin>>ch; x=ch-'A'+1;
			cin>>ch;
			cin>>ch; y=ch-'A'+1;
			memset(vis,0,sizeof vis);
			dfs(x);
			if(vis[y]) {
				printf("Inconsistency found after %d relations.\n",i);
				break;
			}
			v[y].push_back(x);
			dep[x]++;
			if(topsort()) {
				printf("Sorted sequence determined after %d relations: ",i);
				for(ii=n;ii>=1;ii--) {
					for(j=1;j<=n;j++) {
						if(f[j]==ii) {
							printf("%c",j+'A'-1);
							break;
						}
					}
				}
				printf(".\n");
				break;
			}
		}
		if(i<m+1) 
			for(i++;i<=m;i++) 
				cin>>ch>>ch>>ch;
		else printf("Sorted sequence cannot be determined.\n");
	}
	return 0;
}

