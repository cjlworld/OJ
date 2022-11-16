#include<set>
#include<map>
#include<queue>
#include<stack>
#include<cmath>
#include<ctime>
#include<bitset>
#include<vector>
#include<cstdio>
#include<complex>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>

using namespace std;
typedef long long LL;
typedef long double LD;
typedef unsigned long long ULL;

const int N=1e4+5;
const int INF=0x3f3f3f3f;
const int Pow10[]={1,10,100,1000,10000};

int p[N],tot;
bool tag[N];
void prime(int n)
{
	for(int i=2;i<=n;i++) {
		if(!tag[i]) p[++tot]=i;
		for(int j=1;j<=tot && p[j]*i<=n;j++) {
			tag[i*p[j]]=true;
			if(i%p[j]==0) break;
		}
	}
}

vector<int> e[N];

int T;
int A,B;

int dis[N],vis[N]; 
queue<int> q;

int bfs()
{
	memset(dis,0x3f,sizeof dis);
	memset(vis,false,sizeof vis);
	while(q.size()) q.pop();
	
	q.push(A); dis[A]=0; vis[A]=true;
	while(q.size()) {
		int x=q.front(); q.pop();
		for(int i=0;i<(int)e[x].size();i++) {
			int y=e[x][i];
			if(vis[y]) continue;
			dis[y]=dis[x]+1; vis[y]=true;
			q.push(y);
		}
	}
	return dis[B];
}

int main()
{
//	freopen("1.in","r",stdin);
	
	prime(N-1);
	for(int i=1000;i<=9999;i++) {
		if(tag[i]) continue;
		for(int j=0;j<4;j++) {
			for(int k=0;k<=9;k++) {
				int num=((i/Pow10[j])/10*10+k)*Pow10[j]+(i%Pow10[j]);
				if(num==i || num<1000 || num>9999) 
					continue;
				e[i].push_back(num);
			}
		}
	}
	
	scanf("%d",&T);
	while(T--) {
		scanf("%d%d",&A,&B);
		printf("%d\n",bfs());
	}
	
	return 0;
}

