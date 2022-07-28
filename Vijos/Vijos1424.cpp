#include<cstdio>
#include<iostream>
#define LL long long
using namespace std;
const int N=100+5;
const int M=10+1;
const int S=(1<<M)+5;
int n,m;
int f[N][S][S];
int p[N];
int a[S];
struct state
{
	int st[100];
	int c[100];
	int num;
};
state s[N];
#define lowbit(x) ((x)&(-(x)))
int count(int x)
{
	int res=0;
	while(x) {
		x-=lowbit(x);
		res++;
	}
	return res;
}
void Init(int h)
{
	s[h].num=0;
	for(int i=0;i<=(1<<m)-1;i++) {
		if((i&p[h])||((i>>1)&i)||((i<<1)&i)||((i>>2)&i)||((i<<2)&i))
			continue;
		s[h].st[++s[h].num]=i;
		s[h].c[s[h].num]=count(i);
	}
	return;
}
int main()
{
	//freopen("1.in","r",stdin);
	scanf("%d%d",&n,&m);
	int i,j,k,e,u,v;
	int x,y,z;
	char c;
	for(i=1;i<=n;i++) {
		for(j=1;j<=m;j++) {
			cin>>c;
			if(c=='P') p[i]=(p[i]<<1);
			else p[i]=(p[i]<<1)|1;
		}
		Init(i);
	}
	for(i=1;i<=s[1].num;i++) {
		f[1][i][1]=s[1].c[i];
	}
	s[0].num=1;
	s[0].st[1]=0;
	int ans=-1;
	for(i=2;i<=n;i++) {
		for(j=1;j<=s[i].num;j++) {
			u=s[i].st[j];
			for(k=1;k<=s[i-1].num;k++) {
				v=s[i-1].st[k];
				if(u&v) continue;
				for(e=1;e<=s[i-2].num;e++) {
					z=s[i-2].st[e];
					if(u&z||v&z) continue;
					f[i][j][k]=max(f[i][j][k],f[i-1][k][e]+s[i].c[j]);
				}
				ans=max(ans,f[i][j][k]);
			}
		}	
	}
	for(i=1;i<=s[n].num;i++) 
		for(j=1;j<=s[i-1].num;j++)
			ans=max(ans,f[n][i][j]);
	cout<<ans;
	return 0;
}

