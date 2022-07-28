#include<iostream>
#include<cstdio>
#define LL long long
using namespace std;
const int N=10+2;
const int M=N*N;
const int S=(1<<N)+1;
const int Max_cnt=144+256+256;
LL a[Max_cnt];
LL p[Max_cnt];
LL f[N][M][Max_cnt];
int n,m;
int cnt;
#define lowbit(x) (x&(-x))
LL count(int x)
{
	LL res=0;
	for(;x>0;x-=lowbit(x)) 	
		res++;
	return res;
}
void deal_first()
{
	int i,j;
	cnt=0;
	for(i=0;i<=(1<<n)-1;i++) {
		if((i<<1)&i||(i>>1)&i) 
			continue;
		a[++cnt]=i;
		p[cnt]=count(i);
	}
	for(i=1;i<=cnt;i++) 
		f[1][p[i]][i]++;
	return;
}
LL ans=0;
int main()
{
//	freopen("1.in","r",stdin);
	scanf("%d%d",&n,&m);
	deal_first();
	int i,j,k,u,v,e,o;
	for(i=2;i<=n;i++) { //枚举行 
		for(k=1;k<=cnt;k++) { //现在这一层方案 
			for(j=p[k];j<=m;j++) { //枚举国王数量 
				for(v=1;v<=cnt;v++) { //上一层方案 
					if((a[k]&a[v])||((a[k]<<1)&a[v])||((a[k]>>1)&a[v])) 
						continue;
					f[i][j][k]=f[i][j][k]+f[i-1][j-p[k]][v];
				}
			} 
		}
	}
	ans=0;
	for(i=1;i<=cnt;i++) 
		ans=ans+f[n][m][i];
	printf("%lld",ans);
	return 0;
}

