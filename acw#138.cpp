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

const int N=1e6+5;

struct Hashh
{
	ULL h[N],POW[N];
	ULL P;
	void init(char *arr,int len,ULL _P)
	{
		memset(h,0,sizeof h);
		memset(POW,0,sizeof POW);
		P=_P,POW[0]=1;
		for(int i=1;i<=len;i++) {
			h[i]=h[i-1]*P+(arr[i]-'a');
			POW[i]=POW[i-1]*P;
		}		
	}
	ULL query(int x,int y) { return h[y]-h[x-1]*POW[y-x+1]; }
}A,B;

char a[N];
int n;

int main()
{
//	freopen("1.in","r",stdin);
	int l1,r1,l2,r2;
	scanf("%s",a+1);
	int len=strlen(a+1);
	A.init(a,len,133),B.init(a,len,37);
	scanf("%d",&n);
	while(n--) {
		scanf("%d%d%d%d",&l1,&r1,&l2,&r2);
		if(A.query(l1,r1)==A.query(l2,r2)&&B.query(l1,r1)==B.query(l2,r2))
			printf("Yes\n");
		else printf("No\n");
	}
	return 0;
}

