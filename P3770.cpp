#include<bits/stdc++.h>
#define rint register int
#define ULL unsigned long long
using namespace std;
const int N=10000+5;
const int M=2000+5;
const int P1=131;
const int P2=1313;
const int MOD1=1e9+7;
const int MOD2=1e9+9;
const long long MOD=212370440130137957ll;
int n;
struct data
{
	ULL h1;
	ULL h2;
}a[N];
char ch[M];
inline ULL Hash_A()
{
	ULL res=0;
	for(rint i=0;i<strlen(ch);i++) {
		res=(res*P1+ch[i])%MOD1;
	}
	return res;
}
inline ULL Hash_B()
{
	ULL res=0;
	for(rint i=0;i<strlen(ch);i++) {
		res=(res*P2+ch[i])%MOD2;
	}
	return res;
}
inline bool rule(const data &a,const data &b)
{
	return a.h1<b.h1;
}
int main()
{
//	freopen("1.in","r",stdin);
	scanf("%d",&n);
	int ans=n;
	for(rint i=1;i<=n;i++) {
		scanf("%s",&ch);
		a[i].h1=Hash_A();
		a[i].h2=Hash_B();
	}
	sort(a+1,a+n+1,rule);
	for(rint i=1;i<=n-1;i++) {
		if(a[i].h1==a[i+1].h1&&a[i].h2==a[i+1].h2) ans--;
	}
	printf("%d",ans);
	return 0;
}
