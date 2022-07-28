#include<cstdio>
#include<cstring>
#include<iostream>
#define LL long long
using namespace std;
const int N=1e6+5;
const LL P=31;
const LL MOD=998244353ll;
int T;
char a[N],b[N];
LL h[N];
LL POW[N];
inline LL Mod(LL x)
{
	x=x%MOD;
	if(x<0) 
		x+=MOD;
	return x;
}
int main()
{
//	freopen("1.in","r",stdin);
	int i,j;
	int x,y,z;
	scanf("%d",&T);
	LL sum=0;
	int ans=0;
	int lena,lenb;
	POW[0]=1;
	for(i=1;i<=N-2;i++)
		POW[i]=POW[i-1]*P%MOD;
	while(T--) {
		scanf("%s%s",a+1,b+1);
		sum=0ll;
		ans=0;
		lena=strlen(a+1);
		lenb=strlen(b+1);
		for(i=1;i<=lenb;i++) 
			h[i]=(h[i-1]*P+b[i])%MOD;
		for(i=1;i<=lena;i++) 
			sum=(sum*P+a[i])%MOD;
		for(i=lena;i<=lenb;i++) 
			if(Mod(h[i]-h[i-lena]*POW[lena])==sum) 
		ans++;
		printf("%d\n",ans);
	}
	return 0;
}

