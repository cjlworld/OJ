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
const int N=4e5+5;

int one[N],hs[N],idx;
int ver[N],Next[N];
void AddEdge(int h[],int a,int b)
{
	Next[idx]=h[a]; ver[idx]=b; h[a]=idx++;
	Next[idx]=h[b]; ver[idx]=a; h[b]=idx++;
}

int dfn[N],low[N],times;
stack<int> S;

// �����ж�����
// 1. ����Ǹ��ڵ㣬�����������϶���.
// 2. ����Ǹ����� low[son] >= dfn[x]. 

// ����Բ��������Ҫ������һ�� �� ��Ϊ
// 1. �����ڵ�ֻ��һ�����ӣ���һ����������ڵ����ڵ�˫�����������⡣
// 2. ����Ҳ�������⡣ 
// ���Խ�Բ�������ÿ��Ǹ��ڵ㣬�����Ҫ�� 

int cnt; // ����ļ������ı�š� 

void tarjan(int x)
{
	dfn[x]=low[x]=++times;
	S.push(x);
	for(int i=one[x],y;~i;i=Next[i]) {
		y=ver[i];
		if(!dfn[y]) {
			tarjan(y);
			low[x]=min(low[x],low[y]);
			
			if(low[y]>=dfn[x]) {
				cnt++; // �µĵ�˫�ķ��㡣 
				while(S.size() && S.top()!=y) { 
					// ע������ֻ�ܳ�ջ�� y, ��Ϊջ�п��ܻ��� x ������������ 
					AddEdge(hs,S.top(),cnt);
					S.pop();
				}	
				AddEdge(hs,y,cnt); S.pop();
				AddEdge(hs,x,cnt); // ��©��; ͬʱע�����ﲻ��ɾȥ x, ��Ϊ x ���ܴ�����������˫�� 
			}
		}
		else low[x]=min(low[x],dfn[y]);
	}
}

int up[N][21],dep[N],w[N];

void deal_first(int x,int fa)
{
	dep[x]=dep[fa]+1;
	up[x][0]=fa;
	w[x]+=w[fa];
	
	int i,y;
	for(i=1;i<=20;i++) {
		if(!up[x][i-1]) break;
		up[x][i]=up[up[x][i-1]][i-1];
	}
	for(i=hs[x];~i;i=Next[i]) {
		y=ver[i];
		if(y==fa) continue;
		deal_first(y,x);
	}
}

int lca(int x,int y)
{
	int i;
	if(dep[x]<dep[y]) swap(x,y);
	for(i=20;i>=0;i--) 
		if(dep[up[x][i]]>=dep[y]) 
			x=up[x][i];
	
	if(x==y) return x;
	
	for(i=20;i>=0;i--) 
		if(up[x][i]!=up[y][i]) 
			x=up[x][i],y=up[y][i];
	
	return up[x][0];
}

int dist(int x,int y) // ��������֮���Բ�������� 
{
	int z=lca(x,y);
	return w[x]+w[y]-w[z]-w[up[z][0]];
}

int n,m,Q;
int id[N]; // ���Ϊ id �ı߶�Ӧ�ķ��㡣 

int main()
{
//	freopen("1.in","r",stdin);
	int i;
	int x,y;
	while(scanf("%d%d",&n,&m),n||m) {
		memset(id,0,sizeof id);
		memset(one,-1,sizeof one); 
		memset(hs,-1,sizeof hs);
		idx=0; 
		
		memset(low,0,sizeof low);
		memset(dfn,0,sizeof dfn);
		times=0;
		while(S.size()) S.pop();
		cnt=n;
		
		memset(dep,0,sizeof dep);
		memset(up,0,sizeof up);
		memset(w,0,sizeof w);
		
		for(i=1;i<=m;i++) {
			scanf("%d%d",&x,&y);
			AddEdge(one,x,y);
		}
		
		// �Ե�˫��Բ������ 
		for(i=1;i<=n;i++) 
			if(!dfn[i]) tarjan(i);
		
//		for(x=n+1;x<=cnt;x++) {
//			printf("%d : ",x);
//			for(i=hs[x];~i;i=Next[i]) {
//				y=ver[i];
//				printf("%d, ",y);
//			}
//			printf("\n");
//		}
		// ���ʣ�a->b �ıؾ��� = a->b �����Ͼ���Բ���������
		// ���԰� Բ����Ϊ 1 , ������Ϊ 0 ���ɡ� 
		for(i=1;i<=cnt;i++) w[i]=(i<=n);
		for(i=1;i<=n;i++)
			if(!dep[i])	deal_first(i,0); // ��һ����֤��ͨ��������ɭ�֣�����Ҫ���dfs
		
		// ��ÿ���߱��������Ӧ�ķ��㡣 
		for(x=1;x<=n;x++) 
			for(i=one[x];~i;i=Next[i]) {
				y=ver[i];
				if(y<x) { 
					// y<x ��֤ÿ����ֻ���һ�Σ�
					// dist(x,y) ��֤����ͬ����һ�����㡣 
					if(dep[y]==dep[x] || dep[y]<dep[x]) id[i/2+1]=up[x][0];
					else id[i/2+1]=up[y][0];
				}
			}
			
		scanf("%d",&Q);
		while(Q--) {
			scanf("%d%d",&x,&y);
			printf("%d\n",dist(id[x],id[y]));
		}
	}
	return 0;
}

