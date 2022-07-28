#include<cstdio>
#include<iostream>
#define LL long long
using namespace std;
//有些土地相当的贫瘠，不能用来放牧。
//没有哪两块草地有公共边。
//1≤N,M≤12。
const LL MOD=1e8;
const int N=12+3;
const int S=(1<<N)+5;
//1 表示这块土地足够肥沃，0 则表示这块地上不适合种草。
int n,m;
int mp[N];
int a[N][S]; //第N行上的预处理方案 
LL f[N][S];
void Init() //输入和预处理 
{
	int i,j,k;
	int x,y,z;
	cin>>n>>m;
	for(i=1;i<=n;i++) {
		for(j=1;j<=m;j++) {
			cin>>x;
			x=!x;
			mp[i]=(mp[i]<<1)|x;
		}
		for(k=0;k<=(1<<m)-1;k++) {
			if(k&mp[i]||(k<<1)&k||(k>>1)&k) 
				continue;
			a[i][++a[i][0]]=k;
		}
	}
	for(i=1;i<=a[1][0];i++) 
		f[1][i]=1;
	return;
}
int main()
{
//	freopen("1.in","r",stdin);
	Init();
	int i,j,k,u,v;
	int x,y,z;
	for(i=2;i<=n;i++) {
		for(j=1;j<=a[i][0];j++) {
			u=a[i][j];
			for(k=1;k<=a[i-1][0];k++) {
				v=a[i-1][k];
				if(u&v) continue;
				f[i][j]=(f[i][j]+f[i-1][k])%MOD;
			}
		}
	}
	LL ans=0;
	for(i=1;i<=a[n][0];i++) 
		ans=(ans+f[n][i])%MOD;
	cout<<ans%MOD<<endl;
	return 0;
}

