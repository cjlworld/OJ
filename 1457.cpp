#include<cstdio>
#include<cstring>
#include<iostream>
#define LL long long
using namespace std;
const int N=1e6+5;
char a[N];
int nxt[N];
void getnext()
{
	int i,j=0;
	int len=strlen(a+1);
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
//	freopen("1.in","r",stdin);
	int i,j;
	int x,y,z;
	while(a[1]!='.') {
		scanf("%s",a+1);
		if(a[1]=='.') break;
		getnext();
		z=strlen(a+1);
		if(z%(z-nxt[z])==0) 
			printf("%d\n",z/(z-nxt[z]));
		else printf("1\n");
	}
	return 0;
}
