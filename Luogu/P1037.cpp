#include<cstdio>
#include<iostream>
#include<cstring>
#include<vector>
#define LL unsigned long long
using namespace std;
const int N=256;
int k;
char c[N];
int a[N];
int cnt[N];
int len;
int f[N];
inline int lowbit(int x)
{
	return x&(-x);
}
LL count(int x)
{
	LL res=0;
	while(x) {
		res++;
		x-=lowbit(x);
	}
	return res;
}
void Mul(LL x)
{
	int tmp=0;
	for(int i=1;i<=cnt[0]+10;i++) {
		cnt[i]=cnt[i]*x+tmp;
		tmp=cnt[i]/10;
		cnt[i]=cnt[i]%10;
	}
	cnt[0]=cnt[0]+10;
	while(cnt[cnt[0]]==0) cnt[0]--;
	return;
}
int main()
{
//	freopen("1.in","r",stdin);
	int i,j;
	int x,y,z;
	scanf("%s",c+1);
	len=strlen(c+1);
	for(i=1;i<=len;i++) 
		a[i]=c[len-i+1]-'0';
	scanf("%d",&k);
	for(i=0;i<=9;i++) 
		f[i]=f[i]|(1<<i);
	for(i=1;i<=k;i++) {
		scanf("%d%d",&x,&y);
		if(x==y) continue;
		f[x]=f[x]|(1<<y);
	}
	for(int tt=1;tt<=100;tt++) 
		for(i=0;i<=9;i++) {
			for(j=0;j<=9;j++) {
				if(i==j) continue;
				if((f[i]>>j)&1) 
					f[i]=f[i]|f[j];
			}
		}
	cnt[1]=1;
	cnt[0]=1;
	for(i=1;i<=len;i++) {
		if((f[a[i]]&1)&&i==len) Mul(count(f[a[i]])-1ll);
		else Mul(count(f[a[i]]));
	}
	for(i=cnt[0];i>=1;i--)
		cout<<cnt[i];
	return 0;
}

