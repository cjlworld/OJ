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

const int N=2e5+5;
const ULL P=131;

int n,m,Q;
char a[N],b[N];
ULL ha[N],hb[N];
ULL POW[N];

void Hash(char a[],ULL h[],int len)
{
	for(int i=1;i<=len;i++) 
		h[i]=h[i-1]*P+a[i];
}
ULL get(ULL h[],int l,int r)
{
	return h[r]-h[l-1]*POW[r-l+1];
}

int cnt[N];

int main()
{
//	freopen("1.in","r",stdin);
	int i,x;
	
	scanf("%d%d%d",&n,&m,&Q);
	scanf("%s%s",a+1,b+1);
	Hash(a,ha,n),Hash(b,hb,m);
	POW[0]=1;
	for(i=1;i<=max(n,m);i++) POW[i]=POW[i-1]*P;
	
	int L,R,mid;
	for(i=1;i<=n;i++) {
		L=0,R=m+1;
		while(L+1<R) {
			mid=(L+R)>>1;
			if(i+mid-1<=n&&get(ha,i,i+mid-1)==get(hb,1,mid)) L=mid;
			else R=mid;
		}
		cnt[L]++;
	}
	
	while(Q--) {
		scanf("%d",&x);
		printf("%d\n",cnt[x]);
	}
	return 0;
}

