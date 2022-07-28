#include<cstdio>
#include<iostream>
#define LL long long
using namespace std;
const int N=256;
int s,t,n;
int a[N];
int tmp[N];
bool flag[N];
int cnt=-1;
void print()
{
	if(cnt==-1) {
		cnt++;
		return;
	}
	cnt++;
	for(int i=1;i<=n;i++) {
		putchar(tmp[i]+'a'-1);
	}
	putchar(10);
	return;
}
void dfs(int step)
{
	if(cnt==5) return;
	for(int i=(!flag[step]) ? a[step] : tmp[step-1]+1;i<=t;i++) {
		if(!flag[step]) flag[step]=true;
		tmp[step]=i;
		if(step==n) 
		{
			print();
			if(cnt==5) return;
		}
		else dfs(step+1);
		tmp[step]=0;
	}
	return;
}
int main()
{
//	freopen("1.in","r",stdin);
	int i,j;
	int x,y,z;
	char c;
	scanf("%d%d%d",&s,&t,&n);
	for(i=1;i<=n;i++) {
		cin>>c;
		a[i]=c-'a'+1;
		tmp[i]=a[i];
	}
	dfs(1);
	return 0;
}
// mustn't use "exit(0)"
// error
