#include<set>
#include<map>
#include<cmath>
#include<ctime>
#include<stack>
#include<queue>
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

const int N=1e6+5;

int n;
char a[N];
int nxt[N];

void Getnxt()
{
	memset(nxt,0,sizeof nxt);
	int i,j=0;
	for(i=2;i<=n;i++) {
		while(a[i]!=a[j+1]&&j) j=nxt[j];
		if(a[i]==a[j+1]) j++;
		nxt[i]=j; 
	}
}


int main()
{
//	freopen("1.in","r",stdin);
	int i;
	int T=0;
	while(scanf("%d",&n),n) {
		scanf("%s",a+1);
		Getnxt();
		printf("Test case #%d\n",++T);
		for(i=1;i<=n;i++) {
			if(i%(i-nxt[i])==0&&i/(i-nxt[i])>1) 
				printf("%d %d\n",i,i/(i-nxt[i]));
		}
		printf("\n");
	}
	return 0;
}

