#include<queue>
#include<cstdio>
#include<cstring>
#include<iostream>
#define LL long long
using namespace std;
const int N=5e5+5;
int ch[N][26];
int cnt[N];
int fail[N];
int pool,root;
inline void clear()
{
	memset(ch,0,sizeof ch);
	memset(cnt,0,sizeof cnt);
	memset(fail,0,sizeof fail);
	pool=0;
	root=0;
	return;;
}
inline int newnode()
{
	pool++;
	memset(ch[pool],0,sizeof ch[pool]);
	cnt[pool]=0;
	fail[pool]=0;
	return pool;
}
inline void insert(const char *a,int len)
{
	int i,now=0;
	for(i=1;i<=len;i++) {
		if(ch[now][a[i]-'a']==0) 
			ch[now][a[i]-'a']=newnode();
		now=ch[now][a[i]-'a'];
	}
	cnt[now]++;
	return;
}
void AC_build()
{
	int i;
	int now;
	std::queue<int> q;
	while(q.size()) 	
		q.pop();
	for(i=0;i<26;i++) {
		if(ch[0][i]) {
			fail[ch[0][i]]=0;
			q.push(ch[0][i]);
		}
	}
	while(q.size()) {
		now=q.front(); q.pop();
		for(i=0;i<26;i++) {
			if(ch[now][i]) {
				fail[ch[now][i]]=ch[fail[now]][i];
				q.push(ch[now][i]);
			}
			else ch[now][i]=ch[fail[now]][i];
		}
	}
	return;
}
void print()
{
	int i,now;
//	queue<int> q;
//	while(q.size()) q.pop();
//	q.push(0);
//	while(q.size()) {
//		now=q.front(); q.pop();
//		cerr<<now<<endl;
//		for(i=0;i<26;i++) 
//			if(ch[now][i]!=0) 
//				q.push(ch[now][i]);
//	}
	for(int i=0;i<=pool;i++)//cerr<<endl<<i<<"--->"
		for(int j=0;j<=25;j++) 
			if(ch[i][j]>0) 
				cerr<<i<<" "<<ch[i][j]<<endl; 
	return;
}
inline int query(const char *a,int len)
{
	int i,v;
	int res=0;
	int now=0;
	for(i=1;i<=len;i++) {
		now=ch[now][a[i]-'a'];
		for(v=now;v!=0;v=fail[v]) 
			res+=cnt[v],cnt[v]=0;
	}
	return res;
}
char a[N*2];
int T,n;
int main()
{
//	freopen("1.in","r",stdin);
//	freopen("1.out","w",stdout);
	int i;
	scanf("%d",&T);
	while(T--) {
		clear();
		scanf("%d",&n);
		for(i=1;i<=n;i++) {
			scanf("%s",a+1);
			insert(a,strlen(a+1));
		}
		AC_build();
		scanf("%s",a+1);
		printf("%d\n",query(a,strlen(a+1)));
	}
	
	return 0;
}

