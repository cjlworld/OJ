#include<iostream>
#include<iomanip>
#include<cmath>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<cstdlib>
using namespace std;
int n,m;// （其中N(<32000)表示总钱数，m(<60)为希望购买物品的个数。）
int par[256];
int we[256],v[256];//we---price,v---importance,c[i]=w[i]*v[i];
int f[200005];
bool used[256];
int k[256];
long long sum=0,head=0;
int fa,s=0,wei=0;
struct data
{
	int c;
	int w;
	int num;
}a[256][20005];
void Init()
{
	cin>>n>>m;
	int i,j;
	int x;
	for(i=1;i<=m;i++) par[i]=i; 
	for(i=1;i<=m;i++) {
		cin>>we[i]>>v[i]>>x;
		we[i]/=10;
		if(x!=0) par[i]=x;
	}
	return;
}
void dfs(int step) 
{
	if(step==head+1) {
		a[sum][0].num++;
		a[sum][a[sum][0].num].c=s;
		a[sum][a[sum][0].num].w=wei;
		return;
	}
	
	wei+=we[k[step]];
	s+=we[k[step]]*v[k[step]];
	dfs(step+1);
	wei-=we[k[step]];
	s-=we[k[step]]*v[k[step]];
	
	dfs(step+1);
}
void pre_deal()
{
	int i,j;
	for(i=1;i<=m;i++) {
		if(!used[par[i]]) {  
			sum++;
			fa=par[i]; used[fa]=true;

			head=0;
			memset(k,0,sizeof(k));
			
			for(j=i;j<=m;j++) 
				if(j!=fa&&par[j]==fa) { head++; k[head]=j; }
			
			s=v[fa]*we[fa]; wei=we[fa];
			dfs(1);
		
		}
	}
	return;
}
void dp()
{
	int i,j,t;
	for(i=1;i<=sum;i++) {
		for(j=n/10;j>=0;j--) {
			for(t=1;t<=a[i][0].num;t++) {
				if(j-a[i][t].w>=0)
					f[j]=max(f[j],f[j-a[i][t].w]+a[i][t].c);
			}
		}
	}
	cout<<f[n/10]*10;
	return;
}
int main()
{
//	freopen("1.in","r",stdin);
	Init();
	pre_deal();
	dp();
//	cout<<endl;
//	for(int i=1;i<=n/10;i++) cout<<f[i]<<" ";
	return 0;
}

