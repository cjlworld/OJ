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

// �� siz �� ���ġ� 
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

// ��һ�õ���� 
struct Father
{
	int u,num; // ������� Father �ı�� u , �Լ� now �� u �ĵ� num �����ӡ� 
	LL dist; // now �� u �ľ��롣
	Father(int u,int num,LL dist) : u(u),num(num),dist(dist) {}
};
vector<Father> f[N]; // ���ȼ���, Խ�ϲ��������Խǰ�档 
struct Son
{
	int age;
	LL dist;
	// �����С��ϵ������Ҫ�á� 
	bool operator<(const Son& t) const
	{
		return age<t.age;
	}
	// ���캯���� 
	Son(int age,LL dist) : age(age),dist(dist) {}
};
vector<Son> son[N][3];

// ���㵱ǰ�����Ե�ǰ���ĵĹ��ס�
// ͬʱ��� �����еĽ�㡣 
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
// ��������� 
void build(int x)
{
	if(vis[x]) return;
	Gravity(x,-1,Getsiz(x,-1),x); // ������ 
	vis[x]=true;
	
	f[x].push_back(Father(x,-1,0)); // �����Լ������� query һ�������Լ������������ 
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
	for(int k=0;k<(int)f[u].size();k++) { // �������£��޽���������ֱ��ȡ�ߣ��н��ľ����µݹ顣 
		Father& fa=f[u][k];
//		printf("father is [%d , %d , %lld]\n",fa.u,fa.num,fa.dist);
		if(age[fa.u]>=l && age[fa.u]<=r) res+=fa.dist; // ���� ���ȵĹ��ס� 
		for(int i=0;i<3;i++) {
			if(i==fa.num) continue; 
			// u ����ڴ������ڣ�����һ������ son[fa.u][fa.num] �� ���ף������ظ����� 
			vector<Son>& v=son[fa.u][i];
			if(v.empty()) continue; // empty() ��ζ�� fa û�� ��� son. 
//			printf("son[%d][%d] is : \n",fa.u,i);
//			for(int j=0;j<(int)v.size();j++) 
//				printf("%d %lld\n",v[j].age,v[j].dist);
//			printf("end []\n");
			// ���� vector ��������㹱�ס� 
			int a=lower_bound(v.begin(),v.end(),Son(l,-1))-v.begin();
			int b=upper_bound(v.begin(),v.end(),Son(r,-1))-v.begin();
			
//			printf("a is searching for %d , a = %d\n",l,a);
//			printf("b is searching for %d , b = %d\n",r,b);
//			printf("a = %d , b = %d\n",a,b);
			res+=fa.dist*(b-a)+v[b-1].dist-v[a-1].dist;
			// ע�� b-1 �� a-1 �ĺ��岻ͬ��
			// b-1 ����Ϊ b�ľ��� > r
			// a-1 ����Ϊ Ҫǰ׺������� 
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

	build(1); // ��������� 
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

