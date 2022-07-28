#include<set>
#include<map>
#include<queue>
#include<stack>
#include<ctime>
#include<cmath>
#include<bitset>
#include<vector>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>

using namespace std;
typedef long long LL;
typedef unsigned long long ULL;

const int N=2.2e6+5;

int p[N];
char a[N],c[N];

int manacher()
{
	memset(c,'\0',sizeof c);
	memset(p,0,sizeof p);
	int len=strlen(a),n=1,i,mid,r;
	c[0]='~',c[1]='|';
	for(i=0;i<len;i++) 
		c[++n]=a[i],c[++n]='|';
	
	for(i=1,mid=0,r=0;i<=n;i++) {
		p[i]=min(p[mid*2-i],r-i+1);
		while(c[i-p[i]]==c[i+p[i]]) p[i]++;
		if(i+p[i]-1>r) r=i+p[i]-1,mid=i; 
	}
	int ans=0;
	for(i=1;i<=n;i++)
		ans=max(ans,p[i]-1);
	return ans;
}

int main()
{
//	freopen("1.in","r",stdin);
	int t=0;
	while(scanf("%s",a)==1) {
		if(!strcmp(a,"END")) break;
		printf("Case %d: %d\n",++t,manacher());
	}
	return 0;
}

