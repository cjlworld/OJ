#include<vector>
#include<cstdio>
#include<iostream>
#define LL long long
#define rint register int
using namespace std;
const int N=1e5+5;
const int M=4e5+5;
int one[N];
int ver[M],Next[M];
int tot=1;
inline void AddEdge(const int &a,const int &b)
{
	tot++;
	Next[tot]=one[a];
	one[a]=tot;
	ver[tot]=b;
	return;
}
//===============================
int in[N],out[N];
bool vis[M];
vector<int> ans;
int type,n,m;
void euler(int now)
{
	int tmp;
	for(int &i=one[now];i>0;i=Next[i]) {
		if(vis[i]) continue;
		tmp=(type==1) ? ((i&1) ? -(i>>1) : (i>>1)) : (i-1); // ��Ϊ��one[now]�ı䣬iҲ��ı� 
		vis[i]=true;                                           // �����б�Ҫ����ǰ�ߴ��� 
		if(type==1) vis[i^1]=true;         // ��¼vis 
		euler(ver[i]);
		if(type==1) ans.push_back(tmp);      // ���ݼӱߣ���ʵ�ǼӸ��뻷 
		else ans.push_back(tmp);       // �ȼӸ��뻷��Ҫ�ǻ����е㻹���������ߵĻ� 
	} //�ټ����Ǹ��������ݵ�ʱ��������������
	// Ҳ�����ȱ������ı���Ϊ����ĩβ������������˵����
	// ��������ı���Ϊ���Ŀ�ʼ 
	return;
}
int main()
{
//	freopen("1.in","r",stdin);
	rint i;
	int x,y;
	scanf("%d%d%d",&type,&n,&m);
	for(i=1;i<=m;i++) {
		scanf("%d%d",&x,&y);
		AddEdge(x,y);
		if(type==1) AddEdge(y,x);
		out[x]++; in[y]++;
	}
	if(type==1) {
		for(i=1;i<=n;i++) 
			if((in[i]+out[i])&1) { // ����ͼ ��Ϊż�� 
				printf("NO");
				return 0;
			}
	}
	else {
		for(i=1;i<=n;i++) 
			if(in[i]!=out[i]) { // ����ͼ���==���� 
				printf("NO");
				return 0;
			}
	}
	for(i=1;i<=n;i++) //���Թ����㣬��Ϊ������û����������ڵıߣ���Υ������ 
		if(one[i]) {
			euler(i);
			break;
		}
	if((int)ans.size()!=m) printf("NO");
	else {
		printf("YES\n");
		while(ans.size()) 
			printf("%d ",ans.back()),ans.pop_back();
	}
	return 0;
}

