#include<cstdio>
#include<cstring>
#include<iostream>
#define LL long long
using namespace std;
const int N=500000+5;
char a[N];
int nxt[N];
int ans[N];
void getnxt()
{
	int len=strlen(a+1);
	int i,j=0;
	for(i=2;i<=len;i++) {
		while(j>0&&a[i]!=a[j+1]) 
			j=nxt[j];
		if(a[i]==a[j+1]) 
			nxt[i]=++j;
		else nxt[i]=0;
	}
	return;
}
int main()
{
	int x;
	int i;
	while(scanf("%s",a+1)==1) {
		getnxt();
		x=strlen(a+1);
		ans[0]=0;
		for(i=x;i>0;i=nxt[i]) 
			ans[++ans[0]]=i;
		for(i=ans[0];i>=1;i--) 
			printf("%d ",ans[i]);	
		puts("");	
	}
	return 0;
}

