#include<cstdio>
#include<cstring>
#include<iostream>
#define LL long long
using namespace std;
const int N=1e6+5;
const int INF=(-1u)>>1;
int len;
char a[N];
int nxt[N];
void getnext()
{
	int i,j=0;
	for(i=2;i<=len;i++) {
		while(j>0&&a[j+1]!=a[i])
			j=nxt[j];
		if(a[j+1]==a[i])
			nxt[i]=++j;
		else nxt[i]=0;
	}
	return;
}
int main()
{
//	freopen("1.in","r",stdin);
	int i,j;
	int x,y,z;
	scanf("%d %s",&len,a+1);
	getnext();
	x=len-nxt[len];
	cout<<x-nxt[x];
	return 0;
}

