#include<cstdio>
#include<cstring>
#include<iostream>
#define LL long long
#define rint register int
using namespace std;
const int N=256;
int nxt[N];
char s[N]={'\0','s','o','s',};
void getnext(const char *a)
{
	rint i,j=0;
	int len=strlen(a+1);
	for(i=2;i<=len;i++) {
		while(j>0&&a[i]!=a[j+1]) 
			j=nxt[j];
		if(a[i]==a[j+1]) 
			nxt[i]=++j;
	}
	return;
}
int kmp(const char *a,const char *b)
{
	rint i,j=0;
	int res=0;
	int lena=strlen(a+1),lenb=strlen(b+1);
	for(i=1;i<=lena;i++) {
		while(j>0&&a[i]!=b[j+1])
			j=nxt[j];
		if(a[i]==b[j+1]) 
			j++;
		if(j==lenb) 
			res++;
	}
	return res;
}
int n;
struct people
{
	char name[25];
	char a[N];
	int cnt;
}v[N];
int main()
{
//	freopen("1.in","r",stdin);
	rint i;
	getnext(s);
	scanf("%d",&n);
	for(i=1;i<=n;i++) {
		scanf("%s",v[i].name+1);
		scanf("%s",v[i].a+1);
		v[i].cnt=kmp(v[i].a,s);
	}
	int cmax=0;
	for(i=1;i<=n;i++) 
		cmax=max(cmax,v[i].cnt);
	for(i=1;i<=n;i++) {
		if(v[i].cnt<cmax) 
			continue;
		printf("%s ",v[i].name+1);
	}
	printf("\n%d\n",cmax);
	return 0;
}

