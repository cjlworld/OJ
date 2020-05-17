#include<cstdio>
#include<cstring>
#include<iostream>
#define LL long long
#define rint register int 
using namespace std;
const int N=20+5;
const int M=1024;
char a[N][M];
int b[N];
int n;
int w[N][N];
inline bool Compare(const char *a,int st,const char *b,int ed)
{
	for(int i=1;i<=ed;i++) 
		if(a[st+i-1]!=b[i]) 
			return false;
	return true; 
}
// if prefix of b is a suf of a
int mp(const char *a,const char *b)
{
	int lena=strlen(a+1);
	int lenb=strlen(b+1);
	for(int i=1;i<=min(lena,lenb)-1;i++) {
		if(Compare(a,lena-i+1,b,i))
			return i;
	}
	return 0;
}
int vis[N];
int ans=0;
void dfs(const int &now,const int &tmp)
{
	ans=max(ans,tmp);
	for(int i=1;i<=n;i++) {
		if(vis[i]==2||w[now][i]==0) 
			continue;
		vis[i]++;
		dfs(i,tmp+b[i]-w[now][i]);
		vis[i]--;
	}
	return;
}
int main()
{
//	freopen("1.in","r",stdin);
	rint i,j;
	char c;
	scanf("%d",&n);
	for(i=1;i<=n;i++) {
		scanf("%s",a[i]+1);
		b[i]=strlen(a[i]+1);
	}	
	cin>>c;
	for(i=1;i<=n;i++) 
		for(j=1;j<=n;j++) 
			w[i][j]=mp(a[i],a[j]);
	for(i=1;i<=n;i++) {
		if(a[i][1]==c) {
			vis[i]++;
			dfs(i,b[i]);
			vis[i]--;
		}
	}
	cout<<ans;
	return 0;
}

