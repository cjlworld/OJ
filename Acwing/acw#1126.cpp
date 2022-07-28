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
typedef long double LD;
typedef unsigned long long ULL;

const int N=2e5+5;

int one[N],idx;
double edge[N];
int Next[N],ver[N]; 
void AddEdge(int a,int b,double c) 
{
	ver[idx]=b; edge[idx]=c; Next[idx]=one[a]; one[a]=idx++; 
}

int n,m,A,B; 

double dis[N];
bool vis[N];
priority_queue< pair<double,int> > q; // 本来就是大根堆 

void Dijstra(int st)
{
	int x,y; double z;
	q.push(pair<double,int>(dis[st]=1,st)); 
	while(q.size()) {
		x=q.top().second; q.pop();
		if(vis[x]) continue;
		vis[x]=true;
		for(int i=one[x];~i;i=Next[i]) {
			y=ver[i]; z=edge[i];
			if(!vis[y] && dis[x]*z>dis[y]) {
				dis[y]=dis[x]*z;
				q.push(pair<double,int>(dis[y],y));
			}
		}
	}
}

int main()
{
//	freopen("1.in","r",stdin);
	memset(one,-1,sizeof one);
	int x,y; double z;
	
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++) {
		scanf("%d%d%lf",&x,&y,&z); z=1.0-z/100.0;
		AddEdge(x,y,z); AddEdge(y,x,z);
	}
	scanf("%d%d",&A,&B);
	
	Dijstra(A);
//	cout<<dis[B]<<endl;
	printf("%.8lf\n",100.0/dis[B]);
	return 0;
}

