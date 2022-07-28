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
		tmp=(type==1) ? ((i&1) ? -(i>>1) : (i>>1)) : (i-1); // 因为当one[now]改变，i也会改变 
		vis[i]=true;                                           // 所以有必要将当前边存下 
		if(type==1) vis[i^1]=true;         // 记录vis 
		euler(ver[i]);
		if(type==1) ans.push_back(tmp);      // 回溯加边，其实是加个半环 
		else ans.push_back(tmp);       // 先加个半环，要是环上有点还有其他出边的话 
	} //再加上那个环，回溯的时候会把另外半边填上
	// 也就是先遍历到的边作为环的末尾（假设有这种说法）
	// 后遍历到的边作为环的开始 
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
			if((in[i]+out[i])&1) { // 无向图 度为偶数 
				printf("NO");
				return 0;
			}
	}
	else {
		for(i=1;i<=n;i++) 
			if(in[i]!=out[i]) { // 有向图入度==出度 
				printf("NO");
				return 0;
			}
	}
	for(i=1;i<=n;i++) //忽略孤立点，因为孤立点没有与外界相邻的边，不违反定义 
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

