#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>

using namespace std;
typedef long long LL;

const int N=2e5+5,M=2*N;

int one[N],idx;
int ver[M],edge[M],Next[M];
inline void AddEdge(int a,int b,int c)
{
	Next[idx]=one[a]; ver[idx]=b; edge[idx]=c; one[a]=idx++;
}

int age[N];
bool vis[N];
int n,m,oldest;

// 找 siz 和 重心。 
int Getsiz(int x,int fa)
{
	if(vis[x]) return 0;
	int res=1;
	for(int i=one[x],y;~i;i=Next[i]) {
		y=ver[i];
		if(y==fa || vis[y]) continue;
		res+=Getsiz(y,x);
	}
//	if(res>10) cerr<<res<<endl;
	return res;
}

int siz[N];
void Gravity(int x,int fa,int Ts,int& Root)
{
	siz[x]=1;
	int ms=0;
	for(int i=one[x],y;~i;i=Next[i]) {
		y=ver[i];
		if(vis[y] || y==fa) continue;
		Gravity(y,x,Ts,Root);
		ms=max(ms,siz[y]);
		siz[x]+=siz[y];
	}
	ms=max(ms,Ts-siz[x]);
	if(ms<=Ts/2) Root=x;
}

// 存一棵点分树 
struct Father
{
	int u,num; // 点分树中 Father 的编号 u , 以及 now 在 u 的第 num 个儿子。 
	LL dist; // now 到 u 的距离。
	Father(int u,int num,LL dist) : u(u),num(num),dist(dist) {}
};
vector<Father> f[N]; // 祖先集合, 越上层的祖先在越前面。 
struct Son
{
	int age;
	LL dist;
	// 定义大小关系，二分要用。 
	bool operator<(const Son& t) const
	{
		return age<t.age;
	}
	// 构造函数。 
	Son(int age,LL dist) : age(age),dist(dist) {}
};
vector<Son> son[N][3];

// 计算当前子树对当前重心的贡献。
// 同时标记 子树中的结点。 
void Work(int x,int fa,LL dist,int wc,int num,vector<Son>& v)
{
	if(vis[x]) return;
	f[x].push_back(Father(wc,num,dist));// cerr<<f[x].size()<<endl;
	v.push_back(Son(age[x],dist));// cerr<<v.size()<<endl;
	for(int i=one[x],y;~i;i=Next[i]) {
		y=ver[i];
		if(y==fa) continue;
		Work(y,x,dist+edge[i],wc,num,v);
	}	
}
// 建点分树。 
void build(int x)
{
	if(vis[x]) return;
	Gravity(x,-1,Getsiz(x,-1),x); // 找重心 
	vis[x]=true;
	
	f[x].push_back(Father(x,-1,0)); // 加入自己，便于 query 一并处理自己子树的情况。 
	for(int i=one[x],k=0;~i;i=Next[i]) {
		int y=ver[i];
		if(vis[y]) continue;
		vector<Son>& v=son[x][k];
//		cerr<<v.size()<<endl;
		v.push_back(Son(-1,0)); v.push_back(Son(oldest+1,0));
		Work(y,-1,edge[i],x,k,v);
		k++;
		sort(v.begin(),v.end());
		for(int j=1;j<(int)v.size();j++) v[j].dist+=v[j-1].dist;
	}
	for(int i=one[x];~i;i=Next[i]) build(ver[i]);
}

LL query(int u,int l,int r)
{
	LL res=0;
	for(int k=0;k<(int)f[u].size();k++) { // 由上往下，无交的子树就直接取走，有交的就往下递归。 
		Father& fa=f[u][k];
//		printf("father is [%d , %d , %lld]\n",fa.u,fa.num,fa.dist);
		if(age[fa.u]>=l && age[fa.u]<=r) res+=fa.dist; // 特判 祖先的贡献。 
		for(int i=0;i<3;i++) {
			if(i==fa.num) continue; 
			// u 如果在此子树内，则下一层会加入 son[fa.u][fa.num] 的 贡献，不必重复处理。 
			vector<Son>& v=son[fa.u][i];
			if(v.empty()) continue; // empty() 意味着 fa 没有 这个 son. 
//			printf("son[%d][%d] is : \n",fa.u,i);
//			for(int j=0;j<(int)v.size();j++) 
//				printf("%d %lld\n",v[j].age,v[j].dist);
//			printf("end []\n");
			// 根据 vector 里的数计算贡献。 
			int a=lower_bound(v.begin(),v.end(),Son(l,-1))-v.begin();
			int b=upper_bound(v.begin(),v.end(),Son(r,-1))-v.begin();
			
//			printf("a is searching for %d , a = %d\n",l,a);
//			printf("b is searching for %d , b = %d\n",r,b);
//			printf("a = %d , b = %d\n",a,b);
			res+=fa.dist*(b-a)+v[b-1].dist-v[a-1].dist;
			// 注意 b-1 和 a-1 的含义不同。
			// b-1 是因为 b的距离 > r
			// a-1 是因为 要前缀和相减。 
		}
	}	
	return res;
}

int main()
{
	int i;
	int x,y,z;
	
	scanf("%d%d%d",&n,&m,&oldest);
	for(i=1;i<=n;i++) 
		scanf("%d",&age[i]);
	memset(one,-1,sizeof one);
	for(i=1;i<=n-1;i++) {
		scanf("%d%d%d",&x,&y,&z);
		AddEdge(x,y,z); AddEdge(y,x,z);
	}

	build(1); // 建点分树。 
//	ULL maxdep=0;
//	for(int i=1;i<=n;i++) maxdep=max(maxdep,f[i].size());
//	cerr<<maxdep<<endl;
	LL ans=0;
	while(m--) {
		scanf("%d%d%d",&z,&x,&y);
		x=(x+ans)%oldest,y=(y+ans)%oldest;
		if(x>y) swap(x,y);
		ans=query(z,x,y);
		printf("%lld\n",ans);
	}
	return 0;
}

