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

const int N=1e7+5;

int ch[N][4],fail[N],fa[N],tot;
bool vis[N];
int match[N];

void insert(int a[],int len,int id)
{
	int now=0;
	for(int i=1;i<=len;i++) {
		int& s=ch[now][a[i]];
		if(!s) s=++tot,fa[s]=now;
		now=s;
//		cerr<<a[i]<<" "<<tot<<endl;
	}
	match[id]=now;
}

void ACbuild()
{
	queue<int> q;
	int i,x;
	for(i=0;i<4;i++) 
		if(ch[0][i]) q.push(ch[0][i]);
	
	while(q.size()) {
		x=q.front(); q.pop();
		for(i=0;i<4;i++) {
			if(ch[x][i]) {
				fail[ch[x][i]]=ch[fail[x]][i];
				q.push(ch[x][i]);
			}
			else ch[x][i]=ch[fail[x]][i];
		}
	}
}

void query(int a[],int len)
{
	int now=0,s;
	for(int i=1;i<=len;i++) {
		s=ch[now][a[i]];
		now=s;
		vis[now]=true;
	}
}

int one[N],idx;
int Next[N],ver[N];
inline void AddEdge(int a,int b)
{
	Next[idx]=one[a],ver[idx]=b,one[a]=idx++;
}

void dp(int x)
{
	for(int i=one[x],y;~i;i=Next[i]) {
		y=ver[i];
		dp(y);
		vis[x]|=vis[y];
	}
}

char str[N];
int b[N],a[N];

inline int trans(char c)
{
	if(c=='E') return 0;
	else if(c=='S') return 1;
	else if(c=='W') return 2;
	else return 3;
}

int n,m;

int main()
{
//	freopen("1.in","r",stdin);
	int i,j;
	
	scanf("%d%d",&n,&m);
	scanf("%s",str+1);
	for(i=1;i<=n;i++)
		b[i]=trans(str[i]);
	
	for(i=1;i<=m;i++) {
		scanf("%s",str+1);
		int len=strlen(str+1);
		for(j=1;j<=len;j++) 
			a[j]=trans(str[j]);
		
//		for(j=1;j<=len;j++) 
//			printf("%d",a[j]);
//		printf("\n");
		insert(a,len,i);
	}
	
	ACbuild();
	query(b,n);
	
	memset(one,-1,sizeof one);
	for(i=1;i<=tot;i++) AddEdge(fail[i],i);
	dp(0);
	
	for(i=1;i<=m;i++) {
		int ans=0;
		for(j=match[i];j;j=fa[j]) {
			if(!ans && vis[j]) ans=1;
			else if(ans) ans++;
		}
		printf("%d\n",ans);
	}
	return 0;
}

