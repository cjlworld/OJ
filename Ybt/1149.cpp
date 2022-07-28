#include<cstdio>
#include<cstring>
#include<iostream>
#define LL long long
using namespace std;
const int N=500+5;
char a[N];
int len;
char word[N];
int main()
{
//	freopen("1.in","r",stdin);
	int i,j;
	int x,y,z;
	while(scanf("%s",a+1)==1) {
		x=strlen(a+1);
		if(a[x]=='.') 
			a[x]='\0',x--;
		if(x>len) {
			memset(word,'\0',sizeof word);
			for(i=1;i<=x;i++) 
				word[i]=a[i];
			len=x;
		} 
	}
	for(i=1;i<=len;i++) 
		putchar(word[i]);
	return 0;
}

