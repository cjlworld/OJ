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

const int N=1000+5,M=2e5+5;

int one[M],idx;
int Next[M],ver[M];
void AddEdge(int a,int b)
{
	Next[++idx]=one[a];
	one[a]=idx;
	ver[idx]=b;
}

int match[N]; // ����ͼ��һ�ߴ��Ѿ�ƥ��Ľڵ� 
bool vis[N]; 

bool dfs(int x)
{
	for(int i=one[x],y;i;i=Next[i]) {
		if(!vis[y=ver[i]]) { // �����Ѿ� ��Ԥ�� �� ȷ�ϲ��� �Ľڵ���ѡ�� 
			vis[y]=true; // �Ȱ� ta Ԥ����,�������,���� true,����,˵��û������·,�����ظ�ɨ��.
			if(!match[y] || dfs(match[y])) { // 1. û��ƥ��ĵ� ||2. �Ѿ�ƥ��ĵ����ҵ����� 
				match[y]=x; //�ҵ�����·,������ match[]; 
				return true;
			}
		}
	}
	return false;
}

int n1,n2,m;
int main()
{
//	freopen("1.in","r",stdin);
	int i,x,y;
	scanf("%d%d%d",&n1,&n2,&m);
	for(i=1;i<=m;i++) {
		scanf("%d%d",&x,&y);
		AddEdge(x,y+n1),AddEdge(y+n1,x);
	}
	int ans=0;
	for(i=1;i<=n1;i++) {
		memset(vis,0,sizeof vis);
		if(dfs(i)) ans++;
	}
	printf("%d\n",ans);
	return 0;
}

