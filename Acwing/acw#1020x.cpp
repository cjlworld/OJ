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

const int N=1000+5,INF=1e9+5;

int o2[N],n2[N],w[N];
int toto,totn,n;

struct Node
{
	int o2,n2,w;
	Node(int a,int b,int c) : o2(a),n2(b),w(c) {}
	Node() {}
};
queue<Node> q;
bool vis[N][25][85];
int f[N][25][85]; 

int ans=INF;
void spfa()
{
	memset(f,0x3f,sizeof f);
	f[0][0][0]=0;
	q.push(Node(0,0,0));
	int x,y,z,u,v;;
	while(q.size()) {
		x=q.front().o2; y=q.front().n2; z=q.front().w;
		q.pop();
		vis[x][y][z]=false;
		if(f[x][y][z]>=ans) continue;
		if(x>=n) {
			if(y>=toto&&z>=totn) ans=f[x][y][z];
			continue;
		}
		// 不选第x+1件物品 
		if(f[x+1][y][z]>f[x][y][z]) { 
			f[x+1][y][z]=f[x][y][z];
			if(!vis[x+1][y][z])
				q.push(Node(x+1,y,z));
		}
		// 选 第x+1件物品 
		u=min(toto,y+o2[x+1]); v=min(totn,z+n2[x+1]);
		if(f[x+1][u][v]>f[x][y][z]+w[x+1]) {
			f[x+1][u][v]=f[x][y][z]+w[x+1];
			if(!vis[x+1][u][v]) 	
				q.push(Node(x+1,u,v));
		}
	}
}
int main()
{
//	freopen("1.in","r",stdin);
	cin>>toto>>totn>>n;
	for(int i=1;i<=n;i++)
		cin>>o2[i]>>n2[i]>>w[i];
	
	spfa();
	cout<<ans;
	return 0;
}

