#include<cstdio>
#include<cstring>
#include<iostream>
#define LL long long
using namespace std;
const int N=256;
char s1[N],s2[N];
int n;
int lc[N],rc[N],v[N],cnt=0;
int head;
int Merge(int l,int r)
{
	if(l>r) return 0;
	head--;
	int i,j;
	int tmp=0;
	for(i=l;i<=r;i++) 
		if(s1[i]==s2[head]) {
			tmp=i;
			break;
		}
	cnt++;
	int res=cnt;
	v[res]=tmp;
	rc[res]=Merge(tmp+1,r);
	lc[res]=Merge(l,tmp-1);
	return res;
}
void dfs(int now)
{
	if(now==0) return;
	cout<<s1[v[now]];
	dfs(lc[now]);
	dfs(rc[now]);
	return;
}
int main()
{
//	freopen("1.in","r",stdin);
	int i,j;
	int x,y,z;
	scanf("%s",s1+1);
	scanf("%s",s2+1);
	n=strlen(s1+1);
	head=n+1;
	dfs(Merge(1,n));
	return 0;
}

