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

const int N=8e5+5,M=2e6+5;

int one[N],idx;
int ver[N],Next[N];
inline void AddEdge(int a,int b)
{
	Next[idx]=one[a],ver[idx]=b,one[a]=idx++;
}

int ch[N][26],fail[N],match[N];
LL cnt[N];
int tot;

void insert(char a[],int id)
{
	int now=0;
	for(int i=1;a[i];i++) {
		int &s=ch[now][a[i]-'a'];
		if(!s) s=++tot;
		now=s;
	}
	match[id]=now;
}

void ACbuild()
{
	queue<int> q;
	int i,x;
	for(i=0;i<26;i++) 
		if(ch[0][i]) q.push(ch[0][i]);
	while(q.size()) {
		x=q.front(); q.pop();
		for(i=0;i<26;i++) {
			if(ch[x][i]) {
				fail[ch[x][i]]=ch[fail[x]][i];
				q.push(ch[x][i]);
			}
			else ch[x][i]=ch[fail[x]][i];
		}
	}
}

void query(char a[])
{
	int now=0;
	for(int i=1;a[i];i++) {
		int s=ch[now][a[i]-'a'];
		now=s;
		cnt[now]++;
	}
}

void dp(int x)
{
	for(int i=one[x];~i;i=Next[i]) 
		dp(ver[i]),cnt[x]+=cnt[ver[i]];
}

int n,m;
char a[M],b[M];

int main()
{
//	freopen("1.in","r",stdin);
	int i;
	
	scanf("%d",&n);
	for(i=1;i<=n;i++) {
		scanf("%s",a+1);
		insert(a,i);
	}
	ACbuild();
	
	scanf("%s",b+1);
	query(b);
	
	memset(one,-1,sizeof one);
	for(i=1;i<=tot;i++) AddEdge(fail[i],i);
	dp(0);
	
	for(i=1;i<=n;i++) 
		printf("%lld\n",cnt[match[i]]);
	return 0;
}

