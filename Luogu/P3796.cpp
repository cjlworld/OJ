#include<queue>
#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>

using namespace std;

const int N=1e6+5;

int ch[N][26],fail[N],f[N];
int match[N];
int tot;

void insert(char a[],int id)
{
	int now=0;
	for(int i=1;a[i];i++) {
		int& son=ch[now][a[i]-'a'];
		if(!son) {
			son=++tot;
			memset(ch[son],0,sizeof ch[son]);
			fail[son]=0; f[son]=0;
		}
		now=son;
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
//		printf("fail[ %d ] = %d\n",x,fail[x]);
		for(i=0;i<26;i++) {
			if(ch[x][i]) {
				fail[ch[x][i]]=ch[fail[x]][i];
				q.push(ch[x][i]);
			}
			else ch[x][i]=ch[fail[x]][i];
			
//			printf("ch[%d][%d] = %d\n",x,i,ch[x][i]);
		}
	}
}

void query(char a[])
{
	int now=0;
	for(int i=1;a[i];i++) {
		now=ch[now][a[i]-'a'];
//		printf("%c in %d\n",a[i],now);
		f[now]++;
	}		
}

int one[N],idx;
int ver[N],Next[N];
inline void AddEdge(int a,int b)
{
	Next[idx]=one[a]; ver[idx]=b; one[a]=idx++;
}

void dp(int x)
{
	for(int i=one[x],y;~i;i=Next[i]) {
		y=ver[i];
		dp(y);
		f[x]+=f[y];
	}
}

int n;
char str[N],b[250][250];

int main()
{
//	freopen("1.in","r",stdin);
	int i;
	
	while(scanf("%d",&n),n) {
		memset(ch[0],0,sizeof ch[0]); fail[0]=0; f[0]=0;
		memset(one,-1,sizeof one);
		memset(match,0,sizeof match);
		tot=idx=0;
		
		for(i=1;i<=n;i++) {
			scanf("%s",b[i]+1);
			insert(b[i],i);
		}
		ACbuild();
		scanf("%s",str+1);
		query(str);
	
		for(i=1;i<=tot;i++) AddEdge(fail[i],i);
		dp(0);
		
		int mx=0; vector<int> ans;
		for(i=1;i<=n;i++) {
			if(f[match[i]]>mx) {
				ans.clear();
				ans.push_back(i);
				mx=f[match[i]];
			}
			else if(f[match[i]]==mx) ans.push_back(i);
		}
		
		printf("%d\n",mx);
		for(i=0;i<(int)ans.size();i++) puts(b[ans[i]]+1);
	}
	return 0;
}

