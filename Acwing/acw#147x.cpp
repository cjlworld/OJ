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
typedef pair<LL,int> PLI;

const int N=2e5+5;
const LL INF=1e15+5;

int n,m;
LL a[N],d[N];

priority_queue<PLI,vector<PLI>,greater<PLI> > q;

bool vis[N];

int l[N],r[N];
int idx;
int hh,tt;
void init()
{
	memset(l,0,sizeof l);
	memset(r,0,sizeof r);
	hh=1,tt=n+3,idx=1;
	r[hh]=tt,l[tt]=hh;
}
void insert(int pos) // 插入在 pos 的后面。 
{
	idx++; 
	l[idx]=pos,r[idx]=r[pos];
	l[r[idx]]=r[l[idx]]=idx;
}
void del(int pos)
{
	l[r[pos]]=l[pos];
	r[l[pos]]=r[pos];
}


int main()
{
//	freopen("1.in","r",stdin);
	int i,x,L,R;
	LL z;
	scanf("%d%d",&n,&m);
	for(i=1;i<=n;i++) 
		scanf("%lld",&a[i]);
	for(i=2;i<=n;i++) 
		d[i]=a[i]-a[i-1],q.push(PLI(d[i],i));
	init();	
	d[hh]=d[tt]=INF;
	insert(hh);
	for(i=3;i<=n;i++) insert(i-1);
	// 第i个节点在链表中的编号为i
	LL ans=0;
	int cnt=0;
	while(cnt<m) {
		z=q.top().first,x=q.top().second;
		q.pop();
		L=l[x],R=r[x];
//		cerr<<L<<" "<<R<<" "<<ans+z<<endl;
		if(vis[x]) continue;
		ans+=z,cnt++;
		vis[L]=vis[R]=true;
		
		del(L),del(R);
		d[x]=d[L]+d[R]-d[x];
		q.push(PLI(d[x],x));
	}
	printf("%lld\n",ans);
	return 0;
}

