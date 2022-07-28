#include<cstdio>
#include<cstring>
#include<iostream>

using namespace std;

const int N=256,M=2e4+5,INF=0x3f3f3f3f;

struct Edges
{
	int u,v,val;
	Edges(int u=0,int v=0,int val=0) :
		u(u),v(v),val(val) {}
	// �� u �� v ȨֵΪ val ������ߡ� 
}e[M];

int n,m,rt;
int col[N],all; // ���ڻ��ı�ţ���ż������� 
int fa[N],min_pre[N]; // ��С��ߵ���㣬��С��ߵ�Ȩֵ�� 
int vis[N];

int DMST()
{
	int ans=0;
	while(true) {
		// ��ʼ�� 
		all=0;
		memset(col,0,sizeof col);
		memset(fa,0,sizeof fa);
		memset(vis,0,sizeof vis);
		memset(min_pre,0x3f,sizeof min_pre);
		
		// ��ÿ�������С���
		for(int i=1;i<=m;i++) 
			if(e[i].u!=e[i].v && e[i].val<min_pre[e[i].v])
				fa[e[i].v]=e[i].u,min_pre[e[i].v]=e[i].val;
		
		for(int i=1;i<=n;i++) 
			if(i!=rt && min_pre[i]==INF) return -1; // �������һ����û����ߣ��򲻴�������ͼ��
		for(int i=1;i<=n;i++) {
			if(i==rt) continue;
			ans+=min_pre[i]; // ����ñߵ�Ȩֵ����ʵҲ�����صĻ��ڲ��ϱߵĲ�����
			
			// �һ� 
			int u=i;
			while(u!=rt && !vis[u] && !col[u])
				vis[u]=i,u=fa[u]; // �ҹ��˾ͱ�ǣ������ظ�ɨ�衣
			// ����ñ������� O(n^2) �ġ� 
			// ��i������ѡ�����������
			// ��������������Ѿ��ж��Ļ� ���� rt 
			// ��Ϊ���Ǳ�֤�����ĵ��������Ϊ 1 ������һ����һ��û����ߣ������г��ߡ� 
			// ���������� �� ���� rt ��һ�����Ա�֤������ȥ�ˡ�
			
			if(u!=rt && vis[u]==i) { // ע�� i ��һ���ڻ�� 
				col[u]=++all; // �ѻ��ǳ�������ǡ� 
				for(int v=fa[u];v!=u;v=fa[v]) 
					col[v]=all;
			} 
		}
		if(!all) return ans; // �޻�˵���㷨������
		
		// ����,���½�ͼ�� 
		for(int i=1;i<=n;i++) //�����ڻ��еĵ�Ҳ��һ�����
			if(!col[i]) col[i]=++all;
		int tot=0;
		for(int i=1;i<=m;i++) {
			int u=col[e[i].u],v=col[e[i].v];
			if(u==v) continue; // ���� u==v �ı��Ѿ�û���ˣ�ɾȥ�� 
			e[++tot]=Edges(u,v,e[i].val-min_pre[e[i].v]);
			// ���� e[i].v (ָ����ǰ�Ļ�) ֻ�Ტ��һ������һ������ıߣ�
			// e[i].val-val ��������������ı�ʱ�ڲ���ʽ�ϱߡ�
			// ���������ϵĵ㣬�򽫱�Ȩ�޸ĳ� 0�������ظ�����𰸡� 
		}
		n=all; m=tot; rt=col[rt];
	}
}

int main()
{
	scanf("%d%d%d",&n,&m,&rt);
	for(int i=1;i<=m;i++) 
		scanf("%d%d%d",&e[i].u,&e[i].v,&e[i].val);
	int ans=DMST();
	if(ans!=-1) printf("%d\n",ans);
	else puts("-1");
	return 0;
}

