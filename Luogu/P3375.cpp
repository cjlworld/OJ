#include<cstdio>
#include<cstring>
#include<iostream>
#define LL long long
using namespace std;
const int N=1e6+5;
void getnext(char *arr,int *nxt)
{
	int i,j=0;
	int len=strlen(arr+1);
	for(i=2;i<=len;i++) {
		while(j>0&&arr[i]!=arr[j+1]) 
			j=nxt[j];
		if(arr[i]==arr[j+1]&&i!=j+1) 
			j++;
		nxt[i]=j;
	}
	return;
}
int nxt[N];
void kmp(char *arr,char *brr)
{
	getnext(brr,nxt);
	int i,j=0;
	int lena=strlen(arr+1);
	int lenb=strlen(brr+1);
	for(i=1;i<=lena;i++) {
		while(j>0&&arr[i]!=brr[j+1]) 
			j=nxt[j];
		if(arr[i]==brr[j+1])
			j++;
		if(j==lenb) 
			printf("%d\n",i-lenb+1);
	}
}
char a[N],b[N];
int main()
{
//	freopen("1.in","r",stdin);
	int i;
	int x;
	scanf("%s %s",a+1,b+1);
	kmp(a,b);
	x=strlen(b+1);
	for(i=1;i<=x;i++) 
		printf("%d ",nxt[i]);
	return 0;
}


