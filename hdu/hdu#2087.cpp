#include<cstdio>
#include<cstring>
#include<iostream>
#define LL long long
using namespace std;
const int N=1024;
int nxt[N];
//nxt[i] stands for the longest prefix \in b[1...j]
char a[N],b[N];
void getnext()
{
	int i,j=0;
	int len=strlen(b+1);
	for(i=2;i<=len;i++) {
		while(j>0&&b[i]!=b[j+1]) 
			j=nxt[j];
		if(b[i]==b[j+1]) 
			nxt[i]=++j;
	}
	return;
}
int kmp(const char *a,const char *b)
{
	int i,j=0;
	int res=0;
	int lena=strlen(a+1);
	int lenb=strlen(b+1);
	for(i=1;i<=lena;i++) {
		while(j>0&&a[i]!=b[j+1]) 
			j=nxt[j];
		if(a[i]==b[j+1]) 
			j++;
		if(j==lenb) {
			res++;
			j=0; // again from the begin
		}
	}
	return res;
}
int main()
{
//	freopen("1.in","r",stdin);
	while(scanf("%s%s",a+1,b+1)==2) {
		getnext();
		printf("%d\n",kmp(a,b));
	}
	return 0;
}

