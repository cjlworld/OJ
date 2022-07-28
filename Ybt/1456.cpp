#include<cstdio>
#include<iostream>
#include<cstring>
#define LL long long 
using namespace std;
LL n;
const LL N=500000+5;
const LL Mod=1e9+7;
const LL MOD2=131313;
const LL P=131;
struct node
{
	LL data;
	int next;
};
node a[N];
LL adj[N],one[N];
LL tot=0;
char d[256],ch[256];
LL ha;
inline LL Hash(char c[])
{
	LL res=0;
	int len=strlen(c);
	for(int i=0;i<len;i++) 
		res=(res*P+c[i])%Mod;
	return res;
}
inline void add(LL key)
{
	LL t=(key%MOD2)+1;
	tot++;
	if(one[t]==0) one[t]=tot;
	else a[adj[t]].next=tot;
	adj[t]=tot;
	a[tot].data=key;
	return;
}
inline bool find(LL key)
{
	LL t=(key%MOD2)+1;
	for(int i=one[t];i;i=a[i].next) 
		if(a[i].data==key) return true;
	return false;
}
int main()
{
//	freopen("1.in","r",stdin);
	scanf("%lld",&n);
	int i,j;
	for(i=1;i<=n;i++) {
		scanf("%s",d);
		gets(ch);
		ha=Hash(ch);
		if(d[0]=='a') add(ha);
		else {
			if(find(ha)) puts("yes");
			else puts("no");
		}
	}
	return 0;
}

