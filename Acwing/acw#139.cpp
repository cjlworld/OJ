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

// ¹þÏ£+¶þ·Ö 
const int N=1e6+5;
const ULL P=133;

ULL h1[N],h2[N],Pow[N];
char a[N];
int T,n;

ULL get1(ULL l,ULL r) { return h1[r]-h1[l-1]*Pow[r-l+1]; }
ULL get2(ULL l,ULL r) { return h2[l]-h2[r+1]*Pow[r-l+1]; }

int main()
{
//	freopen("1.in","r",stdin);
	int i;
	int L,R,mid;
	Pow[0]=1;
	for(i=1;i<=N-1;i++) 
		Pow[i]=Pow[i-1]*P;
		
	while(scanf("%s",a+1)==1) {
		if(a[1]=='E') break;
		T++;
		n=strlen(a+1);
		h1[0]=h2[n+1]=0;
		for(i=1;i<=n;i++) h1[i]=h1[i-1]*P+a[i];
		for(i=n;i>=1;i--) h2[i]=h2[i+1]*P+a[i];
		
		int ans=0;
		
		for(i=1;i<=n;i++) {
			L=0,R=min(i,n-i)+1; // [L,R)
			while(L+1<R) {
				mid=(L+R)>>1;
				if(get1(i-mid,i)==get2(i,i+mid)) L=mid;
				else R=mid;
			}
			ans=max(ans,2*L+1);
		}
		for(i=1;i<=n-1;i++) {
			L=-1,R=min(i,n-(i+1))+3;
			while(L+1<R) {
				mid=(L+R)>>1;
				if(i-mid>=1&&i+mid+1<=n&&get1(i-mid,i)==get2(i+1,i+mid+1)) L=mid;
				else R=mid;
			}
			ans=max(ans,2*(L+1));
		}
		printf("Case %d: %d\n",T,ans);
	}
	return 0;
}

