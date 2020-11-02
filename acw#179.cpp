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

const unsigned P=199999;
const int INF=1e9+5;
const int dx[]={1,-1,0,0},dy[]={0,0,1,-1};

struct HashExcel
{
	int one[P],idx;
	unsigned ver[P];
	int Next[P],step[P];
	void insert(unsigned x,int st)
	{
		unsigned u=x%P;
		for(int i=one[u];i;i=Next[i]) 
			if(ver[i]==x) {
				step[i]=st;
				return;
			}
		Next[++idx]=one[u],one[u]=idx;
		ver[idx]=x,step[idx]=st;
	}
	int query(unsigned x)
	{
		unsigned u=x%P;
		for(int i=one[u];i;i=Next[i]) 
			if(ver[i]==x) return step[i];
		return INF;
	}
}H;
int a[40];
int A()
{
	int res=0;
	for(int i=0;i<9;i++) 
		if(a[i]) res+=abs((a[i]-1)/3-i/3)+abs((a[i]-1)%3-i%3);
	return res;
}
unsigned Hash()
{
	unsigned res=0;
	for(int i=0;i<9;i++)
		res=res*10u+a[i];
	return res;
}
int path[56];
int op[20][4];

bool dfs(int u,int cur,int depth)
{
	if(u-1+A()>depth) return false;
	else if(u-1==depth) return true;
	unsigned h=Hash();
	if(H.query(h)<u-1) return false;
	else H.insert(h,u-1);
	int i,y;
	for(i=0;i<4;i++) {
		if(op[cur][i]!=-1) {
			y=op[cur][i];
			swap(a[cur],a[y]);
			path[u]=i;
			if(dfs(u+1,y,depth)) return true;
			path[u]=-1;
			swap(a[cur],a[y]);
		}
	}
	return false;
}

int main()
{
	char ch;
	int i,j,k,x,y,cnt=0;
	memset(op,-1,sizeof op);
	memset(path,-1,sizeof path);
	// 预处理出所有的操作 
	for(i=0;i<3;i++) 
		for(j=0;j<3;j++) 
			for(k=0;k<4;k++) {
				x=i+dx[k],y=j+dy[k];
				if(x<3&&x>=0&&y<3&&y>=0) 
					op[i*3+j][k]=x*3+y;
			}
	
	for(i=0;i<9;i++) {
		cin>>ch;
		if(ch=='x') {
			x=i;
			continue;
		}
		a[i]=ch-'0';
		for(j=0;j<i;j++) 
			if(a[j]>0&&a[j]>a[i]) cnt++;
	}
	if(cnt&1) printf("unsolvable\n");
	else {
		int depth=0;
		while(!dfs(1,x,depth)) depth++;
		for(i=1;i<=depth;i++) {
			if(path[i]==0) printf("d");
			else if(path[i]==1) printf("u");
			else if(path[i]==2) printf("r");
			else printf("l");
		}
		printf("\n");
	}
	return 0;
}
